#ifndef MenuMedicamento_H
#define MenuMedicamento_H

#include <iostream>
#include <string>

#include "archivoMedicamento.h"

class MenuMedicamento {
    private:
        std::string opc;
        archivoMedicamento miArchivoMedicamento;

    public:
        MenuMedicamento();
        ~MenuMedicamento();

        void setOpc(std::string valorOpc);
        std::string getOpc();

        void menu();
        void agregar();
        void eliminar();
        void buscar();
        void cargarDatos();
};

#endif // MenuMedicamento_H