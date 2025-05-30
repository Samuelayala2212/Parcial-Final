#ifndef BATTLE_H
#define BATTLE_H

#include "reguetonero.h"
#include <vector>

class Battle {
private:
    std::vector<Reguetonero> reguetoneros;
    int reguetoneroActual;
    bool batallaTerminada;

public:
    Battle();
    
    void iniciarBatalla();
    void mostrarMenu();
    void ejecutarTurno(int opcion);
    void cambiarReguetonero();
    bool haTerminado() const;
    void anunciarGanador() const;
};

#endif