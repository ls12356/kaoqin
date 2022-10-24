#include "login.h"
#include "ui_login.h"
#include "lsk_main.h"
#include "ATSysDatabaseControl.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
//登录
void login::on_pushButton_clicked()
{

    qlonglong userid = ui->le_username->text().toLongLong();
    ATSysDatabaseControl::setDatabase(ATSysDatabaseControl::setNewDatabase());
    user_info info=ATSysDatabaseControl::userload(userid);
 //??
    if(ui->le_pwd->text()==""||ui->le_username->text()==""){

        QMessageBox::warning(this,tr(""),tr("ûΪ"),QMessageBox::Yes);
        return;
    }
    if(ui->le_pwd->text()==info.userpwd)
    {
        lsk_main *lmain =new lsk_main();
        lmain->show();
        this->hide();
    }
    //?
    else{
        ui->label_3->setText(tr("û"));
    }
}
//重置
void login::on_pushButton_2_clicked()
{
    ui->le_username->setText("");
    ui->le_pwd->setText("");
}
