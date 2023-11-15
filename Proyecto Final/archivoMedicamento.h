#ifndef ARCHIVOMEDICAMENTO_H
#define ARCHIVOMEDICAMENTO_H

#include <fstream>
#include <string>
#include <sstream>

#include "lista.h"
#include "Medicamento.h"
#include "indexDuple.h"

class archivoMedicamento {
    private:
        std::fstream archivo;
        std::fstream archivoPorCodigo;

        std::string nameFileMedicamento;
        std::string indexCodeFileMedicamento;

        Lista<indexDuple<>> indexadoPorCodigo;

        void reIndex();

        template <class T>
        Lista<T> fileToList(std::fstream&, Lista<T>);

        template <class T>
        bool listToFile(const Lista<T>&, std::fstream&);

        template <class T>
        int getIndex(const Lista<indexDuple<T>>&, const T&) const;

    public:
        archivoMedicamento();
        ~archivoMedicamento();

        void addData(const Medicamento&);
        void addData(Lista<Medicamento>&);
        Medicamento getData(const int&);
        void delData(const int&);
        int findData(const std::string&) const;
        Lista<Medicamento> toList();
        void clear();
        bool existenDatos();

        void compress();
        void cargarDatos();
};

#endif // ARCHIVOMEDICAMENTO_H