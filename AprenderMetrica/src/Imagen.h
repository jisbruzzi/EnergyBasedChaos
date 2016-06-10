#ifndef IMAGEN
#define IMAGEN
#include <iostream>
#include "ArchivoTrain.h"
#include "Entrada.h"
class ArchivoNeighbors;
using namespace std;
class Imagen{
	public:
	Imagen(ArchivoTrain& archivo, Entrada& entrada);
	Imagen(ArchivoTrain& archivo, const string& linea, Entrada& entrada);
	vector<float> pixeles;
	Entrada& entrada;
	double euclideanaCuadrada(Imagen& otra);
	//bool esIntruso(Imagen& posible, ArchivoNeighbors& neighbors);
	double dTargetMasDistante(ArchivoNeighbors& neighbors);
};
#endif
