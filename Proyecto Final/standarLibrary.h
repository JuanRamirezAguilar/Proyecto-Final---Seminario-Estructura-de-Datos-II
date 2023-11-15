#ifndef STANDARLIBRARY_H_INCLUDED
#define STANDARLIBRARY_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void pausa();
void timeStop(int Milsec);
void limpiaBuffer();
void gotoxy(int x, int y);
void setborder(int altura, int anchura);
void AltEnter();
void borrarPantalla(int columna, int filaInicial, int filaFinal);

#endif // STANDARLIBRARY_H_INCLUDED