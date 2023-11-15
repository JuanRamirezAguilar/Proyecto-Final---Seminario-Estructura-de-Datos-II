#ifndef FECHA_H
#define FECHA_H

#include <iostream>

#define MINANIO 1900
#define MAXANIO 2100

enum Meses{ENERO = 1, FEBRERO, MARZO, ABRIL, MAYO, JUNIO, JULIO, AGOSTO, SEPTIMEBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE};

class Fecha {
    private:
        int dia;
        int mes;
        int anio;

    public:
        // Constructores
        Fecha();
        Fecha(int day, int month, int year);
        Fecha(const Fecha &copia);
        // Metodos
        std::string toString() const;
        int toInt() const;
        bool anioEsValido(int valorAnio) const;
        bool mesEsValido(int valorMes) const;
        bool diaEsValido(int valorMes, int valorDia) const;
        // Setters
        void setDia(int dia);
        void setMes(int mes);
        void setAnio(int anio);
        // Getters
        int getDia() const;
        int getMes() const;
        int getAnio() const;
        // Operadores
        Fecha &operator = (const Fecha& copia);
        bool operator == (const Fecha& comparado) const;
        bool operator != (const Fecha& comparado) const;
        bool operator < (const Fecha& comparado) const;
        bool operator <= (const Fecha& comparado) const;
        bool operator > (const Fecha& comparado) const;
        bool operator >= (const Fecha& comparado) const;
        friend std::ostream& operator << (std::ostream& out, const Fecha& objSalida);
        friend std::istream& operator >> (std::istream& in, Fecha& objEntrada);
};

#endif // FECHA_H