#include "kviz.h"

Kviz::Kviz() {}

Kviz::Kviz(int IDKviza, QString NazivKviza, std::vector<Pitanje> KolekcijaPitanja)
    : m_IDKviza(IDKviza), m_NazivKviza(NazivKviza), m_KolekcijaPitanja(KolekcijaPitanja)
{

}

Kviz::~Kviz() {}

Kviz::Kviz(const Kviz& original)
    : m_IDKviza(original.m_IDKviza), m_NazivKviza(original.m_NazivKviza), m_KolekcijaPitanja(original.m_KolekcijaPitanja)
{

}

void Kviz::setIDKviza(int IDKviza)
{
    m_IDKviza = IDKviza;
}
int Kviz::getIDKviza()
{
    return m_IDKviza;
}

void Kviz::setNazivKviza(QString NazivKviza)
{
    m_NazivKviza = NazivKviza;
}
QString Kviz::getNazivKviza()
{
    return m_NazivKviza;
}

void Kviz::setKolekcijaPitanja(std::vector<Pitanje>& KolekcijaPitanja)
{
    m_KolekcijaPitanja = KolekcijaPitanja;
}
std::vector<Pitanje> Kviz::getKolekcijaPitanja()
{
    return m_KolekcijaPitanja;
}
