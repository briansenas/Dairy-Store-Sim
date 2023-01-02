#include <iostream>
#include "utils.h"
#include <fstream>
#define NUM_DAYS 30
#define NOT_ONLY_MEANS 1

using namespace std;

float* tabla_d1, *tabla_d15, *tabla_d2, *tabla_demanda;
float litros_diarios = 1000.0;
float capacidad_latas = 10.0;
unsigned int capacidad_almacenamiento = 200, capacidad_actual = 0, capacidad_inicial;
unsigned int table_sz = 4, max_iters = 30;
float precio_actual, ganancia = 0;

ofstream myfile;
bool streambuffer;

float dias_donados = 0, dias_insuff = 0, cantidad_donada = 0, ventas_perdidas = 0;
float accum_dias_donados = 0, accum_dias_insuff = 0, accum_cantidad_donada = 0;
float accum_ventas_perdidas = 0, accum_beneficios = 0;

float MIN_FOR_1 = 125, MIN_FOR_2 = 75;

void inicializacion();

int main(int argc, char** argv){
    srand(1);
    if(argc<=4){
        cerr << "[ERROR]: Execution Format Wrong!" << endl;
        cerr << "./main streambuffer(0:tty,1:file) max_iters(1,inf) capacidad_actual(0,capacidad_almacenamiento) "
             << "capacidad_almacenamiento(1,inf) [capacidad_produccion(10,inf) min_for_1 min_for_2]" << endl;
        exit(-1);
    }

    streambuffer = atoi(argv[1]);
    max_iters = atoi(argv[2]);
    capacidad_inicial = atoi(argv[3]);
    capacidad_actual = capacidad_inicial;
    capacidad_almacenamiento = atoi(argv[4]);
    if(capacidad_actual > capacidad_almacenamiento)
        capacidad_actual = capacidad_almacenamiento;

    if(argc>5){
        float produce = atof(argv[5]);
        if(produce >= capacidad_latas)
            litros_diarios = produce;
    }
    if(argc>6){
        float min_for_1 = atof(argv[6]);
        if(min_for_1 >= 0){
            MIN_FOR_1 = atof(argv[6]);
        }
    }
    if(argc>7){
        float min_for_2 = atof(argv[7]);
        if(min_for_2 >= 0){
            MIN_FOR_2 = atof(argv[7]);
        }
    }

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
    accum_beneficios /= max_iters;

    informe();

    cout << endl;
    return 0;
}

void inicializacion(){
    capacidad_actual = capacidad_inicial;
    dias_donados = 0;
    dias_insuff = 0;
    cantidad_donada = 0;
    ventas_perdidas = 0;
    ganancia = 0;
}
