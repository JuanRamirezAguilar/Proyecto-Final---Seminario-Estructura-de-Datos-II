#include "archivoConsulta.h"

#include <fstream>
#include <cstdlib>
#include <sstream>

#include "Paciente.h"
#include "Nombre.h"
#include "Fecha.h"
#include "Domicilio.h"
#include "Hora.h"
#include "Medico.h"
#include "Diagnostico.h"
#include "Medicamento.h"
#include "Consulta.h"

#include "archivoDiagnostico.h"

#include "ArchivoMedico.h"

#define NAMEFILE "archivoConsulta.txt"

ArchivoConsulta::ArchivoConsulta() : nameFileConsulta(NAMEFILE) {
    if (!std::ifstream(NAMEFILE)) {
        std::ofstream create(NAMEFILE);
        create.close();
    }
}

ArchivoConsulta::~ArchivoConsulta() {
    if (archivo.is_open()) {
        archivo.close();
    }
}

template<class T>
Lista<T> ArchivoConsulta::fileToList(std::fstream& myFStream, Lista<T> miLista) {
    string myStr;
    T data;

    int i = 1;
    while (getline(myFStream, myStr, '#')) {
        
        if (myStr.empty()) { continue; }
        std::cout << i++ << ") Leyendo: " << myStr << std::endl;
        stringstream myStringStream(myStr);

        getline(myStringStream, myStr, '*');

        if (myStr == "1") {
            myStringStream >> data;
            miLista.insertar(data);
        }
    }

    return miLista;
}

template<class T>
bool ArchivoConsulta::listToFile(const Lista<T>& myLista, std::fstream & myFstream) {
    for (int i = 0; i < myLista.length(); i++) {
        myFstream << "1*" << myLista[i] << "#";
    }
    return true;
}

int ArchivoConsulta::getIndex(const Consulta & c) {
    archivo.open(nameFileConsulta, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::getIndex()");
    }

    while (!archivo.eof()) {
        Consulta miConsulta;
        std::string myString;

        std::streampos idx = archivo.tellg();
        std::getline(archivo, myString, '#');
        if (myString.empty()) { continue; }

        std::stringstream mySString(myString);

        mySString >> miConsulta;
        if (miConsulta == c) {
            archivo.close();
            return int(idx);
        }
    }
    archivo.close();
    return -1;
}

void ArchivoConsulta::addData(const Consulta & consultaToAdd) {
    Lista<Consulta> myList;
    myList.insertar(consultaToAdd);
    addData(myList);
}

void ArchivoConsulta::addData(Lista<Consulta>& myList) {
    archivo.open(nameFileConsulta, ios_base::out | ios_base::app);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::addData()");
    }

    listToFile(myList, archivo);
    archivo.close();
}

Consulta ArchivoConsulta::getData(const int & idx) {
    string myString;
    Consulta miConsulta;

    archivo.open(nameFileConsulta);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::getData()");
    }

    archivo.seekg(idx);
    getline(archivo, myString, '#');
    if (myString.empty()) {
        throw ios_base::failure("Dato inexistente.");
    }

    stringstream myStrString(myString);
    getline(myStrString, myString, '*');
    if (myString == "0") {
        throw ios_base::failure("Dato borrado.");
    }
    myStrString >> miConsulta;

    archivo.close();
    return miConsulta;
}

void ArchivoConsulta::delData(const int& idx) {
    archivo.open(nameFileConsulta, ios_base::in | ios_base::out);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::delData()");
    }

    archivo.seekp(idx);
    archivo << "0";
    archivo.close();
}

int ArchivoConsulta::findData(const Consulta & c) {
    return getIndex(c);
}

Lista<Consulta> ArchivoConsulta::toList() {
    archivo.open(nameFileConsulta, ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::toList()");
    }
    Lista<Consulta> listaAux;
    listaAux = fileToList(archivo, listaAux);
    archivo.close();

    return listaAux;
}

void ArchivoConsulta::clear() {
    remove(nameFileConsulta.c_str());
}

void ArchivoConsulta::compress() {
    string tempFileName = "temp.file";

    // Se renombra el archivo "archivoMedicos" a "temp.file".
    rename(nameFileConsulta.c_str(), tempFileName.c_str());

    // Se abre el archivo original en modo escritura.
    archivo.open(nameFileConsulta, ios_base::out | ios_base::trunc);

    // Se abre el archivo temporal en modo lectura.
    ifstream tempFile(tempFileName.c_str());

    // Revisa si ninguno de los archivos se abrió correctamente.
    if (!tempFile.is_open() or !archivo.is_open()) {
        throw ios_base::failure("Error al abrir el archivo.");
    }

    string myString;
    // Bucle para obtener todos los registros del archivo temporal.
    while (getline(tempFile, myString, '#')) {
        // Si el registro tiene un 0 al inicio, no se toma en cuenta.
        if (myString.empty() or myString[0] == '0') {
            continue;
        }
        // Se vuelve a escribir el dato que sí es válido en el archivo original.
        archivo << myString << "#";
    }

    // Se cierran ambos archivos.
    tempFile.close();
    archivo.close();

    // Se elimina el archivo temporal.
    remove(tempFileName.c_str());

}

Lista<Consulta> ArchivoConsulta::getConsultas() {
    return miListaDeConsultas;
}

bool ArchivoConsulta::existenDatos() {
    archivo.open(nameFileConsulta, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoConsulta::existenDatos()");
    }

    archivo.seekg(0, std::ios::end);
    bool existenDatos = (archivo.tellg() > 0);
    archivo.close();

    return existenDatos;
}

void ArchivoConsulta::cargarDatos() {
    archivo.open(NAMEFILE, std::ios_base::in);
    std::cout << "Se va a empezar a leer el archivo." <<std::endl; std::cin.ignore();
    if (!archivo.is_open()) {
        throw std::ios_base::failure("Error al abrir el archivo en ArchivoConsulta::cargarDatos()");
    }
    miListaDeConsultas = fileToList(archivo, miListaDeConsultas);
    std::cout << "Se termino de leer el archivo." <<std::endl; std::cin.ignore();
    archivo.close();
}
