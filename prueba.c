#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
    double x = -10;
    double y = 1.5;
    double z = -1.5;

    double xx = fabs(x);

    double zz = fabs(z);

    printf("%lf %lf",xx,zz);

    return 0;
}