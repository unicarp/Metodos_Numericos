#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//inicializacion de funciones (estetica)
void alojarMemoria(double *, int );
void manejoError(const char *);
double *guardarArray(int);
void imprimirMatriz(double *,int, int);
void validez(double *, double *, int);
void normalizacion(double *, double *, int);
void gaussSeidel(double *, double *, double *, int, int, double);


int main(){
    int n, iter;
    double error;

    printf("Ingrese en el orden:\n"
            "Numero de icognitas\n"
            "Matriz A de coeficientes\n"
            "Vector B de igualaciones\n"
            "Vector X de valores iniciales\n"
            "Numero maximo de iteraciones\n"
            "Error maximo permitido\n");

    scanf("%d", n);
    
    double *matriz = guardarArray(n*n);
    double *b = guardarArray(n);
    double *x = guardarArray(n);

    scanf("%d %lf", &iter, &error);
    //se terminana de pedir los datos

    //Primero se checa que se pueda resolver el sistema por este método
    validez(matriz, b, n);

    //Despues se normaliza la matriz
    normalizacion(matriz, b, n);

    //Finalmente se hace el metodo numerico
    gaussSeidel(matriz, x, b, n, iter, error);

    return 0;
}

//Toma los errores que puedan surgir
//Se deberá escribir el mensaje que se desea dar como salida
void manejoError(const char *mensaje){
    fprintf(stderr,"Error: %s",mensaje);
    exit(EXIT_FAILURE);//Indica el final del programa debido a un error
}

//Reserva la nueva memoria a usar para el arreglo
//array apuntador del que se va a crear el arreglo
//n es el numero total de elements en el arreglo
void alojarMemoria(double *array,int n){
    array = (double *)malloc(sizeof(double)*n);
    if(array == NULL){
        manejoError("No se pudo asignar memoria correctamente.");
    }
}

//Guarda un arreglo de forma general
//n es el numero total de elementos en el arreglo
double *guardarArray(int n){
    double *array = NULL;

    alojarMemoria(array, n);

    for(int i = 0; i <n; i++){
        scanf("%lf", array + i);    //Los datos deben estar separados por algún tipo de espacio
    }

    return array;
}

/*Imprime la matriz de valores
n debe ser el numero de filas
m debe ser el numero de columnas*/
void imprimirMatriz(double *array, int n, int m){
    printf("\n");
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
            printf("%lf\n", *(array + i));   //cuando solo se imprime un vectos
        }
    }
}

/*
Valida si la matriz se puede resolver por Gauss-Seidel
Revisa si existe una diagonal dominante en la matriz
b debe ser el vector de resultados
n debe ser el número de incognitas
*/
void validez(double *matriz,double *b, int n){
    double *temporal = NULL;        //vector que se usará solo para respaldar los elementos de una fila

    int m;          //numero para comprobar la posicion del absoluto mayor en la iteración atual
    int r;          //numero para guardar la posicion de la iteracion actual
    int p = -1;     //numero para guardar la posicion del abosluto mayor en la iteracion anterior
    int c;          //numero de comprobaciones en un mimso bucle, al ser 2 volvemos a recorrer desde el inicio
    int i = 0;      //numero para iterar, debe ser igual a n para salir
    int j;          //iterador de las columnas
    double absact;  //Valor absoluto del valor actual
    double absant;  //valor absoluto del valor anterior
    double absmay;  //valor absoluto mayor

    alojarMemoria(temporal, n);
    
    printf("\nMatriz A:");
    imprimirMatriz(matriz, n, n);

    printf("\nVector B:");
    imprimirMatriz(b, n, 1);        //imprime la matriz y el vector de resultados

    fflush(stdout);

    while(i < n){//seguira intentando acomodar las filas hasta que pueda verlas todas o hasta que encuentre uno con el absoluto mayor en la misma posición
        c = 0;
        r = 0;
        for(j = 0; j < n; j++){
            if(j == 0){     //guarda siempre el absoluto de la primera posicion
                absact = fabs(*(matriz + (i*n)));
                absmay = absact;    //guarda el primer absoluto como el mayor hasta el momento
                r = 0;      //guarda la primera posicion actual como 0
                m = 0;      //guarda la posicion del absoluto mayor como 0
            }else{
                absant = absact;    //respalda el absoluto actual
                absact = fabs(*(matriz + (i*n) + j));   //actualiza el nuevo absoluto actual
                r++;
                if(absmay < absact){ //remplaza el absoluto mayor si encuentra uno mas grande
                    m = r;      //guarda la posicion del nuevo absoluto mayor
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
                *(matriz+(i*n)+k) = *(temporal + k);    //intercambia las filas de la matriz
            }
            *(temporal+i) = *(b+m);
            *(b+m) = *(b+i);
            *(b+i) = *(temporal+i);      //intercambia las filas del vector b

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
                suma = suma + fabs(*(matriz+(i*n)+j));      //suma los valores absolutos de la fila excepto el de la diagonal
            }
        }
        if(*(matriz+(i*n)+i) < suma){      //revisa que que el valor en la diagonal sea mayor a la suma de los absolutos de las filas
            manejoError("La matriz no se puede resolver por Gauss-Seidel, no tiene diagonal dominante");
        }
    }

    free(temporal);
    temporal = NULL;
}

//Normalizacion de la matriz
//n debe ser el numero de incognitas
//b debe ser el vector de resultados
void normalizacion(double *matriz, double *b, int n){
    double normal;   //Valor de la posicion ii

    for(int i = 0; i < n; i++){
        normal = *(matriz + (i*n) + i);
        if(normal != 1){
            if(normal == 0){
                manejoError("Se encontró un 0 en la diagonal dominante");   //un 0 en la diagonal indetermina los resultados
            }
            for(int j = 0; j < n; j++){
                *(matriz + (i*n) + j) = (*(matriz + (i*n) + j))/normal;     //divide todos los valores de una fila de A por el valor correspondiente en la diagonal
            }
            *(b + i) = (*(b+i))/normal;     //divide los valores de B por la norma correspondiente
        }
    }

    printf("\nNormalizacion A:");
    imprimirMatriz(matriz , n , n);

    printf("\nNormalizacion B:");
    imprimirMatriz(b , n , 1);

    fflush(stdout);
}


//Proceso final de Gauss-Seidel
//n debe ser el numero de incognitas
//iter es el numero maximo de iteraciones permititdas
//double es el error maximo permitido
void gaussSeidel(double *matriz, double *x, double *b, int n, int iter,double error){
    int numIteracion = 1;       //numero de iteracion actual
    int i, j;                   //los iteradores se inician aquí para que sea más fácil usarse más adelante
    double *errores = NULL;     //todos los errores actuales entre las incognitas nuevas y las anteriores
    double *xAnt = NULL;        //el vector x anterior
    double errorActual = 0;     //el error actual más grande

    alojarMemoria(errores,n);

    alojarMemoria(xAnt,n);

    do{
        for(i = 0; i < n; i++){
            *(xAnt + i) = *(x + i);     //guarda un respaldo de X en un conjunto de las X anteriores
            *(x + i) = *(b + i);        //cambia el valor actual de X por el del vector de resultados B
            for(j = 0; j < n; j++){
                if (j != i){        //evita restar la X sobre la que estamos trabajando
                    *(x + i) = (*(x + i)) - (*(matriz + (i*n) + j))*(*(x + j)); //resta los valores anteriores de X y los que quedan en tiempo real por el coeficiente
                }
            }
            *(errores + i) = fabs((*(xAnt + i)) - (*(x + i)));       //calcula el error
            if(i == 0){
                errorActual = *errores;
            }else if(*(errores + i) > errorActual){
                errorActual = *(errores + i);       //se asegura de obtener siempre el error más grande
            }
        }

        numIteracion++;     //aumenta el numero de iteracion a la siguiente

    }while(errorActual > error && iter >= numIteracion);

    free(errores);
    free(xAnt);

    printf("\nVector X: ");
    imprimirMatriz(x, n, 1);

    printf("\nNúmero final de iteraciones:.....%d", numIteracion-1);
    printf("\nError máximo final:..............%lf", errorActual);

}


