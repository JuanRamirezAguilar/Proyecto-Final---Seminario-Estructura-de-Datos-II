#include "fileMaster.h"

#include "ArchivoConsulta.h"

#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include "standarLibrary.h"
#include "Paciente.h"
#include "Nombre.h"
#include "Fecha.h"
#include "Domicilio.h"
#include "Hora.h"
#include "Medico.h"
#include "Diagnostico.h"
#include "Medicamento.h"
#include "Consulta.h"

FileMaster::FileMaster() {}
FileMaster::~FileMaster() {}

Lista<Consulta> FileMaster::getMisConsultas() {return misConsultas;}
Lista<Medico> FileMaster::getMisMedicos() {return misMedicos;}

Lista<Consulta> FileMaster::importBackup(const std::string& nombreArchivo) {
    ArchivoMedico miArchivoMedico;
    ArchivoPaciente miArchivoPaciente;
    archivoMedicamento miArchivoMedicamento;
    ArchivoDiagnostico miArchivoDiagnostico;
    ArchivoConsulta miArchivoConsulta;

    std::ifstream archivoEntrada;
    archivoEntrada.open(nombreArchivo, std::ios::in);   
    if (!archivoEntrada) {
        throw std::runtime_error("Error al abrir el archivo fileMaster::importBackup()");
    }

    std::string miCampo;
    while(!archivoEntrada.eof()) {

        std::getline(archivoEntrada, miCampo, '#');
        if (miCampo.empty()) { continue; }

        // Se instancian las clases necesarias
        Nombre miNombre;
        Fecha miFecha;
        Hora miHora;
        Domicilio miDomicilio;
        Paciente miPaciente;
        Medico miMedico;
        Medicamento miMedicamento;
        Diagnostico miDiagnostico;
        Consulta miConsulta;

        std::stringstream flujoDeRegistro(miCampo);

        // Toma la fecha de la consulta
        flujoDeRegistro >> miFecha;
        miConsulta.setFecha(miFecha);
        
        // Toma la hora de la consulta
        flujoDeRegistro >> miHora;
        miConsulta.setHora(miHora);

        // Toma el Diagnostico de la consulta
        flujoDeRegistro >> miDiagnostico;
        miConsulta.setDiagnostico(miDiagnostico);
        if (!misDiagnosticos.buscar(miDiagnostico)) {
            misDiagnosticos.insertar(miDiagnostico);
        }

        // Toma la Indicacion de la consulta
        getline(flujoDeRegistro, miCampo, '*');
        miConsulta.setIndicacion(miCampo);

        // Toma el Medico de la consulta;
        flujoDeRegistro >> miMedico;
        miConsulta.setMedico(miMedico);
        if (!misMedicos.buscar(miMedico)) {
            misMedicos.insertar(miMedico);
        }
        
        // Toma el Paciente de la consulta;
        flujoDeRegistro >> miPaciente;
        miConsulta.setPaciente(miPaciente);
        if (!misPacientes.buscar(miPaciente)) {
            misPacientes.insertar(miPaciente);
        }

        // Toma el Medicamento de la consulta;
        flujoDeRegistro >> miMedicamento;
        miConsulta.setMedicamento1(miMedicamento);
        if (!misMedicamentos.buscar(miMedicamento)) {
            misMedicamentos.insertar(miMedicamento);
        }
        flujoDeRegistro >> miMedicamento;
        miConsulta.setMedicamento2(miMedicamento);
        if (!misMedicamentos.buscar(miMedicamento)) {
            misMedicamentos.insertar(miMedicamento);
        }
        flujoDeRegistro >> miMedicamento;
        miConsulta.setMedicamento3(miMedicamento);
        if (!misMedicamentos.buscar(miMedicamento)) {
            misMedicamentos.insertar(miMedicamento);
        }

        // Se ingresa en la lista
        if (!misConsultas.buscar(miConsulta)) {
            misConsultas.insertar(miConsulta);
        }
    }
    
    miArchivoMedico.addData(misMedicos);
    miArchivoPaciente.addData(misPacientes);
    miArchivoMedicamento.addData(misMedicamentos);
    miArchivoDiagnostico.addData(misDiagnosticos);
    miArchivoConsulta.addData(misConsultas);
    archivoEntrada.close();

    gotoxy(3, 21);
    cout << "Numero de registros importados: " << misConsultas.get_tam() << ".";
    gotoxy(3, 22);
    cout << "Numero de diagnosticos importados: " << misDiagnosticos.get_tam() << ".";
    gotoxy(3, 23);
    cout << "Numero de medicos importados: " << misMedicos.get_tam() << ".";
    gotoxy(3, 24);
    cout << "Numero de pacientes importados: " << misPacientes.get_tam() << ".";
    gotoxy(3, 25);
    cout << "Numero de medicamentos importados: " << misMedicamentos.get_tam() << ".";

    return misConsultas;
}

void FileMaster::exportBackup() {
    fstream archivoOrigen, archivoImporte;
    archivoOrigen.open("archivoConsulta.txt", ios_base::in);
    archivoImporte.open("import_file_consultas.file", ios_base::out);

    if (!archivoOrigen.is_open() and !archivoImporte.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en FileMaster::exportBackup");
    }

    string myString;

    while (!archivoOrigen.eof()) {
        std::getline(archivoOrigen, myString, '#');

        if (myString.empty()) {
            continue;
        }

        stringstream myStrString(myString);

        getline(myStrString, myString, '*');
        if (myString == "1") {
            getline(myStrString, myString);
            archivoImporte << myString << "#";
        }
    }
    archivoOrigen.close();
    archivoImporte.close();
}
