#ifndef LSK_ADD_H
#define LSK_ADD_H

#include <QWidget>

namespace Ui {
    class lsk_add;
}

class lsk_add : public QWidget
{
    Q_OBJECT
public:
    explicit lsk_add(QWidget *parent = 0);
    ~lsk_add();


private:
    Ui::lsk_add *ui;

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void load();
};

#endif // LSK_ADD_H
