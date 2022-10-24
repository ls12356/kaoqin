#include "lsk_card.h"
#include "ui_lsk_card.h"
#include "lsk_main.h"
#include "login.h"
#include "ATSysDatabaseControl.h"
#include <QMessageBox>
#include <QDebug>


lsk_card::lsk_card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lsk_card)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->setSingleShot(false);
    timer->start(1000);

    tipTimer=new QTimer(this);
    connect(tipTimer,SIGNAL(timeout()),this,SLOT(hideTip()));
    tipTimer->setSingleShot(true);
    tipTimer->setInterval(3000);
    onTimeout();

    hideTip();
}

lsk_card::~lsk_card()
{
    delete ui;
}
//时间组
void lsk_card::onTimeout()
{
    QDateTime dt = QDateTime::currentDateTime();
//    qlonglong a=dt.toTime_t();
//    qDebug()<<a;
    QString str =dt.toString("yyyy-MM-dd hh:mm:ss");
//    qDebug()<<str;
    ui->lb_date->setText(str);
//    ui->lb_date->setText(dt.toString("yyyy-MM-dd"));
//    if(ui->lb_hour->number()!=dt.time.hour())
//       ui->lb_hour->setText(dt.time().hour().toString);
//    if(ui->lb_min->number()!=dt.time.hour())
//       ui->lb_min->setText(dt.time().minute().toString);
//    ui->lcdNumber->display(dt.time().second());
}
//显示考勤的图形图标
void lsk_card::showTip(const QString &tip,bool valid)
{
    ui->label_tip->setText(tip);
    ui->label_tip->show();
    if(valid)
    {
        ui->lb_red->setStyleSheet("");
        ui->lb_green->setStyleSheet(

                " background-color: rgb(255, 85, 255);\n"
                "border-radius:30px;"
                );
    }
    else
    {
        ui->lb_red->setStyleSheet(
                "background-color: rgb(255, 0, 127);\n"
                "border-radius:30px;"
                );
        ui->lb_green->setStyleSheet("");

    }
}

//隐藏考勤的图形图标
void lsk_card::hideTip()
{
    ui->label_tip->hide();
    ui->lb_red->setStyleSheet("");
    ui->lb_green->setStyleSheet("");
}


//打卡
void lsk_card::on_pushButton_2_clicked()
{
    if(ATSysDatabaseControl::setDatabase(ATSysDatabaseControl::setNewDatabase()))
    {
        qlonglong decID = ui->lineEdit->text().toLongLong();
        employee_info info = ATSysDatabaseControl::load(decID);
        if(info.id > 0 && info.state =="正常")
        {
            showTip("欢迎你"+info.name,true);
            ATSysDatabaseControl::checkIn(decID,info.name);
        }
        else if(info.id > 0 && info.state == "已注销")
        {
             showTip("此卡已注销"+info.name,true);
        }
        else
             showTip("此卡无效",false);
        tipTimer->start();
    }
    else
        QMessageBox::information(this,"提示","数据库初始化失败！");
}
//返回
void lsk_card::on_pushButton_clicked()
{
    login *lsk = new login();
    lsk->show();
    this->hide();
}
