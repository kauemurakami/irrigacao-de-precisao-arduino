#include <math.h>
#include "dht.h"
#include <virtuabotixRTC.h>

//rele
#define pin_rele 11

//relogio
//myRTC(clock, data, rst)
virtuabotixRTC myRTC(6,7,8);

 //constantes testes
double radiacSolar = 7.8; //MJ/m^2/dia
double g = 0;  //fluxo de calor, normalmente desprezivel
double veloVento = 2; // velocidade do vento em ms/s
          
//higometro
#define analogi A0
#define digital 15
#define gnd_pinn 16
#define vcc_pinn 17

//definindo um intervalo padrão de 5 segundos
#define intervalo 3000
unsigned long delayIntervalo;

//LDR
#define LDRPIN A5
int horaA = 0;
//SENSOR DE UMIDADE E TEMPERATURA
#define DHTPIN 2
dht sensorDHT;

// variaveis de controle
boolean estado = false;
double mediaTemperatura = 0 , mediaUmidade = 0, temperatura = 0, umidade = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //pin higometro
  pinMode(analogi, INPUT);
  pinMode(digital, INPUT);
  pinMode(gnd_pinn, OUTPUT);
  pinMode(vcc_pinn, OUTPUT);

  digitalWrite(gnd_pinn, LOW);
  digitalWrite(vcc_pinn, HIGH);

  //pinrele
  pinMode(pin_rele, OUTPUT);
  digitalWrite(pin_rele, LOW);
  
  //definindo horario inicial apenas uma vez
  //myRTC.setDS1302Time(04, 24, 18, 5, 5, 9, 2019);
}

//loop infinito
void loop() {
    
    delay(intervalo);

    //Serial.println(analogRead(analogi));//print higometro    
        myRTC.updateTime();
        int hora = myRTC.hours;
        int minutos = myRTC.minutes;
        int segundos = myRTC.seconds;
        
        if(horaA == 0 || minutos == 0){
            horaA = minutos+1;
            if(estado == false){
              estado = true;
            }
          }
    
      if(horaA == minutos && estado == true && analogRead(analogi) > 900){  
        
        Serial.print(hora);
        Serial.print(":");
        Serial.print(minutos);
        Serial.print(":");
        Serial.print(segundos);
        
        horaA = minutos+1;
        //leitura dos dados  
           //dht
          float leitura = sensorDHT.read22(DHTPIN);
      
        Serial.print(" | Humidity: "); 
        Serial.print(sensorDHT.humidity , 1);
        if(umidade == 0){
            umidade = (sensorDHT.humidity);
          }else{
            mediaUmidade = media(umidade,(sensorDHT.humidity));
            umidade = sensorDHT.humidity;        
            }
            
        Serial.print(" % \t | \t Temperature: "); 
        Serial.print(sensorDHT.temperature, 1);
        Serial.print(" *C ");
          if(temperatura == 0){
            temperatura = (sensorDHT.temperature);
          }else{
            mediaTemperatura = media(temperatura,(sensorDHT.temperature));
            temperatura = sensorDHT.temperature;        
          }
        
        //ldr
        int valorLDR = analogRead(LDRPIN);   
        //exibindo dados ldr
        Serial.print("\t | \t  Luminosidade ");
        Serial.print(valorLDR);
        Serial.print(" |");
        Serial.println("\n");
    
       Serial.print("temperatura atual : ");
       Serial.println(temperatura);
       Serial.print("media temperatura :" );
       Serial.println(mediaTemperatura);
       Serial.print("umidade atual :");
       Serial.println(umidade);
       Serial.print("media umidade :");
       Serial.println( mediaUmidade);
    
        if(mediaTemperatura != 0){
         
          double evapt = penman(
            pressaoSaturacaoES(mediaTemperatura), 
            pava(mediaUmidade,pressaoSaturacaoES(mediaTemperatura)),
            dcsva(pressaoSaturacaoES(mediaTemperatura),mediaTemperatura),
            mediaTemperatura, veloVento, radiacSolar, mediaUmidade);       
          Serial.print("resultado de evaporação de dalton  mm/d: ");
       
          //funcao_volume(evap);

          digitalWrite(pin_rele,  HIGH);
          delay(4000);
          digitalWrite(pin_rele,  LOW);
          delay(1000);
        }
      }
}

long media(float n1, float n2){
  return (n1+n2)/2;
}

//es pressao de saturação de vapor de água Kpa
double pressaoSaturacaoES(double mediaTemperatura){
  const double PSICOM = 0.6108;
  return PSICOM * ( pow(10,((7.5 * temperatura) / (237.3 + temperatura))));
}

//declividade da curva de saturação do vapor de água
double dcsva(double es, double temperatura){
  int const PADRAO = 4098;
  double eq = temperatura + 237.3;
  return ( (PADRAO * es) / ( pow(eq, 2) ) );
}

//ea pressao atual do vapor de agua Kpa
double pava(double ur, double es){
    return (es * ur) / 100;
}

//método de Penman
double penman(
    double es, 
    double ea, 
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

void funcao_volume(double milimetros){

double volume_agua;
double altura_metros;
double metros_cubicos;
// a perda de 1 milimetro de água equivale a 10 metros cubicos de agua que equivale a 1000 litros de agua em 1 hectare= 10 000 metros quadrados
// perda de 100ml de agua por metro quadrado

altura_metros= milimetros/1000;

//definição de largura 1 metro
// definição de comprimento 1 metro

metros_cubicos=1*1*altura_metros;
volume_agua= metros_cubicos*1000;

//Serial.print("O volume de agua em litros representa: ");
//Serial.print(volume_agua);
}
