#include "ATSysDatabaseControl.h"
#include <QStringList>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include <QCoreApplication>



const QString ATSysDatabaseControl::_dbConnName("_atsystem_db_");
const QString ATSysDatabaseControl::_userTableName("tbl_user_info");
const QString ATSysDatabaseControl::_manageTableName("tbl_manage");
const QString ATSysDatabaseControl::_employeeTableName("tbl_employee");
const QString ATSysDatabaseControl::_logTableName("tbl_log");

QSqlDatabase *ATSysDatabaseControl::_db =NULL;


ATSysDatabaseControl::ATSysDatabaseControl()
{
    if(_db != NULL)
        return;
    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", _dbConnName));
}

ATSysDatabaseControl::~ATSysDatabaseControl()
{
    if(_db == NULL)
    {
        return;
    }
    _db->close();
    delete _db;
    _db = NULL;
    QSqlDatabase::removeDatabase(_dbConnName);
}

bool ATSysDatabaseControl::setDatabase(QString path)
{
    if(_db->isOpen())
    {
        _db->close();
    }
    _db->setDatabaseName(path);
    if(!_db->open())
    {
        return false;
    }

    if(!_db->tables().contains(_userTableName))
    {
        // 如果数据库中没有tbl_user_info表则创建它
        _db->exec(QString("CREATE TABLE [%1] ("
                  "[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "[userid] INTEGER  UNIQUE NOT NULL,"
                  "[username] TEXT  NULL,"
                  "[userpwd] TEXT  NULL"
                  ")").arg(_userTableName)
                  );
    }
    //创建管理员表
    if(!_db->tables().contains(_manageTableName))
    {
        // 如果数据库中没有tbl_manage表则创建它
        _db->exec(QString("CREATE TABLE [%1] ("
                  "[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "[manageid] INTEGER  UNIQUE NOT NULL,"
                  "[name] TEXT  NULL,"
                  "[sex] TEXT  NULL,"
                  "[pwd] TEXT  NOT NULL,"
                  "[permission] TEXT NULL"
                  ")").arg(_manageTableName)
                  );
    }
    //创建员工表
    if(!_db->tables().contains(_employeeTableName))
    {
        // 如果数据库中没有tbl_employee表则创建它
        _db->exec(QString("CREATE TABLE [%1] ("
                  "[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "[card] INTEGER NOT NULL,"
                  "[name] TEXT  NULL,"
                  "[sex] TEXT  NULL,"
                  "[state] TEXT NULL"
                  ")").arg(_employeeTableName)
                  );
    }
    //创建日志表
    if(!_db->tables().contains(_logTableName))
    {
        // 如果数据库中没有tbl_log表则创建它
        _db->exec(QString("CREATE TABLE [%1] ("
                  "[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "[card] INTEGER NOT NULL,"
                  "[name] TEXT  NULL,"
                  "[date] TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL"
                  ")").arg(_logTableName)
                  );
    }
    return _db;
}

//设置新的数据库的路径
QString ATSysDatabaseControl::setNewDatabase()
{
    //获取数据库路径，在项目的debug文件中
// qDebug()<<"db card:"<<QCoreApplication::applicationDirPath() + "/ATSystem.db";
    return QCoreApplication::applicationDirPath() + "/ATSystem.db";
}




user_info ATSysDatabaseControl::userload(qlonglong userid)
{
    user_info info;
    info.id = 0;
    info.userid = 0;
    QSqlQuery query(
                QString(
                    "SELECT * from %1 WHERE"
                    " userid='%2'"
                    ).arg(_userTableName).arg(userid)
                , *_db);
//    qDebug()<<"query:"<<query.executedQuery();
    if(query.next())
    {
        info.id = query.value(0).toInt();
        info.userid = query.value(1).toLongLong();
        info.username = query.value(2).toString();
        info.userpwd = query.value(3).toString();
    }
    return info;
}

//加载所有管理员的信息，然后村到泛型的ret变量中
QList<manage_info> ATSysDatabaseControl::manageload()
{
    QSqlQuery query(
                QString("SELECT * from %1")
                .arg(_manageTableName)
                , *_db);
    QList<manage_info> ret;
    while(query.next())
    {
        manage_info info;
        info.id = query.value(0).toInt();
        info.manageid = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.pwd = query.value(4).toString();
        info.permission = query.value(5).toString();
        ret.append(info);
    }
    return ret;
}



//添加管理员信息
void ATSysDatabaseControl::manageadd(qlonglong manageid, const QString &name,const QString &sex,const QString &pwd,const QString &permission)
{
    _db->exec(
                QString(
                        "INSERT INTO [%1]"
                        "( manageid,name,sex,pwd,permission)VALUES('%2','%3','%4','%5','%6')")
                .arg(_manageTableName) .arg(manageid) .arg(name) .arg(sex) .arg(pwd) .arg(permission));
}
//删除管理员信息
void ATSysDatabaseControl::manageremove(qlonglong manageid)
{
     _db->exec(QString("DELETE FROM %1 WHERE manageid = %2")
               .arg(_manageTableName).arg(manageid));
}

//根据姓名查询
manage_info ATSysDatabaseControl::manageload(QString managename)
{
    manage_info info;
    info.id = 0;
    info.manageid = 0;
    QSqlQuery query(
                QString(
                        "SELECT * from %1 WHERE"
                        "name ='%2'"
                        ).arg(_manageTableName).arg(managename)
                ,*_db);
    qDebug()<<"query:"<<query.executedQuery();
    if(query.next())
    {
        info.id = query.value(0).toInt();
        info.manageid = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.pwd = query.value(4).toString();
        info.permission = query.value(5).toString();
    }
    return info;
}

//根据卡号查询
manage_info ATSysDatabaseControl::manageload(qlonglong manid)
{
    manage_info info;
    info.id = 0;
    info.manageid = 0;
    QSqlQuery query(
                QString(
                        "SELECT * from %1 WHERE"
                        "manageid ='%2'"
                        ).arg(_manageTableName).arg(manid)
                ,*_db);
//    qDebug()<<"query:"<<query.executedQuery();
    if(query.next())
    {
        info.id = query.value(0).toInt();
        info.manageid = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.pwd = query.value(4).toString();
        info.permission = query.value(5).toString();
    }
    return info;
}

//查询所有员工的信息，然后存到泛型的ret变量中
QList<employee_info> ATSysDatabaseControl::load()
{
    QSqlQuery query(
                QString("SELECT * from %1")
                .arg(_employeeTableName)
                , *_db);
    QList<employee_info> ret;
    while(query.next())
    {
        employee_info info;
        info.id = query.value(0).toInt();
        info.card = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.state = query.value(4).toString();
        ret.append(info);
    }
    return ret;
}


//查询员工表
employee_info ATSysDatabaseControl::load(qlonglong card)
{
    employee_info info;
    info.id = 0;
    info.card = 0;
    QSqlQuery query(
                QString(
                        "SELECT id,card,name,sex,state from %1 WHERE"
                        " card =%2"
                        ).arg(_employeeTableName).arg(card)
                ,*_db);
//    qDebug()<<"query:"<<query.executedQuery();
    if(query.next())
    {
        info.id = query.value(0).toInt();
        info.card = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.state = query.value(4).toString();
    }
    return info;
}

//模糊查询员工表
QList<employee_info> ATSysDatabaseControl::Vagueload(qlonglong ID)
{

//    info.id = 0;
//    info.manageid = 0;
    QSqlQuery query(
                QString(
                        "SELECT id,card,name,sex,state from %1 WHERE"
                        " card like '%2%'"
                        ).arg(_employeeTableName).arg(ID)
                ,*_db);
    QList<employee_info> ret;
    while(query.next())
    {
        employee_info info;
        info.id = query.value(0).toInt();
        info.card = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        info.sex = query.value(3).toString();
        info.state = query.value(4).toString();
        ret.append(info);
    }
    return ret;
}

//添加员工信息
void ATSysDatabaseControl::add(qlonglong card,const QString &name,const QString &sex,const QString &state)
{
    _db->exec(
                QString(
                        "INSERT OR REPLACE INTO [%1]"
                        "(card,name,sex,state)VALUES (%2,'%3','%4','%5')")
                .arg(_employeeTableName).arg(card).arg(name).arg(sex).arg(state));
}

//更新员工信息
void ATSysDatabaseControl::update(qlonglong card,const QString &name,const QString &sex,const QString &state)

{
    /*qDebug()<<"当前的SQL语句为："<<*/_db->exec(
            QString(
                    "UPDATE [%1]"
                    " SET name='%2',sex='%3',state='%4' where card=%5")
            .arg(_employeeTableName) .arg(name).arg(sex) .arg(state) .arg(card)).executedQuery();
}


//注销员工信息表，状态变为已注销
void ATSysDatabaseControl::cancel(qlonglong card)
{
    _db->exec(QString("UPDATE %1 SET state = '%2' WHERE card = %3")
              .arg(_employeeTableName).arg("已注销").arg(card));
}
//删除员工信息表
void ATSysDatabaseControl::remove(qlonglong card)
{
    _db->exec(QString("DELETE FORM %1 WHERE card = %2")
              .arg(_employeeTableName).arg(card));
}
//加载日志信息列表
QList<log_info> ATSysDatabaseControl::loadAllLog(qlonglong card)
{
    QSqlQuery query(
                QString("SELECT * FROM %1 WHERE card=%2")
                .arg(_logTableName).arg(card)
                ,*_db);
    QList<log_info> ret;
    while(query.next())
    {
        log_info info;
        info.id = query.value(0).toInt();
        info.card = query.value(1).toLongLong();
        info.name = query.value(2).toString();
        QDateTime dt =query.value(3).toDateTime();
        info.date=dt;
        ret.append(info);
    }
    return ret;

}
//添加日志
void ATSysDatabaseControl::checkIn(qlonglong card,const QString &name)
{
    _db->exec(QString(
                "INSERT INTO [%1]"
                " (card,name) VALUES (%2,'%3')")
              .arg(_logTableName)
              .arg(card)
              .arg(name));
}

static ATSysDatabaseControl __dummy_instance__;
