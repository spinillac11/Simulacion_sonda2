#include "declarations.h"

void trans_galileo(bodies & Nbody){
    int N = Nbody.size();
    //Sistema de referencia respecto al ultimo elemento cuerpo
    for(int ii = 0; ii < N; ++ii){
        Nbody[ii].R = Nbody[ii].R - Nbody[N-1].R;
        Nbody[ii].V = Nbody[ii].V - Nbody[N-1].V;
    }
}

void update(bodies & Nbody, double time){
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

void print(bodies & Nbody){
    //Abrir archivo
    std::ofstream outfile;
    outfile.open("data.txt");

    int N = Nbody.size();
    double time = 0.0;

    //Simular e imprimir
    for(int ii = 0; ii < NSTEPS; ++ii){
        time = DT*ii;
        update(Nbody, time);
        trans_galileo(Nbody);
        
        //Imprimir cada 100 pasos
        if(ii%100 == 0){
            outfile << time << " , ";
            for(int ii = 0; ii < N; ii++){
            outfile << Nbody[ii].R.x << " , " << Nbody[ii].R.y <<  " , ";
            }
            outfile << "\n";
        }
    }
    outfile.close();
}

void init_planet(Cuerpo & P, double phi){
    double Rp = P.R.norm();
    double wp = sqrt(G*MS*pow(Rp, -3));

    //Inicializar planeta con mejor phi
    P.R.x = Rp*cos(phi); P.R.y = Rp*sin(phi); // posicion
    P.V.x = -wp*Rp*sin(phi); P.V.y = wp*Rp*cos(phi); //velocidad

}


double init_phi(bodies Nbody, double Rp){
    //Angulo inicial
    double phi = 0.0;
    // velocidad angular
    double wp = sqrt(G*MS*pow(Rp, -3));
    //control velocidad - verificar que llega a la orbita del planeta
    bool control = true;

    //Actualizar hasta llegar a la orbita deseada
    for(int ii = 0; ii < NSTEPS; ++ii){

        update(Nbody, DT*ii);
        trans_galileo(Nbody);

        if(fabs(Nbody[0].R.norm() - Rp) <= eps){
            control = false;
            //Calcular angulo inicial
            phi = acos(Nbody[0].R.x/Rp)-wp*DT*ii;
            break;
        }
    }

    if(control){
        std::cout << "La velocidad no es suficiente" << "\n";
    }
    return phi;
}

void best_phi(bodies Nbody, vec &Phi, vec &time, double Rf, double phi){
    int N = Nbody.size();
    init_planet(Nbody[N-2], phi);
    //Distancia entre sonda y el planeta
    Vec3D r;

    bool check = false;

    for(int ii = 0; ii < NSTEPS; ++ii){
        update(Nbody, DT*ii);
        trans_galileo(Nbody);

        r =  Nbody[0].R-Nbody[N-2].R;

        //Descartar si se choca con el planeta
        if(r.norm() <= Nbody[N-2].rad){
            break;
        }
        //Guardar si llega a la oribita deseada tras el impulso
        if(fabs(Nbody[0].R.norm() - Rf) <= eps){
            Phi.push_back(phi);
            time.push_back(DT*ii);
            break;
        }
    }
}

void init_assist(Cuerpo & P, vec Phi, vec time){

    double count = 0;
    double t0 = 0.0;
    double phi = 0.0;
    if(time.size() > 0){

        //Encontrar tiempo minimo
        for(int ii = 0; ii < time.size(); ii++){
            if(t0 > time[ii]){
                t0 = time[ii];
                count = ii;
            }
        }
        // Mejor phi
        phi = Phi[count];
        std::cout << "El angulo inicial entre los planetas es: " << phi << " rad";
    }
    else{
        std::cout << "No se encontro posicion optima" << "\n";
    }
    init_planet(P, phi);
}
