#include "izbor.h"
#include "ui_izbor.h"
#include "igra.h"
#include <QPixmap>

Izbor::Izbor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Izbor)
{
    ui->setupUi(this);

    QObject::connect(this, &Izbor::ucitajKviz, this, &Izbor::ucitavanjeKviza);
    QObject::connect(this, &Izbor::igraj, this, &Izbor::igranje);
    QObject::connect(this, &Izbor::zavrsi, this, &Izbor::ispis);

    QPixmap slika2("://database/slika2.jpg");
    w = ui->label_slika2->width();
    h = ui->label_slika2->height();
    ui->label_slika2->setPixmap(slika2.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->comboBox_odgovori->setPlaceholderText("--Vas odgovor--");
    ui->comboBox_odgovori->setCurrentIndex(-1);
}

Izbor::~Izbor()
{
    delete ui;
}

void Izbor::ucitajNaziviID(QString imeKviza, int ID)
{
    kviz.setNazivKviza(imeKviza);
    kviz.setIDKviza(ID);
    ui->label_nazivKviza->setText(kviz.getNazivKviza());
    emit Izbor::ucitajKviz();
}

void Izbor::ucitajIme(QString ime)
{
    imeIgraca = ime;
}

void Izbor::ucitavanjeKviza()
{
    QSqlQuery query3;
    query3.prepare("SELECT * FROM pitanje WHERE IDKviza = (:IDKviza)");
    query3.bindValue(":IDKviza", kviz.getIDKviza());
    query3.exec();

    while (query3.next())
    {
        odgovori[0] = query3.value(3).toString();
        odgovori[1] = query3.value(4).toString();
        odgovori[2] = query3.value(5).toString();
        odgovori[3] = query3.value(6).toString();
        Pitanje p(query3.value(0).toInt(), query3.value(1).toInt(), query3.value(2).toString(), odgovori, query3.value(7).toInt());
        KolekcijaPitanja.emplace_back(p);
    }

    kviz.setKolekcijaPitanja(KolekcijaPitanja);

    emit Izbor::igraj();
}

void Izbor::igranje()
{
    if(i == 0)
    {
        ui->pushButton_prethodno->setVisible(false);
    }
    else
    {
        ui->pushButton_prethodno->setVisible(true);
    }
    if(i == 6)
    {
        ui->pushButton_naredno->setVisible(false);
        ui->pushButton_zavrsi->setVisible(true);
    }
    else
    {
        ui->pushButton_naredno->setVisible(true);
        ui->pushButton_zavrsi->setVisible(false);
    }

    ui->comboBox_odgovori->clear();
    ui->label_brPitanja->setText("Pitanje " + QString::number(i + 1) + ":");
    ui->label_Pitanje->setText(kviz.getKolekcijaPitanja()[i].getPitanje());
    for (int j = 0; j < 4; j++)
    {
        ui->comboBox_odgovori->addItem(kviz.getKolekcijaPitanja()[i].getOdgovor(j));
    }
    ui->comboBox_odgovori->setCurrentIndex(odg[i] - 1);
}

void Izbor::ispis()
{
    for(int k = 0; k < 7; k++)
    {
        if(odg[k] == kviz.getKolekcijaPitanja()[k].getTacanOdgovor())
        {
            tacni_odg++;
        }
    }

    ui->label_Pitanje->setText("Takmicar " + imeIgraca + " je pogodio " + QString::number(tacni_odg) + "/"
                               + QString::number(kviz.getKolekcijaPitanja().size()) + " pitanja.");
    ui->label_brPitanja->setVisible(false);
    ui->comboBox_odgovori->setVisible(false);
    ui->pushButton_naredno->setVisible(false);
    ui->pushButton_prethodno->setVisible(false);
    ui->pushButton_zavrsi->setVisible(false);
    QPixmap slika3("://database/Purple-Confetti");
    w = ui->label_konfete->width();
    h = ui->label_konfete->height();
    ui->label_konfete->setPixmap(slika3.scaled(w, h, Qt::IgnoreAspectRatio));
}

void Izbor::on_pushButton_naredno_clicked()
{
    odg[i] = ui->comboBox_odgovori->currentIndex() + 1;

    i++;

    emit Izbor::igraj();
}


void Izbor::on_pushButton_prethodno_clicked()
{
    odg[i] = ui->comboBox_odgovori->currentIndex() + 1;

    i--;

    emit Izbor::igraj();
}

void Izbor::on_pushButton_zavrsi_clicked()
{
    odg[i] = ui->comboBox_odgovori->currentIndex() + 1;

    emit Izbor::zavrsi();
}

