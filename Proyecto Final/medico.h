#ifndef MEDICO_H
#define MEDICO_H

#include "Nombre.h"
#include "Hora.h"

class Medico {
    private:
        std::string codigo;
        Nombre nombre;
        std::string cedula;
        Hora horaEntrada;
        Hora horaSalida;

    public:
        // Constructores
        Medico();
        Medico(std::string valorCodigo, Nombre valorNombre, std::string valorCedula, Hora valoEntrada, Hora valorSalida);
        Medico(const Medico& copia);
        // Destructor
        ~Medico();
        // Medtodos
        std::string toString()  const;
        unsigned long long toInt() const;
        // Setters
        void setCodigo(std::string valorCodigo);
        void setNombre(Nombre valorNombre);
        void setCedula(std::string valorCedula);
        void setHoraEntrada(Hora valorEntrada);
        void setHoraSalida(Hora valorSalida);
        // Getters
        std::string getCodigo() const;
        Nombre getNombre() const;
        std::string getCedula() const;
        Hora getHoraEntrada() const;
        Hora getHoraSalida() const;
        // Operadores
        Medico &operator = (const Medico& copia);
        bool operator == (const Medico& comparado) const;
        bool operator != (const Medico& comparado) const;
        bool operator < (const Medico& comparado) const;
        bool operator <= (const Medico& comparado) const;
        bool operator > (const Medico& comparado) const;
        bool operator >= (const Medico& comparado) const;
        friend std::ostream& operator << (std::ostream& out, const Medico& objSalida);
        friend std::istream& operator >> (std::istream& in, Medico& objEntrada);
};

#endif // MEDICO_H