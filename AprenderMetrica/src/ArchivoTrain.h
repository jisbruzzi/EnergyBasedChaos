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
	streampos bytes_archivo;
	
	public:
	long unsigned int neighborsEnBloque(Imagen& a, long unsigned int p_inicial, long unsigned int p_final);
	vector<Entrada> entradas;
	void parsearPosicion(streampos pos,vector<float>& en);
	void parsearFila(const string& fila,vector<float>& en);
	ArchivoTrain();
	int dimensiones;
	double distancia(Entrada& e1, Entrada& e2);
	void conectarTargetNeighbors(int k);
	void guardarTargetNeighbours();
	private:
	int detectarDimensiones(const string& primera_linea);
	void conectarleTargetNeighbors(Entrada& a,int k);
	
};
#endif
