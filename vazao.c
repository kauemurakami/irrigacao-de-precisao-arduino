#include <stdio.h>
#include <ctype.h>
#include <math.h>


double vazao(double qtLitros){

    //Litros por segundo
    double const VAZAO_BOMBA = 0.025;

    return (qtLitros/VAZAO_BOMBA);
}
