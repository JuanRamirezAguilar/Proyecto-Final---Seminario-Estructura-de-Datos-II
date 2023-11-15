#include "paciente.h"

#include <iostream>

// Constructores
Paciente::Paciente() : numSeguroSocial(""), telefono("") {} // default
Paciente::Paciente(Nombre nom, std::string nss, Fecha fdn, Domicilio dom, std::string tel) : nombre(nom), numSeguroSocial(nss),
fechaDeNacimiento(fdn), domicilio(dom), telefono(tel) {} // Paremetrizado
Paciente::Paciente(const Paciente& copia) : nombre(copia.nombre), numSeguroSocial(copia.numSeguroSocial),
fechaDeNacimiento(copia.fechaDeNacimiento), domicilio(copia.domicilio), telefono(copia.telefono) {} // Copia

// Destructor
Paciente::~Paciente() {}

// Metodos
std::string Paciente::toString() const{
    return nombre.toString() + ", " + numSeguroSocial + ", " + fechaDeNacimiento.toString()
    + ", " + domicilio.toString() + ", " + telefono;
}

// Setters
void Paciente::setNombre(Nombre valorNombre) {nombre = valorNombre;}
void Paciente::setNumSeguroSocial(std::string valorSeguro) {numSeguroSocial = valorSeguro;}
void Paciente::setFechaDeNacimiento(Fecha valorFecha) {fechaDeNacimiento = valorFecha;}
void Paciente::setDomicilio(Domicilio valorDomiciio) {domicilio = valorDomiciio;}
void Paciente::setTelefono(std::string valorTelefono) {telefono = valorTelefono;}

// Getters
Nombre Paciente::getNombre() const {return nombre;}
std::string Paciente::getNumSeguroSocial() const {return numSeguroSocial;}
Fecha Paciente::getFechaDeNacimiento() const {return fechaDeNacimiento;}
Domicilio Paciente::getDomicilio() const {return domicilio;}
std::string Paciente::getTelefono() const {return telefono;}

// Operadores
Paciente& Paciente::operator = (const Paciente& copia) {
    if (this == &copia) { return *this; }
    nombre = copia.nombre;
    numSeguroSocial = copia.numSeguroSocial;
    fechaDeNacimiento = copia.fechaDeNacimiento;
    domicilio = copia.domicilio;
    telefono = copia.telefono;
    return *this;
}

bool Paciente::operator == (const Paciente& comparado) const{
    return numSeguroSocial == comparado.numSeguroSocial;
}

bool Paciente::operator == (const Nombre& comparado) const{
    return nombre == comparado;
}

bool Paciente::operator != (const Paciente& comparado) const {
    return numSeguroSocial != comparado.numSeguroSocial;
}

bool Paciente::operator != (const Nombre& comparado) const {
    return nombre != comparado;
}

bool Paciente::operator < (const Paciente& comparado) const {
    return numSeguroSocial < comparado.numSeguroSocial;
}

bool Paciente::operator > (const Paciente& comparado) const {
    return numSeguroSocial > comparado.numSeguroSocial;
}

bool Paciente::operator <= (const Paciente& comparado) const {
    return numSeguroSocial <= comparado.numSeguroSocial;
}

bool Paciente::operator >= (const Paciente& comparado) const {
    return numSeguroSocial >= comparado.numSeguroSocial;
}

std::ostream& operator << (std::ostream& out, const Paciente& objSalida) {
    out << objSalida.numSeguroSocial << "*";
    out << objSalida.nombre;
    out << objSalida.fechaDeNacimiento;
    out << objSalida.domicilio;
    out << objSalida.telefono << "*";
    return out; 
}

std::istream& operator >> (std::istream& in, Paciente& objEntrada) {
    std::string myString;
    Nombre auxNombre;
    Domicilio auxDomicilio;
    Fecha auxFecha;

    std::getline(in, myString, '*');
    objEntrada.setNumSeguroSocial(myString);

    in >> auxNombre;
    objEntrada.setNombre(auxNombre);

    in >> auxFecha;
    objEntrada.setFechaDeNacimiento(auxFecha);

    in >> auxDomicilio;
    objEntrada.setDomicilio(auxDomicilio);

    std::getline(in, myString, '*');
    objEntrada.setTelefono(myString);

    return in;
}