#include <QString>
#include <QSqlDatabase>
#include <QDialog>

#ifndef DBMANAGER_H
#define DBMANAGER_H

class DbManager
{
public:
    DbManager(const QString& path);

    ~DbManager();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
