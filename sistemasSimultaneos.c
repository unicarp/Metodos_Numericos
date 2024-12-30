#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Tomaremos los errores que puedan surgir
void manejoError(const char *mensaje){
    fprintf(stderr,"Error: %s",mensaje);
    exit(EXIT_FAILURE);//Indica el final del programa debido a un error
}

//Guarda la matriz de coeficientes
double *guardarArray(int n){
    double *array = NULL;

    array = (double *)malloc(sizeof(double)*n);
    if(array == NULL){
        manejoError("No se pudo asignar memoria correctamente.");
    }

    for(int i = 0; i <n; i++){
        scanf("%f", array + i);
    }

    return array;
}

//Valida si la matriz se puede resolver por este metodo
double *validez(double *matriz,double *b, int n){//n debe ser el numero de incognitas
    double *temporal = NULL;

    int m;          //numero para comprobar la posicion del absoluto mayor en la iteración atual
    int r;          //numero para guardar la posicion de la iteracion actual
    int p = -1;     //numero para guardar la posicion del abosluto mayor en la iteracion anterior
    int c;          //numero de comprobaciones en un mimso bucle, al ser 2 volvemos a recorrer desde el inicio
    int i = 0;      //numero para iterar, debe ser igual a n para salir
    int j;          //iterador de las columnas
    double absact;  //Valor absoluto del valor actual
    double absant;  //valor absoluto del valor anterior
    double absmay;  //valor absoluto mayor

    temporal = (double *)malloc(sizeof(double)*n);

    if(temporal == NULL){
        manejoError("No se pudo asignar memoria correctamente");
    }

    while(i < n){//seguirá intentando acomodar las filas hasta que pueda verlas todas o hasta que encuentre uno con el absoluto mayor en la misma posición
        c = 0;
        r = 0;
        j = i*n;
        do{
            if(j%n == 0){
                absact = fabs(*(matriz + j));
                absmay = absact;
                r = 0;
                m = 0;
            }else{
                absant = absact;
                absact = fabs(*(matriz + j));
                r++;                    
                if(absmay < absact){
                    m = r;
                    absmay = absact;
                }
            }
            j++;
        }while(j%n < n-1);

        if(m != i){
            if(p == m){
                manejoError("La matriz no se puede resolver por Gauss-Seidel");
            }
            p = m;
            for(int k = 0; k <n; k++){
                *(temporal + k) = *(matriz+(m*n)+k);
                *(matriz+((m-1)*n)+k) = *(matriz+(i*n)+k);
                *(matriz+(i*n)+k) = *(temporal + k);        //intercambiamos las filas de la matriz
            }
            *temporal = *(b+m);
            *(b+m) = *(b+i);
            *(b+i) = *(temporal);                           //intercambiamos las filas del vector b
        }else{
            i++;
        }
    }
}

//Pivotea para garantizar la resolucion
double *pivoteo(double *matriz,double *b, int n){
    double *temporal = NULL;

    temporal = (double *)malloc(sizeof(double)*n);

    if(temporal == NULL){
        manejoError("No se pudo asignar memoria correctamente");
    }



    return matriz;
}

//Proceso final de Gauss-Seidel
double *gaussSeidel(int n, int iter,double error, double *matriz, double *x){
    int numIteracion = 1;
    double errorActual = 0;
    double *resultado = NULL;

    resultado = (double*)malloc(sizeof(double)*n);
    if(resultado == NULL){
        manejoError("No se pudo asignar memoria correctamente");
    }

    return resultado;
}

//Imprime la matriz de valores
void imprimirMatriz(double *array, int n, int m){
    printf("\n");
    for(int i = 0; i <n; i++){
        if(i%(n/m) != (n/m)-1){
            printf("%f ", *(array + i));
        }else{
            printf("%f\n", *(array + i));
        }
    }
}

int main(){
    //Por ingresar algo

    return 0;
}
