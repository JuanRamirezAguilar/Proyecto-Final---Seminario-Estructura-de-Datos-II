#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

#include <string>

class Medicamento {
    private:
        std::string codigo;
        std::string nombre;

    public:
        // Constructores
        Medicamento();
        Medicamento(std::string valorCodigo, std::string valorNombre);
        Medicamento(const Medicamento& copia);
        // Destructor
        ~Medicamento();
        // Metodos
        std::string toString() const;
        // Setters
        void setCodigo(std::string valorCodigo);
        void setNombre(std::string valorNombre);
        // Getters
        std::string getCodigo();
        std::string getNombre();
        // Operadores
        Medicamento &operator = (const Medicamento& copia);
        bool operator == (const Medicamento& comparado) const;
        bool operator != (const Medicamento& comparado);
        bool operator < (const Medicamento& comparado);
        bool operator <= (const Medicamento& comparado);
        bool operator > (const Medicamento& comparado);
        bool operator >= (const Medicamento& comparado);
        friend std::ostream& operator << (std::ostream& out, const Medicamento& objSalida);
        friend std::istream& operator >> (std::istream& in, Medicamento& objEntrada);
};

#endif