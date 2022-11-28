#include "declarations.h"

void trans_galileo(cuerpos & Nbody){
    int N = Nbody.size();
    for(int ii = 0; ii < N; ++ii){
        Nbody[ii].R = Nbody[ii].R - Nbody[N-1].R;
        Nbody[ii].V = Nbody[ii].V - Nbody[N-1].V;
    }
}

void force(cuerpos & Nbody, double time){
    int N = Nbody.size();

    //Reiniciar fuerzas
    for(int ii = 0; ii < N; ii++){
        Nbody[ii].F.x = Nbody[ii].F.y = Nbody[ii].F.z = 0.0;
    }
    //Calcular fuerza
    for(int ii = 0; ii < N; ii++){
        for(int jj = 0; jj < N; jj++){
            if(ii != jj){
                Vec3D r;
                // direccion de la fuerza m1->m2
                r = Nbody[jj].R - Nbody[ii].R;
                //norma
                double r_norm = std::pow((r.x*r.x)+(r.y*r.y)+(r.z*r.z), -1.5);

                // Fuerza - Ley de gravitacion universal
                double esc = G*Nbody[ii].mass*Nbody[jj].mass*r_norm; 
                Nbody[ii].F = Nbody[ii].F + r*esc;
            }
        }
        //Actualizar posicion y velocidad
        if(time == 0.0){
            Nbody[ii].start_leap_frog(DT);
        }
        else{
            Nbody[ii].leap_frog(DT);
        }
    }
}

void print(cuerpos & Nbody, double time){
    int N = Nbody.size();
    //Imprimir resultados
    std::cout << time << " , ";
    for(int ii = 0; ii < N; ii++){
        std::cout << Nbody[ii].R.x << " , " << Nbody[ii].R.y <<  " , ";
    }
    std::cout << "\n";
}


 bool gassist(cuerpos & Nbody, double Rp){
    bool control = false;
    double normb = sqrt(Nbody[0].R^Nbody[0].R); 
    if(fabs(normb - Rp) <= eps){control = true;}
    return control;
}

