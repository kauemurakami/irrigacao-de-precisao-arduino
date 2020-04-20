#include <stdio.h>
#include <ctype.h>
#include <math.h>

/**
PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA
**/

double psva(double temperatura){
    const double PSICOM = 0.6108;
    return PSICOM * ( pow(10,((7.5 * temperatura) / (237.3 + temperatura))));
}
