int pinoAnalogico = A0; //PINO ANALÓGICO (MEDE A INTENSIDADE DO CAMPO MAGNÉTICO)
int pinoDigital = 8; //PINO DIGITAL (DETECTA A PRESENÇA DO CAMPO MAGNÉTICO)
  
void setup (){
  pinMode(pinoAnalogico, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoDigital, INPUT); //DEFINE O PINO COMO ENTRADA
  Serial.begin(9600); //INICIALIZA A SERIAL
}

void loop (){

  Serial.print("Intesidade do campo magnético(Pino A0): "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(analogRead(pinoAnalogico) * (5.0 / 1023.0)); //IMPRIME NO MONITOR SERIAL UM VALOR
  //DE TENSÃO QUE REPRESENTA A INTENSIDADE DO CAMPO MAGNÉTICO
  Serial.println("V"); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("Detecção do campo magnético(Pino D8): "); //IMPRIME O TEXTO NO MONITOR SERIAL
  
  if(digitalRead(pinoDigital) == HIGH){ //SE LEITURA DO PINO FOR IGUAL A HIGH, FAZ
      Serial.println("Detectado"); //IMPRIME O TEXTO NO MONITOR SERIAL
  }else{ //SENÃO
      Serial.println("Não detectado"); //IMPRIME O TEXTO NO MONITOR SERIAL
  }
  Serial.println("----------------------------------------------------------------"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS
}
