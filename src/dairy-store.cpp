#include <iostream>
#include "utils.h"
#include <fstream>
#define NUM_DAYS 30
#define NOT_ONLY_MEANS 1

using namespace std;

float* tabla_d1;
float* tabla_d15;
float* tabla_d2;
float* tabla_demanda;
unsigned int table_sz = 4;
float litros_diarios = 1000.0;
float capacidad_latas = 10.0;
unsigned int capacidad_almacenamiento = 200;
unsigned int capacidad_actual = 0;
unsigned int max_iters = 30;

ofstream myfile;
bool streambuffer;

float dias_donados = 0;
float dias_insuff = 0;
float cantidad_donada = 0;
float ventas_perdidas = 0;
float accum_dias_donados = 0;
float accum_dias_insuff = 0;
float accum_cantidad_donada = 0;
float accum_ventas_perdidas = 0;

void inicializacion();

int main(int argc, char** argv){
    srand(1);
    if(argc<=4){
        cerr << "[ERROR]: Execution Format Wrong!" << endl;
        cerr << "./main streambuffer(0:tty,1:file) max_iters(1,inf) capacidad_actual(0,capacidad_almacenamiento) "
             << "capacidad_almacenamiento(1,inf)" << endl;
        exit(-1);
    }

    streambuffer = atoi(argv[1]);
    max_iters = atoi(argv[2]);
    capacidad_actual = atoi(argv[3]);
    capacidad_almacenamiento = atoi(argv[4]);
    if(capacidad_actual > capacidad_almacenamiento)
        capacidad_actual = capacidad_almacenamiento;

    construye_todo();

    if(streambuffer)
        openfile();

    unsigned int i, j;
    unsigned int demanda = 0;
    for(j=0;j<max_iters;++j){
        inicializacion();
        for(i=0;i<NUM_DAYS;++i){
            demanda = genera_demanda();
            producir_leche();
            calcula_ventas(demanda);
            if(streambuffer==1)
                progress_bar((float) i / (float) max_iters);
        }
        if(NOT_ONLY_MEANS)
            generar_informe(j);
        acumula_resultados();
    }
    progress_bar(1);

    accum_dias_donados /= max_iters;
    accum_dias_insuff /= max_iters;
    accum_cantidad_donada /= max_iters;
    accum_ventas_perdidas /= max_iters;

    informe();

    cout << endl;
    return 0;
}

void inicializacion(){
    dias_donados = 0;
    dias_insuff = 0;
    cantidad_donada = 0;
    ventas_perdidas = 0;
}
