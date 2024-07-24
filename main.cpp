#include "game.h"
#include "dbmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.database/kvizDjura.db";
    DbManager db(dbPath);
    Game g;
    g.init();
    g.show();

    return a.exec();
}
