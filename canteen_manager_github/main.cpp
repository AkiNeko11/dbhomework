#include "canteen_manager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    canteen_manager w;
    w.show();
    return a.exec();
}
