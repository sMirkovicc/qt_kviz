#include <QtSql>

#ifndef IGRA_H
#define IGRA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Igra;
}
QT_END_NAMESPACE

class Igra : public QWidget
{
    Q_OBJECT

public:
    Igra(QWidget *parent = nullptr);
    ~Igra();

private slots:
    void on_pushButton_UnesiIme_clicked();

    void on_pushButton_izborKviza_clicked();

private:
    Ui::Igra *ui;
    QString ime;
    QSqlDatabase m_db;
    QString imeKviza;
    int idKviza;

};
#endif // IGRA_H
