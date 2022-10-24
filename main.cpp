#include <QtGui/QApplication>
#include "lsk_main.h"
#include "lsk_add.h"
#include "test.h"
#include "login.h"
#include "lsk_card.h"
#include "QTextCodec"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    lsk_card w;
    w.show();

    return a.exec();
}
