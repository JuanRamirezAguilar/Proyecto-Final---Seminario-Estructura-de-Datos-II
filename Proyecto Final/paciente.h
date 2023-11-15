#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

#include "Nombre.h"
#include "Fecha.h"
#include "Domicilio.h"

class Paciente {
    private:
        Nombre nombre;
        std::string numSeguroSocial;
        Fecha fechaDeNacimiento;
        Domicilio domicilio;
        std::string telefono;

    public:
        // Constructores
        Paciente();
        Paciente(Nombre nom, std::string nss, Fecha fdn, Domicilio dom, std::string tel);
        Paciente(const Paciente& copia);
        // Destructor
        ~Paciente();
        // Metodos
        std::string toString() const;
        // Setters
        void setNombre(Nombre valorNombre);
        void setNumSeguroSocial(std::string valorSeguro);
        void setFechaDeNacimiento(Fecha valorFecha);
        void setDomicilio(Domicilio valorDomiciio);
        void setTelefono(std::string valorTelefono);
        // Getters
        Nombre getNombre() const;
        std::string getNumSeguroSocial() const;
        Fecha getFechaDeNacimiento() const;
        Domicilio getDomicilio() const;
        std::string getTelefono() const;
        // Operadores
        Paciente &operator = (const Paciente& copia);
        bool operator == (const Paciente& comparado) const;
        bool operator == (const Nombre& comparado) const;
        bool operator != (const Paciente& comparado) const;
        bool operator != (const Nombre& comparado) const;
        bool operator < (const Paciente& comparado) const;
        bool operator > (const Paciente& comparado) const;
        bool operator <= (const Paciente& comparado) const;
        bool operator >= (const Paciente& comparado) const;
        friend std::ostream& operator << (std::ostream& out, const Paciente& objSalida);
        friend std::istream& operator >> (std::istream& in, Paciente& objEntrada);
};


#endif