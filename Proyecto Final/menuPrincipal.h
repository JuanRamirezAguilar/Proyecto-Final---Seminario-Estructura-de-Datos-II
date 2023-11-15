#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <string>
#include "fileMaster.h"
#include "menuConsultas.h"
#include "MenuMedicos.h"
#include "MenuPaciente.h"
#include "MenuMedicamento.h"
#include "menuDiagnosticos.h"

#include "StandarLibrary.h"
#include "Colores.h"

class MenuPrincipal {
    private:
        std::string opc;
        bool existenArchivos;
        FileMaster miFileMaster;
    
    public:    
        MenuPrincipal();
        ~MenuPrincipal();

        void menu();
        void salir();
        void consultas();
        void medicos();
        void pacientes();
        void diagnosticos();
        void medicamentos();
        void importarArchivo();
        void exportarArchivo();
        void enConstruccion();
};

#endif