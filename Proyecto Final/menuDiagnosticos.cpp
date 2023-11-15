#include "menuDiagnosticos.h"

#include "StandarLibrary.h"
#include "Colores.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define ALTURA_BORDE 100
#define ANCHURA_BORDE 150
#define ANCHURA_PANTALLA 1366
#define ALTURA_PANTALLA 768

const std::string Titulo = "Sistema Integral de Registros Medicos";
const std::string Subtitulo = "Menu de Diagnosticos";

MenuDiagnosticos::MenuDiagnosticos() {}

MenuDiagnosticos::~MenuDiagnosticos() {}

void MenuDiagnosticos::setOpc(std::string valorOpc) { opc = valorOpc; }
std::string MenuDiagnosticos::getOpc() { return opc; }

void MenuDiagnosticos::menu() {
    std::string opciones;
    do {
        system(CLEAR);
        std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB; std::cout << "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB; std::cout << "Agregar un Diagnostico." << GB "        [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 10);
        std::cout <<ARB; std::cout << "Elimnar un Diagnostico." << GB "        [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 11);
        std::cout <<ARB; std::cout << "Buscar un Diagnostico." << GB "         [ " <<RF<< "C" <<GB " ]";
        gotoxy(3, 12);
        std::cout <<ARB; std::cout << "Regresar al menu anterior." << GB "     [ " <<RF<< "X" <<GB " ]";

        gotoxy(3, 14);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 14);
        fflush(stdin);
        std::cout <<RF; std::getline(std::cin, opciones); setOpc(opciones); std::cout <<RTNC;

        if (opc == "A" or opc == "a")      { agregar(); } 
        else if (opc == "B" or opc == "b") { eliminar(); } 
        else if (opc == "C" or opc == "c") { buscar(); }
        else if (opc == "X" or opc == "x") { return; }
        else { gotoxy(3, 16); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opc <<GB<< "\" no es una opcion valida..."<<RTNC; pausa(); }

    } while (opc != "X" and opc != "x");
}

void MenuDiagnosticos::agregar() {
    Diagnostico nuevoDiagnostico;
    std::string auxString;

    const std::string subtiImport = "Agregar un Diagnostico";

    system(CLEAR);
    std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARB << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    gotoxy(3, 7);
    std::cout << GB << "Ingresar un Diagnostico nuevo al archivo." <<RTNC;

    bool codigoValido = false;
    while (!codigoValido) {
        gotoxy(3, 9);
        std::cout << ARB << "Dame el codigo del diagnostico:" <<RTNC;
        
        gotoxy(35, 9);
        fflush(stdin);
        std::cout <<VB; std::getline(cin, auxString); std::cout <<RTNC;

        if (miArchivoDiagnostico.findData(auxString) != -1) {
            gotoxy(3, 11);
            std::cout << RB << "El codigo introducido no es valida intentalo de nuevo" <<RTNC; pausa();

            // Este bucle borra los escrito en la pantalla
            borrarPantalla(3, 9, 11);
        } else {
            codigoValido = true;
            nuevoDiagnostico.setCodigo(auxString);
        }
    }

    gotoxy(3, 11);
    std::cout << ARB << "Dame la descripcion del diagnostico:" <<RTNC;
    fflush(stdin);
    gotoxy(40, 11);
    std::cout <<VB; std::getline(cin, auxString); std::cout <<RTNC;
    nuevoDiagnostico.setDescripcion(auxString);

    miArchivoDiagnostico.addData(nuevoDiagnostico);

    gotoxy(3, 13);
    std::cout << VB << "Diagnostico Registrado en el archivo..." <<RTNC; pausa();
}

void MenuDiagnosticos::eliminar() {
    if (miArchivoDiagnostico.existenDatos()) {

        std::string auxCodigo;

        system(CLEAR);
        const std::string subtiImport = "Eliminar un Diagnostico";
        std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
        std::cout << AB << subtiImport <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB<< "Ingresa el codigo del diagnostico a eliminar:";
        
        gotoxy(49, 7);
        fflush(stdin);
        std::cout <<VB; getline(std::cin, auxCodigo); std::cout <<RTNC;

        int idx = miArchivoDiagnostico.findData(auxCodigo);

        if (idx != -1) {
            string opcBorrar;
            Diagnostico showDiagnostico = miArchivoDiagnostico.getData(idx);

            gotoxy(3, 9);
            std::cout << "Diagnostico:" << std::endl;
            gotoxy(3, 10);
            std::cout << AF << showDiagnostico.toString();

            gotoxy(3, 12);
            std::cout << ARB << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
            gotoxy(3, 13);
            std::cout << GB << "Si.  [ " <<RF<< "Y" <<GB " ]";
            gotoxy(3, 14);
            std::cout << GB << "No.  [ " <<RF<< "N" <<GB " ]";
            gotoxy(3, 16);
            std::cout <<GB << "Tu opcion ==> ";
            gotoxy(18, 16);
            std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

            if (opcBorrar == "Y" or opcBorrar == "y") {
                miArchivoDiagnostico.delData(idx);
                miArchivoDiagnostico.compress();
                gotoxy(3, 18);
                std::cout <<VB<< "Diagnostico eliminado correctamente."<<RTNC; pausa();
            } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                gotoxy(3, 18);
                std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar diagnostico..." <<RTNC; timeStop(1000);
            } 
        } else {
            gotoxy(3, 9);
            std::cout <<RB<< "No se encontró un diagnostico con ese codigo."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No existen registros validos que buscar."<<RTNC; pausa();
    }
}

void MenuDiagnosticos::buscar() {
    if (miArchivoDiagnostico.existenDatos()) {
        std::string opcBuscar;
        gotoxy(3, 16);
        std::cout << ARB << "Buscar por Codigo." << GB"        [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 17);
        std::cout << ARB << "Buscar por Descripcion." << GB"   [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 18);
        std::cout << ARB << "Regresar al menu." << GB"         [ " <<RF<< "X" <<GB " ]";
        gotoxy(3, 19);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 19);
        fflush(stdin);
        std::cout <<RF; std::getline(std::cin, opcBuscar); setOpc(opcBuscar); std::cout <<RTNC;

        if (opcBuscar == "A" or opcBuscar == "a") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Diagnostico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;

            gotoxy(3, 7);
            std::cout <<ARB<< "Ingresa el codigo del diagnostico a buscar:";
            gotoxy(46, 7);
            fflush(stdin);
            std::cout << VB; getline(std::cin, stringAux); std::cout << RTNC;

            int idx = miArchivoDiagnostico.findData(stringAux);
            
            if (idx != -1) {
                Diagnostico diagnosticoAux = miArchivoDiagnostico.getData(idx);

                // Imprime el codigo del Diagnostico
                gotoxy(3, 9);
                cout << ARB << "Codigo del Diagnostico:";
                gotoxy(26, 9);
                cout << VF << diagnosticoAux.getCodigo();

                // Imprime la descripcion del Diagnostico
                gotoxy(3, 10);
                cout << ARB << "Descripcion del Diagnostico:";
                gotoxy(31, 10);
                cout << VF << diagnosticoAux.getDescripcion();
                pausa();

            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un diagnostico con ese nombre."<<RTNC; pausa();
            }

        } else if (opcBuscar == "B" or opcBuscar == "b") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Diagnostico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;

            gotoxy(3, 7);
            std::cout <<ARB<< "Ingresa la descripcion del diagnostico a buscar:";
            gotoxy(51, 7);
            fflush(stdin);
            std::cout << VB; getline(std::cin, stringAux); std::cout << RTNC;

            Diagnostico aux;
            aux.setDescripcion(stringAux);

            int idx = miArchivoDiagnostico.findData(aux);
            
            if (idx != -1) {
                Diagnostico diagnosticoAux = miArchivoDiagnostico.getData(idx);

                // Imprime el codigo del Diagnostico
                gotoxy(3, 9);
                cout << ARB << "Codigo del Diagnostico:";
                gotoxy(26, 9);
                cout << VF << diagnosticoAux.getCodigo();

                // Imprime la descripcion del Diagnostico
                gotoxy(3, 10);
                cout << ARB << "Descripcion del Diagnostico:";
                gotoxy(31, 10);
                cout << VF << diagnosticoAux.getDescripcion();
                pausa();

            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un diagnostico con ese nombre."<<RTNC; pausa();
            }
        } else if (opcBuscar == "X" or opcBuscar == "x") {
            return;
        } else {
            gotoxy(3, 21); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opcBuscar <<GB<< "\" no es una opcion valida..."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No existen registros validos que buscar."<<RTNC; pausa();
    }
}

void MenuDiagnosticos::cargarDatos()
{ miArchivoDiagnostico.cargarDatos(); }