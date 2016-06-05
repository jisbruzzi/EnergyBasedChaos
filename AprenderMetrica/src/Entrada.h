#ifndef ENTRADA
#define ENTRADA
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class Entrada{
	public:
	Entrada(streampos posicion, string desde);//ojo que no se guarda el string en memoria por dioh muchachoh(?)
	streampos posicion;
	char label;
	int cantidadTargetNeighbors;
	long mayorDistancia;
	vector<Entrada*> targetNeighbors;
	setCantidadTargetNeighbors(int k){
		cantidadTargetNeighbors = k;
		mayorDistancia = -1;
	}
	void posibleTargetNeighbor(Entrada& otra,long distancia_entre);
};
#endif
