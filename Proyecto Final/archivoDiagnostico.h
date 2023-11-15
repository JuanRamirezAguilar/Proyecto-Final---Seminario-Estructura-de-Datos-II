#ifndef ARCHIVODIAGNOSTICO_H
#define ARCHIVODIAGNOSTICO_H

#include <fstream>
#include <string>
#include <sstream>

#include "lista.h"
#include "Diagnostico.h"
#include "indexDuple.h"

class ArchivoDiagnostico {
    private:
        std::fstream archivo;
        std::fstream archivoPorCodigo;
        std::fstream archivoPorDescripcion;

        std::string nameFileDiagnostico;
        std::string indexCodeFileDiagnostico;
        std::string indexDescripcionFileDiagnostico;

        Lista<indexDuple<>> indexadoPorCodigo;
        Lista<indexDuple<>> indexadoPorDescripcion;

        Lista<Diagnostico> misDiagnosticos;

        void reIndex();

        template <class T>
        Lista<T> fileToList(std::fstream&, Lista<T>);

        template <class T>
        bool listToFile(const Lista<T>&, std::fstream&);

        template <class T>
        int getIndex(const Lista<indexDuple<T>>&, const T&) const;

    public:
        ArchivoDiagnostico();
        ~ArchivoDiagnostico();
        void addData(const Diagnostico&);
        void addData(Lista<Diagnostico>&);
        Diagnostico getData(const int&);
        void delData(const int&);
        int findData(const std::string&) const;
        int findData(const Diagnostico&) const;
        Lista<Diagnostico> toList();
        void clear();
        bool existenDatos();

        Lista<Diagnostico> getMisDiagnosticos();

        void compress();
        void cargarDatos();
};

#endif