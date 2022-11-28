#include "declarations.h"

int main(){
    //Datos Sol
    double mS = 333000.0;
    //Datos Tierra
    double mt = 1.0;
    double rt = 1.0;
    double wt = sqrt(G*mS*pow(rt, -3));
    double vt = wt*rt; //Orbita circular w*r 
    //Datos Jupiter
    double mj = 317.81;
    double rj = 5.203;
    double wj = sqrt(G*mS*pow(rj, -3));
    double vj = wj*rj; //Orbita circular w*r 
    //Datos Sonda
    double ms = 4.225E-22;
    double r0s = rt;
    double v0s = 0.81; //Velocidad de transicion

    double x0j = rj*cos(2.14598);
    double y0j = rj*sin(2.14598);
    double vxj = -wj*rj*sin(2.14598);
    double vyj = wj*rj*cos(2.14598);

    //---(x0,y0,z0,Vx0,Vy0,Vz0,m)
    Cuerpo Sol(0,0,0,0,0,0,mS);
    Cuerpo Tierra(rt,0,0,0,vt,0,mt);
    Cuerpo Jupiter(x0j,y0j,0,vxj,vyj,0,mj);
    Cuerpo Sonda(r0s,4.25875E-5,0,0,v0s,0, ms);

    cuerpos N = {Sonda, Tierra, Jupiter, Sol};

    //Fuerza inicial
    double time = 0.0;
    force(N, time);
    trans_galileo(N);
    print(N,0.0);

    for(int ii = 1; ii < NSTEPS; ++ii){
        time = DT*ii;
        force(N, time);
        trans_galileo(N);
        print(N, time);
        //if(gassist(N, rj)){break;}
    }

    //double phi = acos(N[0].R.x/rj)-wj*time;
    //std::cout << phi; //2.13458

    return 0;
}

