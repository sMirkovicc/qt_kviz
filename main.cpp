#include "dbmanager.h"
#include "rootwidget.h"

#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.database/kviz.db";
    DbManager db(dbPath);

    RootWidget root;
    root.show();
    root.init();

    return a.exec();
}
