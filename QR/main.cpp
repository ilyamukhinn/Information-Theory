#include "qr.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QR w;
    w.show();
    return a.exec();
}
