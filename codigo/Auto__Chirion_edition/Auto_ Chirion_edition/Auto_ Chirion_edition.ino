#include <Ps3Controller.h>
#define PIN_IN_1 19
#define PIN_IN_2 21
#define PIN_IN_ENA 0
#define PIN_IN_3 2
#define PIN_IN_4 15
#define PIN_IN_ENB 18
#define LED_ON 32
void MotorHorario()
{
  digitalWrite (PIN_IN_1, HIGH);
  digitalWrite (PIN_IN_2, LOW);
}
void MotorAntihorario()
{
  digitalWrite (PIN_IN_1, LOW);
  digitalWrite (PIN_IN_2, HIGH);
}

void MotordiereccionIZQ(){
  digitalWrite (PIN_IN_3, HIGH);
  digitalWrite (PIN_IN_4, LOW);
}

void Motordiereccion(){
  digitalWrite (PIN_IN_3, LOW);
  digitalWrite (PIN_IN_4, HIGH);
}

void MotorStop()
{
  digitalWrite (PIN_IN_1, LOW);
  digitalWrite (PIN_IN_2, LOW);
}
  void MotorStopD(){
  digitalWrite (PIN_IN_3, LOW);
  digitalWrite (PIN_IN_4, LOW);
}

void notify()
{  
    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 )
       MotorAntihorario();
    if( Ps3.event.button_up.l2 )
       MotorStop();
    if( Ps3.event.button_down.r2 )
       MotorHorario();
      if( Ps3.event.button_up.r2 )
      MotorStop();
   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l2) ){
       Serial.print("Pressing the left trigger button: ");
       Serial.println(Ps3.data.analog.button.l2, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
       Serial.print("Pressing the right trigger button: ");
       Serial.println(Ps3.data.analog.button.r2, DEC);
   }
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
      int x = Ps3.data.analog.stick.lx;
      int POS; 
       Serial.println(x); 
   if (x == -128){
      MotordiereccionIZQ();
      POS = 1;
   } 
   if (x == 127) {
     Motordiereccion();
    POS = 2;
   }
   if (x == 0) {
   if (POS == 1){
     Motordiereccion();
     MotorStopD();
     POS = 0; 
   }
   if (POS == 2){
     MotordiereccionIZQ();
     MotorStopD();
     POS = 0;
  
   } 
   }
     /*  Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();*/
    }
}
void onConnect(){
    Serial.println("Connected.");
    digitalWrite(LED_ON, HIGH);
}

void setup(){
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("c0:38:96:af:ac:b9");

    Serial.println("Ready.");
  pinMode(LED_ON, OUTPUT);
  pinMode(PIN_IN_1, OUTPUT);
  pinMode(PIN_IN_2, OUTPUT);
  pinMode(PIN_IN_ENA, OUTPUT);
  pinMode(PIN_IN_3, OUTPUT);
  pinMode(PIN_IN_4, OUTPUT);
  pinMode(PIN_IN_ENB, OUTPUT);

  digitalWrite(PIN_IN_ENA, HIGH);
  digitalWrite(PIN_IN_ENB, HIGH);
}

void loop()
{
    if(!Ps3.isConnected())
        return;  
    delay(2000);
}
