#include "MenuMedicos.h"

#include "StandarLibrary.h"
#include "Colores.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Propiedades del tamaño del marco de la ventana.
#define ALTURA_BORDE 100
#define ANCHURA_BORDE 150
#define ANCHURA_PANTALLA 1366
#define ALTURA_PANTALLA 768

const std::string Titulo = "Sistema Integral de Registros Medicos";
const std::string Subtitulo = "Menu de Medicos";

MenuMedicos::MenuMedicos() : opc(""), existenArchivosMedicos(false) {
    if (std::ifstream("archivoMedicos.txt"))
        existenArchivosMedicos = true;
}

MenuMedicos::~MenuMedicos() {}

void MenuMedicos::setOpc(std::string valorOpc) { opc = valorOpc; }
std::string MenuMedicos::getOpc() { return opc; }

void MenuMedicos::menu() {
    std::string opciones;
    do {
        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARF << Subtitulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB<< "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB<< "Agregar un Medico.         [ " <<RF<< "A" <<ARB " ]";
        gotoxy(3, 10);
        std::cout <<ARB<< "Elimnar un Medico.         [ " <<RF<< "B" <<ARB " ]";
        gotoxy(3, 11);
        std::cout <<ARB<< "Buscar un Medico.          [ " <<RF<< "C" <<ARB " ]";
        gotoxy(3, 12);
        std::cout <<ARB<< "Regresar al menu anterior. [ " <<RF<< "X" <<ARB " ]";

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

void MenuMedicos::agregar() {
    // Variables para la construccion del medico.
    Medico miMedico;
    Nombre MiNombre;
    Hora miHoraIn, miHoraOut;
    std::string miString;
    int auxHora, auxMin;

    if (!std::ifstream("archivoMedicos.txt"))
        std::ofstream("archivoMedicos.txt");
    importarArchivo();

    const std::string subtiImport = "Agregar un Medico";

    system(CLEAR);
    std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARF << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    gotoxy(3, 7);
    std::cout << GB << "Ingresar un medico nuevo al archivo." <<RTNC;

    gotoxy(3, 9);
    std::cout << AQF << "Dame la Cedula del medico:" <<RTNC;
    gotoxy(30, 9);
    std::cout << AB; fflush(stdin);
    std::getline(cin, miString); std::cout << RTNC;
    miMedico.setCedula(miString);

    // El bucle revisa si el nombre no esta repetido.
    bool nombreValido = false;
    while (!nombreValido) {
        gotoxy(3, 10);
        std::cout << AQF << "Dame el Apellido del Medico:" <<RTNC;
        std::cout << AB; fflush(stdin);
        gotoxy(32, 10);
        std::getline(cin, miString); std::cout << RTNC;
        MiNombre.setApellido(miString);

        gotoxy(3, 11);
        std::cout << AQF << "Dame el Nombre del Medico:" <<RTNC;
        gotoxy(30, 11);
        std::cout << AB; fflush(stdin);
        std::getline(cin, miString); std::cout << RTNC;
        MiNombre.setNombre(miString);

        int idx = miArchivoMedico.findData(MiNombre);
        if (idx == -1) {
            miMedico.setNombre(MiNombre);
            nombreValido = true;
        } else {
            gotoxy(3, 13);
            std::cout << RB << "El nombre ingresaste ya le pertenece a otro medico; intentalo de nuevo." << std::endl;
            pausa();
            // La funcion borra lo escrito anteriormente para que se pueda volver a utilizar.
            borrarPantalla(3, 10, 13);
        }
    }


    // El bucle revisa si el codigo no esta repetido.
    bool codigoValido = false;
    while (!codigoValido) {
        gotoxy(3, 12);
        std::cout << AQF << "Dame el Codigo del Medico:" <<RTNC;
        gotoxy(30, 12);
        std::cout <<AB; fflush(stdin);
        std::getline(cin, miString); std::cout <<RTNC;

        importarArchivo();
        int idx = miArchivoMedico.findData(miString);
        if (idx == -1) {
            miMedico.setCodigo(miString);
            codigoValido = true;
        } else {
            gotoxy(3, 14);
            std::cout << RB << "El codigo ingresaste ya le pertenece a otro medico; intentalo de nuevo." << std::endl;
            pausa();
        
            // La funcion borra lo escrito anteriormente para que se pueda volver a utilizar.
            borrarPantalla(3, 12, 14);
        }
    }

    // El bucle revisa si la hora es valida.
    bool horaValida = false;
    while (!horaValida) {
        // Hora Entrada.
        gotoxy(3, 14);
        std::cout << AQF << "Dame la hora de entrada del Medico:" <<RTNC;
        
        gotoxy(39, 13);
        std::cout << RB << "HH" <<RTNC;
        gotoxy(42, 13);
        std::cout << RB << ":" <<RTNC;
        gotoxy(44, 13);
        std::cout << RB << "MM" <<RTNC;

        gotoxy(39, 14);
        std::cout<<AB; std::cin >> auxHora;
        gotoxy(44, 14);
        std::cin >> auxMin; std::cout<<RTNC;

        miHoraIn.setHora(auxHora); miHoraIn.setMinuto(auxMin);

        // Hora Salida.
        gotoxy(3, 16);
        std::cout << AQF << "Dame la hora de salida del Medico:" <<RTNC;

        gotoxy(39, 15);
        std::cout << RB << "HH" <<RTNC;
        gotoxy(42, 15);
        std::cout << RB << ":" <<RTNC;
        gotoxy(44, 15);
        std::cout << RB << "MM" <<RTNC;

        gotoxy(39, 16);
        std::cout<<AB; std::cin >> auxHora;
        gotoxy(44, 16);
        std::cin >> auxMin; std::cout<<RTNC;

        miHoraOut.setHora(auxHora); miHoraOut.setMinuto(auxMin);

        if (!miHoraIn.esHoraValida() or !miHoraOut.esHoraValida()) {
            gotoxy(3, 18);
            std::cout << RB << "Alguna de las horas introducidas no es valida, intentalo de nuevo" <<RTNC; pausa();
            borrarPantalla(3, 13, 18);
        } else {
            horaValida = true;
            miMedico.setHoraEntrada(miHoraIn);
            miMedico.setHoraSalida(miHoraOut);
        }
    }

    miArchivoMedico.addData(miMedico);

    gotoxy(3, 18);
    std::cout << VB << "Medico Registrado en el archivo..." <<RTNC; pausa();
}

void MenuMedicos::eliminar() {
    if (existenArchivosMedicos) {
        std::string opcElim;
        gotoxy(3, 16);
        std::cout << ARB << "Eliminar por Nombre.  [ " <<RF<< "A" <<ARB " ]";
        gotoxy(3, 17);
        std::cout << ARB << "Eliminar por Codigo.  [ " <<RF<< "B" <<ARB " ]";
        gotoxy(3, 18);
        std::cout << ARB << "Regresar al menu.     [ " <<RF<< "X" <<ARB " ]";
        gotoxy(3, 19);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 19);
        std::cout <<RF; std::getline(std::cin, opcElim); setOpc(opcElim); std::cout <<RTNC;

        if (opcElim == "A" or opcElim == "a") {
            Nombre miNombre;
            system(CLEAR);
            const std::string subtiImport = "Eliminar un Medico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;
            gotoxy(3, 7);
            std::cout <<AQF<< "Ingresa el apellido del Medico a buscar: ";
            gotoxy(44, 7);
            std::cout<<AB; fflush(stdin);
            getline(std::cin, stringAux); std::cout<<RTNC;
            miNombre.setApellido(stringAux);

            gotoxy(3, 8);
            std::cout <<AQF<< "Ingresa el nombre del Medico a buscar: ";
            gotoxy(42, 8);
            std::cout<<AB; fflush(stdin);
            getline(std::cin, stringAux); std::cout<<RTNC;
            miNombre.setNombre(stringAux);

            int idx = miArchivoMedico.findData(miNombre);

            if (idx != -1) {
                string opcBorrar;
                Medico showMedico = miArchivoMedico.getData(idx);

                gotoxy(3, 10);
                std::cout << GB << "Medico:" << std::endl;
                gotoxy(3, 11);
                std::cout << ARF << "Nombre del medico: " << VB << showMedico.getNombre().toString();
                gotoxy(3, 12);
                std::cout << ARF << "Cedula: " << VB << showMedico.getCedula();

                gotoxy(3, 14);
                std::cout << AQF << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
                gotoxy(3, 15);
                std::cout << AQF << "Si.  [ " <<RF<< "Y" <<AQF " ]";
                gotoxy(3, 16);
                std::cout << AQF << "No.  [ " <<RF<< "N" <<AQF " ]";
                gotoxy(3, 18);
                std::cout <<GB << "Tu opcion ==> ";
                gotoxy(17, 18);
                std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

                if (opcBorrar == "Y" or opcBorrar == "y") {
                    miArchivoMedico.delData(idx);
                    miArchivoMedico.compress();
                    gotoxy(3, 20);
                    std::cout <<VB<< "Medico eliminado correctamente."<<RTNC; pausa();
                } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                    gotoxy(3, 20);
                    std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar medico..." <<RTNC; timeStop(1000);
                } 
            } else {
                gotoxy(3, 10);
                std::cout <<RB<< "No se encontró un medico con ese nombre."<<RTNC; pausa();
            }

        } else if (opcElim == "B" or opcElim == "b") {
            system(CLEAR);
            const std::string subtiImport = "Eliminar un Medico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string codigo;
            gotoxy(3, 7);
            std::cout <<AQF<< "Ingresa el codigo del Medico a buscar:";
            gotoxy(41, 7);
            std::cout<<AB; fflush(stdin);
            getline(std::cin, codigo); std::cout<<RTNC;
            int idx = miArchivoMedico.findData(codigo);

            if (idx != -1) {
                string opcBorrar;
                Medico showMedico = miArchivoMedico.getData(idx);

                gotoxy(3, 9);
                std::cout << GB << "Medico:" << std::endl;
                gotoxy(3, 10);
                std::cout << ARF << "Nombre del medico: " << VB << showMedico.getNombre().toString();
                gotoxy(3, 11);
                std::cout << ARF << "Cedula: " << VB << showMedico.getCedula();

                gotoxy(3, 13);
                std::cout << AQF << "Seguro que lo quieres borrar?" << RTNC <<std::endl;
                gotoxy(3, 14);
                std::cout << AQF << "Si.  [ " <<RF<< "Y" <<AQF " ]";
                gotoxy(3, 15);
                std::cout << AQF << "No.  [ " <<RF<< "N" <<AQF " ]";
                gotoxy(3, 16);
                std::cout <<GB << "Tu opcion ==> ";
                gotoxy(18, 16);
                std::cout <<RF; std::getline(std::cin, opcBorrar); setOpc(opcBorrar); std::cout <<RTNC;

                if (opcBorrar == "Y" or opcBorrar == "y") {
                    miArchivoMedico.delData(idx);
                    miArchivoMedico.compress();
                    gotoxy(3, 18);
                    std::cout <<VB<< "Medico eliminado correctamente."<<RTNC; pausa();
                } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
                    gotoxy(3, 18);
                    std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar medico..." <<RTNC; timeStop(1000);
                } 
            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un medico con ese codigo."<<RTNC; pausa();
            }

        } else if (opcElim == "X" or opcElim == "x") {
            return;
        } else {
            gotoxy(3, 21); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opcElim <<GB<< "\" no es una opcion valida..."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16); std::cout << RB << "No existen archivos donde eliminar al medico." << RTNC; pausa();
    }
}

void MenuMedicos::buscar() {
    if (existenArchivosMedicos) {

        std::string opcBuscar;
        gotoxy(3, 16);
        std::cout << ARB << "Buscar por Nombre.  [ " <<RF<< "A" <<ARB " ]";
        gotoxy(3, 17);
        std::cout << ARB << "Buscar por Codigo.  [ " <<RF<< "B" <<ARB " ]";
        gotoxy(3, 18);
        std::cout << ARB << "Regresar al menu.   [ " <<RF<< "X" <<ARB " ]";
        gotoxy(3, 19);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 19);
        fflush(stdin);
        std::cout <<RF; std::getline(std::cin, opcBuscar); setOpc(opcBuscar); std::cout <<RTNC;

        if (opcBuscar == "A" or opcBuscar == "a") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Medico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;
            Nombre nombreAux;

            gotoxy(3, 7);
            std::cout <<AQF<< "Ingresa el apellido del Medico a buscar:";
            std::cout<<AB; fflush(stdin);
            gotoxy(43, 7);
            getline(std::cin, stringAux); std::cout<<RTNC;
            nombreAux.setApellido(stringAux);

            gotoxy(3, 8);
            std::cout <<AQF<< "Ingresa el nombre del Medico a buscar:";
            std::cout<<AB; fflush(stdin);
            gotoxy(41, 8);
            getline(std::cin, stringAux); std::cout<<RTNC;
            nombreAux.setNombre(stringAux);

            importarArchivo();
            int idx = miArchivoMedico.findData(nombreAux);
            
            if (idx != -1) {
                Medico medicoAux = miArchivoMedico.getData(idx);

                // Imprime el Nombre del Medico
                gotoxy(3, 10);
                cout << ARB << "Nombre del Medico:";
                gotoxy(21, 10);
                cout << VF << medicoAux.getNombre().toString();

                // Imprime el Codigo del Medico
                gotoxy(3, 11);
                cout << ARB << "Codigo del Medico:";
                gotoxy(21, 11);
                cout << VF << medicoAux.getCodigo();

                // Imprime la Cedula del Medico
                gotoxy(3, 12);
                cout << ARB << "Cedula del Medico:";
                gotoxy(21, 12);
                cout << VF << medicoAux.getCedula();

                // Imprime la Hora de Entrada del Medico
                gotoxy(3, 13);
                cout << ARB << "Hora de Entrada del Medico:";
                gotoxy(30, 13);
                cout << VF << medicoAux.getHoraEntrada().toString();

                // Imprime la Hora de Salida del Medico
                gotoxy(3, 14);
                cout << ARB << "Hora de Salida del Medico:";
                gotoxy(29, 14);
                cout << VF << medicoAux.getHoraSalida().toString();

                pausa();

            } else {
                gotoxy(3, 10);
                std::cout <<RB<< "No se encontro un medico con ese nombre."<<RTNC; pausa();
            }

        } else if (opcBuscar == "B" or opcBuscar == "b") {
            system(CLEAR);
            const std::string subtiImport = "Buscar un Medico";
            std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

            gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
            std::cout << VB << Titulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
            std::cout << ARB << Subtitulo <<RTNC;
            gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
            std::cout << AB << subtiImport <<RTNC;

            std::string stringAux;

            gotoxy(3, 7);
            std::cout <<AQF<< "Ingresa el codigo del Medico a buscar: ";
            gotoxy(45, 7);
            std::cout<<AB; fflush(stdin);
            getline(std::cin, stringAux); std::cout<<RTNC;

            importarArchivo();
            int idx = miArchivoMedico.findData(stringAux);
            
            if (idx != -1) {
                Medico medicoAux = miArchivoMedico.getData(idx);

                // Imprime el Nombre del Medico
                gotoxy(3, 9);
                cout << ARB << "Nombre del Medico:";
                gotoxy(21, 9);
                cout << VF << medicoAux.getNombre().toString();

                // Imprime el Codigo del Medico
                gotoxy(3, 10);
                cout << ARB << "Codigo del Medico:";
                gotoxy(21, 10);
                cout << VF << medicoAux.getCodigo();

                // Imprime la Cedula del Medico
                gotoxy(3, 11);
                cout << ARB << "Cedula del Medico:";
                gotoxy(21, 11);
                cout << VF << medicoAux.getCedula();

                // Imprime la Hora de Entrada del Medico
                gotoxy(3, 12);
                cout << ARB << "Hora de Entrada del Medico:";
                gotoxy(30, 12);
                cout << VF << medicoAux.getHoraEntrada().toString();

                // Imprime la Hora de Salida del Medico
                gotoxy(3, 13);
                cout << ARB << "Hora de Salida del Medico:";
                gotoxy(29, 13);
                cout << VF << medicoAux.getHoraSalida().toString();

                pausa();

            } else {
                gotoxy(3, 9);
                std::cout <<RB<< "No se encontro un medico con ese codigo."<<RTNC; pausa();
            }
        } else if (opcBuscar == "X" or opcBuscar == "x") {
            return;
        } else {
            gotoxy(3, 21); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opcBuscar <<GB<< "\" no es una opcion valida..."<<RTNC; pausa();
        }
    } else {
        gotoxy(3, 16); std::cout << RB << "No existen archivos donde buscar al medico." << RTNC; pausa();
    }
}

void MenuMedicos::importarArchivo() {
    miArchivoMedico.importBackup();
}