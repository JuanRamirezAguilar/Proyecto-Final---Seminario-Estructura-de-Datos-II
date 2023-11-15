#include "MenuPaciente.h"

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
const std::string Subtitulo = "Menu de Pacientes";

MenuPaciente::MenuPaciente() {}

MenuPaciente::~MenuPaciente() {}

void MenuPaciente::setOpc(std::string valorOpc) { opc = valorOpc; }

std::string MenuPaciente::getOpc() { return opc; }

void MenuPaciente::menu() {
    std::string opciones;
    do {
        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARB << Subtitulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB << "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB << "Agregar un Paciente.         " << GB "[ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 10);
        std::cout <<ARB << "Elimnar un Paciente.         " << GB "[ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 11);
        std::cout <<ARB << "Buscar un Paciente.          " << GB "[ " <<RF<< "C" <<GB " ]";
        gotoxy(3, 12);
        std::cout <<ARB << "Regresar al menu anterior.   " << GB "[ " <<RF<< "X" <<GB " ]";

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

void MenuPaciente::agregar() {
    Paciente nuevoPaciente;
    Nombre nuevoNombre;
    Fecha nuevaFecha;
    Domicilio nuevoDomicilio;
    std::string auxString;
    int auxDia, auxMes, auxAnio;

    const std::string subtiImport = "Agregar un Paciente";

    system(CLEAR);
    std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARB << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    gotoxy(3, 7);
    std::cout << GF << "Ingresar un Paciente nuevo al archivo." <<RTNC;

    gotoxy(3, 9);
    std::cout << GF << "Dame el numero del seguro social del paciente:" <<RTNC;
    gotoxy(50, 9);
    fflush(stdin);
    std::getline(cin, auxString);
    nuevoPaciente.setNumSeguroSocial(auxString);

    gotoxy(3, 11);
    std::cout << GF << "Dame el apellido del paciente:" <<RTNC;
    fflush(stdin);
    gotoxy(34, 11);
    std::getline(cin, auxString);
    nuevoNombre.setApellido(auxString);

    gotoxy(3, 13);
    std::cout << GF << "Dame el nombre del paciente:" <<RTNC;
    gotoxy(32, 13);
    fflush(stdin);
    std::getline(cin, auxString);
    nuevoNombre.setNombre(auxString);
    nuevoPaciente.setNombre(nuevoNombre);

    bool fechaValida = false;
    while (!fechaValida) {
        gotoxy(3, 15);
        std::cout << GF << "Dame la fecha de nacimiento del paciente:" <<RTNC;
        gotoxy(50, 15); std::cout << "/"; gotoxy(56, 15); std::cout << "/";

        gotoxy(46, 14); std::cout << "Dia";
        gotoxy(52, 14); std::cout << "Mes";
        gotoxy(59, 14); std::cout << "A" << char(164)  << "o";

        gotoxy(46, 15); cin >> auxDia;
        gotoxy(52, 15); cin >> auxMes;
        gotoxy(59, 15); cin >> auxAnio;

        if (!nuevaFecha.diaEsValido(auxMes, auxDia) or !nuevaFecha.mesEsValido(auxMes) or !nuevaFecha.anioEsValido(auxAnio)) {
            gotoxy(3, 17);
            std::cout << RB << "La fecha introducida no es valida intentalo de nuevo" <<RTNC; pausa();

            for (int x = 3; x < 100; x++) {
                for (int y = 15; y < 18; y++) {
                    gotoxy(x, y); std::cout << " ";
                }
            }
        } else {
            fechaValida = true;
            nuevaFecha.setDia(auxDia); nuevaFecha.setMes(auxMes); nuevaFecha.setAnio(auxAnio);
            nuevoPaciente.setFechaDeNacimiento(nuevaFecha);
        }
    }


    gotoxy(3, 17);
    std::cout << GF << "Dame el nombre de la calle donde vive el paciente:" <<RTNC;
    fflush(stdin);
    gotoxy(54, 17);
    std::getline(cin, auxString);
    nuevoDomicilio.setCalle(auxString);

    gotoxy(3, 19);
    std::cout << GF << "Dame el numero de la casa donde vive el paciente:" <<RTNC;
    gotoxy(53, 19);
    std::cin >> auxDia;
    nuevoDomicilio.setNumero(auxDia);

    gotoxy(3, 21);
    std::cout << GF << "Dame el nombre de la colonia donde vive el paciente:" <<RTNC;
    fflush(stdin);
    gotoxy(56, 21);
    std::getline(cin, auxString);
    nuevoDomicilio.setColonia(auxString);

    gotoxy(3, 23);
    std::cout << GF << "Dame el numero postal de la zona donde vive el paciente:" <<RTNC;
    gotoxy(60, 23);
    std::cin >> auxDia;
    nuevoDomicilio.setCodigoPostal(auxDia);

    gotoxy(3, 25);
    std::cout << GF << "Dame el municipio donde vive el paciente:" <<RTNC;
    fflush(stdin);
    gotoxy(45, 25);
    std::getline(cin, auxString);
    nuevoDomicilio.setMunicipio(auxString);

    nuevoPaciente.setDomicilio(nuevoDomicilio);

    gotoxy(3, 27);
    std::cout << GF << "Dame el telefono del paciente:" <<RTNC;
    fflush(stdin);
    gotoxy(34, 27);
    std::getline(cin, auxString);
    nuevoPaciente.setTelefono(auxString);

    miArchivoPaciente.addData(nuevoPaciente);

    gotoxy(3, 29);
    std::cout << VB << "Paciente Registrado en el archivo..." <<RTNC; pausa();
}

void MenuPaciente::eliminar() {
    if (miArchivoPaciente.existenDatos()) {
        std::string opcElim;
        gotoxy(3, 16);
        std::cout << GB << "Eliminar por nombre.             [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 17);
        std::cout << GB << "Eliminar por N.S.S.              [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 18);
        std::cout << GB << "Regresar al menu.                [ " <<RF<< "X" <<GB " ]";
        gotoxy(3, 19);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 19);
        std::cout <<RF; std::getline(std::cin, opcElim); setOpc(opcElim); std::cout <<RTNC;

        if (opcElim == "A" or opcElim == "a") {
            Nombre miNombre;
            system(CLEAR);
            const std::string subtiImport = "Eliminar un Paciente";
            std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;
            gotoxy(3, 7);
            std::cout <<GF<< "Ingresa el apellido del paciente a buscar: ";
            gotoxy(47, 7);
            fflush(stdin);
            getline(std::cin, stringAux);
            miNombre.setNombre(stringAux);

            gotoxy(3, 9);
            std::cout <<GF<< "Ingresa el nombre del paciente a buscar: ";
            gotoxy(45, 9);
            fflush(stdin);
            getline(std::cin, stringAux);
            miNombre.setApellido(stringAux);

            int idx = miArchivoPaciente.findData(miNombre);

            if (idx != -1) {
                string opcBorrar;
                Paciente showPaciente = miArchivoPaciente.getData(idx);

                gotoxy(3, 11);
                std::cout << "Paciente: " << std::endl;
                gotoxy(3, 12);
                std::cout << AF << showPaciente.toString();

                gotoxy(3, 15);
                std::cout << ARB << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
                gotoxy(3, 16);
                std::cout << GB << "Si.  [ " <<RF<< "Y" <<GB " ]";
                gotoxy(3, 17);
                std::cout << GB << "No.  [ " <<RF<< "N" <<GB " ]";
                gotoxy(3, 18);
                std::cout <<GB << "Tu opcion ==> ";
                gotoxy(18, 18);
                std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

                if (opcBorrar == "Y" or opcBorrar == "y") {
                    miArchivoPaciente.delData(idx);
                    miArchivoPaciente.compress();
                    gotoxy(3, 20);
                    std::cout <<VB<< "Paciente eliminado correctamente."<<RTNC; pausa();
                } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                    gotoxy(3, 20);
                    std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar paciente..." <<RTNC; timeStop(1000);
                } 
            } else {
                gotoxy(3, 11);
                std::cout <<RB<< "No se encontró un paciente con ese nombre."<<RTNC; pausa();
            }

        } else if (opcElim == "B" or opcElim == "b") {
            system(CLEAR);
            const std::string subtiImport = "Eliminar un paciente";
            std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string codigo;
            gotoxy(3, 7);
            std::cout <<GF<< "Ingresa el numero del seguro social del paciente a buscar: ";
            gotoxy(63, 7);
            fflush(stdin);
            getline(std::cin, codigo);
            /////////////////////////////////
            int idx = miArchivoPaciente.findData(codigo);

            if (idx != -1) {
                string opcBorrar;
                Paciente showPaciente = miArchivoPaciente.getData(idx);

                gotoxy(3, 9);
                std::cout << "Paciente: " << std::endl;
                gotoxy(3, 10);
                std::cout << AF << showPaciente.toString();

                gotoxy(3, 13);
                std::cout << ARB << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
                gotoxy(3, 14);
                std::cout << GB << "Si.  [ " <<RF<< "Y" <<GB " ]";
                gotoxy(3, 15);
                std::cout << GB << "No.  [ " <<RF<< "N" <<GB " ]";
                gotoxy(3, 16);
                std::cout <<GB << "Tu opcion ==> ";
                gotoxy(18, 16);
                std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

                if (opcBorrar == "Y" or opcBorrar == "y") {
                    miArchivoPaciente.delData(idx);
                    miArchivoPaciente.compress();
                    gotoxy(3, 18);
                    std::cout <<VB<< "Paciente eliminado correctamente."<<RTNC; pausa();
                } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                    gotoxy(3, 18);
                    std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar paciente..." <<RTNC; timeStop(1000);
                } 
            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un paciente con ese codigo."<<RTNC; pausa();
            }

        } else if (opcElim == "X" or opcElim == "x") {
            return;
        } else {
            gotoxy(3, 21); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opcElim <<GB<< "\" no es una opcion valida..."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No hay registros que eliminar."<<RTNC; pausa();
    }   
}

void MenuPaciente::buscar() {
    if (miArchivoPaciente.existenDatos()) {

        std::string opcBuscar;
        gotoxy(3, 16);
        std::cout << GB << "Buscar por Nombre.  [ " <<RF<< "A" <<GB " ]";
        gotoxy(3, 17);
        std::cout << GB << "Buscar por N.S.S.   [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 18);
        std::cout << GB << "Regresar al menu.   [ " <<RF<< "X" <<GB " ]";
        gotoxy(3, 19);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 19);
        fflush(stdin);
        std::cout <<RF; std::getline(std::cin, opcBuscar); setOpc(opcBuscar); std::cout <<RTNC;

        if (opcBuscar == "A" or opcBuscar == "a") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Paciente";
            std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;
            Nombre nombreAux;

            gotoxy(3, 7);
            std::cout <<GF<< "Ingresa el apellido del paciente a buscar:";
            gotoxy(46, 7);
            fflush(stdin);
            getline(std::cin, stringAux);
            nombreAux.setApellido(stringAux);

            gotoxy(3, 9);
            std::cout <<GF<< "Ingresa el nombre del paciente a buscar:";
            gotoxy(44, 9);
            fflush(stdin);
            getline(std::cin, stringAux);
            nombreAux.setNombre(stringAux);

            int idx = miArchivoPaciente.findData(nombreAux);
            
            if (idx != -1) {
                Paciente pacienteAux = miArchivoPaciente.getData(idx);

                // Imprime el N.S.S del Paciente
                gotoxy(3, 11);
                std::cout << ARB << "N.S.S del paciente:";
                gotoxy(23, 11);
                std::cout << VF << pacienteAux.getNumSeguroSocial();

                // Imprime el Nombre del Paciente
                gotoxy(3, 12);
                std::cout << ARB << "Nombre del Paciente:";
                gotoxy(24, 12);
                std::cout << VF << pacienteAux.getNombre().toString();

                // Imprime la Fecha de Nacimiento del Paciente del Medico
                gotoxy(3, 13);
                std::cout << ARB << "Fecha de Naciemiento del Paciente:";
                gotoxy(38, 13);
                std::cout << VF << pacienteAux.getFechaDeNacimiento().toString();

                // Imprime el Domicilio del Paciente
                gotoxy(3, 14);
                std::cout << ARB << "Domicilio del Paciente:";
                gotoxy(27, 14);
                std::cout << VF << pacienteAux.getDomicilio().toString();

                // Imprime el telefono del Paciente
                gotoxy(3, 15);
                std::cout << ARB << "Numero de Telefono del Paciente:";
                gotoxy(36, 15);
                std::cout << VF << pacienteAux.getTelefono();

                pausa();

            } else {
                gotoxy(3, 11);
                std::cout <<RB<< "No se encontro un paciente con ese nombre."<<RTNC; pausa();
            }

        } else if (opcBuscar == "B" or opcBuscar == "b") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Paciente";
            std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;

            gotoxy(3, 7);
            std::cout <<GF<< "Ingresa el N.S.S del paciente a buscar:";
            gotoxy(43, 7);
            fflush(stdin);
            getline(std::cin, stringAux);

            int idx = miArchivoPaciente.findData(stringAux);
            
            if (idx != -1) {
                Paciente pacienteAux = miArchivoPaciente.getData(idx);

                // Imprime el N.S.S del Paciente
                gotoxy(3, 11);
                std::cout << ARB << "N.S.S del paciente:";
                gotoxy(23, 11);
                std::cout << VF << pacienteAux.getNumSeguroSocial();

                // Imprime el Nombre del Paciente
                gotoxy(3, 12);
                std::cout << ARB << "Nombre del Paciente:";
                gotoxy(24, 12);
                std::cout << VF << pacienteAux.getNombre().toString();

                // Imprime la Fecha de Nacimiento del Paciente del Medico
                gotoxy(3, 13);
                std::cout << ARB << "Fecha de Naciemiento del Paciente:";
                gotoxy(38, 13);
                std::cout << VF << pacienteAux.getFechaDeNacimiento().toString();

                // Imprime el Domicilio del Paciente
                gotoxy(3, 14);
                std::cout << ARB << "Domicilio del Paciente:";
                gotoxy(27, 14);
                std::cout << VF << pacienteAux.getDomicilio().toString();

                // Imprime el telefono del Paciente
                gotoxy(3, 15);
                std::cout << ARB << "Numero de Telefono del Paciente:";
                gotoxy(36, 15);
                std::cout << VF << pacienteAux.getTelefono();

                pausa();

            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un paciente con ese codigo."<<RTNC; pausa();
            }
        } else if (opcBuscar == "X" or opcBuscar == "x") {
            return;
        } else {
            gotoxy(3, 21); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opcBuscar <<GB<< "\" no es una opcion valida..."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16);
        std::cout <<RB<< "No hay registros que buscar."<<RTNC; pausa();
    }
}

void MenuPaciente::cargarDatos() {
    miArchivoPaciente.cargarDatos();
}