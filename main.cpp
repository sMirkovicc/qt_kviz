#include "igra.h"
#include "izbor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Igra w;
    w.show();

    return a.exec();
}
