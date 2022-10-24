#ifndef LSK_CARD_H
#define LSK_CARD_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class lsk_card;
}

class lsk_card : public QWidget
{
    Q_OBJECT

public:
    explicit lsk_card(QWidget *parent = 0);
    ~lsk_card();

private:
    Ui::lsk_card *ui;
    QTimer *timer;
    QTimer *tipTimer;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onTimeout();
    void hideTip();
    void showTip(const QString &tip,bool valid);
};

#endif // LSK_CARD_H
