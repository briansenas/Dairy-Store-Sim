#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <iostream>
using namespace std;

void construye_demanda();
void construye_tabla_d1();
void construye_tabla_d15();
void construye_tabla_d2();

// Construye todas las tablas y la demanda relacionada.
void construye_todo();

void producir_leche();

int genera_demanda();

void calcula_ventas(unsigned int demanda);

void generar_informe(int i);
void informe();
void acumula_resultados();

void openfile();

double uniforme();

//https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progress_bar(float progress);
//https://stackoverflow.com/questions/5525668/how-to-implement-readlink-to-find-the-path
string get_selfpath();

#endif
