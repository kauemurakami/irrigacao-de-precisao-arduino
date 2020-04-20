#include <stdio.h>
#include <ctype.h>
#include <math.h>

double penman(
    double ea, 
    double es, 
    double s, 
    double temperatura, 
    double veloVento, 
    double radiacSolar, 
    double umidadeRelativa){
        
        //CONSTANTES
        double const CONST1 = 0.408;
        double const COEF1 = 0.063; //GAMA constante psicométrica Kpa/⁰C
        double const COEF2 = 0.34;
        double const G = 0; // FLUXO DE CALOR Desprezivel para valores diários
        return 
            ( ((CONST1 * s) * (radiacSolar - G)) + 
            ( ( (COEF1 * 900 * veloVento) * (es-ea))/ (temperatura + 273) ) )
            /
            (s + (COEF1 * (1 + (COEF2 * veloVento))));
}