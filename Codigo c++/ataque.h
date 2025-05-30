#ifndef ATAQUE_H
#define ATAQUE_H

#include <string>

class Ataque {
private:
    std::string nombre;
    int danio;
    std::string descripcion;

public:
    Ataque(std::string nombre, int danio, std::string descripcion);
    
    std::string getNombre() const;
    int getDanio() const;
    std::string getDescripcion() const;
};

#endif