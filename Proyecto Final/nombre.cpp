#include "nombre.h"
#include <iostream>

using std::string;

// Constructores
Nombre::Nombre() : nombres(""), apellidos("") {}
Nombre::Nombre(string name, string lastName) : nombres(name), apellidos(lastName) {}
Nombre::Nombre(const Nombre& copia) : nombres(copia.nombres), apellidos(copia.apellidos) {}

// Destructor
Nombre::~Nombre() {}

// Metodos
string Nombre::toString() const{
    return nombres + " " + apellidos;
}

// Setters
void Nombre::setNombre(string valorNombre) {nombres = valorNombre;}
void Nombre::setApellido(string valorApellido) {apellidos = valorApellido;}

// Getters
string Nombre::getNombre() {return nombres;}
string Nombre::getApellido() {return apellidos;}

// Operadores
Nombre& Nombre::operator=(const Nombre& copia) {
    if (this == &copia) { return *this; }
    nombres = copia.nombres;
    apellidos = copia.apellidos;
    return *this;
}

bool Nombre::operator == (const Nombre& comparado) const{
    return (nombres == comparado.nombres) && (apellidos == comparado.apellidos);
}

bool Nombre::operator != (const Nombre& comparado) const{
    return !(*this == comparado);
}

bool Nombre::operator < (const Nombre& comparado) const{
    if (apellidos < comparado.apellidos) {
            return true;
        } else if (apellidos == comparado.apellidos) {
            return nombres < comparado.nombres;
        }
    return false;
}

bool Nombre::operator > (const Nombre& comparado) const{
    if (apellidos > comparado.apellidos) {
        return true;
    } else if (apellidos == comparado.apellidos) {
        return nombres > comparado.nombres;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Nombre& objSalida) {
    out << objSalida.nombres << "*" << objSalida.apellidos << "*";
    return out;
}

std::istream& operator >> (std::istream& in, Nombre& objEntrada) {
    std::string myString;
    std::getline(in, myString, '*');
    objEntrada.setNombre(myString);
    std::getline(in, myString, '*');
    objEntrada.setApellido(myString);
    return in;
}