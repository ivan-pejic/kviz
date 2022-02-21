#include "kvizlogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KvizLogin w;
    w.show();

    return a.exec();
}
