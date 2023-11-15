#include "consulta.h"

// Constructores
Consulta::Consulta() {}

Consulta::Consulta(Fecha valorFecha, Hora valorHora, std::string valorIndicacion, Paciente valorPaciente, Medico valorMedico,
Diagnostico valorDiagnostico, Medicamento valorMedicamento1, Medicamento valorMedicamento2,
Medicamento valorMedicamento3) : fecha(valorFecha), hora(valorHora), indicacion(valorIndicacion), paciente(valorPaciente),
medico(valorMedico), diagnostico(valorDiagnostico), medicamento1(valorMedicamento1), medicamento2(valorMedicamento2),
medicamento3(valorMedicamento3) {}

Consulta::Consulta(const Consulta& copia) : fecha(copia.fecha), hora(copia.hora), indicacion(copia.indicacion), paciente(copia.paciente), medico(copia.medico),
diagnostico(copia.diagnostico), medicamento1(copia.medicamento1), medicamento2(copia.medicamento2), medicamento3(copia.medicamento3) {}

// Destructor
Consulta::~Consulta() {}

// Metodos
std::string Consulta::toString() const{
    return "Fecha de Consulta: " + fecha.toString() + "\nPaciente: " + paciente.toString() + "\nMedico: " + medico.toString() +
            "\nDiagnostico: " + diagnostico.toString()  + "\nIndicacion: " + indicacion + "\nMedicamento1: " + medicamento1.toString() + "\nMedicamento2: " + medicamento2.toString() + 
            "\nMedicamento3: " + medicamento3.toString();
}

int Consulta::toInt() const{
    return 1;
}

// Setters
void Consulta::setFecha(Fecha valorFecha) {fecha = valorFecha;}
void Consulta::setHora(Hora valorHora) {hora = valorHora;}
void Consulta::setIndicacion(std::string valorIndicacion) {indicacion = valorIndicacion;}
void Consulta::setPaciente(Paciente valorPaciente) {paciente = valorPaciente;}
void Consulta::setMedico(Medico valorMedico) {medico = valorMedico;}
void Consulta::setDiagnostico(Diagnostico valorDiagnostico) {diagnostico = valorDiagnostico;}
void Consulta::setMedicamento1(Medicamento valorMedicamento) {medicamento1 = valorMedicamento;}
void Consulta::setMedicamento2(Medicamento valorMedicamento) {medicamento2 = valorMedicamento;}
void Consulta::setMedicamento3(Medicamento valorMedicamento) {medicamento3 = valorMedicamento;}

// Getters
Fecha Consulta::getFecha() const{return fecha;}
Hora Consulta::getHora() const{return hora;}
std::string Consulta::getIndicacion() const {return indicacion;}
Paciente Consulta::getPaciente() const{return paciente;}
Medico Consulta::getMedico() const{return medico;}
Diagnostico Consulta::getDiagnostico() const{return diagnostico;}
Medicamento Consulta::getMedicamento1 () const { return medicamento1; }
Medicamento Consulta::getMedicamento2 () const { return medicamento2; }
Medicamento Consulta::getMedicamento3 () const { return medicamento3; }

// Operadores
Consulta& Consulta::operator = (const Consulta& copia) {
    if (this == &copia) { return *this; }
    fecha = copia.fecha;
    hora = copia.hora;
    indicacion = copia.indicacion;
    paciente = copia.paciente;
    medico = copia.medico;
    diagnostico = copia.diagnostico;
    medicamento1 = copia.medicamento1;
    medicamento2 = copia.medicamento2;
    medicamento3 = copia.medicamento3;
    return *this;
}

bool Consulta::operator == (const Consulta& comparado) const{
    return (fecha == comparado.fecha) && (hora == comparado.hora) && (paciente.getNumSeguroSocial() == comparado.paciente.getNumSeguroSocial());
}

bool Consulta::operator != (const Consulta& comparado) const{
    return !(*this == comparado);
}

bool Consulta::operator < (const Consulta& comparado) const{
    return toInt() < comparado.toInt();
}

bool Consulta::operator <= (const Consulta& comparado) const{
    return toInt() < comparado.toInt() || *this == comparado;
}

bool Consulta::operator > (const Consulta& comparado) const{
    return toInt() > comparado.toInt();
}

bool Consulta::operator >= (const Consulta& comparado) const{
    return toInt() > comparado.toInt() || *this == comparado;
}

std::ostream& operator << (std::ostream& out, const Consulta& objSalida) {
    out << objSalida.fecha;
    out << objSalida.hora;
    out << objSalida.diagnostico;
    out << objSalida.indicacion << "*";
    out << objSalida.medico;
    out << objSalida.paciente;
    out << objSalida.medicamento1;
    out << objSalida.medicamento2;
    out << objSalida.medicamento3;

    return out;
}

std::istream & operator>>(std::istream & in, Consulta & objEntrada) {

    // Toma la fecha de la consulta
    in >> objEntrada.fecha;
    
    // Toma la hora de la consulta
    in >> objEntrada.hora;

    std::string myString;
    std::getline(in, myString, '*');
    objEntrada.setIndicacion(myString);

    // Toma el Diagnostico de la consulta
    in >> objEntrada.diagnostico;

    // Toma el Medico de la consulta;
    in >> objEntrada.medico;

    // Toma el Paciente de la consulta;
    in >> objEntrada.paciente;

    // Toma el Medicamento de la consulta;
    in >> objEntrada.medicamento1;
    in >> objEntrada.medicamento2;
    in >> objEntrada.medicamento3;

    // Se ingresa en la lista
    return in;
}