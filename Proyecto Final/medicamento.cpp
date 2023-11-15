#include "medicamento.h"

#include <iostream>

// Constructores
Medicamento::Medicamento() : codigo(""), nombre("") {}
Medicamento::Medicamento(std::string valorCodigo, std::string valorNombre) : codigo(valorCodigo), nombre(valorNombre) {}
Medicamento::Medicamento(const Medicamento& copia) : codigo(copia.codigo), nombre(copia.nombre) {}

// Destructor
Medicamento::~Medicamento() {}

// Metodos
std::string Medicamento::toString() const{
    return codigo + ", " + nombre;
}

// Setters
void Medicamento::setCodigo(std::string valorCodigo) {codigo = valorCodigo;}
void Medicamento::setNombre(std::string valorNombre) {nombre = valorNombre;}

// Getters
std::string Medicamento::getCodigo() {return codigo;}
std::string Medicamento::getNombre() {return nombre;}

// Operadores
Medicamento& Medicamento::operator = (const Medicamento& copia) {
    if (this == &copia) { return *this; }
    codigo = copia.codigo;
    nombre = copia.nombre;
    return *this;
}

bool Medicamento::operator == (const Medicamento& comparado) const {
    return (codigo == comparado.codigo);
}

bool Medicamento::operator != (const Medicamento& comparado) {
    return !(*this == comparado);
}

bool Medicamento::operator < (const Medicamento& comparado) {
    return codigo.length() < comparado.codigo.length();
}

bool Medicamento::operator <= (const Medicamento& comparado) {
    return codigo.length() < comparado.codigo.length() || codigo.length() == comparado.codigo.length();
}

bool Medicamento::operator > (const Medicamento& comparado) {
    return codigo.length() > comparado.codigo.length();
}

bool Medicamento::operator >= (const Medicamento& comparado) {
    return codigo.length() > comparado.codigo.length() || codigo.length() == comparado.codigo.length();
}

std::ostream& operator << (std::ostream& out, const Medicamento& objSalida) {
    out << objSalida.codigo << "*" << objSalida.nombre << "*";
    return out;
}

std::istream& operator >> (std::istream& in, Medicamento& objEntrada) {
    std::string myString;

    std::getline(in, myString, '*');
    objEntrada.setCodigo(myString);

    std::getline(in, myString, '*');
    objEntrada.setNombre(myString);

    return in;
}