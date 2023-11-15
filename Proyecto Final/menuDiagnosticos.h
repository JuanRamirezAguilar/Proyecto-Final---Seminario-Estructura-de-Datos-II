#ifndef MENUDIAGNOSTICOS_H
#define MENUDIAGNOSTICOS_H

#include <iostream>
#include <string>

#include "archivoDiagnostico.h"

class MenuDiagnosticos {
    private:
        std::string opc;
        ArchivoDiagnostico miArchivoDiagnostico;

    public:
        
        MenuDiagnosticos();
        ~MenuDiagnosticos();

        void setOpc(std::string valorOpc);
        std::string getOpc();

        void menu();
        void agregar();
        void eliminar();
        void buscar();
        void cargarDatos();
};

#endif