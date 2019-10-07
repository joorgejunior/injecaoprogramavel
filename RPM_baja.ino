#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

long freq, tempo, rpm;
int pulsos;
boolean pulso;
void setup() {
  pulso=HIGH;
  pinMode(2,INPUT);
  lcd.begin(20, 2);
  lcd.setCursor(3,0);
  lcd.print("TACOMETRO");
}

void loop() {
  tempo = millis();
  if(digitalRead(2)==HIGH)
  {
    if(pulso==HIGH)
    {
      pulsos = pulsos + 1;
    }
    pulso=LOW; 
  }
  else{
    pulso=HIGH;
  }
  if(tempo%2000==0){
    freq = pulsos/2;
    rpm = freq*60;
    lcd.setCursor(7,1);
    lcd.print(rpm);
    lcd.print("RPM");
    pulsos=0;  
  }
}
