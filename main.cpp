#include <iostream>
#include <locale.h>
#include "psva.c"


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
    
    //PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA
    double es =  psva(temperatMedia);   
    printf("%f", psva(temperatMedia));

    //PRESSÃO ATUAL DE VAPOR DE ÁGUA
}

