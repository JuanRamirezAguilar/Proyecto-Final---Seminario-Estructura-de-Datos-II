#include "archivoMedicamento.h"

archivoMedicamento::archivoMedicamento() : nameFileMedicamento("archivoMedicamentos.txt"), 
indexCodeFileMedicamento("archivoMedicamentoCodigo.txt") {
    if (!std::ifstream(nameFileMedicamento)) {
        std::ofstream create(nameFileMedicamento);
        create.close();
    }                                                
}

archivoMedicamento::~archivoMedicamento() {
    if (archivo.is_open()) {
        archivo.close();
    }
    if (archivoPorCodigo.is_open()) {
        archivoPorCodigo.close();
    }
}

void archivoMedicamento::reIndex() {
    string myString;
    int myIndex;
    Medicamento miMedicamento;
    indexDuple<> miTupleCodigo;

    archivo.open(nameFileMedicamento, ios_base::in);

    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::reIndex()");
    }

    indexadoPorCodigo.anular();

    while (!archivo.eof()) {
        myIndex = int(archivo.tellg());
        getline(archivo, myString, '#');

        if (myString.empty()) {
            continue;
        }
        stringstream myStrString(myString);

        getline(myStrString, myString, '*');
        if (myString == "1") {
            myStrString >> miMedicamento;

            miTupleCodigo.setIndex(myIndex);
            miTupleCodigo.setData(miMedicamento.getCodigo());

            indexadoPorCodigo.insertar(miTupleCodigo);
        }
    }
        // Se pasa la lista de Tuplas "Codigo" a su archivo.
        archivoPorCodigo.open(indexCodeFileMedicamento, ios_base::out | ios_base::trunc);
        if (!archivoPorCodigo.is_open()) {
            throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::reIndex()");
        }
        
        archivoPorCodigo.clear();
        listToFile(indexadoPorCodigo, archivoPorCodigo);
        archivoPorCodigo.close();
        archivo.close();
}

template<class T>
Lista<T> archivoMedicamento::fileToList(std::fstream& myFStream, Lista<T> miLista) {
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
bool archivoMedicamento::listToFile(const Lista<T>& myLista, std::fstream & myFstream) {
    for (int i = 0; i < myLista.length(); i++) {
        myFstream << "1*" << myLista[i] << "#";
    }
    return true;
}

template<class T>
int archivoMedicamento::getIndex(const Lista<indexDuple<T>>& miLista, const T& e) const {
    for (int i = 0; i < miLista.length(); i++) {
        if (miLista[i].getData() == e) {
            return miLista[i].getIndex();
        }
    }
    return -1;
}

void archivoMedicamento::addData(const Medicamento & medicamentoToAdd) {
    Lista<Medicamento> myList;
    myList.insertar(medicamentoToAdd);
    addData(myList);
}

void archivoMedicamento::addData(Lista<Medicamento>& myList) {
    archivo.open(nameFileMedicamento, ios_base::out | ios_base::app);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::addData()");
    }

    listToFile(myList, archivo);
    archivo.close();
    reIndex();
}

Medicamento archivoMedicamento::getData(const int & idx) {
    string myString;
    Medicamento miMedicamento;

    archivo.open(nameFileMedicamento);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::getData()");
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
    myStrString >> miMedicamento;

    archivo.close();
    return miMedicamento;
}

void archivoMedicamento::delData(const int& idx) {
    archivo.open(nameFileMedicamento, ios_base::in | ios_base::out);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::delData()");
    }

    archivo.seekp(idx);
    archivo << "0";
    archivo.close();

    reIndex();
}

int archivoMedicamento::findData(const string& code) const {
    return getIndex(indexadoPorCodigo, code);
}

Lista<Medicamento> archivoMedicamento::toList() {
    archivo.open(nameFileMedicamento, ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en archivoMedicamento::toList()");
    }
    Lista<Medicamento> listaAux;
    listaAux = fileToList(archivo, listaAux);
    archivo.close();

    return listaAux;
}

void archivoMedicamento::clear() {
    remove(nameFileMedicamento.c_str());
}

void archivoMedicamento::compress() {
    string tempFileName = "temp.file";

    // Se renombra el archivo "archivoMedicos" a "temp.file".
    rename(nameFileMedicamento.c_str(), tempFileName.c_str());

    // Se abre el archivo original en modo escritura.
    archivo.open(nameFileMedicamento, ios_base::out | ios_base::trunc);

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

bool archivoMedicamento::existenDatos() {
    archivo.open(nameFileMedicamento, std::ios_base::in);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error al cargar el archivo en ArchivoMedicamento::existenDatos()");
    }

    archivo.seekg(0, std::ios::end);
    bool existenDatos = (archivo.tellg() > 0);
    archivo.close();

    return existenDatos;
}

void archivoMedicamento::cargarDatos() {
    reIndex();
}