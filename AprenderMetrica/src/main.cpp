#include <iostream>
#include "ArchivoTrain.h"
#include "Imagen.h"
#include "Trabajador.h"
#define MAX_DIMENSIONES 784
#include "ArchivoNeighbors.h"
#include <set>
#include "ActiveSet.h"
/**
 * Necesito que el archivo venga en 
 * "exactamente" el mismo formato que 
 * el train de kaggle, se detecta la
 * cantidad de dimensiones
 * */
//weinberger 09 - páginas 33 a 35
using namespace std;

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
			cout<<"Voy a calcular la matriz M"<<endl;
			ArchivoTrain archivo;
			ArchivoNeighbors neighbors(archivo);
			set<ActiveSet*> caca;
			neighbors.agregarActiveSets(caca);
			cout<<"Los impostores que encontré son "<<caca.size()<<endl;
		}
	}
	return 0;
}

