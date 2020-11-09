#include <iostream>
#include <locale.h>
#include "psva.c"
#include "pava.c"
#include "dcsva.c"
#include "penman.c"
#include "vazao.c"
#include "lamina_dagua.c"

//PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA


int main(){
    setlocale(LC_ALL, "portuguese");


    //tempo irrigação
    double tempo;
    //Graus Célsius
    double temperatMedia = 26;
    //Porcentagem
    double umidadeRelativa = 72;
    //m/s
    double velocVento = 2;
    //MegaJoules
    double radiacSolar = 7.8;

    //litros evaporados
    double qtLitros;

    //RESULTADO DE FUNÇÕES
    //PRESSÃO DE SATURAÇÃO DE VAPOR DE ÁGUA Kpa
    double es =  psva(temperatMedia);
    printf("\n PSVA %.2f ", es);

    //PRESSÃO ATUAL DE VAPOR DE ÁGUA Kpa
    double ea = pava(umidadeRelativa, es);
    printf("\n PAVA %.2f ", ea);

    //DECLIVIDADE DE CURVA DE SATURAÇÃO DE VAPOR DE ÁGUA Kpa/⁰C
    double s = dcsva(es, temperatMedia);
    printf("\n DCSVA %.2f ", s);

    //MÉTODO DE PENMAN MONTEITH FAO 56 mm/dia⁻¹
    double eto = penman(ea,es,s,temperatMedia,velocVento,radiacSolar, umidadeRelativa);
    printf("\n ETo %.2f ", eto);

    //CÁLCULO DA LÂMINA D'ÁGUA
    qtLitros = lamina(eto);
    printf("\n LITROS EVAPORADOS %.2f ", qtLitros);

    //TEMPO DE ACIONAMENTO DA BOMBA
    tempo = vazao(qtLitros);
    printf("\n TEMPO DE ACIONAMENTO (seg) %.2f ", tempo);

}

