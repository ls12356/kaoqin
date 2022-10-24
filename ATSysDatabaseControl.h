#ifndef ATSYSDATABASECONTROL_H
#define ATSYSDATABASECONTROL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDateTime>

//管理员信息表--manage_info
    //id,管理员编号，姓名，性别，密码，权限（0，超级管理员；1，普通用户）
    //id,manageid,name,sex,pwd,permission
    //int,int,QString,QString,QString,QString
//员工信息表----employee_info
    //id,卡号，姓名，性别，状态（0，正常；1，注销）
    //id,card,name,sex,state
    //int,int,QString,QString,QString
//打卡日志表-----log_info
    //id,卡号，姓名，日期
    //id，card,name,date
    //int,int,QString,QDateTime

//用户信息表
struct user_info{
    int id;
    qlonglong userid;
    QString username;
    QString userpwd;
};

//管理员信息表
struct manage_info{
    int id;
    qlonglong  manageid;
    QString name;
    QString sex;
    QString pwd;
    QString permission;
};
//员工信息表
struct employee_info{
    int id;
    qlonglong  card;
    QString name;
    QString sex;
    QString state;//状态：正常，以注销

};
//打卡日志表
struct log_info{
    int id;
    qlonglong  card;
    QString name;
    QDateTime date;//日期
};
class QSqlDatabase;


class ATSysDatabaseControl : public QObject
{
public:
    QString dbPath; //定义一个设置数据库路径的全局变量
    ATSysDatabaseControl();//初始化操作
    ~ATSysDatabaseControl();//释放，结束操作

    /**
     * @brief setDatabase 设置数据库文件路径
     *
     * @param path 数据库文件路径
     * @return bool 设置是否成功
     */
    static bool setDatabase(QString path);//原始的设置数据库的路径

    static QString setNewDatabase();//重新编写的设置数据库的路径，这里写成了固定的路径

    /**
     * @brief load 加载考勤卡信息列表
     *
     * @return QList<employee_info>
     */
     static user_info userload(qlonglong userid);//加载用户信息表
    //管理员
     static QList<manage_info>manageload();//加载管理员信息表
     static void manageadd(qlonglong manageid, const QString &name,const QString &sex,const QString &pwd,const QString &permission);
     static void manageremove(qlonglong manageid) ;//删除信息
     static manage_info manageload(QString managename);
     static manage_info manageload(qlonglong manid);
     // 员工 泛型
     static QList<employee_info> load();
     static employee_info load(qlonglong card);
     static QList<employee_info> Vagueload(qlonglong ID);//模糊查询

     static void add(qlonglong card,const QString &name,const QString &sex,const QString &state);//状态：正常，以注销
     static void update(qlonglong card,const QString &name,const QString &sex,const QString &state);


     static void cancel(qlonglong card);
     static void remove(qlonglong card);

     static QList<log_info> loadCheckInLog();

     static QList<log_info> loadAllLog(qlonglong card);
     static QList<employee_info> loadAllEmploy(qlonglong card);
     static void checkIn(qlonglong card,const QString &name);


private:
    static const QString _dbConnName; /**< TODO */
     static const QString _userTableName; /**< TODO */
    static const QString _manageTableName; /**< TODO */
    static const QString _employeeTableName;
    static const QString _logTableName;
    static QSqlDatabase *_db; /**< TODO */
};

#endif // DATABASECONTROL_H


