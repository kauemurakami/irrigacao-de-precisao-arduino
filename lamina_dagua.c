#include <stdio.h>
#include <ctype.h>
#include <math.h>

double lamina(double penman){
    double const VOLUME_RECEOSO = 0.0012661265;
    //1m²
    int const AREA = 1;
    double eq = penman * AREA;
    return eq + VOLUME_RECEOSO ;
}
