#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
/**
 * Necesito que el archivo venga en 
 * "exactamente" el mismo formato que 
 * el train de kaggle, se detecta la
 * cantidad de dimensiones
 * */
//weinberger 09 - páginas 33 a 35
using namespace std;

int detectarDimensiones(const string& primera_linea){
	istringstream stream(primera_linea);
	int dimensiones = 0;
	char dummy[50];
	while(!stream.eof()){
		stream.getline(dummy,50,',');
		dimensiones+=1;
	}
	return dimensiones-1;//la primera columna es "label!!"
}
void parsearFila(const string& fila,vector<float>& en){
	istringstream stream(fila);
	char numero[50];
	stream.getline(numero,50,',');//el primer número es el label
	while(!stream.eof()){
		stream.getline(numero,50,',');
		istringstream stream_numero(numero);
		float obtenido;
		stream_numero>>obtenido;
		en.push_back(obtenido);
		cout<<obtenido<<" ";
	}
}

int main(int argc, char* argv[]){
	cout<<"Holaaaa"<<endl;
	string primera_linea;
	ifstream entrada;
	entrada.open("entrada.csv");
	getline(entrada,primera_linea);
	int dimensiones = detectarDimensiones(primera_linea);
	cout<<"Dimensiones: "<<dimensiones<<endl;
	string segunda_linea;
	getline(entrada,segunda_linea);
	vector<float> imagen;
	parsearFila(segunda_linea,imagen);
}

