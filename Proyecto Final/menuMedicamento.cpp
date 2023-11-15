#include "MenuMedicamento.h"

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
const std::string Subtitulo = "Menu de Medicamentos";

MenuMedicamento::MenuMedicamento() {}

MenuMedicamento::~MenuMedicamento() {}

void MenuMedicamento::setOpc(std::string valorOpc) { opc = valorOpc; }

std::string MenuMedicamento::getOpc() { return opc; }

void MenuMedicamento::menu() {
    std::string opciones;
    do {
        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB; std::cout << "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB; std::cout << "Agregar un Medicamento." << GB"        [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 10);
        std::cout <<ARB; std::cout << "Elimnar un Medicamento." << GB"        [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 11);
        std::cout <<ARB; std::cout << "Buscar un Medicamento." << GB"         [ " <<RF<< "C" <<GB " ]";
        gotoxy(3, 12);
        std::cout <<ARB; std::cout << "Regresar al menu anterior." <<GB"     [ " <<RF<< "X" <<GB " ]";

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

void MenuMedicamento::agregar() {
    Medicamento nuevoMedicamento;
    std::string auxString;

    const std::string subtiImport = "Agregar un Medicamento";

    system(CLEAR);
    std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARB << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    gotoxy(3, 7);
    std::cout << GB << "Ingresar un Medicamento nuevo al archivo." <<RTNC;

    bool codigoValido = false;
    while (!codigoValido) {
        gotoxy(3, 9);
        std::cout << ARB << "Dame el codigo del medicamento:" <<RTNC;
        gotoxy(35, 9);
        fflush(stdin);
        std::cout << VB; std::getline(cin, auxString); std::cout << RTNC;

        int idx = miArchivoMedicamento.findData(auxString);
        if (idx == -1) {
            codigoValido = true;
            nuevoMedicamento.setCodigo(auxString);
        } else {
            gotoxy(3, 11);
            std::cout << RB << "El codigo que introduciste no es valido." <<RTNC; pausa();
            borrarPantalla(3, 9, 11);
        }
    }

    gotoxy(3, 11);
    std::cout << ARB << "Dame el nombre del medicamento:" <<RTNC;
    fflush(stdin);
    gotoxy(35, 11);
    std::cout << VB; std::getline(cin, auxString); std::cout << RTNC;
    nuevoMedicamento.setNombre(auxString);

    miArchivoMedicamento.addData(nuevoMedicamento);

    gotoxy(3, 13);
    std::cout << VB << "Medicamento Registrado en el archivo..." <<RTNC; pausa();
}

void MenuMedicamento::eliminar() {
    if (miArchivoMedicamento.existenDatos()) {

        std::string auxCodigo;

        system(CLEAR);
        const std::string subtiImport = "Eliminar un Medicamento";
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
        std::cout << AB << subtiImport <<RTNC;

        gotoxy(3, 7);
        std::cout <<ARB<< "Ingresa el codigo del medicamento a buscar:";
        gotoxy(47, 7);
        fflush(stdin);
        std::cout << VB; getline(std::cin, auxCodigo); std::cout << RTNC;

        int idx = miArchivoMedicamento.findData(auxCodigo);

        if (idx != -1) {
            string opcBorrar;
            Medicamento showMedicamento = miArchivoMedicamento.getData(idx);

            gotoxy(3, 11);
            std::cout << ARB << "Medicamento: " << std::endl;
            gotoxy(3, 12);
            std::cout << AF << showMedicamento.toString();

            gotoxy(3, 15);
            std::cout << ARB << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
            gotoxy(3, 16);
            std::cout << ARB << "Si.  " << GB"[ " <<RF<< "Y" <<GB " ]";
            gotoxy(3, 17);
            std::cout << ARB << "No.  " << GB"[ " <<RF<< "N" <<GB " ]";
            gotoxy(3, 18);
            std::cout <<GB << "Tu opcion ==> ";
            gotoxy(18, 18);
            std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

            if (opcBorrar == "Y" or opcBorrar == "y") {
                miArchivoMedicamento.delData(idx);
                miArchivoMedicamento.compress();
                gotoxy(3, 20);
                std::cout <<VB<< "Medicamento eliminado correctamente."<<RTNC; pausa();
            } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                gotoxy(3, 20);
                std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar medicamento..." <<RTNC; timeStop(1000);
            } 
        } else {
            gotoxy(3, 11);
            std::cout <<RB<< "No se encontró un medicamento con ese codigo."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No hay medicamentos que borrar."<<RTNC; pausa();
    }

}

void MenuMedicamento::buscar() {
    if (miArchivoMedicamento.existenDatos()) {

        system(CLEAR);
        const std::string subtiImport = "Buscar un Medicamento";
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
        std::cout << AB << subtiImport <<RTNC;

        std::string auxCodigo;

        gotoxy(3, 7);
        std::cout <<ARB<< "Ingresa el codigo del medicamento:";
        gotoxy(38, 7);
        fflush(stdin);
        std::cout << VB; getline(std::cin, auxCodigo); std::cout << RTNC;

        int idx = miArchivoMedicamento.findData(auxCodigo);
            
        if (idx != -1) {
            Medicamento MedicamentoAux = miArchivoMedicamento.getData(idx);

            // Imprime el Codigo del Medicamento
            gotoxy(3, 9);
            std::cout << ARB << "Codigo del medicamento:";
            gotoxy(27, 9);
            std::cout << AB << MedicamentoAux.getCodigo();

            // Imprime el Nombre del Medicamento
            gotoxy(3, 11);
            std::cout << ARB << "Nombre del Medicamento:";
            gotoxy(27, 11);
            std::cout << AB << MedicamentoAux.getNombre();
            pausa();

        } else {
            gotoxy(3, 9);
            std::cout <<RB<< "No se encontro un medicamento con ese codigo."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No hay medicamentos que buscar."<<RTNC; pausa();
    }
}

void MenuMedicamento::cargarDatos() {
    miArchivoMedicamento.cargarDatos();
}