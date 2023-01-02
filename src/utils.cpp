#include "utils.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unistd.h>
#define PATH_MAX 1024
#define DEBUG 0
using namespace std::chrono;
using namespace std;

extern float* tabla_d1, *tabla_d15, *tabla_d2, *tabla_demanda;
extern unsigned int table_sz;

extern ofstream myfile;
extern bool streambuffer;

extern float litros_diarios, capacidad_latas;
extern unsigned int capacidad_almacenamiento, capacidad_almacenamiento;
extern unsigned int capacidad_actual, max_iters;

extern float dias_donados, dias_insuff, cantidad_donada, ventas_perdidas;
extern float ganancia, precio_actual;

extern float accum_dias_donados, accum_dias_insuff, accum_cantidad_donada;
extern float accum_ventas_perdidas, accum_beneficios;
extern float MIN_FOR_1, MIN_FOR_2;

double uniforme()
{
    int t = random();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

void construye_demanda(){
    tabla_demanda = new float[table_sz];
    tabla_demanda[0] = 50;
    tabla_demanda[1] = 90;
    tabla_demanda[2] = 130;
    tabla_demanda[3] = 170;
}

void construye_tabla_d1(){
    tabla_d1 = new float[table_sz];
    tabla_d1[0] = 0.1;
    tabla_d1[1] = 0.3;
    tabla_d1[2] = 0.6;
    tabla_d1[3] = 1;
}

void construye_tabla_d15(){
    tabla_d15 = new float[table_sz];
    tabla_d15[0] = 0.15;
    tabla_d15[1] = 0.45;
    tabla_d15[2] = 0.80;
    tabla_d15[3] = 1;
}

void construye_tabla_d2(){
    tabla_d2 = new float[table_sz];
    tabla_d2[0] = 0.30;
    tabla_d2[1] = 0.70;
    tabla_d2[2] = 0.9;
    tabla_d2[3] = 1;
}

void construye_todo(){
    construye_demanda();
    construye_tabla_d1();
    construye_tabla_d15();
    construye_tabla_d2();
}

void producir_leche(){
    float cantidad_producida = litros_diarios/capacidad_latas;
    capacidad_actual += cantidad_producida;
    if(capacidad_actual > capacidad_almacenamiento){
        float donadas = capacidad_actual - capacidad_almacenamiento;
        if(DEBUG)
            cout << "Donando " << donadas << "..." << "\t";
        capacidad_actual = capacidad_almacenamiento;
        cantidad_donada += donadas;
        dias_donados++;
    }
    if(DEBUG)
        cout << capacidad_actual << "\t" ;
}

void calcula_ventas(unsigned int demanda){
   if(demanda > capacidad_actual){
       if(DEBUG){
            cout << "Insuficiente " << demanda-capacidad_actual << "..." << "\t";
            cout << "Ganancia de " << capacidad_actual * precio_actual << "\t";
       }
       dias_insuff++;
       ventas_perdidas += demanda-capacidad_actual;
       ganancia += capacidad_actual * precio_actual;
       capacidad_actual = 0;
   }else{
       capacidad_actual -= demanda;
       if(DEBUG)
            cout << "Ganancia de " << capacidad_actual * precio_actual << "\t";
       ganancia += demanda * precio_actual;
   }
   if(DEBUG)
        cout << endl;
}

int genera_demanda_d1(){
    unsigned int i;
    double u = uniforme();
    i = 0;
    while((i<table_sz) && (u>=tabla_d1[i]))
        i++;
    return tabla_demanda[i];
}

int genera_demanda_d15(){
    unsigned int i;
    double u = uniforme();
    i = 0;
    while((i<table_sz) && (u>=tabla_d15[i]))
        i++;
    return tabla_demanda[i];
}

int genera_demanda_d2(){
    unsigned int i;
    double u = uniforme();
    i = 0;
    while((i<table_sz) && (u>=tabla_d2[i]))
        i++;

    return tabla_demanda[i];
}

int genera_demanda(){
    int demanda = 0;
    if(capacidad_actual>=MIN_FOR_1){
        if(DEBUG)
            cout << "1" << "\t";
        precio_actual = 1;
        demanda = genera_demanda_d1();
    }else if(capacidad_actual > MIN_FOR_2){
        if(DEBUG)
            cout << "1.5" << "\t";
        precio_actual = 1.5;
        demanda = genera_demanda_d15();
    }else{
        if(DEBUG)
            cout << "2" << "\t";
        precio_actual = 2;
        demanda = genera_demanda_d2();
    }
    if(DEBUG)
        cout << demanda << "\t";
    return demanda;
}

void acumula_resultados(){
    accum_dias_donados += dias_donados;
    accum_dias_insuff += dias_insuff;
    accum_cantidad_donada += cantidad_donada;
    accum_ventas_perdidas += ventas_perdidas;
    accum_beneficios += ganancia;
}

void generar_informe(int i){
    stringstream oss;
    if(streambuffer==0){
        if(i==0) {
            cout<< fixed << setprecision(2) << "Dias Donados"
                << setw(20) << "Cantidad Donada"
                << setw(20) << "Dias Insuff"
                << setw(20) << "Ventas Perdidas"
                << setw(20) << "Ganancia"
                << endl;
        }
        oss << fixed << setprecision(2) << dias_donados
            << setw(22) << cantidad_donada
            << setw(22) << dias_insuff
            << setw(22) << ventas_perdidas
            << setw(22) << ganancia
            << endl;
        cout  << oss.str();
    }else{
        oss << fixed << setprecision(2) << setw(10) << dias_donados
            << setw(10) << cantidad_donada
            << setw(10) << dias_insuff
            << setw(10) << ventas_perdidas
            << setw(10) << ganancia
            << endl;
        myfile << oss.str();
    }
}
void informe(){
    stringstream oss;
    if(streambuffer==0){
        cout << "########################## MEDIAS OBTENIDAS ##########################" << endl;
        cout    << fixed << setprecision(2) << "Dias Donados"
                << setw(20) << "Cantidad Donada"
                << setw(20) << "Dias Insuff"
                << setw(20) << "Ventas Perdidas"
                << setw(20) << "Ganancia"
                << endl;
        oss << fixed << setprecision(2) << accum_dias_donados
            << setw(22) << accum_cantidad_donada
            << setw(22) << accum_dias_insuff
            << setw(22) << accum_ventas_perdidas
            << setw(22) << accum_beneficios
            << endl;
        cout  << oss.str();
    }else{
        myfile << "\n\n";
        oss << fixed << setprecision(2) << setw(10) << accum_dias_donados
            << setw(10) << accum_cantidad_donada
            << setw(10) << accum_dias_insuff
            << setw(10) << accum_ventas_perdidas
            << setw(10) << accum_beneficios
            << endl;
        myfile << oss.str();
    }
}


void openfile(){
    // Try to store the results in a file
    string path;
    stringstream oss;
    path = get_selfpath();
    path = path.substr(0,path.find_last_of("/\\") + 1) + "../resultados/" ;
    oss << "dairy-N:" << capacidad_actual << "-M:" << capacidad_almacenamiento
        << "-L:" << litros_diarios << "-M1:" << MIN_FOR_1 << "-M2:" << MIN_FOR_2
        << ".txt";
    cout << oss.str() << endl;
    myfile.open(path + oss.str(),ios::out|ios::trunc);
    if(!myfile.is_open()){
        cerr << "[ERROR]: Couldn't open file to save results" << endl;
        streambuffer = 0;
    }
}

//https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progress_bar(float progress){
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

//https://stackoverflow.com/questions/5525668/how-to-implement-readlink-to-find-the-path
string get_selfpath() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';
        return std::string(buff);
    }
    /* handle error condition */
    return "";
}
