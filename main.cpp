#include "primefindergui.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrimeFinderGui w;
    w.show();
    return a.exec();
}
