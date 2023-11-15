#include "archivoMedico.h"

#include <fstream>
#include <cstdlib>
#include <sstream>

#include "Nombre.h"
#include "Hora.h"
#include "Medico.h"

using namespace std;

// Constructor
ArchivoMedico::ArchivoMedico() : nameFileMedico("archivoMedicos.txt"), indexNameFileMedico("archivoMedicosNombre.txt"),
indexCodeFileMedico("archivoMedicosCodigo.txt") {
    if (!std::ifstream(nameFileMedico)) {
        std::ofstream create(nameFileMedico);
        create.close();
    }
}

void ArchivoMedico::reIndex() {
    string myString;
    int myIndex;
    Medico miMedico;
    indexDuple<> miTupleCode;
    indexDuple<Nombre> miTupleName;

    archivo.open(nameFileMedico, ios_base::in);

    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::reIndex()");
    }

    indexadoPorCodigo.anular();
    indexadoPorNombre.anular();

    while (!archivo.eof()) {
        myIndex = int(archivo.tellg());
        getline(archivo, myString, '#');

        if (myString.empty()) {
            continue;
        }
        stringstream myStrString(myString);

        getline(myStrString, myString, '*');
        if (myString == "1") {
            myStrString >> miMedico;

            miTupleCode.setIndex(myIndex);
            miTupleCode.setData(miMedico.getCodigo());
            miTupleName.setIndex(myIndex);
            miTupleName.setData(miMedico.getNombre());

            indexadoPorCodigo.insertar(miTupleCode);
            indexadoPorNombre.insertar(miTupleName);
        }
    }
        // Se pasa la lista de Tuplas "Codigo" a su archivo.
        archivoPorCodigo.open(indexCodeFileMedico, ios_base::out | ios_base::trunc);
        if (!archivoPorCodigo.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::reIndex()");
        }
        
        archivoPorCodigo.clear();
        listToFile(indexadoPorCodigo, archivoPorCodigo);
        archivoPorCodigo.close();

        // Se pasa la lista de Tuplas "Nombre" a su archivo.
        archivoPorNombre.open(indexNameFileMedico, ios_base::out | ios_base::trunc);
        if (!archivoPorNombre.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::reIndex()");
        }

        archivoPorNombre.clear();
        listToFile(indexadoPorNombre, archivoPorNombre);
        archivoPorNombre.close();
        archivo.close();
}

// Destructor
ArchivoMedico::~ArchivoMedico() {
    if (archivo.is_open()) {
        archivo.close();
    }
    if (archivoPorNombre.is_open()) {
        archivoPorNombre.close();
    }
    if (archivoPorCodigo.is_open()) {
        archivoPorCodigo.close();
    }
}

template<class T>
Lista<T> ArchivoMedico::fileToList(std::fstream& myFStream, Lista<T> miLista) {
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
bool ArchivoMedico::listToFile(const Lista<T>& myLista, std::fstream & myFstream) {
    for (int i = 0; i < myLista.length(); i++) {
        myFstream << "1*" << myLista[i] << "#";
    }
    return true;
}

template<class T>
int ArchivoMedico::getIndex(const Lista<indexDuple<T>>& miLista, const T& e) const {
    for (int i = 0; i < miLista.length(); i++) {
        if (miLista[i].getData() == e) {
            return miLista[i].getIndex();
        }
    }
    return -1;
}

void ArchivoMedico::addData(const Medico & medicoToAdd) {
    /*archivoNombre.open(NombreArchivo, ios_base::out | ios_base::app);
    if (!archivoNombre.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para esrcitura.");
    }
    archivoNombre << "1*" << medicoToAdd << "#";
    archivoNombre.close();*/
    Lista<Medico> myList;
    myList.insertar(medicoToAdd);
    addData(myList);
}

void ArchivoMedico::addData(Lista<Medico>& myList) {
    archivo.open(nameFileMedico, ios_base::out | ios_base::app);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::addData()");
    }

    listToFile(myList, archivo);
    archivo.close();
    reIndex();
}

Medico ArchivoMedico::getData(const int & idx) {
    string myString;
    Medico miMedico;

    archivo.open(nameFileMedico);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::getData()");
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
    myStrString >> miMedico;

    archivo.close();
    return miMedico;
}

void ArchivoMedico::delData(const int& idx) {
    archivo.open(nameFileMedico, ios_base::in | ios_base::out);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::delData()");
    }

    archivo.seekp(idx);
    archivo << "0";
    archivo.close();

    reIndex();
}

int ArchivoMedico::findData(const string& code) const {
    return getIndex(indexadoPorCodigo, code);
}

int ArchivoMedico::findData(const Nombre& e) const {
    return getIndex(indexadoPorNombre, e);
}

Lista<Medico> ArchivoMedico::toList() {
    archivo.open(nameFileMedico, ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::toList()");
    }
    Lista<Medico> listaAux;
    listaAux = fileToList(archivo, listaAux);
    archivo.close();

    return listaAux;
}

void ArchivoMedico::clear() {
    remove(nameFileMedico.c_str());
}

void ArchivoMedico::compress() {
    string tempFileName = "temp.file";

    // Se renombra el archivo "archivoMedicos" a "temp.file".
    rename(nameFileMedico.c_str(), tempFileName.c_str());

    // Se abre el archivo original en modo escritura.
    archivo.open(nameFileMedico, ios_base::out | ios_base::trunc);

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

bool ArchivoMedico::existenDatos() {
    archivo.open(nameFileMedico, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedico::existenDatos()");
    }

    archivo.seekg(0, std::ios::end);
    bool existenDatos = (archivo.tellg() > 0);
    archivo.close();

    return existenDatos;
}

void ArchivoMedico::importBackup() {
    reIndex();
}
