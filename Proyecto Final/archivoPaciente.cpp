#include "archivoPaciente.h"

#include <fstream>
#include <cstdlib>
#include <sstream>

#include "Paciente.h"
#include "Nombre.h"
#include "Fecha.h"
#include "Domicilio.h"

/*#define NombreArchivo "archivoPacientes.txt"
#define archivoIndicePorNombre "archivoPacientesNombre.txt"
#define archivoIndicePorSeguroSocial "archivoPacientesSeguro.txt"
*/

ArchivoPaciente::ArchivoPaciente() : nameFilePacientes("archivoPacientes.txt"),
indexNameFilePaciente("archivoPacientesNombre.txt"), indexSeguroFilePaciente("archivoPacientesSeguro.txt") {
    if (!std::ifstream(nameFilePacientes)) {
        std::ofstream create(nameFilePacientes);
        create.close();
    }
}

ArchivoPaciente::~ArchivoPaciente() {
    if (archivo.is_open()) {
        archivo.close();
    }
    if (archivoPorNombre.is_open()) {
        archivoPorNombre.close();
    }
    if (archivoPorSeguroSocial.is_open()) {
        archivoPorSeguroSocial.close();
    }
}

void ArchivoPaciente::reIndex() {
    string myString;
    int myIndex;
    Paciente miPaciente;
    indexDuple<> miTupleSeguro;
    indexDuple<Nombre> miTupleName;

    archivo.open(nameFilePacientes, ios_base::in);

    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::reIndex()");
    }

    indexadoPorNombre.anular();
    indexadoPorSeguro.anular();

    while (!archivo.eof()) {
        myIndex = int(archivo.tellg());
        getline(archivo, myString, '#');

        if (myString.empty()) {
            continue;
        }
        stringstream myStrString(myString);

        getline(myStrString, myString, '*');
        if (myString == "1") {
            myStrString >> miPaciente;

            miTupleSeguro.setIndex(myIndex);
            miTupleSeguro.setData(miPaciente.getNumSeguroSocial());
            miTupleName.setIndex(myIndex);
            miTupleName.setData(miPaciente.getNombre());

            indexadoPorSeguro.insertar(miTupleSeguro);
            indexadoPorNombre.insertar(miTupleName);
        }
    }
        // Se pasa la lista de Tuplas "Codigo" a su archivo.
        archivoPorSeguroSocial.open(indexSeguroFilePaciente, ios_base::out | ios_base::trunc);
        if (!archivoPorSeguroSocial.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::reIndex()");
        }
        
        archivoPorSeguroSocial.clear();
        listToFile(indexadoPorSeguro, archivoPorSeguroSocial);
        archivoPorSeguroSocial.close();

        // Se pasa la lista de Tuplas "Nombre" a su archivo.
        archivoPorNombre.open(indexNameFilePaciente, ios_base::out | ios_base::trunc);
        if (!archivoPorNombre.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::reIndex()");
        }

        archivoPorNombre.clear();
        listToFile(indexadoPorNombre, archivoPorNombre);
        archivoPorNombre.close();
        archivo.close();
}

template<class T>
Lista<T> ArchivoPaciente::fileToList(std::fstream& myFStream, Lista<T> miLista) {
    string myStr;
    T data;

    while (!myFStream.eof()) {
        getline(myFStream, myStr, '#');
        
        if (myStr.empty()) { continue; }

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
bool ArchivoPaciente::listToFile(const Lista<T>& myLista, std::fstream & myFstream) {
    clear();
    for (int i = 0; i < myLista.length(); i++) {
        myFstream << "1*" << myLista[i] << "#";
    }
    return true;
}

template<class T>
int ArchivoPaciente::getIndex(const Lista<indexDuple<T>>& miLista, const T& e) const {
    for (int i = 0; i < miLista.length(); i++) {
        if (miLista[i].getData() == e) {
            return miLista[i].getIndex();
        }
    }
    return -1;
}

void ArchivoPaciente::addData(const Paciente & pacienteToAdd) {
    Lista<Paciente> myList;
    myList.insertar(pacienteToAdd);
    addData(myList);
}

void ArchivoPaciente::addData(Lista<Paciente>& myList) {
    archivo.open(nameFilePacientes, ios_base::out | ios_base::app);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::addData()");
    }

    listToFile(myList, archivo);
    archivo.close();
    reIndex();

}

Paciente ArchivoPaciente::getData(const int & idx) {
    string myString;
    Paciente miPaciente;

    archivo.open(nameFilePacientes);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::getData()");
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
    myStrString >> miPaciente;

    archivo.close();
    return miPaciente;
}

void ArchivoPaciente::delData(const int& idx) {
    archivo.open(nameFilePacientes, ios_base::in | ios_base::out);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::delData()");
    }

    archivo.seekp(idx);
    archivo << "0";
    archivo.close();

    reIndex();
}

int ArchivoPaciente::findData(const string& code) const {
    return getIndex(indexadoPorSeguro, code);
}

int ArchivoPaciente::findData(const Nombre& e) const {
    return getIndex(indexadoPorNombre, e);
}

Lista<Paciente> ArchivoPaciente::toList() {
    archivo.open(nameFilePacientes, ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::toList()");
    }
    Lista<Paciente> listaAux;
    listaAux = fileToList(archivo, listaAux);
    archivo.close();

    return listaAux;
}

void ArchivoPaciente::clear() {
    remove(nameFilePacientes.c_str());
}

void ArchivoPaciente::compress() {
    string tempFileName = "temp.file";

    // Se renombra el archivo "archivoMedicos" a "temp.file".
    rename(nameFilePacientes.c_str(), tempFileName.c_str());

    // Se abre el archivo original en modo escritura.
    archivo.open(nameFilePacientes, ios_base::out | ios_base::trunc);

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

    // Se hace un reIndex del archivo.
    reIndex();
}

bool ArchivoPaciente::existenDatos() {
    archivo.open(nameFilePacientes, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoPaciente::existenDatos()");
    }

    archivo.seekg(0, std::ios::end);
    bool existenDatos = (archivo.tellg() > 0);
    archivo.close();

    return existenDatos;
}

void ArchivoPaciente::cargarDatos() {
    reIndex();
}
