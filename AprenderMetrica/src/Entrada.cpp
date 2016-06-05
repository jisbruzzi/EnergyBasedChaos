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

void Entrada::posibleTargetNeighbor(Entrada& otra,long distancia_entre){
	
}
