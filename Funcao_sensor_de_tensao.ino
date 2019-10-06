//##MODULO SENSOR DC 25V – ALARME##//
int pinoSensorDC = A4; //##DECLARACAO DA PORTA REFERENTE AO SENSOR DC 0-25V ALARME
int valorDC = 0;
float tensaoDC = 0;
//################################//

void setup() {
Serial.begin(9600);
}

void loop() {
valorDC = analogRead(pinoSensorDC);
tensaoDC = ((valorDC*0.00489)*5);
Serial.println(tensaoDC);
delay(500);
}
