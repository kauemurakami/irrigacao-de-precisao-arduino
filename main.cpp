#include <iostream>
#include <locale.h>
#include "psva.c"
#include "pava.c"
#include "dcsva.c"
#include "penman.c"



//PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA


int main(){
    setlocale(LC_ALL, "portuguese");
    
    //Graus Célsius
    double temperatMedia = 26;
    //Porcentagem
    double umidadeRelativa = 72;
    //m/s
    double velocVento = 2;
    //MegaJoules
    double radiacSolar = 7.8;
    
    //RESULTADO DE FUNÇÕES
    //PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA Kpa
    double es =  psva(temperatMedia);
    printf("PSVA %.2f ", es);
    //PRESSÃO ATUAL DE VAPOR DE ÁGUA Kpa
    double ea = pava(umidadeRelativa, es);
    printf("PAVA %.2f ", ea);
    //DECLIVIDADE DE CURVA DE SATURAÇÃO DE VAPOR DE ÁGUA Kpa/⁰C
    double s = dcsva(es, temperatMedia);
    printf("DCSVA %.2f ", s);
    //MÉTODO DE PENMAN MONTEITH FAO 56
    double eto = penman(ea,es,s,temperatMedia,velocVento,radiacSolar, umidadeRelativa);
    printf("ETo %.2f ", eto);

}   

