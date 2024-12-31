#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Tomaremos los errores que puedan surgir
void manejoError(const char *mensaje){
    fprintf(stderr,"Error: %s",mensaje);
    exit(EXIT_FAILURE);//Indica el final del programa debido a un error
}

//Guarda un arreglo de forma general
double *guardarArray(int n){
    double *array = NULL;

    array = (double *)malloc(sizeof(double)*n);
    if(array == NULL){
        manejoError("No se pudo asignar memoria correctamente.");
    }

    for(int i = 0; i <n; i++){
        scanf("%lf", array + i);    //Los datos deben estar separados por algún tipo de espacio
    }

    return array;
}

//Imprime la matriz de valores
void imprimirMatriz(double *array, int n, int m){   //n debe ser el numero de filas
    printf("\n");                                   //m debe ser el numero de columnas
    for(int i = 0; i <n; i++){
        if(m > 1){
            for(int j = 0; j < m; j++){
                if(j == m-1){
                    printf("%lf\n", *(array + (i*n) + j));
                }else{
                    printf("%lf ", *(array + (i*n) + j));
                }
            }
        }else{
            printf("%lf\n", *(array + i));          //Para cuando solo se imprime un vectos
        }
    }
}

/*
Valida si la matriz se puede resolver por Gauss-Seidel
Revisa si existe una diagonal dominante en la matriz
*/
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
    
    printf("\nMatriz A:");
    imprimirMatriz(matriz, n,n);
    printf("\nVector B:");
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
            *(temporal+i) = *(b+m);
            *(b+m) = *(b+i);
            *(b+i) = *(temporal+i);                            //intercambiamos las filas del vector b
            printf("\nMatriz A:");
            imprimirMatriz(matriz, n,n);
            printf("\nVector B:");
            imprimirMatriz(b, n, 1);
            fflush(stdout);
        }else{
            i++;
        }
    }

    double suma;

    for(i = 0; i < n; i++){
        suma = 0;
        for(j = 0; j < n; j++){
            if(j != i){
                suma = suma + fabs(*(matriz+(i*n)+j));
            }
        }
        if(*(matriz+(i*n)+i) < suma)
            manejoError("La matriz no se puede resolver por Gauss-Seidel, no tiene diagonal dominante");
    }

    free(temporal);
    temporal = NULL;
}

//Normalizacion de la matriz
void normalizacion(double *matriz, double *b, int n){//n debe ser el numero de incognitas
    double normal;   //Valor de la posicion ii

    for(int i = 0; i < n; i++){
        normal = *(matriz + (i*n) + i);
        if(normal == 0){
            manejoError("Se encontró un 0 en la diagonal dominante");
        }
        for(int j = 0; j < n; j++){
            *(matriz + (i*n) + j) = (*(matriz + (i*n) + j))/normal;
        }
        *(b + i) = (*(b+i))/normal;
    }

    printf("\nNormalizacion A:");
    imprimirMatriz(matriz , n , n);
    printf("\nNormalizacion B:");
    imprimirMatriz(b , n , 1);
    fflush(stdout);
}


//Proceso final de Gauss-Seidel
void gaussSeidel(int n, int iter,double error, double *matriz, double *x){
    int numIteracion = 1;
    double errorActual = 0;
    double *resultado = NULL;

    resultado = (double*)malloc(sizeof(double)*(n*n));
    if(resultado == NULL){
        manejoError("No se pudo asignar memoria correctamente");
    }

}


int main(){
    int n = 5; // Número de incógnitas

    double matriz[] = {
	    1, 1, 1, 1, 7,         
        0, 5, 2, 1, 2,  
        0, 0, 7, 2, 2,  
	    2, 1, 1, 0, 0,  
        1, 2, 3, 10, 2   
    };
    
    double *b = guardarArray(5);

    imprimirMatriz(b,n,1);

    validez(matriz, b, n);
    normalizacion(matriz, b, n);

    return 0;
}
