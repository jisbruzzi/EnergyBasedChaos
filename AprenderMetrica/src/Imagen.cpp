#include "Imagen.h"
Imagen::Imagen(ArchivoTrain& archivo, Entrada& en):entrada(en){
	archivo.parsearPosicion(en.posicion,pixeles);
	//cout<<"-----------"<<endl;
	vector<float>::iterator it;
	/*
	cout<<endl;
	for(it = pixeles.begin(); it!=pixeles.end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;
	* */
}

double Imagen::euclideanaCuadrada(Imagen& otra){
	double suma = 0;
	for(int i = 0; i<pixeles.size(); ++i){
		float dif = pixeles[i]-otra.pixeles[i];
		suma += dif*dif;
	}
	return suma;
}
