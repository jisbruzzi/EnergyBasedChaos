#ifndef ARCHIVONEIGHBORS
#define ARCHIVONEIGHBORS
#include "ArchivoTrain.h"
#include <set>
#include "ActiveSet.h"
class ArchivoNeighbors{
	private:
	ArchivoTrain& train;
	
	public:
	map<ulint,Imagen*> imagenes;
	void agregarActiveSets(set<ActiveSet*>& sets);
	ArchivoNeighbors(ArchivoTrain& train);
	void conectarImagenes();
	void cargarImagenes();
	
};
#endif
