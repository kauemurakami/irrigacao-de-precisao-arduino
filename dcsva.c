#include <stdio.h>
#include <ctype.h>
#include <math.h>

double dcsva(double es, double temperatura){
    int const PADRAO = 4098;
    double eq = temperatura + 237.3;
    return ( (PADRAO * es) / ( pow(eq, 2) ) );
}