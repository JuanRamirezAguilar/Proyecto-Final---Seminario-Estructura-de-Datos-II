#ifndef ARCHIVOMEDICO_H
#define ARCHIVOMEDICO_H

#include <fstream>
#include <string>

#include "lista.h"

#include "Medico.h"
#include "Nombre.h"

#include "indexDuple.h"

class ArchivoMedico {
    private:
        std::fstream archivo;
        std::fstream archivoPorNombre;
        std::fstream archivoPorCodigo;

        std::string nameFileMedico;
        std::string indexNameFileMedico;
        std::string indexCodeFileMedico;

        Lista<indexDuple<std::string>> indexadoPorCodigo;
        Lista<indexDuple<Nombre>> indexadoPorNombre;

        void reIndex();

        template <class T>
        Lista<T> fileToList(std::fstream&, Lista<T>);

        template <class T>
        bool listToFile(const Lista<T>&, std::fstream&);

        template <class T>
        int getIndex(const Lista<indexDuple<T>>&, const T&) const;

    public:
        ArchivoMedico();
        ~ArchivoMedico();
        void addData(const Medico&);
        void addData(Lista<Medico>&);
        Medico getData(const int&);
        void delData(const int&);
        int findData(const std::string&) const;
        int findData(const Nombre&) const;
        Lista<Medico> toList();
        void clear();
        bool existenDatos();

        Lista<Medico> getMisMedicos();

        void compress();
        void importBackup();
        void exportBackup(const std::string&);
};

#endif
