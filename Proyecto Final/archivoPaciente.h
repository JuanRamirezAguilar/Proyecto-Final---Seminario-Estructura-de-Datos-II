#ifndef ARCHIVOPACIENTE_H
#define ARCHIVOPACIENTE_H

#include <fstream>
#include <string>
#include <sstream>

#include "lista.h"

#include "Paciente.h"
#include "Nombre.h"
#include "Fecha.h"
#include "Domicilio.h"

#include "indexDuple.h"

class ArchivoPaciente {
    private:
        std::fstream archivo;
        std::fstream archivoPorNombre;
        std::fstream archivoPorSeguroSocial;

        std::string nameFilePacientes;
        std::string indexNameFilePaciente;
        std::string indexSeguroFilePaciente;

        Lista<indexDuple<Nombre>> indexadoPorNombre;
        Lista<indexDuple<>> indexadoPorSeguro;

        void reIndex();

        template <class T>
        Lista<T> fileToList(std::fstream&, Lista<T>);

        template <class T>
        bool listToFile(const Lista<T>&, std::fstream&);

        template <class T>
        int getIndex(const Lista<indexDuple<T>>&, const T&) const;

    public:
        ArchivoPaciente();
        ~ArchivoPaciente();
        void addData(const Paciente&);
        void addData(Lista<Paciente>&);
        Paciente getData(const int&);
        void delData(const int&);
        int findData(const std::string&) const;
        int findData(const Nombre&) const;
        Lista<Paciente> toList();
        void clear();
        bool existenDatos();

        void compress();
        void cargarDatos();
};

#endif