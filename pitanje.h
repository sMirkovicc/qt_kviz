#include <QString>

#ifndef PITANJE_H
#define PITANJE_H

class Pitanje
{
private:
    int m_IDPitanja;
    int m_IDKviza;
    QString m_Pitanje;
    QString m_nizOdgovor[4];
    int m_TacanOdgovor;
public:
    Pitanje();

    Pitanje(int IDPitanja, int IDKviza, QString Pitanje, QString nizOdgovor[4], int TacanOdgovor);

    ~Pitanje();

    Pitanje(const Pitanje& original);

    void setIDPitanja(int IDPitanja);
    int getIDPitanja();

    void setIDKviza(int IDKviza);
    int getIDKviza();

    void setPitanje(QString Pitanje);
    QString getPitanje();

    void setOdgovor(int i, QString Odgovor);
    QString getOdgovor(int i);

    bool setTacanOdgovor(int TacanOdgovor);
    int getTacanOdgovor();
};

#endif // PITANJE_H
