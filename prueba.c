#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void manejoError(const char *mensaje){
    fprintf(stderr,"Error: %s",mensaje);
    exit(EXIT_FAILURE);//Indica el final del programa debido a un error
}

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
            printf("%lf\n", *(array + i));
        }
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

    return 0;
}