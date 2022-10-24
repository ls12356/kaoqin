#include "lsk_main.h"
#include "ui_lsk_main.h"
#include "lsk_add.h"
#include "lsk_chaxun.h"
#define PI 3.1415926
#include<QPainter>
#include<QTimer>
#include<QPixmap>
#include<math.h>
#include<QPainter>

lsk_main::lsk_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lsk_main)
{
    ui->setupUi(this);
    startTimer(1000);//括号中指调用一次所用多少毫秒；每隔相应的时间调用一次函数
}

lsk_main::~lsk_main()
{
    delete ui;
}


int t;
void lsk_main::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        QPixmap map(":/new/prefix1/l.jpeg");
        QRect q(0,0,769,960);
        QRect q2(0,0,width(),height());
        painter.drawPixmap(q2,map,q);

        //基础的表盘结构通过循环结构——利用三角函数标示刻度
        painter.drawEllipse(100,100,320,320);
        double x1,x2,y1,y2;
        for(int j=0;j<60;j++)
        {
            x1=260+160*cos(2*PI/60*j);
            y1=260+160*sin(2*PI/60*j);
            x2=260+155*cos(2*PI/60*j);
            y2=260+155*sin(2*PI/60*j);
            painter.drawLine(x1,y1,x2,y2);

            x1=260+160*cos(2*PI/12*j);
            y1=260+160*sin(2*PI/12*j);
            x2=260+150*cos(2*PI/12*j);
            y2=260+150*sin(2*PI/12*j);
            painter.drawLine(x1,y1,x2,y2);
        }


        //十二个数字，在这一过程中可以对半径以及中心微调使得数字更整齐
        int R=143;
        for(int i=1;i<13;i++)
        {
            painter.drawText(255+R*sin(2*PI/12*i),261-R*cos(2*PI/12*i),QString::number(i));
        }


        //将秒针的终点与timerEvent关联，让秒针随着时间的调用动起来
        int i;
        double x,y;
        for( i=0;i<60;i++)
        {

            x=260+150*cos(2*PI/60*t);
            y=260+150*sin(2*PI/60*t);

        }
        painter.setPen(QPen(Qt::red,5));
        painter.drawLine(260,260,x,y);//秒针
        painter.drawLine(260,260,290,150);//分针
        painter.drawLine(260,260,271,171);//时针
 }

void lsk_main::timerEvent(QTimerEvent* event)
{
      t++;
      repaint();
}




//添加按钮
void lsk_main::on_pushButton_clicked()
{
    lsk_add *ladd = new lsk_add();
    ladd->show();
    this->hide();
}


//查询
void lsk_main::on_pushButton_5_clicked()
{
    lsk_chaxun *lcx = new lsk_chaxun();
    lcx->show();
    this->hide();
}
