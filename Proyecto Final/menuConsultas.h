#ifndef MENUCONSULTAS_H
#define MENUCONSULTAS_H

#include "Consulta.h"
#include "archivoConsulta.h"
#include "lista.h"

#include <string>

class MenuConsultas {
    private:
        std::string opc;
        ArchivoConsulta archivo;

    public:

        MenuConsultas();
        ~MenuConsultas();
        
        void setOpc(std::string valorOpc);

        std::string getOpc();
        bool getExisteImporte();

        void menu();
        void agregar();
        void eliminar();
        void imprimir();
};

#endif