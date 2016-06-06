#include "ArchivoTrain.h"
#include "Imagen.h"
void ArchivoTrain::parsearFila(const string& fila,vector<float>& en){
	istringstream stream(fila);
	char numero[50];
	stream.getline(numero,50,',');//el primer número es el label
	while(!stream.eof()){
		stream.getline(numero,50,',');
		istringstream stream_numero(numero);
		float obtenido;
		stream_numero>>obtenido;
		en.push_back(obtenido);
		//cout<<obtenido<<" ";
	}
}
void ArchivoTrain::parsearPosicion(streampos pos,vector<float>& en){
	entrada.open("entrada.csv");//así gunciona seekg (???????)
	char fila[2048];
	entrada.seekg(pos,ios_base::beg).getline(fila,2048);
	//cout<<"Desde posicon: "<<pos<<endl;
	//cout<<"esta es:"<<entrada.seekg(pos,ios_base::beg).tellg()<<endl;
	parsearFila(fila,en);
	entrada.close();
}


int ArchivoTrain::detectarDimensiones(const string& primera_linea){
	istringstream stream(primera_linea);
	int dimensiones = 0;
	char dummy[50];
	while(!stream.eof()){
		stream.getline(dummy,50,',');
		dimensiones+=1;
	}
	return dimensiones-1;//la primera columna es "label!!"
}

ArchivoTrain::ArchivoTrain(){
	entrada.open("entrada.csv");
	//----------inicializar la cantidad de dimensiones-------//
	string primera_linea;
	getline(entrada,primera_linea);
	dimensiones = detectarDimensiones(primera_linea);
	cout<<"Dimensiones: "<<dimensiones<<endl;
	//----------generar las entradas
	
	string linea_entrada;
	while(!entrada.eof()){
		streampos posicion = entrada.tellg();
		//std::cout<<posicion<<endl;
		getline(entrada, linea_entrada);
		Entrada nueva(posicion, linea_entrada);
		entradas.push_back(nueva);
	}
	entrada.close();//así gunciona seekg (???????)
	
}

double ArchivoTrain::distancia(Entrada& e1, Entrada& e2){
	//cout<<"a"<<endl;
	Imagen img1(*this,e1), img2(*this,e2);
	return img1.euclideanaCuadrada(img2);
}

void ArchivoTrain::conectarTargetNeighbors(int k){
	vector<Entrada>::iterator it;
	long int procesadas = 0;
	long int total = entradas.size();
	for(it = entradas.begin(); it!=entradas.end(); ++it){
		conectarleTargetNeighbors(*it,k);
		procesadas += 1;
		cout<<"Procesadas: "<<(float)procesadas/(float)total*100<<"%"<<endl;
	}
}

void ArchivoTrain::conectarleTargetNeighbors(Entrada& a,int k){
	a.setCantidadTargetNeighbors(k);
	vector<Entrada>::iterator it;
	long int procesadas = 0;
	long int total = entradas.size();
	for(it = entradas.begin(); it!=entradas.end(); ++it){
		procesadas += 1;
		if( procesadas%((int)((float)total/10)) ==0){
			cout<<"Subrocesadas: "<<(float)procesadas/(float)total*100<<"%"<<endl;
		}
		if(it->label==a.label){
			double distancia_entre = distancia(*it,a);
			a.posibleTargetNeighbor(*it,distancia_entre);
		}
	}
}
