#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "bodies.h"

typedef std::vector<Cuerpo> bodies; //Nombre para vector de objetos
typedef std::vector<double> vec; // Nombre para vector de doubles

//Constantes globales
const double G = 8.2214E-7; //Constantes G
const double T = 80; //Tiempo
const double DT = 0.0001; //Intervalo de tiempo
const int NSTEPS = int(T/DT); //Pasos
const double eps = 0.0001; //margen error

//Datos Sol
const double MS = 333000.0;
//Datos Tierra
const double m_t = 1.0;
const double r_t = 1.0;
const double w_t = sqrt(G*MS*pow(r_t, -3));
const double v_t = w_t*r_t; //Orbita circular w*r 
const double rad_t = 4.25875E-5;

//declaracion de funciones
//Calcular fuerza entre N particulas y actualizar posiciones
void update(bodies & Nbody, double time);
void trans_galileo(bodies & Nbody);
void print(bodies & Nbody);
void init_planet(Cuerpo & P, double phi);
double init_phi(bodies Nbody, double Rp);
void best_phi(bodies Nbody, vec &Phi, vec &time, double Rf, double phi);
void init_assist(Cuerpo & P, vec Phi, vec time);