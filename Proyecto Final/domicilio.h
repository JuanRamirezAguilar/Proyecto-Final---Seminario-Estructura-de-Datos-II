#ifndef DOMICILIO_H
#define DOMICILIO_H

#include <string>

class Domicilio {
    private:
        int numero;
        std::string calle;
        std::string colonia;
        int codigoPostal;
        std::string municipio;

    public:
        // Constructores
        Domicilio();
        Domicilio(int num, std::string call, std::string col, int cp, std::string mun);
        Domicilio(const Domicilio& copia);
        // Constructor
        ~Domicilio();
        // Metodos
        std::string toString() const;
        // Setters
        void setNumero(int valorNumero);
        void setCalle(std::string valorCalle);
        void setColonia(std::string valorColonia);
        void setCodigoPostal(int valorCodigo);
        void setMunicipio(std::string valorMunicipio);
        // Getters
        int getNumero() const;
        std::string getCalle() const;
        std::string getColonia() const;
        int getCodigoPostal() const;
        std::string getMunicipio() const;
        // Operadores
        Domicilio &operator = (const Domicilio& copia);
        bool operator == (const Domicilio& comparado);
        bool operator != (const Domicilio& comparado);
        friend std::ostream& operator << (std::ostream& out, const Domicilio& objSalida);
        friend std::istream& operator >> (std::istream& in, Domicilio& objEntrada);
};

#endif