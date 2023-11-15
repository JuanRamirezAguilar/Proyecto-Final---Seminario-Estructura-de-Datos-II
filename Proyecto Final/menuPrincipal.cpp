#include "menuPrincipal.h"

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

MenuPrincipal::MenuPrincipal() : opc(""), existenArchivos(false) {}

MenuPrincipal::~MenuPrincipal() {}

void MenuPrincipal::menu() {
    AltEnter();
    do {
        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB<< "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB<< "Consultas." << GB "           [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 10);
        std::cout <<ARB<< "Medicos." << GB "             [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 11);
        std::cout <<ARB<< "Pacientes." << GB "           [ " <<RF<< "C" <<GB " ]";
        gotoxy(3, 12);
        std::cout <<ARB<< "Diagnosticos." << GB "        [ " <<RF<< "D" <<GB " ]";
        gotoxy(3, 13);
        std::cout <<ARB<< "Medicamentos." << GB "        [ " <<RF<< "E" <<GB " ]";
        gotoxy(3, 14);
        std::cout <<ARB<< "Importar archivo." << GB "    [ " <<RF<< "F" <<GB " ]";
        gotoxy(3, 15);
        std::cout <<ARB<< "Exportar archivo." << GB "    [ " <<RF<< "G" <<GB " ]";
        gotoxy(3, 16);
        std::cout <<ARB<< "Salir del programa." << GB "  [ " <<RF<< "X" <<GB " ]";

        gotoxy(3, 18);
        std::cout <<GB<< "Tu opcion ==> ";
        gotoxy(18, 18);
        fflush(stdin);
        std::cout <<RF; std::getline(std::cin, opc);  std::cout <<RTNC;

        if (opc == "A" or opc == "a") { consultas(); }
        else if (opc == "B" or opc == "b") { medicos(); }
        else if (opc == "C" or opc == "c") { pacientes(); }
        else if (opc == "D" or opc == "d") { diagnosticos(); }
        else if (opc == "E" or opc == "e") { medicamentos(); }
        else if (opc == "F" or opc == "f") { importarArchivo(); }
        else if (opc == "G" or opc == "g") { exportarArchivo(); }
        else if (opc == "X" or opc == "x") { salir(); }

        else { gotoxy(3, 20); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opc <<GB<< "\" no es una opcion valida..."<<RTNC; pausa(); }

    } while (opc != "X" and opc != "x");
}

void MenuPrincipal::salir() {
    gotoxy(3, 20);
    std::cout <<RB; std::cout << "Saliendo del programa..."<<RTNC; //timeStop(2000);
}

void MenuPrincipal::consultas() {
    MenuConsultas miMenuConsultas;
    miMenuConsultas.menu();
}

void MenuPrincipal::medicos() {
    MenuMedicos miMenuMedicos;
    miMenuMedicos.menu();
}

void MenuPrincipal::pacientes() {
    MenuPaciente miMenuPacientes;
    miMenuPacientes.cargarDatos();
    miMenuPacientes.menu();
}

void MenuPrincipal::diagnosticos() {
    MenuDiagnosticos miMenuDiagnosticos;
    miMenuDiagnosticos.cargarDatos();
    miMenuDiagnosticos.menu();
}

void MenuPrincipal::medicamentos() {
    MenuMedicamento miMenuMedicamento;
    miMenuMedicamento.cargarDatos();
    miMenuMedicamento.menu();
}

void MenuPrincipal::importarArchivo() {
    gotoxy(3, 20); std::cout << ARB << "Dame el nombre del archivo a importar:"<<RTNC;
    std::string nameImporte;
    fflush(stdin);
    std::cout<<AB; gotoxy(42, 20); std::getline(std::cin, nameImporte); std::cout<<RTNC;
    
    if (ifstream(nameImporte)) {
        miFileMaster.importBackup(nameImporte);
        gotoxy(3, 27); std::cout << VB << "Archivo importado correctamente."<<RTNC; pausa();
        existenArchivos = true;
    } else {
        gotoxy(3, 21); std::cout << RB << "No existe archivo con ese nombre, intentalo de nuevo."<<RTNC; pausa();
    }
}

void MenuPrincipal::exportarArchivo() {
    if (existenArchivos) {
        miFileMaster.exportBackup();
        if (ifstream("import_file_consultas.file")) {
            gotoxy(3, 20); std::cout << VB << "Archivo exportado exitosamente."<<RTNC; pausa();
        } else {
            gotoxy(3, 20); std::cout << RB << "El archivo no se ha podido exportar."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 20);
        std::cout <<RB; std::cout << "Primero importa el archivo..."<<RTNC; pausa();
    }
}

void MenuPrincipal::enConstruccion() {
    gotoxy(3, 20); std::cout << RB << "Esta opcion del programa esta en construccion..."<<RTNC; pausa();
}