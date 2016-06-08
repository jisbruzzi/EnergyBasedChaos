#include "ArchivoTrain.h"
#include "Imagen.h"
#include <cstdlib>
#include <ctime>
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
	time_t tiempo_inicio = clock();
	vector<Entrada>::iterator it;
	long int procesadas = 0;
	long int total = entradas.size();
	//for(it = entradas.begin(); it!=entradas.end(); ++it){
	for(it = entradas.begin(); (&(*it))!=&entradas[100]; ++it){
		conectarleTargetNeighbors(*it,k);
		procesadas += 1;
		time_t tiempo_actual = clock();
		float segundos = (float)(tiempo_actual - tiempo_inicio) / CLOCKS_PER_SEC;
		float proporcion = (float)procesadas/(float)total;
		float estimacion = segundos/proporcion;
		cout<<"Procesadas: "<<proporcion*100<<"%"<<"Segundos estimados:"<<estimacion<<"Horas: "<<estimacion/3600<<endl;
	}
}
/*
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
*/
void ArchivoTrain::conectarleTargetNeighbors(Entrada& a,int k){
	
	a.setCantidadTargetNeighbors(k);
	Imagen img_a(*this,a);
	vector<Entrada>::iterator it;
	entrada.open("entrada.csv");
	long unsigned int pos_final = 0;
	entrada.seekg(entradas[0].posicion);
	
	while(pos_final<entradas.size()-1){
		cout<<pos_final<<endl;
		long unsigned int siguiente = pos_final +42000;//constante mágica, 30...60 son óptimos
		if(siguiente>=entradas.size())siguiente=entradas.size()-1;
		//neighborsEnBloque(img_a,pos_final,siguiente);
		//pos_final = siguiente;
		pos_final = neighborsEnBloque(img_a,pos_final,siguiente);
	}
	//cout<<"LLegue hasta: "<<pos_final<<" No es menor que: "<<entradas.size()-1<<endl;
	
	//neighborsEnBloque(img_a,0,80);
	//cout<<"Entradas sze: "<<entradas.size()<<" pos final: "<<pos_final<<endl;
	entrada.close();
}

long unsigned int ArchivoTrain::neighborsEnBloque(Imagen& a, long unsigned int p_inicial, long unsigned int p_final){
	
	//cout<<"Pos inicial: " <<entrada.tellg()<<endl;
	//cargar el bloque en el char*
	streampos tamanio_buffer =entradas[p_final].posicion - entradas[p_inicial].posicion;
	char* buf = (char*) malloc((tamanio_buffer)*sizeof(char));
	entrada.get(buf,tamanio_buffer,'j');//no hay jotas
	//me desplazo un caracter más
	char dummy;
	entrada.get(dummy);
	//estadísticas
	/*
	cout<<"Pos final: " <<entrada.tellg()<<endl;
	string s(buf),h;
	//cout<<buf<<s<<"  "<<tamanio_buffer<<"  "<<s.size()<<endl;
	cout<<tamanio_buffer<<"  "<<s.size()<<endl;
	cout<<"Arranqué en:" <<entradas[p_inicial].posicion<<" termino en: "<<entradas[p_final].posicion;
	cin>>h;
	*/
	
	istringstream oss(buf);
	string fila;
	for(long unsigned int i = p_inicial; i<p_final;++i){
		getline(oss,fila);
		
		if(fila.size()!=0){
			//cout<<(int)entradas[i].label<<" "<<(int)a.entrada.label<<endl;
			if(entradas[i].label == a.entrada.label){
				Imagen img_leida(*this,fila,entradas[i]);
				double distancia_entre = a.euclideanaCuadrada(img_leida);
				a.entrada.posibleTargetNeighbor(entradas[i],distancia_entre);
			}
		}else{
			cout<<"Ignoro: "<<i<<fila<<endl;
		}
	}
	free(buf);
	return p_final;
}

/*
void ArchivoTrain::conectarleTargetNeighbors(Entrada& a,int k){
	a.setCantidadTargetNeighbors(k);
	Imagen img_a(*this,a);
	vector<Entrada>::iterator it;
	
	entrada.open("entrada.csv");
	long int procesadas = 0;
	long int total = entradas.size();
	for(it = entradas.begin(); it!=entradas.end(); ++it){
		procesadas += 1;
		if(procesadas%((int)((float)total/10)) ==0){
			cout<<"Subrocesadas: "<<(float)procesadas/(float)total*100<<"%"<<endl;
		}
		string fila;
		getline(entrada,fila);
		if(it->label==a.label){
			Imagen img_leida(*this,fila,*it);
			double distancia_entre = img_a.euclideanaCuadrada(img_leida);
			a.posibleTargetNeighbor(*it,distancia_entre);
		}
	}
	entrada.close();
}
* */

/*
void ArchivoTrain::conectarleTargetNeighbors(Entrada& a,int k){
	a.setCantidadTargetNeighbors(k);
	Imagen img_a(*this,a);
	Entrada& it = entradas[0];
	entrada.open("entrada.csv");
	
	long int total = entradas.size();
	stringstream stream;
	char* buf = NULL;
	entradas[0].posicion = 0;
	for(long unsigned int i = 0; i<(long unsigned int)total-3; ++i){
		if(i%100==0){
			free(buf);
			long unsigned int siguiente = i+100;
			if(siguiente>=entradas.size())siguiente = total - 1;
			streampos pos_siguiente=entradas[siguiente].posicion;//ignoro el último...
			
			if(pos_siguiente > bytes_archivo)pos_siguiente = bytes_archivo;//nunca pasa
			//cout<<"bytes:"<<bytes_archivo<<endl;
			streampos tamanio_buffer = pos_siguiente-entradas[i].posicion;
			buf = (char*) malloc(tamanio_buffer*sizeof(char));
			entrada.getline(buf,tamanio_buffer,EOF);
			stream.ignore(stream.tellg());
			stream.write(buf,tamanio_buffer);
			//if(tamanio_buffer<10)cout<<"Es chiquito!"<<i<<" "<<siguiente<<"tam buf: "<<tamanio_buffer<<"pos sgte:"<<entradas[siguiente].posicion<<"Pos enrada i:"<<entradas[i].posicion<<endl;
			//cout<<"------------"<<buf[0]<<buf[1]<<buf[2]<<buf[3]<<endl;
		}
		
		it = entradas[i];
		if(i%((int)((float)total/10)) == 0){
			cout<<"Subprocesadas: "<<(float)i/(float)total*100<<"%"<<endl;
		}
		string fila;
		getline(stream,fila);
		//cout<<"------------"<<i<<"-----"<<fila<<endl;
		
		if(it.label==a.label && fila.size()>0){
			Imagen img_leida(*this,fila,it);
			cout<<"i: "<<i<<endl;
			double distancia_entre = img_a.euclideanaCuadrada(img_leida);
			//a.posibleTargetNeighbor(it,distancia_entre);
			
		}
		
	}
	entrada.close();
}

*/

void ArchivoTrain::guardarTargetNeighbours(){
	ofstream salida;
	salida.open("TargetNeighbours.dat");
	vector<Entrada>::iterator it;
	//for(it=entradas.begin(); it!=entradas.end(); ++it){
	for(it = entradas.begin(); (&(*it))!=&entradas[100]; ++it){
		it->agregarEn(salida);
	}
}
