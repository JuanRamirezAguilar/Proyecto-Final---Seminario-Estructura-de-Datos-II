#ifndef NOMBRE_H
#define NOMBRE_H

#include <string>

class Nombre {
    private:
        std::string nombres;
        std::string apellidos;

    public:
        // Constructores
        Nombre();
        Nombre(std::string name, std::string lastName);
        Nombre(const Nombre& copia);
        // Destructor
        ~Nombre();
        // Metodos
        std::string toString() const;
        // Setters
        void setNombre(std::string valorNombre);
        void setApellido(std::string valorApellido);
        // Getters
        std::string getNombre();
        std::string getApellido();
        // Operadores
        Nombre &operator = (const Nombre& copia);
        bool operator == (const Nombre& comparado) const;
        bool operator != (const Nombre& comparado) const;
        bool operator < (const Nombre& comparado) const;
        bool operator > (const Nombre& comparado) const;
        friend std::ostream& operator << (std::ostream& out, const Nombre& objSalida);
        friend std::istream& operator >> (std::istream& in, Nombre& objEntrada);
};

#endif