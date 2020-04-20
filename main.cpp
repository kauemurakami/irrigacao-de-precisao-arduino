#include <iostream>
#include <locale.h>
#include "psva.c"
#include "pava.c"



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
    //PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA
    double es =  psva(temperatMedia);
    printf("%.2f PSVA", es);
    //PRESSÃO ATUAL DE VAPOR DE ÁGUA
    double ea = pava(umidadeRelativa, es);
    printf("%.2f PAVA", ea);

}   

