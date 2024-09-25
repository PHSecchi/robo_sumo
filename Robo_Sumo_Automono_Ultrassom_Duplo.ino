//Robô Sumo - 08/12/2017
//Alunos:
//Pedro H Secchi
//Letícia Ladislau
//Rafael Salvador
//IFSP - Campus Catanduva
#include "Ultrasonic.h"
//--------------------------------------------
//Declara pinos de acionamento do relê
#define pRDE       2
#define pRTE       3
#define pRTD       4
#define pRDD       5
//Declara pinos dos sensores infravermelhos
#define pSDD       10
#define pSTD       11
#define pSTE       12
#define pSDE       13
//Declara pinos de trigger e echo dos sensore ultrassonicos
#define pTUD       17
#define pEUD       16
#define pTUE       14
#define pEUE       15
//Prototipagem das funções --------------------------------------------
void LEITURA();
void ACIONAMENTO();
void US_D();
void US_E();
void SUS();
void SIV();

//Declara variaveis auxiliares
 int ald=0;
 int ale=0;
 int dud=0;
 int due=0;
 int tud=0;
 int tue=0;
 int siv=0;
 int sus=0;
 int gir=-1;
 int dist=175;
//--------------------------------------------
void setup() {
//Seta os pinos como entrada ou saída
  pinMode(pSDD, INPUT);
  pinMode(pSTD, INPUT);
  pinMode(pSTE, INPUT);
  pinMode(pSDE, INPUT);
  

  pinMode(pRDD, OUTPUT);
  pinMode(pRTD, OUTPUT);
  pinMode(pRTE, OUTPUT);
  pinMode(pRDE, OUTPUT);

  pinMode(pTUD, OUTPUT);
  pinMode(pEUD, INPUT);
  pinMode(pTUE, OUTPUT);
  pinMode(pEUE, INPUT);

  //Serial.begin(9600);

}
//--------------------------------------------
void loop() {
  LEITURA();
  ACIONAMENTO();
}
//--------------------------------------------
void LEITURA() {
  //Setando as variavesi com valores default
  ald=0;
  ale=0;
  dud=0;
  due=0;
  sus=0;
  siv=1;

  SIV();
  if(siv==0)
  { US_D();
  delay(100);
  US_E();
  if(sus=1) 
  {SUS();
    }
    
  }

 
 //delay(1000);
}
//--------------------------------------------

void US_D(){// verifica o valor do utrassom direito e seta variavel caso tenha encontrado algo
digitalWrite(pTUD,LOW);
delayMicroseconds(2);
digitalWrite(pTUD,HIGH);
delayMicroseconds(10);
digitalWrite(pTUD,LOW);
tud = pulseIn(pEUD, HIGH,5000);
dud = tud/29.4 / 2;
if(dud<dist&&dud>0)
{sus=1;}
delay(1);
//Serial.print("Direita: ");Serial.println(dud);delay(1000);
}
//--------------------------------------------
void US_E(){// verifica o valor do utrassom esquerdo e seta variavel caso tenha encontrado algo
digitalWrite(pTUE,LOW);
delayMicroseconds(2);
digitalWrite(pTUE,HIGH);
delayMicroseconds(10);
digitalWrite(pTUE,LOW);
tue = pulseIn(pEUE, HIGH,5000);
due = tue/29.4 / 2;
if(due<dist&&due>0)
{sus=1;}
delay(1);
//Serial.print("|Direita: ");Serial.println(dud);Serial.print("|Esquerda:  ");Serial.print(due);delay(1000);
}
//--------------------------------------------
void SUS(){ //resolve os valores referentes a leitura dos sensores ultrassônicos verificando para qual direção ele vai virar
if(dud>due&&due>0)
{ald = 1;}
if(due>dud&&dud>0)
{ale = 1;}
if(dud==due&&dud>0&&due>0)
{ald = 1;
 ale = 1;}
//Serial.print(ale);Serial.print("|");Serial.println(ald);
}
//--------------------------------------------
void SIV(){
// Lê os sensorer infra vermelho para verificar se não está na borda da arena 
// Em seguida seta as variaveis auxiliares
 if(digitalRead(pSDD)== HIGH)
 {ald=-1;}
 if(digitalRead(pSTD)== HIGH)
 {ald= 1;}

  if(digitalRead(pSDE)== HIGH)
 {ale=-1;}
 if(digitalRead(pSTE)== HIGH)
 {ale= 1;}

 if(ald == 0 && ale == 0)// caso naõ esteja na borda da arena, seta a variavel para dar continuidade ao processo
 {siv=0;}
}
//--------------------------------------------
void ACIONAMENTO ()
{ switch(ald){//Resolve o acionamento do motor direito
  case  0 :{digitalWrite(pRTD,HIGH);digitalWrite(pRDD,HIGH);gir++;break;}
  case -1 :{digitalWrite(pRTD,LOW);digitalWrite(pRDD,HIGH);break;}
  case  1 :{digitalWrite(pRDD,LOW);digitalWrite(pRTD,HIGH);break;}
  }
 

  switch(ale){ //Resolve o acionamento do motor esquedo
  case  0 :{digitalWrite(pRTE,HIGH);digitalWrite(pRDE,HIGH);gir++;break;}
  case -1 :{digitalWrite(pRTE,LOW);digitalWrite(pRDE,HIGH);break;}
  case  1 :{digitalWrite(pRDE,LOW);digitalWrite(pRTE,HIGH);break;}
  }
  if(gir==2)// Se nenhum acionamento específico foi feito ele gira um pouco
  {digitalWrite(pRTD,LOW);digitalWrite(pRDD,HIGH);
   digitalWrite(pRDE,LOW);digitalWrite(pRTE,HIGH);}
    gir=0;
 }


