#ifndef ARCHIVONEIGHBORS
#define ARCHIVONEIGHBORS
#include "ArchivoTrain.h"
#include <set>
#include "ActiveSet.h"
#include "config.h"
typedef set<ActiveSet,CompararActiveSet> ConjuntoActiveSets;
class ArchivoNeighbors{
	private:
	ArchivoTrain& train;
	
	public:
	map<ulint,Imagen*> imagenes;
	/**
	 * "Compute Nt+1 exactly"
	 * */
	void agregarActiveSets(ConjuntoActiveSets& sets);
	
	/**
	 * "Nt+1 ~ Nt+1 interseccion N(t)" (only search active set)
	 * */
	void filtrarActivos(ConjuntoActiveSets& sets, ConjuntoActiveSets& filtrados);
	
	ArchivoNeighbors(ArchivoTrain& train);
	void conectarImagenes();
	void cargarImagenes();
	
	void calcularG0(Matriz& g0);
	
	void calcularSegundoTerminoGradiente(Matriz& g,ConjuntoActiveSets& activos);
};
#endif
