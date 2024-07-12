#include "igra.h"
#include "kviz.h"
#include "pitanje.h"

#ifndef IZBOR_H
#define IZBOR_H

#include <QDialog>

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
    void ucitajKviz();
    void ucitajIme(QString ime);

private slots:
    void on_pushButton_potvrdaOdg_clicked();

private:
    Ui::Izbor *ui;
    Kviz kviz;
    QString imeIgraca;
    QString odgovori[4];
    std::vector<Pitanje> KolekcijaPitanja;
    int i = 0;
    int odg;
    int tacni_odg = 0;
    int w;
    int h;
};

#endif // IZBOR_H
