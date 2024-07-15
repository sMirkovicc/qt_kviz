#include "igra.h"
#include "kviz.h"
#include "pitanje.h"

#ifndef IZBOR_H
#define IZBOR_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Izbor;
}

class Izbor : public QDialog
{
    Q_OBJECT

public:
    explicit Izbor(QWidget *parent = nullptr);
    ~Izbor();
    void ucitajNaziviID(QString imeKviza, int ID);
    void ucitajIme(QString ime);

private slots:
    void on_pushButton_naredno_clicked();

    void on_pushButton_prethodno_clicked();

    void on_pushButton_zavrsi_clicked();

public slots:
    void ucitavanjeKviza();
    void igranje();
    void ispis();

signals:
    void ucitajKviz();
    void igraj();
    void zavrsi();

private:
    Ui::Izbor *ui;
    Kviz kviz;
    QString imeIgraca;
    QString odgovori[4];
    std::vector<Pitanje> KolekcijaPitanja;
    int i = 0;
    int odg[7];
    int tacni_odg = 0;
    int w;
    int h;
};

#endif // IZBOR_H
