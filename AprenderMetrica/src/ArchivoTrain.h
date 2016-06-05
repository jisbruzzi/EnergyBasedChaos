#ifndef ARCHIVO_TRAIN
#define ARCHIVO_TRAIN
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Entrada.h"
class Imagen;
using namespace std;
class ArchivoTrain{
	private:
	ifstream entrada;
	
	public:
	vector<Entrada> entradas;
	void parsearPosicion(streampos pos,vector<float>& en);
	ArchivoTrain();
	int dimensiones;
	double distancia(Entrada& e1, Entrada& e2);
	private:
	void parsearFila(const string& fila,vector<float>& en);
	int detectarDimensiones(const string& primera_linea);
	void conectarTargetNeighbors(int k);
};
#endif
