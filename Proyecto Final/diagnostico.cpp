#include "diagnostico.h"
#include <iostream>

// Constructores
Diagnostico::Diagnostico() : codigo(""), descripcion("") {}
Diagnostico::Diagnostico(std::string valorCodigo, std::string valorDescripcion) : codigo(valorCodigo), descripcion(valorDescripcion) {}
Diagnostico::Diagnostico(const Diagnostico& copia) : codigo(copia.codigo), descripcion(copia.descripcion) {}

// Destructor
Diagnostico::~Diagnostico() {}

// Metodos
std::string Diagnostico::toString() const{
    return codigo + ", " + descripcion;
}

// Setters
void Diagnostico::setCodigo(std::string valorCodigo) {codigo = valorCodigo;}
void Diagnostico::setDescripcion(std::string valorDescripcion) {descripcion = valorDescripcion;}


// Getters
std::string Diagnostico::getCodigo() const {return codigo;}
std::string Diagnostico::getDescripcion() const {return descripcion;}

// Operadores
Diagnostico& Diagnostico::operator = (const Diagnostico& copia) {
    if (this == &copia) { return *this; }
    codigo = copia.codigo;
    descripcion = copia.descripcion;
    return *this;
}
bool Diagnostico::operator == (const Diagnostico& comparado) const {
    return (descripcion == comparado.descripcion);
}

bool Diagnostico::operator != (const Diagnostico& comparado) {
    return !(*this == comparado);
}

std::ostream& operator << (std::ostream& out, const Diagnostico& objSalida) {
    out << objSalida.codigo << "*" << objSalida.descripcion << "*";
    return out;
}

std::istream& operator >> (std::istream& in, Diagnostico& objEntrada) {
    std::string myString;

    std::getline(in, myString, '*');
    objEntrada.setCodigo(myString);

    std::getline(in, myString, '*');
    objEntrada.setDescripcion(myString);

    return in;
}