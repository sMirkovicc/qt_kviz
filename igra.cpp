#include "igra.h"
#include "ui_igra.h"
#include "izbor.h"
#include <QPixmap>

Igra::Igra(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Igra)
{
    ui->setupUi(this);

    QPixmap slika("://database/slika.jpg");
    int w = ui->label_slika->width();
    int h = ui->label_slika->height();
    ui->label_slika->setPixmap(slika.scaled(w, h, Qt::IgnoreAspectRatio));

    ui->pushButton_izborKviza->setVisible(false);
    ui->comboBox_izborKviza->setVisible(false);
    ui->label_2->setVisible(false);
}

Igra::~Igra()
{
    delete ui;
}

void Igra::on_pushButton_UnesiIme_clicked()
{

    if(ui->unosImena->text() != "")
    {
        ime = ui->unosImena->text();
        qDebug() << ime;
        ui->pushButton_UnesiIme->setDisabled(true);

        ui->pushButton_izborKviza->setVisible(true);
        ui->comboBox_izborKviza->setVisible(true);
        ui->label_2->setVisible(true);

        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("/home/Sara/saraqt/qt_kviz/database/kviz.db");

        if (!m_db.open())
        {
            qDebug() << "Error: connection with database failed";
        }
        else
        {
            qDebug() << "Database: connection ok";
        }

        QSqlQuery query("SELECT * FROM kviz");
        int idName = query.record().indexOf("Naziv");
        while (query.next())
        {
            ui->comboBox_izborKviza->addItem(query.value(idName).toString());
        }
        ui->comboBox_izborKviza->setPlaceholderText("--Izaberite zeljeni kviz--");
        ui->comboBox_izborKviza->setCurrentIndex(-1);
    }
}

void Igra::on_pushButton_izborKviza_clicked()
{
    if(ui->comboBox_izborKviza->currentIndex() != -1)
    {
        imeKviza = ui->comboBox_izborKviza->currentText();
        qDebug() << imeKviza;

        QSqlQuery query1;
        query1.prepare("SELECT IDKviza FROM kviz WHERE Naziv = '" + imeKviza + "'");
        query1.bindValue(":name", imeKviza);

        if (query1.exec())
        {
            if (query1.next())
            {
                idKviza = query1.value(0).toInt();
                qDebug() << idKviza;
            }
        }

        Izbor izbor;
        izbor.ucitajNaziviID(imeKviza, idKviza);
        izbor.ucitajIme(ime);
        izbor.setModal(true);
        izbor.exec();
    }
}

