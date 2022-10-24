#include "test.h"
#include "ui_test.h"
#include "ATSysDatabaseControl.h"

#include <QFileDialog>
#include "QMessageBox"


test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui;
}
//选择操作
void test::on_pushButton_clicked()
{
    QString dbPath = QFileDialog::getSaveFileName(
                    this,"choose file",
                    ui->lineEdit->text(),
                    "database(*.db *.db3)",
                    NULL,
                    QFileDialog::DontConfirmOverwrite);


            return;
        if(ATSysDatabaseControl::setDatabase(dbPath))
        {
                ui->lineEdit->setText(dbPath);
        }
}
//刷新操作

void test::on_pushButton_2_clicked()
{
    manage_info m_info = ATSysDatabaseControl::manageload(ui->lineEdit->text());
    while(ui->tableWidget->rowCount() > 0) ui->tableWidget->removeRow(0);

    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0,0,
                             new QTableWidgetItem(QString::number(m_info.manageid)));
    ui->tableWidget->setItem(0,1,
                             new QTableWidgetItem(m_info.name));
    ui->tableWidget->setItem(0,2,
                             new QTableWidgetItem(m_info.pwd));
    ui->tableWidget->setItem(0,3,
                             new QTableWidgetItem(m_info.sex));

}
//提交操作

void test::on_pushButton_3_clicked()
{
    QString uname;
    QString upwd;
    uname = ui->lineEdit_2->text();
    upwd = ui->lineEdit_3->text();
    manage_info m_info = ATSysDatabaseControl::manageload(uname);
//    qDebug()<<"uname:"<<m_info.name;
//    qDebug()<<"upwd:"<<m_info.pwd;
    if(((m_info.name ==uname)&&(m_info.pwd == upwd)))
    {
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0,
                                 new QTableWidgetItem(QString::number(m_info.manageid)));
        ui->tableWidget->setItem(0,1,
                                 new QTableWidgetItem(m_info.name));
        ui->tableWidget->setItem(0,2,
                                 new QTableWidgetItem(m_info.pwd));
        ui->tableWidget->setItem(0,3,
                                 new QTableWidgetItem(m_info.sex));
    }
    else if(uname == "")
        QMessageBox::warning(this,"tip","name not empty");
    else if(upwd == "")
        QMessageBox::warning(this,"tip","pwd not empty");
    else
        QMessageBox::warning(NULL,"tip","name or pwd error");
}

//删除操作
//void test::on_pushButton_9_clicked()
//{
//    QString card =ui->lineEdit_card->text();
//    employee_info list = atsysdatabasecontrol::load(card.toLongLong());
//    if(list.card <=0)
//    {
//        QMessageBox::warning(this,"warning","card not find");
//        return;
//    }
//    int question;
//    question=QMessageBox::question(this,"提示","确定删除该用户吗？",QMesssageBox::Yes|QMessageBox::No,QMessageBox::No);
//    if(question=QMessageBox::Yes)
//    {
//        atsysdatabasecontrol::remove(card.toLongLong);
//        QMessageBox::about(NULL,"提示","删除成功");
//    }
//    if(question=QMessageBox::No)
//        return;
//    load();
//}

//注销操作
//void test::on_pushButton_8_clicked()
//{
//    QString card =ui->lineEdit_card->text();
//    employee_info list = atsysdatabasecontrol::load(card.toLongLong());
//    if(list.card <=0)
//    {
//        QMessageBox::warning(this,"warning","card not find");
//        return;
//    }
//    int question;
//    question=QMessageBox::question(this,"提示","确定注销该用户吗？",QMesssageBox::Yes|QMessageBox::No,QMessageBox::No);
//    if(question=QMessageBox::Yes)
//    {
//        atsysdatabasecontrol::remove(card.toLongLong);
//        QMessageBox::about(NULL,"提示","注销成功");
//    }
//    if(question=QMessageBox::No)
//        return;
//    load();
//}


//添加用户登记操作
//void test::on_pushButton_4_clicked()
//{
//    QString card =ui->lineEdit_card->text();
//    QString name =ui->lineEdit_name->text();
//    if(card.isEmpty() || name.isEmpty())
//    {
//        QMessageBox::warning(this,"警告","卡号或姓名不能为空");
//        return;
//    }
//    employee_info list= atsysdatabasecontrol::load(card.toLongLong);
//    if(list.card > 0)
//    {
//        QMessageBox::warning(this,"警告","该卡号已登记");
//        return;
//    }
//    //状态：正常
//    atsysdatabasecontrol::add(card.toLongLong(),
//                              name,
//                              ui->comboBox->currentText(),
//                              "正常");
//    load();
//    ui->lineEdit_card->clear();
//    ui->lineEdit_name->clear();
//    ui->comboBox->setCurrentIndex(0);
//    QMessageBox::information(this,"提示","登记完成");
//}

//修改操作
//void test::on_pushButton_7_clicked()
//{
//    QString card =ui->lineEdit_card->text();
//    employee_info list= atsysdatabasecontrol::load(card.toLongLong());
//    if(list.card <= 0)
//    {
//        QMessageBox::warning(this,"warning","card not find");
//        return;
//    }
//    atsysdatabasecontrol::update(card.toLongLong(),
//                                 ui->lineEdit_name->text(),
//                                 ui->comboBox->currentText(),
//                                 ui->comboBox_2->currentText());
//    load();
//    ui->lineEdit_card->clear();
//    ui->lineEdit_name->clear();
//    ui->comboBox->setCurrentIndex(0);
//    ui->comboBox_2->setCurrentIndex(0);
//    QMessageBox::information(this,"tip","success!");
//}
