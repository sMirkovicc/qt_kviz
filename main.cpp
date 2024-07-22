#include "game.h"
#include "dbmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbManager db("/home/Sara/saraqt/qt_kviz/database/kviz.db");
    Game g;
    g.init();
    g.show();

    return a.exec();
}
