/*#Juego de la vida Conway
#Al iniciar al programa se debe ingresar las dimensiones de la matriz y numero de iteraciones y el estado inicial.

#Las reglas del simulador del juego de la vida son:

# - Si la celula viva tiene a su alrededor menos de 2 celulas vivas muere por soledad.
# - Si una celula tiene alrededor mas de 3 celulas vivas muere por sobrepoblacion.
# - Si la celula tiene 2 o 3 celulas alrededor vive.
# - En una celda que tiene exactamente 3 celulas alrededor surgira vida en forma de una celula viva.
#Desarrollar un programa que reciba las dimensiones del sistema matricial e imprima la matriz resultante despues de t iteraciones 
#y la cantidad de nacimientos en cada iteracion ordenados de mayor a menor.
*/

#include <iostream>

using namespace std;
int M[19][19]={0};
int C[19][19]={0};
int nacidos[400]={0};
int n=0, m=0, t=0;   //n= filas, m= columnas
int celula=0;
int a=0, b=0, aux;

int vecinos(int f, int c){
    int cont=0;
    if(M[f-1][c-1]==1){ cont++;}
    if(M[f-1][c]==1){   cont++;}
    if(M[f-1][c+1]==1){ cont++;}
    if(M[f][c-1]==1){   cont++;}
    if(M[f][c+1]==1){   cont++;}
    if(M[f+1][c-1]==1){ cont++;}
    if(M[f+1][c]==1){   cont++;}
    if(M[f+1][c+1]==1){ cont++;}
    return cont;
}

int main() {

    cin>>n>>m>>t;
    if(n<0 || n>19 || m<0 || m>19 || t<0 || t>999){
        cout<<"Valor incorrecto";
        return 0;
    }
    for(int f=0; f<n; f++){
        for(int c=0; c<m; c++){
            cin>>M[f][c];
        }
    }

    for(int i=0; i<t; i++){              //Bucle de iteraciones

        for(int f=0; f<n; f++){
            for(int c=0; c<m; c++){
                switch(M[f][c]){
                    case 0:             //Se tiene que revisar si la celula puede NACER
                        celula=vecinos(f, c);
                        if(celula==3){ C[f][c]=1; a++;}
                        else { C[f][c]=0;}
                        nacidos[b]=a;
                        break;
                    case 1:             //Se tiene que revisar si la celula puede VIVIR o MORIR
                        celula=vecinos(f, c);
                        if(celula<2 || celula>3){ C[f][c]=0;}
                        else{ C[f][c]=1;}
                        break;
                }
            }
        }
        a=0;
        b++;
        for(int f=0; f<n; f++) {
            for (int c=0; c<m; c++) {
                M[f][c]=C[f][c];
            }
        }

    }

    for(int f=0; f<n; f++) {
        for (int c=0; c<m; c++) {
            cout<<M[f][c]<<" ";
        }
       cout<<endl;
    }

    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(nacidos[j]>nacidos[j+1]){    // Número anterior es mayor a Número siguiente?
                aux = nacidos[j];
                nacidos[j]=nacidos[j+1];
                nacidos[j+1]=aux;
            }
        }
    }

    for(int i=t; i>0; i--){
        cout<<nacidos[i]<<endl;
    }


    return 0;
}