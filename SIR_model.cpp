/*#####################################
Solución Numérica de Modelo SIR 
Autor: Nestor Gonzales
Fecha: 28 Octubre 2018

Descripción:

dS/dt = - beta*S*I/N
dI/dt = beta*S*I/N - gamma*I
dR/dt = gamma*I

donde: 

S: Susceptibles
I: Infectados
R: Recuperados

beta: tasa de transmisión
gamma: tasa de remoción
##########################################
*/

#include<iostream>
#include<cmath>
#include <fstream>

using namespace std;

class SIR{
private:

	double t,S,I,R,N, P[3];
	double Derivada[3],h;
	double beta, gamma;
	double tmax;

public:


	SIR(double _beta, double _gamma, double _h, double _S0, double _I0, double _R0, double _tmax);
	~SIR();

	void EDO(double P[3]);
	void Runge_Kutta();
	void Resolver();

};

// Constructor de la clase SIR
SIR::SIR(double _beta, double _gamma, double _h,double _S0, double _I0, double _R0, double _tmax){

	beta 	= _beta;
	gamma 	= _gamma;
	h 	= _h;

	S 	= _S0;
	I 	= _I0;
	R 	= _R0;
	N 	= _S0+_I0+_R0;
	tmax 	= _tmax;
}

SIR::~SIR(){}

// Método para las Ecuaciones diferenciales
void SIR::EDO(double P[3])
{

	Derivada[0] = -beta*P[0]*(P[1]/N);              	// dS/dt

  	Derivada[1] = beta*P[0]*(P[1]/N) - gamma*P[1];   	// dI/dt

  	Derivada[2] = gamma*P[1];                    		// dR/dt
}

//############### Método de solución numérica RK4 #######################
void SIR::Runge_Kutta(){
	int i;
	double k1[3], k2[3], k3[3], k4[3];
	double temporal[3], inicio[3];

	inicio[0]=S; 
	inicio[1]=I; 
	inicio[2]=R;

	EDO(inicio);
	
	for(i=0;i<3;i++)
	{
		k1[i]=h*Derivada[i];
		//cout<<"k1:"<<k1[i]<<" ";
		temporal[i]=inicio[i]+k1[i]/2;
	}

	EDO(temporal);
	
	for(i=0;i<3;i++)
	{
		k2[i]=h*Derivada[i];
		//cout<<"k2:"<<k2[i]<<" ";
		temporal[i]=inicio[i]+k2[i]/2;
	}

	EDO(temporal);
	
	for(i=0;i<3;i++)
	{
		k3[i]=h*Derivada[i];
		//cout<<"k3:"<<k3[i]<<" ";
		temporal[i]=inicio[i]+k3[i];
	}

	EDO(temporal);

	for(i=0;i<3;i++)
	{
		k4[i]=h*Derivada[i];
		//cout<<"k4:"<<k4[i]<<" "<<endl;
		temporal[i]=inicio[i]+(k1[i]/6 + k2[i]/3 + k3[i]/3 + k4[i]/6);
	}


	S=temporal[0]; 
	I=temporal[1]; 
	R=temporal[2];
	
}

//############## Método de resolución del modelo SIR ###########################
void SIR::Resolver(){
		
	t=0;
	
	ofstream archivo;
	string nombreArchivo = "resultados.txt";
	
	archivo.open(nombreArchivo.c_str(),ios::out);
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo"<<endl;
	}
	archivo<<"t"<<"  "<<"S"<<"  "<<"I"<<"  "<<"R"<<"  "<<endl;

	do{
		cout<<t<<"  "<<S<<"  "<<I<<"  "<<R<<"  "<<endl;
		archivo<<t<<"  "<<S<<"  "<<I<<"  "<<R<<"  "<<endl;
		Runge_Kutta();
		t+=h;
	}while(t<=tmax+h);
}

//################ PROGRAMA PRINCIPAL ##########################
int main()
{
	double beta = 1.4247;
	double gamma =0.14286;

	double S0 =1485;
	double I0 = 15;
	double R0 = 0;

	double tmax = 100;
	double h=0.01;

	SIR modeloSIR(beta, gamma, h, S0, I0, R0, tmax);

	modeloSIR.Resolver();

	return(0);

}
