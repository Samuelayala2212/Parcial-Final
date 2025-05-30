#ifndef REGUETONERO_H
#define REGUETONERO_H

#include <string>
#include <vector>
#include "ataque.h"

class Reguetonero {
protected:
    std::string nombre;
    int vida;
    int vidaMaxima;
    std::vector<Ataque> ataques;

public:
    Reguetonero(std::string nombre, int vida, std::vector<Ataque> ataques);
    
    std::string getNombre() const;
    int getVida() const;
    int getVidaMaxima() const;
    const std::vector<Ataque>& getAtaques() const;
    
    void recibirDaño(int cantidad);
    bool estaDerrotado() const;
    void mostrarEstado() const;
};

class Maluma : public Reguetonero {
public:
    Maluma();
};

class BadBunny : public Reguetonero {
public:
    BadBunny();
};

class PlanB : public Reguetonero {
public:
    PlanB();
};

class DonOmar : public Reguetonero {
public:
    DonOmar();
};

#endif