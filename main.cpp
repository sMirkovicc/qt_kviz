#include "dbmanager.h"
#include "rootwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.qt_kviz/kviz.db";
    DbManager db(dbPath);

    RootWidget root;
    root.show();
    root.init();

    return a.exec();
}
