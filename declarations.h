#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "bodies.h"

typedef std::vector<Cuerpo> cuerpos; //Nombre para vector

//Constantes globales
const double G = 8.2214E-7; //Constantes G
const double T = 144; //Tiempo
const double DT = 0.0001; //Intervalo de tiempo
const int NSTEPS = int(T/DT); //Pasos
const double eps = 0.001;

// function declaratons
void force(cuerpos & Nbody, double time);
void trans_galileo(cuerpos & Nbody);
void print(cuerpos & Nbody, double time);
bool gassist(cuerpos & Nbody, double Rp);