#ifndef MenuPaciente_H
#define MenuPaciente_H

#include "archivoPaciente.h"

class MenuPaciente {
    private:
        std::string opc;
        ArchivoPaciente miArchivoPaciente;

    public:
        MenuPaciente();
        ~MenuPaciente();

        void setOpc(std::string valorOpc);
        std::string getOpc();

        void menu();
        void agregar();
        void eliminar();
        void buscar();
        void cargarDatos();
};

#endif