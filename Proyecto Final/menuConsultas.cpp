#include "menuConsultas.h"

#include "StandarLibrary.h"
#include "Colores.h"
#include "archivoDiagnostico.h"
#include "archivoMedico.h"
#include "archivoPaciente.h"
#include "archivoMedicamento.h"

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
const std::string Subtitulo = "Menu de Consultas";

MenuConsultas::MenuConsultas() : opc("x") {}
MenuConsultas::~MenuConsultas() {}

void MenuConsultas::setOpc(std::string valorOpc) { opc = valorOpc; }

std::string MenuConsultas::getOpc() { return opc; }

void MenuConsultas::menu() {
    std::string opciones;
    do {
        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARF << Subtitulo <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB; std::cout << "Opciones del Menu:";
        gotoxy(3, 9);
        std::cout <<ARB; std::cout << "Agregar una consulta." << GB "     [ " <<RF<< "A" << GB " ]";
        gotoxy(3, 10);
        std::cout <<ARB; std::cout << "Elimnar una consulta." << GB "     [ " <<RF<< "B" <<GB " ]";
        gotoxy(3, 11);
        std::cout <<ARB; std::cout << "Mostrar Consultas." << GB "        [ " <<RF<< "C" <<GB " ]";
        gotoxy(3, 12);
        std::cout <<ARB; std::cout << "Regresar al menu anterior." << GB "[ " <<RF<< "X" <<GB " ]";

        gotoxy(3, 15);
        std::cout <<GB << "Tu opcion ==> ";
        gotoxy(18, 15);
        std::cout <<RF; std::getline(std::cin, opciones); setOpc(opciones); std::cout <<RTNC;

        if (opc == "A" or opc == "a") { agregar(); }
        else if (opc == "B" or opc == "b") { eliminar(); }
        else if (opc == "C" or opc == "c") { imprimir(); }
        else if (opc == "X" or opc == "x") { return; }
        else { gotoxy(3, 17); std::cout <<GB; std::cout << "La opcion: \"" <<RB<< opc <<GB<< "\" no es una opcion valida..."<<RTNC; pausa(); }

    } while (opc != "X" and opc != "x");
}

void MenuConsultas::agregar() {
    ArchivoDiagnostico archivoDiagnostico;
    ArchivoMedico archivoMedico;
    ArchivoPaciente archivoPaciente;
    archivoMedicamento archivoMedicamento;

    if (!archivoDiagnostico.existenDatos() or !archivoMedico.existenDatos() or !archivoPaciente.existenDatos() or !archivoMedicamento.existenDatos()) {
        gotoxy(3, 17);
        std::cout <<RB; std::cout << "No existen datos para ingresar a la consulta."<<RTNC;
        gotoxy(3, 18);
        std::cout <<RB; std::cout << "Por favor, antes ingrese médicos, diagnosticos, pacientes, medicamentos al programa."<<RTNC; pausa();
    } else {
        const std::string subtiImport = "Agregar Consulta";
        
        Fecha nuevaFecha;
        Hora nuevaHora;
        std::string nuevaIndicacion;

        system(CLEAR);
        std::cout<<MF; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

        gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
        std::cout << VB << Titulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
        std::cout << ARF << Subtitulo <<RTNC;
        gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
        std::cout << AB << subtiImport <<RTNC;

        gotoxy(3, 7);
        std::cout <<GB; std::cout << "Agregar una consulta al archivo."<<RTNC;

        // Se ingresa la fecha de la consulta.
        bool fechaValida = false;
        while (!fechaValida) {

            int auxDia, auxMes, auxAnio;

            gotoxy(3, 9);
            std::cout << ARB << "Dame la fecha de la consulta:" <<RTNC;
            gotoxy(40, 9); std::cout << "/"; gotoxy(46, 9); std::cout << "/";

            gotoxy(36, 8); std::cout << "Dia";
            gotoxy(42, 8); std::cout << "Mes";
            //gotoxy(49, 8); std::cout << "A" << char(164)  << "o";
            gotoxy(49, 8); std::cout << "Año";

            cout << VB;
            gotoxy(36, 9); cin >> auxDia;
            gotoxy(42, 9); cin >> auxMes;
            gotoxy(49, 9); cin >> auxAnio;
            cout << RTNC;

            if (!nuevaFecha.diaEsValido(auxMes, auxDia) or !nuevaFecha.mesEsValido(auxMes) or !nuevaFecha.anioEsValido(auxAnio)) {
                gotoxy(3, 11);
                std::cout << RB << "La fecha introducida no es valida intentalo de nuevo" <<RTNC; pausa();
                borrarPantalla(3, 8, 12);
            } else {
                fechaValida = true;
                nuevaFecha.setDia(auxDia); nuevaFecha.setMes(auxMes); nuevaFecha.setAnio(auxAnio);
            }
        }

        // Se ingresa la hora de la consulta.
        bool horaValida = false;
        while (!horaValida) {
            int auxMin, auxHora;

            gotoxy(3, 11);
            std::cout << ARB << "Dame la hora de la consulta:" <<RTNC;

            gotoxy(32, 10); std::cout << "HH";
            gotoxy(35, 11); std::cout << ":";
            gotoxy(37, 10); std::cout << "MM";
            
            cout << VB;
            gotoxy(32, 11); cin >> auxHora;
            gotoxy(37, 11); cin >> auxMin;
            nuevaHora.setHora(auxHora); nuevaHora.setMinuto(auxMin);
            cout << RTNC;

            if (!nuevaHora.esHoraValida()) {
                gotoxy(3, 13);
                std::cout << RB << "La hora introducida no es valida intentalo de nuevo" <<RTNC; pausa();
                borrarPantalla(3, 11, 13);
            } else {
                horaValida = true;
            }
        }

        // Se ingresa el diagnostico de la consulta.
        archivoDiagnostico.cargarDatos();

        bool diagnosticoValido = false;
        Diagnostico diagvalido;
        while (!diagnosticoValido) {
            gotoxy(3, 13);
            std::string codigoDiagnostico;
            cout << ARB << "Dame el codigo del diagnostico a agregar: " <<RTNC;
            
            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoDiagnostico);
            cout << RTNC;

            int idx = archivoDiagnostico.findData(codigoDiagnostico);
            if (idx != -1) {
                diagvalido = archivoDiagnostico.getData(idx);
                borrarPantalla(3, 13, 15);

                gotoxy(3, 13);
                cout << ARB << "Se va a agregar este diagnostico." <<RTNC;
                gotoxy(3, 14);
                cout << VB << diagvalido.getDescripcion() <<RTNC;
                diagnosticoValido = true;
            } else {
                gotoxy(3, 15);
                cout << RB << "El codigo del diagnostico no es valido, vuelvelo a intentar." <<RTNC;
                pausa();
                borrarPantalla(3, 13, 15);
            }
        }

        // Se ingresa el médico de la consulta.
        archivoMedico.importBackup();

        bool medicoValido = false;
        Medico medicoShow;
        while (!medicoValido) {
            gotoxy(3, 16);
            std::string codigoMed;
            cout << ARB << "Dame el codigo del medico a agregar a la consulta: " <<RTNC;

            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoMed);
            cout << RTNC;

            int idx = archivoMedico.findData(codigoMed);
            if (idx != -1) {
                medicoShow = archivoMedico.getData(idx);
                borrarPantalla(3, 16, 17);
                gotoxy(3, 16);
                cout << ARB << "Se va a agregar este medico." <<RTNC;
                gotoxy(3, 17);
                cout << VB << "Nombre: " << medicoShow.getNombre().toString() << ", ";
                cout << "Cedula: " << medicoShow.getCedula() << ", " << "Hora de entrada: " << medicoShow.getHoraEntrada().toString() <<RTNC;
                medicoValido = true;
            } else {
                gotoxy(3, 18);
                cout << RB << "El codigo del medico no es valido, vuelvelo a intentar." <<RTNC; pausa();
                borrarPantalla(3, 16, 18);
            }
        }

        // Se ingresa el paciente de la consulta.
        archivoPaciente.cargarDatos();

        bool pacienteValido = false;
        Paciente pacShow;
        while (!pacienteValido) {
            gotoxy(3, 19);
            std::string codigoPac;
            cout << ARB << "Dame el codigo del paciente a agregar a la consulta: " <<RTNC;

            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoPac);
            cout << RTNC;

            int idx = archivoPaciente.findData(codigoPac);
            if (idx != -1) {
                pacShow = archivoPaciente.getData(idx);
                borrarPantalla(3, 19, 19);
                gotoxy(3, 19);
                cout << ARB << "Se va a agregar este paciente." <<RTNC;
                gotoxy(3, 20);
                cout << VB << "Nombre: " << pacShow.getNombre().toString() << ", ";
                cout << VB << "NSS: " << pacShow.getNumSeguroSocial() << ", ";
                cout << VB << "Fecha Nacimiento: " << pacShow.getFechaDeNacimiento().toString() <<RTNC;
                pacienteValido = true;
            } else {
                gotoxy(3, 21);
                cout << RB << "El codigo del paciente no es valido, vuelvelo a intentar." <<RTNC; pausa();
                borrarPantalla(3, 19, 21);
            }
        }

        // Se ingresa el medicamento1 de la consulta.
        archivoMedicamento.cargarDatos();
        bool medicamentoValido = false;
        Medicamento mediShow1, mediShow2, mediShow3;
        while (!medicamentoValido) {
            gotoxy(3, 22);
            std::string codigoMedicamento1, codigoMedicamento2, codigoMedicamento3;
            cout << ARB << "Dame los codigos de los medicamentos a agregar a la consulta (Si no quieres agregar alguno, ingresa \"X\")" <<RTNC;
            gotoxy(3, 23);
            cout << ARB << "Codigos: " << RTNC;

            gotoxy(13, 23);
            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoMedicamento1);
            cout << RTNC;

            gotoxy(23, 23);
            cout << ARB << "," << RTNC;

            gotoxy(25, 23);
            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoMedicamento2);
            cout << RTNC;

            gotoxy(35, 23);
            cout << ARB << "," << RTNC;

            gotoxy(37, 23);
            cout << VB;
            fflush(stdin);
            std::getline(cin, codigoMedicamento3);
            cout << RTNC;

            int idx1 = (codigoMedicamento1 != "X") ? archivoMedicamento.findData(codigoMedicamento1) : -1;
            int idx2 = (codigoMedicamento2 != "X") ? archivoMedicamento.findData(codigoMedicamento2) : -1;
            int idx3 = (codigoMedicamento3 != "X") ? archivoMedicamento.findData(codigoMedicamento3) : -1;

            if ((idx1 != -1 || codigoMedicamento1 == "X") &&
            (idx2 != -1 || codigoMedicamento2 == "X") &&
            (idx3 != -1 || codigoMedicamento3 == "X")) {

                if (codigoMedicamento1 != "X") {
                    mediShow1 = archivoMedicamento.getData(idx1);
                }

                if (codigoMedicamento2 != "X") {
                    mediShow2 = archivoMedicamento.getData(idx2);
                }

                if (codigoMedicamento3 != "X") {
                    mediShow3 = archivoMedicamento.getData(idx3);
                }

                borrarPantalla(3, 22, 23);

                gotoxy(3, 22);
                cout << ARB << "Se va a agregar este medicamento." <<RTNC;
                gotoxy(3, 23);
                cout << VB << "Nombre del medicamento: " << mediShow1.getNombre() << "." <<RTNC;
                gotoxy(3, 24);
                cout << VB << "Nombre del medicamento: " << mediShow2.getNombre() << "." <<RTNC;
                gotoxy(3, 25);
                cout << VB << "Nombre del medicamento: " << mediShow3.getNombre() << "." <<RTNC;
                medicamentoValido = true;
            } else {
                gotoxy(3, 24);
                cout << RB << "El codigo del medicamento no es valido, vuelvelo a intentar." <<RTNC; pausa();
                borrarPantalla(3, 22, 24);
            }
        }

        // Se agrega la indicacion de la consulta.
        gotoxy(3, 27);
        cout << ARB << "Dame la indicacion de la consulta: " <<RTNC;

        cout << VB;
        fflush(stdin);
        getline(cin, nuevaIndicacion);
        cout << RTNC;

        Consulta nuevaConsulta(nuevaFecha, nuevaHora, nuevaIndicacion, pacShow, medicoShow, diagvalido, mediShow1, mediShow2, mediShow3);
        archivo.addData(nuevaConsulta);

        gotoxy(3, 29);
        cout << VF << "Consulta agregada con exito: " <<RTNC; pausa();
    }
}

void MenuConsultas::eliminar() {
    const std::string subtiImport = "Eliminar Consulta";
    std::string nss;
    Consulta consultaAEliminar;

    system(CLEAR);
    std::cout<<MB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARB << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    gotoxy(3, 7);
    cout << ARB << "Borrar una consulta" <<RTNC;

    Fecha miFecha;
    bool fechaValida = false;
    while (!fechaValida) {
        int auxDia, auxMes, auxAnio;

        gotoxy(3, 9);
        std::cout << ARB << "Dame la fecha de la consulta:" <<RTNC;
        gotoxy(40, 9); std::cout << "/"; gotoxy(46, 9); std::cout << "/";

        gotoxy(36, 8); std::cout << "Dia";
        gotoxy(42, 8); std::cout << "Mes";
        gotoxy(49, 8); std::cout << "Año";

        cout << VB;
        gotoxy(36, 9); cin >> auxDia;
        gotoxy(42, 9); cin >> auxMes;
        gotoxy(49, 9); cin >> auxAnio;
        cout << RTNC;

        if (!miFecha.diaEsValido(auxMes, auxDia) or !miFecha.mesEsValido(auxMes) or !miFecha.anioEsValido(auxAnio)) {
            gotoxy(3, 11);
            std::cout << RB << "La fecha introducida no es valida intentalo de nuevo" <<RTNC; pausa();
            borrarPantalla(3, 8, 12);
        } else {
            fechaValida = true;
            miFecha.setDia(auxDia); miFecha.setMes(auxMes); miFecha.setAnio(auxAnio);
        }
    }

    Hora miHora;
    bool horaValida = false;
    while (!horaValida) {
        int auxMin, auxHora;

        gotoxy(3, 11);
        std::cout << ARB << "Dame la hora de la consulta:" <<RTNC;

        gotoxy(32, 10); std::cout << "HH";
        gotoxy(35, 11); std::cout << ":";
        gotoxy(37, 10); std::cout << "MM";
            
        cout << VB;
        gotoxy(32, 11); cin >> auxHora;
        gotoxy(37, 11); cin >> auxMin;
        miHora.setHora(auxHora); miHora.setMinuto(auxMin);
        cout << RTNC;

        if (!miHora.esHoraValida()) {
            gotoxy(3, 13);
            std::cout << RB << "La hora introducida no es valida intentalo de nuevo" <<RTNC; pausa();
            borrarPantalla(3, 11, 13);
        } else {
            horaValida = true;
        }
    }

    gotoxy(3, 13);
    std::cout << ARB << "Dame el numero del seguro social del paciente:" <<RTNC;
    gotoxy(50, 13);
    cout << VB;
    fflush(stdin);
    std::getline(cin, nss);
    cout<<RTNC;

    consultaAEliminar.setFecha(miFecha);
    consultaAEliminar.setHora(miHora);
    consultaAEliminar.getPaciente().setNumSeguroSocial(nss);

    std::string opcBorrar;
    int idx = archivo.findData(consultaAEliminar);
    if (idx != -1) {
        Consulta mostrarConsulta = archivo.getData(idx);

        gotoxy(3, 15);
        std::cout << ARB << "Datos de la consulta:" <<RTNC;
        gotoxy(3, 16);
        std::cout << ARB << "Paciente: " << AB << mostrarConsulta.getPaciente().toString() <<RTNC;
        gotoxy(3, 17);
        std::cout << ARB << "Médico: " << AB << mostrarConsulta.getMedico().toString() <<RTNC;
        gotoxy(3, 18);
        std::cout << ARB << "Diagnostico: " << AB << mostrarConsulta.getDiagnostico().toString() <<RTNC;

        gotoxy(3, 20);
        std::cout << ARB << "Quieres borrar la consulta." <<RTNC;
        gotoxy(3, 21);
        std::cout << ARB << "Si." << GB"  [ " <<RF<< "Y" <<GB " ]";
        gotoxy(3, 22);
        std::cout << ARB << "No." << GB"  [ " <<RF<< "N" <<GB " ]";
        gotoxy(3, 22);
        std::cout <<ARB << "Tu opcion ==> ";
        
        gotoxy(18, 22);
        fflush(stdin);
        std::cout<<RB;
        std::getline(cin, opcBorrar);
        std::cout<<RTNC;
        
        if (opcBorrar == "Y" or opcBorrar == "y") {
            archivo.delData(idx);
            archivo.compress();
            gotoxy(3, 24);
            std::cout <<VB<< "Consulta eliminada correctamente."<<RTNC; pausa();
        } else if(opcBorrar == "N" or opcBorrar == "n" or opcBorrar != "Y" or opcBorrar != "y") {
            gotoxy(3, 24);
            std::cout << RB << "Opcion invalida o elegiste \"N\", Saliendo de eliminar medico..." <<RTNC; timeStop(1000);
        }
    } else {
        gotoxy(3, 15);
        std::cout << RB << "No se encontro una consulta con esos datos." <<RTNC; pausa();
    }
}

void MenuConsultas::imprimir() {
    const std::string subtiImport = "Imprimir todo";
    archivo.cargarDatos();
    Lista<Consulta> consultas = archivo.getConsultas();
    std::cout << "Tamaño de la lista: " << consultas.get_tam() << "." <<endl;

    system(CLEAR);
    std::cout<<ARB; setborder(ALTURA_BORDE, ANCHURA_BORDE); std::cout<<RTNC;

    gotoxy(((ANCHURA_BORDE - int(Titulo.length())) / 2), 3);
    std::cout << VB << Titulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(Subtitulo.length())) / 2), 4);
    std::cout << ARB << Subtitulo <<RTNC;
    gotoxy(((ANCHURA_BORDE - int(subtiImport.length())) / 2), 5);
    std::cout << AB << subtiImport <<RTNC;

    system(CLEAR);
    for (int i = 0; i < consultas.length(); i++) {
        std::cout <<VB<< i + 1 << ")._ " <<RTNC<<std::endl;
        std::cout <<AF<< "Nombre Paciente: " << GB << consultas[i].getPaciente().getNombre().toString() <<RTNC<<std::endl;
        std::cout <<ARF<< "Nombre del Medico: " << GB << consultas[i].getMedico().getNombre().toString() <<RTNC<<std::endl<<std::endl;
    }
    std::cout <<GB<< std::endl << "Presiona Enter para continuar..."; std::cout<<RTNC; pausa();
}
