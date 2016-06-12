#include <iostream>
#include "ArchivoTrain.h"
#include "Imagen.h"
#include "Trabajador.h"
#include "config.h"
#include "ArchivoNeighbors.h"
#include <set>
#include "ActiveSet.h"
#include <fstream>
#include <Eigen/Eigenvalues>
/**
 * Necesito que el archivo venga en 
 * "exactamente" el mismo formato que 
 * el train de kaggle, se detecta la
 * cantidad de dimensiones
 * */
//weinberger 09 - páginas 33 a 35
using namespace std;

void filtrarNegativos(Matriz& m){
	for(int i = 0; i < m.rows(); i++){
		if(m(i,i)<0){
			m(i,i)=0;
		}
	}
}

int main(int argc, char* argv[]){
	if(argc==1){
		cout<<"Y los argumentos?"<<endl;
	}else{
		if(argv[1][0]=='n'){
			cout<<"Recalculando target neighbours"<<endl;
			ArchivoTrain archivo;
			archivo.conectarTargetNeighbors(5,0,1000);
			archivo.guardarTargetNeighbours(0,1000);
		}else if(argv[1][0]=='m'){
			ofstream off("M.dat");
			cout<<"Voy a calcular la matriz M"<<endl;
			ArchivoTrain archivo;
			ArchivoNeighbors neighbors(archivo);
			
			Matriz m,g;
			m.setIdentity();//initialize with the identity matrix
			ConjuntoActiveSets posibles_activos, activos, anterior;//initialize active sets
			neighbors.calcularG0(g);//initialize gradient
			
			
			
			for(int i = 0; i<10; i++){//while not converged do
				if(i==0){//if mod(i,10)==0 || casi convergencia then
					neighbors.agregarActiveSets(posibles_activos);//compute Nt+1 exactly
					activos = posibles_activos//update active set
				}else{
					anteriores = activos;
					neighbors.filtrarActivos(posibles_activos, activos);//compute Nt+1 only search active set
				}
				
				ConjuntoActiveSets salieron, entraron;
				obtenerSalieron(salieron,activos,anterior);
				obtenerEntraron(entraron,activos,anterior);
				Matriz gResta,gSuma;
				neighbors.calcularSegundoTerminoGradiente(gResta,salieron);
				neighbors.calcularSegundoTerminoGradiente(gSuma,entraron);
				g+=g-gResta+gSuma;//sumaresta de gradientes
				
				
				Matriz m_def = m-0.1*g0;//Mt-alfa*Gt+1
				Eigen::EigenSolver<Matriz> solver(m_def);
				Matriz delta = solver.pseudoEigenvalueMatrix();
				Matriz v = solver.pseudoEigenvectors();
				filtrarNegativos(delta);//proyección sobre semidefinidas positivas
				m=v*delta*v.transpose();//take gradient step
			
			}
			
			off<<m;//output Mt
			
		}else if(argv[1][0]=='g'){
			ofstream off("G0.dat");
			cout<<"Voy a calcular la matriz G0"<<endl;
			ArchivoTrain archivo;
			ArchivoNeighbors neighbors(archivo);
			Matriz g0;
			neighbors.calcularG0(g0);
			cout<<"G0 es "<<g0<<endl;
			off<<g0;
		}else if(argv[1][0]=='a'){
			ofstream off("G0.dat");
			cout<<"Voy a calcular los ActiveSets"<<endl;
			Matriz m,g0;
			m.setIdentity();
			ArchivoTrain archivo;
			ArchivoNeighbors neighbors(archivo);
			
			set<ActiveSet,CompararActiveSet> caca;
			neighbors.agregarActiveSets(caca);
			cout<<"Activesets: "<<caca.size()<<endl;
		}
	}
	return 0;
}

