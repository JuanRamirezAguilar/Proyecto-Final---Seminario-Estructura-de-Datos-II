#include <iostream>
#include <windows.h>

#include "menuPrincipal.h"

using namespace std;

int main () {
    SetConsoleOutputCP(CP_UTF8);
    MenuPrincipal miPrograma;
    miPrograma.menu();
    return 0;
}