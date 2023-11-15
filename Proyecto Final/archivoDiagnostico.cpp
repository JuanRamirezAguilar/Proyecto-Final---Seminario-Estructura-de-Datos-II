#include "archivoDiagnostico.h"

#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream>

ArchivoDiagnostico::ArchivoDiagnostico() : nameFileDiagnostico("archivoDiagnosticos.txt"), indexCodeFileDiagnostico("archivoDiagnosticosCodigo.txt"),
indexDescripcionFileDiagnostico("archivoDiagnosticosDescripcion.txt") {
    if (!std::ifstream(nameFileDiagnostico)) {
        std::ofstream create(nameFileDiagnostico);
        create.close();
    }
}

ArchivoDiagnostico::~ArchivoDiagnostico() {
    if (archivo.is_open()) {
        archivo.close();
    }
    if (archivoPorCodigo.is_open()) {
        archivoPorCodigo.close();
    }
    if (archivoPorDescripcion.is_open()) {
        archivoPorDescripcion.close();
    }
}

void ArchivoDiagnostico::reIndex() {
    string myString;
    int myIndex;
    Diagnostico miDiagnostico;
    indexDuple<> miTupleCode;
    indexDuple<> miTupleDescripcion;

    archivo.open(nameFileDiagnostico, ios_base::in);

    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::reIndex()");
    }

    indexadoPorCodigo.anular();
    indexadoPorDescripcion.anular();
    misDiagnosticos.anular();

    while (!archivo.eof()) {
        myIndex = int(archivo.tellg());
        getline(archivo, myString, '#');

        if (myString.empty()) {
            continue;
        }
        stringstream myStrString(myString);

        getline(myStrString, myString, '*');
        if (myString == "1") {
            myStrString >> miDiagnostico;

            miTupleCode.setIndex(myIndex);
            miTupleCode.setData(miDiagnostico.getCodigo());
            miTupleDescripcion.setIndex(myIndex);
            miTupleDescripcion.setData(miDiagnostico.getDescripcion());

            misDiagnosticos.insertar(miDiagnostico);

            indexadoPorCodigo.insertar(miTupleCode);
            indexadoPorDescripcion.insertar(miTupleDescripcion);
        }
    }
        // Se pasa la lista de Tuplas "Codigo" a su archivo.
        archivoPorCodigo.open(indexCodeFileDiagnostico, ios_base::out | ios_base::trunc);
        if (!archivoPorCodigo.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::reIndex()");
        }
        
        archivoPorCodigo.clear();
        listToFile(indexadoPorCodigo, archivoPorCodigo);
        archivoPorCodigo.close();

        // Se pasa la lista de Tuplas "Descripcion" a su archivo.
        archivoPorDescripcion.open(indexDescripcionFileDiagnostico, ios_base::out | ios_base::trunc);
        if (!archivoPorDescripcion.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::reIndex()");
        }

        archivoPorDescripcion.clear();
        listToFile(indexadoPorDescripcion, archivoPorDescripcion);
        archivoPorDescripcion.close();
        archivo.close();
}

template<class T>
Lista<T> ArchivoDiagnostico::fileToList(std::fstream& myFStream, Lista<T> miLista) {
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
bool ArchivoDiagnostico::listToFile(const Lista<T>& myLista, std::fstream & myFstream) {
    for (int i = 0; i < myLista.length(); i++) {
        myFstream << "1*" << myLista[i] << "#";
    }
    return true;
}

template<class T>
int ArchivoDiagnostico::getIndex(const Lista<indexDuple<T>>& miLista, const T& e) const {
    for (int i = 0; i < miLista.length(); i++) {
        if (miLista[i].getData() == e) {
            return miLista[i].getIndex();
        }
    }
    return -1;
}

void ArchivoDiagnostico::addData(const Diagnostico & diagnosticoToAdd) {
    Lista<Diagnostico> myList;
    myList.insertar(diagnosticoToAdd);
    addData(myList);
}

void ArchivoDiagnostico::addData(Lista<Diagnostico>& myList) {
    archivo.open(nameFileDiagnostico, ios_base::out | ios_base::app);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::addData()");
    }

    listToFile(myList, archivo);
    archivo.close();
    reIndex();
}

Diagnostico ArchivoDiagnostico::getData(const int & idx) {
    string myString;
    Diagnostico miDiagnostico;

    archivo.open(nameFileDiagnostico);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::getData()");
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
    myStrString >> miDiagnostico;

    archivo.close();
    return miDiagnostico;
}

void ArchivoDiagnostico::delData(const int& idx) {
    archivo.open(nameFileDiagnostico, ios_base::in | ios_base::out);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::delData()");
    }

    archivo.seekp(idx);
    archivo << "0";
    archivo.close();

    reIndex();
}

int ArchivoDiagnostico::findData(const string& code) const {
    return getIndex(indexadoPorCodigo, code);
}

int ArchivoDiagnostico::findData(const Diagnostico& e) const {
    return getIndex(indexadoPorDescripcion, e.getDescripcion());
}

Lista<Diagnostico> ArchivoDiagnostico::toList() {
    archivo.open(nameFileDiagnostico, ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::toList()");
    }
    Lista<Diagnostico> listaAux;
    listaAux = fileToList(archivo, listaAux);
    archivo.close();

    return listaAux;
}

void ArchivoDiagnostico::clear() {
    std::remove(nameFileDiagnostico.c_str());
}

Lista<Diagnostico> ArchivoDiagnostico::getMisDiagnosticos() {
    return misDiagnosticos;
}

void ArchivoDiagnostico::compress() {
    string tempFileName = "temp.file";

    // Se renombra el archivo "archivoMedicos" a "temp.file".
    rename(nameFileDiagnostico.c_str(), tempFileName.c_str());

    // Se abre el archivo original en modo escritura.
    archivo.open(nameFileDiagnostico, ios_base::out | ios_base::trunc);

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

bool ArchivoDiagnostico::existenDatos() {
    archivo.open(nameFileDiagnostico, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoDiagnostico::existenDatos()");
    }

    archivo.seekg(0, std::ios::end);
    bool existenDatos = (archivo.tellg() > 0);
    archivo.close();

    return existenDatos;
}

void ArchivoDiagnostico::cargarDatos() {
    reIndex();
}