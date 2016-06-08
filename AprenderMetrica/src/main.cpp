#include <iostream>
#include "ArchivoTrain.h"
#include "Imagen.h"
/**
 * Necesito que el archivo venga en 
 * "exactamente" el mismo formato que 
 * el train de kaggle, se detecta la
 * cantidad de dimensiones
 * */
//weinberger 09 - páginas 33 a 35
using namespace std;

int main(int argc, char* argv[]){
	cout<<"Holaaaa"<<endl;
	/*
	string segunda_linea;
	getline(entrada,segunda_linea);
	vector<float> imagen;
	parsearFila(segunda_linea,imagen);
	* */
	ArchivoTrain archivo;
	archivo.conectarTargetNeighbors(5);
	archivo.guardarTargetNeighbours();
}

