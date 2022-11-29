#include "declarations.h"

int main(int argc, char *argv[]){
    
    //Datos planeta asistencia
    double m_p1 = 317.81; //0.815
    double r_p1 = 5.203; //1.52
    double rad_p1 = 0.002; //Maximo acercamiento de la sonda con el planeta
    double w_p1 = sqrt(G*MS*pow(r_p1, -3));
    double v_p1 = w_p1*r_p1; //Orbita circular w*r 

    //Punto de llegada
    double r_p2 = 9.582;

    //Datos Sonda
    double m_sonda = 4.225E-22;
    double v_sonda = sqrt(2*G*MS*r_p1/(r_t*(r_p1+r_t))) + 0.01; //Velocidad de transicion
    double r_sonda = r_t;

    //Inicializar cuerpos de la simulacion
    //---(x0,y0,z0,Vx0,Vy0,Vz0,m,rad)
    Cuerpo Sol(0,0,0,0,0,0,MS,0);
    Cuerpo Tierra(r_t,0,0,0,v_t,0,m_t,rad_t);
    Cuerpo Sonda(r_sonda,rad_t,0,0,v_sonda,0, m_sonda,0);
    Cuerpo P_gassist(r_p1,0,0,0,v_p1,0,m_p1,rad_p1);
 
    //Sistema inicial auxiliar (Sonda, ..., P_assist, Sol)
    bodies N_aux1 = {Sonda, P_gassist, Sol};

    //Calcular phi para punto de encuentro
    double phi = init_phi(N_aux1, r_p1);

    //vectores para almacenar phi y los tiempos respectivos
    vec Phi;
    vec Time;

    //Modificar y guardar mejores phi
    for(int ii = 0; ii < 100; ii++){
        phi += ii*0.00001;
        best_phi(N_aux1, Phi, Time, r_p2, phi);
    }
    //Inicializar planeta con el phi que permite un menor tiempo
    init_assist(P_gassist, Phi, Time);

    //Conjunto N-cuerpos para la simulacion
    //se toma como sistema de referencia el ultimo cuerpo
    bodies N = {Sonda, P_gassist, Sol};
    print(N);


    return 0;
}
