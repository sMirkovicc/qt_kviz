#include "izbor.h"
#include "ui_izbor.h"
#include "igra.h"
#include <QPixmap>

Izbor::Izbor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Izbor)
{
    ui->setupUi(this);
    QPixmap slika2("://database/slika2.jpg");
    w = ui->label_slika2->width();
    h = ui->label_slika2->height();
    ui->label_slika2->setPixmap(slika2.scaled(w, h, Qt::IgnoreAspectRatio));
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
    this->ucitajKviz();
}

void Izbor::ucitajKviz()
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

    ui->comboBox_odgovori->clear();
    ui->label_brPitanja->setText("Pitanje 1:");
    ui->label_Pitanje->setText(kviz.getKolekcijaPitanja()[0].getPitanje());
    for (int j = 0; j < 4; j++)
    {
        ui->comboBox_odgovori->addItem(kviz.getKolekcijaPitanja()[0].getOdgovor(j));
    }
    ui->comboBox_odgovori->setPlaceholderText("--Vas odgovor--");
    ui->comboBox_odgovori->setCurrentIndex(-1);
}

void Izbor::ucitajIme(QString ime)
{
    imeIgraca = ime;
}

void Izbor::on_pushButton_potvrdaOdg_clicked()
{
    if(ui->comboBox_odgovori->currentIndex() != -1)
    {
        odg = ui->comboBox_odgovori->currentIndex() + 1;
        qDebug() << odg;
        if(odg == kviz.getKolekcijaPitanja()[i].getTacanOdgovor())
        {
            tacni_odg++;
            qDebug() << "Br tacnih odg: " << tacni_odg;
        }

        i++;

        if(i < 7)
        {
            ui->comboBox_odgovori->clear();
            ui->label_brPitanja->setText("Pitanje " + QString::number(i + 1) + ":");
            ui->label_Pitanje->setText(kviz.getKolekcijaPitanja()[i].getPitanje());
            for (int j = 0; j < 4; j++)
            {
                ui->comboBox_odgovori->addItem(kviz.getKolekcijaPitanja()[i].getOdgovor(j));
            }

            odg = ui->comboBox_odgovori->currentIndex() + 1;
            qDebug() << odg;
            if(odg == kviz.getKolekcijaPitanja()[i].getTacanOdgovor())
            {
                tacni_odg++;
                qDebug() << "tacni_odg";
            }
        }

        if(i == 7)
        {
            ui->label_Pitanje->setText(imeIgraca + " je pogodio " + QString::number(tacni_odg) + "/"
                                       + QString::number(kviz.getKolekcijaPitanja().size()) + " pitanja.");
            ui->label_brPitanja->setVisible(false);
            ui->comboBox_odgovori->setVisible(false);
            ui->pushButton_potvrdaOdg->setVisible(false);
            QPixmap slika3("://database/Purple-Confetti");
            w = ui->label_konfete->width();
            h = ui->label_konfete->height();
            ui->label_konfete->setPixmap(slika3.scaled(w, h, Qt::IgnoreAspectRatio));
        }
    }
}

