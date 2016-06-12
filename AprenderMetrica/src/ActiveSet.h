#ifndef ACTIVESET
#define ACTIVESET
#include "Imagen.h"
class ActiveSet{
	public:
	Imagen* dato;
	Imagen* targetNeighbor;
	Imagen* impostor;
	ActiveSet(){
		dato = NULL;
		targetNeighbor = NULL;
		impostor=NULL;
	}
};

struct CompararActiveSet{
	bool operator()(const ActiveSet a, const ActiveSet b){
		size_t hash_a = (size_t)a.dato + (size_t)a.targetNeighbor+ (size_t)a.impostor;
		size_t hash_b = (size_t)b.dato + (size_t)b.targetNeighbor+ (size_t)b.impostor;
		return hash_a<hash_b;
	}
};
#endif
