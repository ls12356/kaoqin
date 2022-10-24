#ifndef LSK_CHAXUN_H
#define LSK_CHAXUN_H

#include <QWidget>

namespace Ui {
    class lsk_chaxun;
}

class lsk_chaxun : public QWidget
{
    Q_OBJECT

public:
    explicit lsk_chaxun(QWidget *parent = 0);
    ~lsk_chaxun();

private:
    Ui::lsk_chaxun *ui;


private slots:

    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void log_load(qlonglong card);
    void load();
};

#endif // LSK_CHAXUN_H
