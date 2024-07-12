#include "pitanje.h"

Pitanje::Pitanje() {}

Pitanje::Pitanje(int IDPitanja, int IDKviza, QString Pitanje, QString nizOdgovor[4], int TacanOdgovor)
    : m_IDPitanja(IDPitanja), m_IDKviza(IDKviza), m_Pitanje(Pitanje), m_TacanOdgovor(TacanOdgovor)
{
    for(int i = 0; i < 4; i++)
    {
        m_nizOdgovor[i] = nizOdgovor[i];
    }
}

Pitanje::~Pitanje() {}

Pitanje::Pitanje(const Pitanje& original)
    : m_IDPitanja(original.m_IDPitanja), m_IDKviza(original.m_IDKviza), m_Pitanje(original.m_Pitanje), m_TacanOdgovor(original.m_TacanOdgovor)
{
    for(int i = 0; i < 4; i++)
    {
        m_nizOdgovor[i] = original.m_nizOdgovor[i];
    }
}

void Pitanje::setIDPitanja(int IDPitanja)
{
    m_IDPitanja = IDPitanja;
}
int Pitanje::getIDPitanja()
{
    return m_IDPitanja;
}

void Pitanje::setIDKviza(int IDKviza)
{
    m_IDKviza = IDKviza;
}
int Pitanje::getIDKviza()
{
    return m_IDKviza;
}

void Pitanje::setPitanje(QString Pitanje)
{
    m_Pitanje = Pitanje;
}
QString Pitanje::getPitanje()
{
    return m_Pitanje;
}

void Pitanje::setOdgovor(int i, QString Odgovor)
{
    m_nizOdgovor[i] = Odgovor;
}
QString Pitanje::getOdgovor(int i)
{
    return m_nizOdgovor[i];
}

bool Pitanje::setTacanOdgovor(int TacanOdgovor)
{
    if(TacanOdgovor > 0 && TacanOdgovor < 5)
    {
        m_TacanOdgovor = TacanOdgovor;
        return 1;
    }
    else
    {
        return 0;
    }
}
int Pitanje::getTacanOdgovor()
{
    return m_TacanOdgovor;
}
