#include "lsk_chaxun.h"
#include "ui_lsk_chaxun.h"
#include "ATSysDatabaseControl.h"

#include <QFileDialog>
#include "QMessageBox"

lsk_chaxun::lsk_chaxun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lsk_chaxun)
{
    ui->setupUi(this);
}

lsk_chaxun::~lsk_chaxun()
{
    delete ui;
}
//选择
void lsk_chaxun::on_pushButton_clicked()
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
//刷新
void lsk_chaxun::on_pushButton_2_clicked()
{
    load();
    log_load(ui->lineEdit_db_2->text().toLongLong());
}
//读卡
void lsk_chaxun::on_pushButton_3_clicked()
{

}
//查询
void lsk_chaxun::on_pushButton_4_clicked()
{
    qlonglong decID;
    decID = ui->lineEdit_db_2->text().toLongLong();
    QList<employee_info> list = ATSysDatabaseControl::Vagueload(decID);
    while(ui->tableWidget_2->rowCount() > 0)
        ui->tableWidget_2->removeRow(0);
    for(int i = 0; i<list.count(); i++)
    {
        const employee_info &info = list.at(i);
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i,0,
                                 new QTableWidgetItem(QString::number(info.card)));
        ui->tableWidget_2->setItem(i,1,
                                 new QTableWidgetItem(info.name));
        ui->tableWidget_2->setItem(i,2,
                                 new QTableWidgetItem(info.sex));
        ui->tableWidget_2->setItem(i,3,
                                 new QTableWidgetItem(info.state));
    }
}
//加载员工信息列表的函数
void lsk_chaxun::load()
{
    QList<employee_info> list = ATSysDatabaseControl::load();
    while(ui->tableWidget_2->rowCount() > 0)
        ui->tableWidget_2->removeRow(0);
    for(int i = 0; i<list.count(); i++)
    {
        const employee_info &info = list.at(i);
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i,0,
                                 new QTableWidgetItem(QString::number(info.card)));
        ui->tableWidget_2->setItem(i,1,
                                 new QTableWidgetItem(info.name));
        ui->tableWidget_2->setItem(i,2,
                                 new QTableWidgetItem(info.sex));
        ui->tableWidget_2->setItem(i,3,
                                 new QTableWidgetItem(info.state));
    }
}

//加载日志信息列表的函数
void lsk_chaxun::log_load(qlonglong card)
{
//    qDebug<<"log_load card:"<<QString::number(card);
    QList<log_info> list = ATSysDatabaseControl::loadAllLog(card);
    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
    for(int i = 0; i<list.count(); i++)
    {
        const log_info &info = list.at(i);
        QString dt = info.date.toString("yyyy-MM-dd hh:mm:ss");
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,
                                 new QTableWidgetItem(QString::number(info.card)));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(info.name));
        ui->tableWidget->setItem(i,2,
                                 new QTableWidgetItem(dt));
    }
}
//查看日志
void lsk_chaxun::on_pushButton_5_clicked()
{
    qlonglong decID;
    decID = ui->lineEdit_db_2->text().toLongLong();
    log_load(decID);
}
