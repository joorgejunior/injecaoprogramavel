void setup() {

  // DEFINIÇÃO DOS PINOS DIGITAIS PARA OS LEDS//
 
  pinMode(0,OUTPUT); // NÃO LEMBRO DE EXISTE PINO DIGITAL 0 KKKKK
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
 
void loop() {

  // DEFINIÇÃO
  
  digitalWrite(0,HIGH); // ACENDE O LED NO PINO 0
  digitalWrite(1,HIGH); 
  digitalWrite(2,HIGH); 
  digitalWrite(3,HIGH); 
  digitalWrite(4,HIGH); 
  digitalWrite(5,HIGH); 
  digitalWrite(6,HIGH); 
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH); 
  digitalWrite(9,HIGH); 
  digitalWrite(10,HIGH); 
  digitalWrite(11,HIGH);
  delay(45); // 45 x 10^-3 SEGUNDOS
  
  digitalWrite(0,LOW); // DESLIGA O LED NO PINO 0
  digitalWrite(1,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(3,LOW); 
  digitalWrite(4,LOW); 
  digitalWrite(5,LOW); 
  digitalWrite(6,LOW); 
  digitalWrite(7,LOW); 
  digitalWrite(8,LOW); 
  digitalWrite(9,LOW); 
  digitalWrite(10,LOW); 
  digitalWrite(11,LOW); 
  delay(45); 
  
}
