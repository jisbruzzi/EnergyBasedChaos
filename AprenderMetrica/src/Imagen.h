#ifndef IMAGEN
#define IMAGEN
#include <iostream>
#include "ArchivoTrain.h"
#include "Entrada.h"
using namespace std;
class Imagen{
	public:
	Imagen(ArchivoTrain& archivo, Entrada& entrada);
	vector<float> pixeles;
	Entrada& entrada;
	double euclideanaCuadrada(Imagen& otra);
};
#endif
