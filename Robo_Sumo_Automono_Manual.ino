//Robô Sumo - 03/10/2017
//Alunos:
//Pedro H Secchi
//Letícia Ladislau
//Rafael Salvador
//IFSP - Campus Catanduva

#include "Ultrasonic.h"
Ultrasonic ultrasonic(14,15);

//Declara pino do receptor de rádio
#define pCHVG      7 // pino da chave que controla entre autonômo e manual
#define pCHZ       8 // pino da alavanca de direção
#define pCVT       9 // pino da alavanca de aceleração

//Declara pinos de acionamento do relê
#define pRDD       2
#define pRTD       3
#define pRTE       4
#define pRDE       5

//Declara pinos dos sensores infravermelhos
#define pSDD       10
#define pSTD       11
#define pSTE       12
#define pSDE       13

//Prototipagem das funções 
void LEITURA_RC();
void LEITURA_AT();
void ACIONAMENTO_RC();
void ACIONAMENTO_AT();

//Declara variaveis auxiliares
 int sld=0,
     sle=0,
     sus=0,
     chv_g,
     cnl_1,
     cnl_3;
float sUS=0;




void setup() {
  //Seta os pinos como entrada ou saída
  pinMode(pCHVG, INPUT);
  pinMode(pCHZ, INPUT);
  pinMode(pCVT, INPUT);

  pinMode(pSDD, INPUT);
  pinMode(pSTD, INPUT);
  pinMode(pSTE, INPUT);
  pinMode(pSDE, INPUT);

  pinMode(pRDD, OUTPUT);
  pinMode(pRTD, OUTPUT);
  pinMode(pRTE, OUTPUT);
  pinMode(pRDE, OUTPUT);
 
  Serial.begin(9600);

}

void loop() 
{ //Lê o pino de chave seletora para alterar entre o modo autonômo e manual
  chv_g = pulseIn(pCHVG, HIGH, 25000);
  if (chv_g > 1500)
    {LEITURA_AT();
     ACIONAMENTO_AT();}
  if (chv_g < 1500)
     {LEITURA_RC();
      ACIONAMENTO_RC();}
}

void LEITURA_AT() {
// LÊ os sensorer infra vermelho para verificar se não está na borda da arena 
// Em seguida seta as variaveis auxiliares
 if(digitalRead(pSTD)== HIGH)
 {sld=-1;}
 if(digitalRead(pSDD)== HIGH)
 {sld=1;}

 if(digitalRead(pSDE)== HIGH)
 {sle=-1;}
 if(digitalRead(pSTE)== HIGH)
 {sle=1;}

 sUS = ultrasonic.Ranging(CM); //Lê o sensor de ultrasom
     
}

void ACIONAMENTO_AT()
{ //Resolve o movimento dependendo da leitura dos sensores infravermelhos
  switch(sld){
  case -1:{digitalWrite(pRTD,LOW);digitalWrite(pRDD,HIGH);break;}  
  case  0:{sus+=1;break;}  
  case  1:{digitalWrite(pRDD,LOW);digitalWrite(pRTD,HIGH);break;}
  }
  sld=0;

  switch(sle){
  case -1:{digitalWrite(pRTE,LOW);digitalWrite(pRDE,HIGH);break;}
  case  0:{sus+=1;break;}
  case  1:{digitalWrite(pRDE,LOW);digitalWrite(pRTE,HIGH);break;}
  }
  sle=0;

  if(sus>0)
  {if(sUS<200)// Se houver algo em frente ele vai para frente 
   {digitalWrite(pRDD,LOW);digitalWrite(pRTD,HIGH);
    digitalWrite(pRDE,LOW);digitalWrite(pRTE,HIGH);}

   if(sUS>200)//se não tiver ele gira um pouco
  {digitalWrite(pRDD,LOW);digitalWrite(pRTD,HIGH);
   digitalWrite(pRDE,HIGH);digitalWrite(pRTE,LOW);} 
  sus=0;  
  }
  
}


void LEITURA_RC() {//Lê os dois canais do sensor de rádio para medir o comprimento de pulso 
  cnl_1 = pulseIn(pCHZ, HIGH, 25000);
  cnl_3 = pulseIn(pCVT, HIGH, 25000);
  //Serial.println(chv_g);
  // Serial.println(cnl_1);
  // Serial.println(cnl_3);
  //delay(1500);
}

void ACIONAMENTO_RC()// Verifica o comprimento do pulso para realizar a ação
 {if (cnl_1 > 1050 && cnl_1 < 1363) // Verifica se a alavanca de direção se encontra centralizada
      { //Aceleração
        if (cnl_3 < 1203) //Verifica se a alavanca de acelerção está para frente
        { digitalWrite(pRDD, LOW);
          digitalWrite(pRTD, HIGH);
          digitalWrite(pRTE, HIGH);
          digitalWrite(pRDE, LOW);
        }
        if (1203 < cnl_3 && cnl_3 < 1578) //Verifica se a alavanca de acelerção está centralizada
        { digitalWrite(pRDD, HIGH);
          digitalWrite(pRTD, HIGH);
          digitalWrite(pRTE, HIGH);
          digitalWrite(pRDE, HIGH);
        }
        if (cnl_3 > 1578) ////Verifica se a alavanca de acelerção está para trás
        { digitalWrite(pRDD, HIGH);
          digitalWrite(pRTD, LOW);
          digitalWrite(pRTE, LOW);
          digitalWrite(pRDE, HIGH);
        }
       }
     else
       {delay(500);
        if (cnl_1 > 1363) // Verifica se a alavanca de direção está para direita
       { digitalWrite(pRDD, LOW);
         digitalWrite(pRTD, HIGH);
         digitalWrite(pRTE, LOW);
         digitalWrite(pRDE, HIGH);
       }
      if (cnl_1 < 1050) // Verifica se a alavanca de direção está para esquerda
       { digitalWrite(pRDD, HIGH);
         digitalWrite(pRTD, LOW);
         digitalWrite(pRTE, HIGH);
         digitalWrite(pRDE, LOW);
       }
      }

}





