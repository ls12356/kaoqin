#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
    class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private:
    Ui::login *ui;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // LOGIN_H
