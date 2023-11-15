#include "medico.h"

// Constructores
Medico::Medico() : codigo(""), cedula("") {}
Medico::Medico(std::string valorCodigo, Nombre valorNombre, std::string valorCedula, Hora valoEntrada, Hora valorSalida) :
codigo(valorCodigo), nombre(valorNombre), cedula(valorCedula), horaEntrada(valoEntrada), horaSalida(valorSalida) {}
Medico::Medico(const Medico& copia) : codigo(copia.codigo), nombre(copia.nombre), cedula(copia.cedula),
horaEntrada(copia.horaEntrada), horaSalida(copia.horaSalida) {}

// Destructor
Medico::~Medico() {}

// Medtodos
std::string Medico::toString() const{
    return "Codigo: " + codigo + ", " + "Nombre: " + nombre.toString() + ", " + "Cedula: " + cedula
            + ", " + "Hora de Entrada: " + horaEntrada.toString() + ", " + "Hora de Salida: " + horaSalida.toString();
}

unsigned long long Medico::toInt() const{
    return std::stoull(codigo);
}

// Setters
void Medico::setCodigo(std::string valorCodigo) {codigo = valorCodigo;}
void Medico::setNombre(Nombre valorNombre) {nombre = valorNombre;}
void Medico::setCedula(std::string valorCedula) {cedula = valorCedula;}
void Medico::setHoraEntrada(Hora valorEntrada) {horaEntrada = valorEntrada;}
void Medico::setHoraSalida(Hora valorSalida) {horaSalida = valorSalida;}

// Getters
std::string Medico::getCodigo() const {return codigo;}
Nombre Medico::getNombre() const {return nombre;}
std::string Medico::getCedula() const {return cedula;}
Hora Medico::getHoraEntrada() const {return horaEntrada;}
Hora Medico::getHoraSalida() const {return horaSalida;}

// Operadores
Medico& Medico::operator = (const Medico& copia) {
    if (this == &copia) { return *this; }
    codigo = copia.codigo;
    nombre = copia.nombre;
    cedula = copia.cedula;
    horaEntrada = copia.horaEntrada;
    horaSalida = copia.horaSalida;
    return *this;
}

bool Medico::operator == (const Medico& comparado) const{
    return nombre == comparado.nombre;
}

bool Medico::operator != (const Medico& comparado) const {
    return !(nombre == comparado.nombre);
}

bool Medico::operator < (const Medico& comparado) const{
    return codigo < comparado.codigo;
}

bool Medico::operator <= (const Medico& comparado) const{
    return codigo < comparado.codigo || codigo == comparado.codigo;
}

bool Medico::operator > (const Medico& comparado) const{
    return codigo > comparado.codigo;
}

bool Medico::operator >= (const Medico& comparado) const{
    return codigo > comparado.codigo || codigo == comparado.codigo;
}

std::ostream& operator << (std::ostream& out, const Medico& objSalida) {
    out << objSalida.codigo << "*" << objSalida.nombre << objSalida.cedula << "*" 
    << objSalida.horaEntrada << objSalida.horaSalida;
    return out;
}

std::istream& operator >> (std::istream& in, Medico& objEntrada) {
    std::string miString;
    Nombre auxNombre;
    Hora auxHora;

    std::getline(in, miString, '*');
    objEntrada.setCodigo(miString);

    in >> auxNombre;
    objEntrada.setNombre(auxNombre);

    std::getline(in, miString, '*');
    objEntrada.setCedula(miString);

    in >> auxHora;
    objEntrada.setHoraEntrada(auxHora);
    
    in >> auxHora;
    objEntrada.setHoraSalida(auxHora);

    return in;

}