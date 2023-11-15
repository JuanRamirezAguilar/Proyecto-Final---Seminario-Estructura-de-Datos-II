#ifndef FILEMASTER_H
#define FILEMASTER_H

#include <fstream>
#include <string>

#include "lista.h"

#include "Consulta.h"
#include "indexDuple.h"
#include "lista.h"

#include "ArchivoMedico.h"
#include "ArchivoPaciente.h"
#include "archivoMedicamento.h"
#include "archivoDiagnostico.h"
#include "archivoConsulta.h"

#define NombreArchivo "archivoMedicamentos.txt"
#define archivoIndicePorNombre "archivoConsultasNombre.txt"

class FileMaster {
    private:
        std::fstream archivo;
        Lista<Consulta> misConsultas;
        Lista<Medico> misMedicos;
        Lista<Paciente> misPacientes;
        Lista<Medicamento> misMedicamentos;
        Lista<Diagnostico> misDiagnosticos;

    public:
        FileMaster();
        ~FileMaster();

        Lista<Consulta> getMisConsultas();
        Lista<Medico> getMisMedicos();

        Lista<Consulta> importBackup(const std::string&);
        void exportBackup();
};

#endif