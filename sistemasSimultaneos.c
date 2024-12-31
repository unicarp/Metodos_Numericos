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
        scanf("%lf", array + i);
    }

    return array;
}

//Imprime la matriz de valores
void imprimirMatriz(double *array, int n, int m){   //n debe ser el numero de columnas
    printf("\n");                                   //m debe ser el numero de filas
    for(int i = 0; i <n; i++){
        if(i%(n/m) != (n/m)-1){
            printf("%lff ", *(array + i));
        }else{
            printf("%lf\n", *(array + i));
        }
    }
}

//Valida si la matriz se puede resolver por este metodo
void validez(double *matriz,double *b, int n){//n debe ser el numero de incognitas
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
    
    imprimirMatriz(matriz, n*n,n);
    imprimirMatriz(b, n, 1);
    fflush(stdout);

    while(i < n){//seguirá intentando acomodar las filas hasta que pueda verlas todas o hasta que encuentre uno con el absoluto mayor en la misma posición
        c = 0;
        r = 0;
        for(j = 0; j < n; j++){
            if(j == 0){
                absact = fabs(*(matriz + (i*n)));
                absmay = absact;
                r = 0;
                m = 0;
            }else{
                absant = absact;
                absact = fabs(*(matriz + (i*n) + j));
                r++;                    
                if(absmay < absact){
                    m = r;
                    absmay = absact;
                }
            }
        }

        if(m != i){
            if(p == m){
                manejoError("La matriz no se puede resolver por Gauss-Seidel");
            }
            p = m;
            for(int k = 0; k <n; k++){
                *(temporal + k) = *(matriz+(m*n)+k);
                *(matriz+(m*n)+k) = *(matriz+(i*n)+k);
                *(matriz+(i*n)+k) = *(temporal + k);        //intercambiamos las filas de la matriz
            }
            *temporal = *(b+m);
            *(b+m) = *(b+i);
            *(b+i) = *(temporal);                           //intercambiamos las filas del vector b
            imprimirMatriz(matriz, n*n,n);
            imprimirMatriz(b, n, 1);
            fflush(stdout);
        }else{
            i++;
        }
    }
    imprimirMatriz(matriz, n,n);
    imprimirMatriz(b, n, 1);
    fflush(stdout);

    for(i = 0; i < n; i++){

    }

    free(temporal);
    temporal = NULL;
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


int main(){
    //placeholder

    return 0;
}
