#ifndef ARCHIVOCONSULTA_H
#define ARCHIVOCONSULTA_H

#include <fstream>
#include <string>

#include "lista.h"
#include "Consulta.h"
#include "indexDuple.h"

class ArchivoConsulta {
    private:
        std::fstream archivo;
        std::fstream archivoPorHora;

        Lista<Consulta> miListaDeConsultas;

        std::string nameFileConsulta;

        template <class T>
        Lista<T> fileToList(std::fstream&, Lista<T>);
        template <class T>
        bool listToFile(const Lista<T>&, std::fstream&);


    public:
        ArchivoConsulta();
        ~ArchivoConsulta();
        void addData(const Consulta&);
        void addData(Lista<Consulta>&);
        Consulta getData(const int&);
        void delData(const int&);
        int getIndex(const Consulta & c);
        int findData(const Consulta & c);
        Lista<Consulta> toList();
        void clear();
        bool existenDatos();

        Lista<Consulta> getConsultas();

        void compress();
        void cargarDatos();
};

#endif