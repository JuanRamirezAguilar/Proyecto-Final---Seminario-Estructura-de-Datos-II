#include "fecha.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

// Constructores 
Fecha::Fecha() { // default
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    dia = local->tm_mday;
    mes = local->tm_mon;
    anio = local->tm_year + MINANIO;
}

Fecha::Fecha(int day, int month, int year) : Fecha() { // parametros
    if (anioEsValido(year) && mesEsValido(month) && diaEsValido(month, day)) {
        dia = day; mes = month; anio = year;
    } else {
        std::cout << "Error de fecha, se establecera la fecha por defecto..."; std::cin.ignore();
    }
}

Fecha::Fecha(const Fecha &copia) : dia(copia.dia), mes(copia.mes), anio(copia.anio) {} // copia

// Metodos
std::string Fecha::toString() const {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%02d/%02d/%02d", dia, mes, anio);
    return std::string(buffer);
}

int Fecha::toInt() const {
    return (anio * 10) + (mes * 5) + dia;
}

bool Fecha::anioEsValido(int valorAnio) const{
    return valorAnio >= MINANIO && valorAnio <= MAXANIO;
}

bool Fecha::mesEsValido(int valorMes) const{
    return valorMes >= ENERO && valorMes <= DICIEMBRE;
}

bool Fecha::diaEsValido(int valorMes, int valorDia) const{
    if (valorMes == ABRIL || valorMes == JUNIO || valorMes == SEPTIMEBRE || valorMes == NOVIEMBRE) {
        return valorDia >= 1 && valorDia <= 30;
    } else {
        if (valorMes == ENERO || valorMes == MARZO || valorMes == MAYO || valorMes == JULIO 
            || valorMes == AGOSTO || valorMes == OCTUBRE || valorMes == DICIEMBRE) {
            return valorDia >= 1 && valorDia <= 31;
        } else {
            if (valorMes == FEBRERO){
                return valorDia >= 1 && valorDia <= 28;
            }
        }
    }
    return false;
}

// Setters
void Fecha::setDia(int valorDia) {dia = valorDia;}
void Fecha::setMes(int valorMes) {mes = valorMes;}
void Fecha::setAnio(int valorAnio) {anio = valorAnio;}

// Getters
int Fecha::getDia() const {return dia;}
int Fecha::getMes() const {return mes;}
int Fecha::getAnio() const {return anio;}

// Operadores
Fecha& Fecha::operator=(const Fecha& copia) {
    if (this == &copia) { return *this; }
    dia = copia.dia;
    mes = copia.mes;
    anio = copia.anio;
    return *this;
}

bool Fecha::operator==(const Fecha &comparado) const {
    return toInt() == comparado.toInt();
}

bool Fecha::operator!=(const Fecha &comparado) const {
    return !(*this == comparado);
}

bool Fecha::operator<(const Fecha &comparado) const {
    return toInt() < comparado.toInt();
}

bool Fecha::operator<=(const Fecha &comparado) const {
    return toInt() < comparado.toInt() || *this == comparado;
}

bool Fecha::operator>(const Fecha &comparado) const {
    return toInt() > comparado.toInt();
}

bool Fecha::operator>=(const Fecha &comparado) const {
    return toInt() > comparado.toInt() || *this == comparado;
}

std::ostream& operator<<(std::ostream& out, const Fecha& objSalida) {
    out << objSalida.dia << "/" << objSalida.mes << "/" << objSalida.anio << "*";
    return out;
}

std::istream& operator >> (std::istream& in, Fecha& objEntrada) {
    std::string myString;
    Fecha auxFecha;

    std::getline(in, myString, '*');
    std::stringstream miStream(myString);

    // Revisa si el primer digito de la fecha es un digito
    // Si no lo es, descarta todo el campo y establece una fecha por defecto.
    std::getline(miStream, myString, '/');
    if (!std::isdigit(char(myString[0]))) {
        objEntrada = auxFecha;
        return in;
    }

    // Dia
    objEntrada.setDia(std::stoi(myString));

    // Mes
    std::getline(miStream, myString, '/');
    objEntrada.setMes(std::stoi(myString));

    // Año
    std::getline(miStream, myString);
    objEntrada.setAnio(std::stoi(myString));
    
    return in;
}