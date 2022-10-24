#ifndef LSK_MAIN_H
#define LSK_MAIN_H

#include <QWidget>

namespace Ui {
    class lsk_main;
}

class lsk_main : public QWidget
{
    Q_OBJECT

public:
    explicit lsk_main(QWidget *parent = 0);
    ~lsk_main();
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);


private:
    Ui::lsk_main *ui;

private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_clicked();
};

#endif // LSK_MAIN_H
