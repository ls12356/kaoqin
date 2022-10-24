#ifndef TEST_H
#define TEST_H

#include <QWidget>

namespace Ui {
    class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();

private:
    Ui::test *ui;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // TEST_H
