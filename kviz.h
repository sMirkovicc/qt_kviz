#include "pitanje.h"
#include <vector>

#ifndef KVIZ_H
#define KVIZ_H

class Kviz
{
private:
    int m_IDKviza;
    QString m_NazivKviza;
    std::vector<Pitanje> m_KolekcijaPitanja;
public:
    Kviz();

    Kviz(int IDKviza, QString NazivKviza, std::vector<Pitanje> KolekcijaPitanja);

    ~Kviz();

    Kviz(const Kviz& original);

    void setIDKviza(int IDKviza);
    int getIDKviza();

    void setNazivKviza(QString NazivKviza);
    QString getNazivKviza();

    void setKolekcijaPitanja(std::vector<Pitanje>& KolekcijaPitanja);
    std::vector<Pitanje> getKolekcijaPitanja();
};

#endif // KVIZ_H
