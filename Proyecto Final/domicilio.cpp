#include "domicilio.h"

#include <iostream>

// Constructores
Domicilio::Domicilio() : numero(0), calle(""), colonia(""), codigoPostal(0), municipio("") {}

Domicilio::Domicilio(int num, std::string call, std::string col, int cp, std::string mun) {
    numero = num; calle = call; colonia = col; codigoPostal = cp; municipio = mun;
}

Domicilio::Domicilio(const Domicilio& copia) {
    numero = copia.numero; calle = copia.calle; colonia = copia.colonia; codigoPostal = copia.codigoPostal;
    municipio = copia.municipio;
}

// Metodos
std::string Domicilio::toString() const{
    return std::to_string(numero) + ", " + calle + ", " + colonia + ", " + std::to_string(codigoPostal) + ", " + municipio;
}

// Constructor
Domicilio::~Domicilio() {}

// Setters
void Domicilio::setNumero(int valorNumero) {numero = valorNumero;}
void Domicilio::setCalle(std::string valorCalle) {calle = valorCalle;}
void Domicilio::setColonia(std::string valorColonia) {colonia = valorColonia;}
void Domicilio::setCodigoPostal(int valorCodigo) {codigoPostal = valorCodigo;}
void Domicilio::setMunicipio(std::string valorMunicipio) {municipio = valorMunicipio;}

// Getters
int Domicilio::getNumero() const {return numero;}
std::string Domicilio::getCalle() const {return calle;}
std::string Domicilio::getColonia() const {return colonia;}
int Domicilio::getCodigoPostal() const {return codigoPostal;}
std::string Domicilio::getMunicipio() const {return municipio;}

// Operadores
Domicilio& Domicilio::operator = (const Domicilio& copia) {
    if (this == &copia) { return *this; }
    numero = copia.numero;
    calle = copia.calle;
    colonia = copia.colonia;
    codigoPostal = copia.codigoPostal;
    municipio = copia.municipio;
    return *this;
}

bool Domicilio::operator == (const Domicilio& comparado) {
    return (numero == comparado.numero) && (calle == comparado.calle) && (colonia == comparado.colonia) && 
            (codigoPostal == comparado.codigoPostal) && (municipio == comparado.municipio);
}

bool Domicilio::operator != (const Domicilio& comparado) {
    return !(*this == comparado);
}

std::ostream& operator << (std::ostream& out, const Domicilio& objSalida) {
    out << objSalida.calle << "*";
    out << objSalida.numero << "*";
    out << objSalida.colonia << "*";
    out << objSalida.codigoPostal << "*";
    out << objSalida.municipio << "*";
    return out; 
}

std::istream& operator >> (std::istream& in, Domicilio& objEntrada) {
    std::string myString;
    
    std::getline(in, myString, '*');
    objEntrada.setCalle(myString);

    std::getline(in, myString, '*');
    objEntrada.setNumero(std::stoi(myString));

    std::getline(in, myString, '*');
    objEntrada.setColonia(myString);

    std::getline(in, myString, '*');
    objEntrada.setCodigoPostal(std::stoi(myString));

    std::getline(in, myString, '*');
    objEntrada.setMunicipio(myString);

    return in;
}