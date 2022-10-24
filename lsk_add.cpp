#include "lsk_add.h"
#include "ui_lsk_add.h"
#include "lsk_main.h"
#include "ATSysDatabaseControl.h"

#include <QFileDialog>
#include "QMessageBox"




lsk_add::lsk_add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lsk_add)
{
    ui->setupUi(this);

}

lsk_add::~lsk_add()
{
    delete ui;
}







//返回操作
void lsk_add::on_pushButton_5_clicked()
{
    lsk_main *lmain =new lsk_main();
    lmain->show();
    this->hide();
}
//选择数据库
void lsk_add::on_pushButton_clicked()
{
    QString dbPath = QFileDialog::getSaveFileName(
                    this,"choose file",
                    ui->lineEdit_db->text(),
                    "database(*.db *.db3)",
                    NULL,
                    QFileDialog::DontConfirmOverwrite);

        if(dbPath.isEmpty())
        {
            return;
        }
        if(ATSysDatabaseControl::setDatabase(dbPath))
        {
                ui->lineEdit_db->setText(dbPath);
        }
}

//从数据库中加载考勤信息
void lsk_add::load()
{
    QList<employee_info> list = ATSysDatabaseControl::load();
    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
    for(int i = 0; i<list.count(); i++)
    {
        const employee_info &info = list.at(i);
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,
                                 new QTableWidgetItem(QString::number(info.card)));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(info.name));
        ui->tableWidget->setItem(i,2,
                                 new QTableWidgetItem(info.sex));
        ui->tableWidget->setItem(i,3,
                                 new QTableWidgetItem(info.state));
    }
}

//刷新
void lsk_add::on_pushButton_2_clicked()
{
    QList<employee_info> list= ATSysDatabaseControl::load();
    while(ui->tableWidget->rowCount() > 0)
    ui->tableWidget->removeRow(0);
    for(int i=0; i<list.count();i++)
    {
        const employee_info &info =list.at(i);
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,
                                 new QTableWidgetItem(QString::number(info.card)));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(info.name));
        ui->tableWidget->setItem(i,2,
                                 new QTableWidgetItem(info.sex));
        ui->tableWidget->setItem(i,3,
                                 new QTableWidgetItem(info.state));
    }
}
//这是添加用户的操作登记操作
void lsk_add::on_pushButton_4_clicked()
{
    QString card =ui->lineEdit_card->text();
    QString name =ui->lineEdit_name->text();
    if(card.isEmpty() || name.isEmpty())
    {
       QMessageBox::warning(this,"警告","卡号或姓名不能为空");
       return;
    }
    employee_info list= ATSysDatabaseControl::load(card.toLongLong());
    //如果数据表中卡号已经存在，则无法注册
    if(list.card > 0)//如果卡号存在，这里可以进一步的改进
    {
        QMessageBox::warning(this,"警告","该卡号已登记");
        return;
    }
    //添加用户信息的时候，状态默认为：正常
    ATSysDatabaseControl::add(card.toLongLong(),
                                  name,
                                  ui->comboBox->currentText(),
                                  "正常");
    load();
    ui->lineEdit_card->clear();
    ui->lineEdit_name->clear();
    ui->comboBox->setCurrentIndex(0);
    QMessageBox::information(this,"提示","登记完成");

}

