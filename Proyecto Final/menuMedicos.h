#ifndef MenuMedicos_H
#define MenuMedicos_H

#include "archivoMedico.h"

class MenuMedicos {
    private:
        std::string opc;
        ArchivoMedico miArchivoMedico;
        bool existenArchivosMedicos;

    public:
        MenuMedicos();
        ~MenuMedicos();

        void setOpc(std::string valorOpc);
        std::string getOpc();

        void menu();
        void agregar();
        void eliminar();
        void buscar();
        void importarArchivo();
};

#endif