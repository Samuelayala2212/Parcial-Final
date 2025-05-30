#include <iostream>
#include <vector>
#include "reguetonero.h"
#include "ataque.h"
#include "battle.h"
#include <cstdlib>
#include <ctime>

Ataque::Ataque(std::string nombre, int danio, std::string descripcion):
nombre(nombre), daño(daño), descripcion(descripcion) {}

std::string Ataque::getNombre() const { return nombre; }
int Ataque::getDaño() const { return daño; }
std::string Ataque::getDescripcion() const { return descripcion; }

Reguetonero::Reguetonero(std::string nombre, int vida, std::vector<Ataque> ataques):
nombre(nombre), vida(vida), vidaMaxima(vida), ataques(ataques) {}
std::string Reguetonero::getNombre() const { return nombre; }
int Reguetonero::getVida() const { return vida; }
int Reguetonero::getVidaMaxima() const { return vidaMaxima; }
const std::vector<Ataque>& Reguetonero::getAtaques() const { return ataques; }

void Reguetonero::recibirDaño(int cantidad) {
vida -= cantidad;
if (vida < 0) vida = 0;
}
bool Reguetonero::estaDerrotado() const {
return vida <= 0;
}
void Reguetonero::mostrarEstado() const {
std::cout << nombre << " - Vida: " << vida << "/" << vidaMaxima << std::endl;
}
Maluma::Maluma() : Reguetonero("Maluma", 100, {
Ataque("Felices los 4", 25, "Felices los 4, yo te acepto el tratooo"),
Ataque("Corazón", 20, "TU ME PARTISTE EL CORAZAOOO"),
Ataque("HP", 30, "QUIERE SALIR FUMAR BEBERRR")
}) {}

BadBunny::BadBunny() : Reguetonero("Bad Bunny", 110, {
Ataque("LA CANCION", 30, "PERO CANTAMO BIEN BORRACHO"),
Ataque("Bichiyal", 25, "Ella esta casi casi solteraaa..."),
Ataque("La Santa", 35, "Tu no ere una santa ni yo soy un santo")
}) {}

PlanB::PlanB() : Reguetonero("Plan B", 95, {
Ataque("Fanática Sensual", 20, "ELLA ES FANATICA DE LO SENSUALLL"),
Ataque("Solos", 25, "Solosssss mirandono a los ojosss"),
Ataque("¿Porque te demoras?", 30, "Se que quieressss se te nota")
}) {}

DonOmar::DonOmar() : Reguetonero("Don Omar", 105, {
Ataque("RX", 35, "MA YO SE LO QUE TU QUIERE"),
Ataque("Hooka", 25, "HOOKAAAAAAAA"),
Ataque("Dile", 30, "Dile que bailando te conocí, cuentale")
}) {}

Battle::Battle() : reguetoneroActual(0), batallaTerminada(false) {
reguetoneros.push_back(Maluma());
reguetoneros.push_back(BadBunny());
reguetoneros.push_back(PlanB());
reguetoneros.push_back(DonOmar());
}

void Battle::iniciarBatalla() {
std::cout << "¡Comienza la batalla de reguetoneros!\n";
std::cout << "Elige tu reguetonero:\n";
    
for (size_t i = 0; i < reguetoneros.size(); ++i) {
std::cout << i+1 << ". " << reguetoneros[i].getNombre() << "\n";
}

int eleccion;
std::cin >> eleccion;
reguetoneroActual = eleccion - 1;
std::cout << "Elegiste a" << reguetoneros[reguetoneroActual].getNombre() << "!\n";
}

void Battle::mostrarMenu() {
std::cout << "\n--- MENÚ ---\n";
std::cout << "1. Atacar\n";
std::cout << "2. Cambiar de reguetonero\n";
std::cout << "3. Ver estado\n";
std::cout << "4. Rendirse\n";
std::cout << "Elige una opción: ";
}

void Battle::ejecutarTurno(int opcion) {
switch(opcion) {
case 1: { 
std::cout << "\nElige un ataque:\n";
const auto& ataques = reguetoneros[reguetoneroActual].getAtaques();
for (size_t i = 0; i < ataques.size(); ++i) {
std::cout << i+1 << ". " << ataques[i].getNombre() 
<< " (Daño: " << ataques[i].getDaño() << ") - " 
<< ataques[i].getDescripcion() << "\n";
}
            
int ataqueElegido;
std::cin >> ataqueElegido;
int oponente;
do {
oponente = rand() % reguetoneros.size();
} while (oponente == reguetoneroActual || reguetoneros[oponente].estaDerrotado());
const Ataque& ataque = ataques[ataqueElegido-1];
std::cout << reguetoneros[reguetoneroActual].getNombre() << " usa " 
<< ataque.getNombre() << " contra " 
<< reguetoneros[oponente].getNombre() << "!\n";
reguetoneros[oponente].recibirDaño(ataque.getDaño());
std::cout <<reguetoneros[oponente].getNombre() << " pierde " 
<< ataque.getDaño() << " puntos de vida!\n";
if (reguetoneros[oponente].estaDerrotado()) {
std::cout <<reguetoneros[oponente].getNombre() << " ha sido derrotado!\n";
bool todosDerrotados = true;
for (size_t i = 0; i < reguetoneros.size(); ++i) {
if (i != reguetoneroActual && !reguetoneros[i].estaDerrotado()) {
todosDerrotados = false;
break;
}
}
                
if (todosDerrotados) {
batallaTerminada = true;
anunciarGanador();
}
}
break;
}
case 2: 
cambiarReguetonero();
break;
case 3:
std::cout << "\nEstado actual:\n";
for (const auto& reguetonero : reguetoneros) {
reguetonero.mostrarEstado();
}
break;
case 4: 
batallaTerminada = true;
std::cout << "Se rindió, perdió la batalla\n";
break;
default:
std::cout << "Opción no válida. Intenta de nuevo.\n";
}
}

void Battle::cambiarReguetonero() {
std::cout << "\nElige un nuevo reguetonero:\n";
for (size_t i = 0; i < reguetoneros.size(); ++i) {
if (i != reguetoneroActual && !reguetoneros[i].estaDerrotado()) {
std::cout << i+1 << ". " << reguetoneros[i].getNombre() << "\n";
}
}
    
int eleccion;
std::cin >> eleccion;
reguetoneroActual = eleccion - 1;
    
std::cout << "Ahora tu regueteronero es: " << reguetoneros[reguetoneroActual].getNombre() << "!\n";
}

bool Battle::haTerminado() const {
return batallaTerminada;
}

void Battle::anunciarGanador() const {
std::cout << "\nEl duelo terminó\n";
std::cout <<reguetoneros[reguetoneroActual].getNombre() << " ganó\n";
}

int main() {
srand(time(0)); 
Battle batalla;
batalla.iniciarBatalla();
while (!batalla.haTerminado()) {
batalla.mostrarMenu();
int opcion;
std::cin >> opcion;
batalla.ejecutarTurno(opcion);
}
return 0;
}