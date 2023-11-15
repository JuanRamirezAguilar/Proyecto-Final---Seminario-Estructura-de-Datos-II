#ifndef HORA_H
#define HORA_H

#include <iostream>
#include <string>

class Hora {
    private:
        int minuto;
        int hora;

    public:
        // Constructores
        Hora();
        Hora(int valorHora, int valorMinuto);
        Hora(const Hora& copia);
        // Destructor
        ~Hora();
        // Metodos
        std::string toString() const;
        int toInt() const;
        bool esHoraValida() const;
        // Setters
        void setMinuto(int valorMinuto);
        void setHora(int valorHora);
        // Getters
        int getMinuto() const;
        int getHora() const;
        // Operadores
        Hora &operator = (const Hora& copia);
        
        bool operator == (const Hora& comparado) const;
        bool operator != (const Hora& comparado) const;
        bool operator < (const Hora& comparado) const;
        bool operator <= (const Hora& comparado) const;
        bool operator > (const Hora& comparado) const;
        bool operator >= (const Hora& comparado) const;
        friend std::ostream& operator << (std::ostream& out, const Hora& objSalida);
        friend std::istream& operator >> (std::istream& in, Hora& objEntrada);
};


#endif // HORA_H