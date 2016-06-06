#include "Entrada.h"

Entrada::Entrada(streampos posicion, string desde){
	this->posicion = posicion;
	
	char numero[4];//con uno o 2 me alcanzaría...
	istringstream stream(desde);
	stream.getline(numero,4,',');
	istringstream stream_numero(numero);
	int obtenido;
	stream_numero>>obtenido;
	label = (char) obtenido;
}

Entrada* Entrada::entradaMasLejana(){
	double mayorDistancia = -1;
	Entrada* masLejana = NULL;
	map<Entrada*,double>::iterator it;
	for(it = targets.begin(); it!=targets.end(); ++it){
		if(mayorDistancia == -1 || mayorDistancia < it->second){
			mayorDistancia = it->second;
			masLejana = it->first;
		}
	}
	return masLejana;
}

void Entrada::posibleTargetNeighbor(Entrada& otra,double distancia_entre){
	Entrada* masLejana = entradaMasLejana();
	if(targets.size() < cantidadTargetNeighbors){
		targets[&otra]=distancia_entre;
	}else{
		double distancia_mas_lejana = targets[masLejana];
		if(distancia_mas_lejana > distancia_entre){
			targets.erase(masLejana);
			targets[&otra]=distancia_entre;
		}
	}
	
}
