//*****************************************//
//       ENDEREÇAMENTO DOS SENSORES 
// Tipo:                       Variável:            Endereço A/D:  
// 01 - Sensor LM35             LM35                    A0
// 02 - Sensor DS18B20
// 03 - Sensor Termopar(01)
// 04 - Sensor Termopar(02)
// 05 - Sensor de Tensão
// 06 - Sonda Lambda            ref_sondaLambda
//
//*****************************************//


#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include "max6675.h"

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(47,49,51,53,52,50);
const int LM35 = A0; // Define o pino que lera a saída do LM35

OneWire pino(3);
DallasTemperature barramento(&pino);
DeviceAddress sensor;

float temp_ambiente; // Variável que armazenará a temperatura medida
float temp_admissao;
float temp_agua;
float temp_oleo;
float pos_tbi;
float rpm;
float ref_sondaLambda;

const int pinoSensor = A1; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
 
float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
 
float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
int leituraSensor = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO

int ktcSO = 7; //PINO DIGITAL (SO)
int ktcCS = 9; //PINO DIGITAL (CS)
int ktcCLK = 10; //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA

  barramento.begin();
  barramento.getAddress(sensor, 0);  
}
 
// IMPRESSAO DE DADOS NO DISPLAY // 
void loop()
{
 
  Serial.begin(115200);
  
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("CAPIVARA RACING");
  lcd.setCursor(4, 1);
  lcd.print("MODO: ON");

  lcd.clear();
  //delay(3000);
  lcd.print(ktc.readCelsius());
  //delay(3000);

  barramento.requestTemperatures(); 
  float temp_admissao = barramento.getTempC(sensor);


  

// CALCULO DA LEITURA DO SENSOR DE TENSAO //

  temp_ambiente = (float(analogRead(LM35))*5/(1023))/0.01;
  leituraSensor = analogRead(pinoSensor); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
  tensaoEntrada = (leituraSensor * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
  tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
  

// IMPRESSAO DOS VALORES DOS SENSORES NA SERIAL E NO DISPLAY //
  Serial.print("\n");
  //delay(100);
  Serial.print("Temperatura Ambiente: ");
  Serial.print(temp_ambiente);
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Ambiente: ");
  lcd.setCursor(4, 1);
  lcd.print(temp_ambiente);
  lcd.print(" C");
  Serial.print("\n");

  
  delay(100);
  Serial.print("Temperatura do Motor: ");
  Serial.print(temp_agua);
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("TEMP AGUA: ");
  lcd.setCursor(4, 1);
  lcd.print(temp_agua);
  lcd.print(" C");

  Serial.print("\n");
  delay(100);
  Serial.print("Temperatura do Oleo: ");
  Serial.print(temp_oleo);
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("TEMP OLEO: ");
  lcd.setCursor(4, 1);
  lcd.print(temp_oleo);
  lcd.print(" C");

  Serial.print("\n");
  delay(100);
  Serial.print("Tensão de Entrada: ");
  Serial.print(tensaoMedida,2); //IMPRIME NA SERIAL O VALOR DE TENSÃO DC MEDIDA E LIMITA O VALOR A 2 CASAS DECIMAIS
  Serial.print(" V");
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("TENSAO BATERIA: ");
  lcd.setCursor(4, 1);
  lcd.print(tensaoMedida);
  lcd.print(" V");
  
  Serial.print("\n");
  delay(100);
  Serial.print("Referência Sonda Lambda: ");
  Serial.print(ref_sondaLambda); 
  Serial.print(" V");
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REF SONDA LAMBDA: ");
  lcd.setCursor(4, 1);
  lcd.print(ref_sondaLambda);
  lcd.print(" V");
  
  Serial.print("\n");
  delay(100);
  Serial.print("Temperatura Admissão: ");
  Serial.print(temp_admissao);
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura Admissao: ");
  lcd.setCursor(4, 1);
  lcd.print(temp_admissao);
  lcd.print(" C");
  
  Serial.print("\n");
  delay(100);
  Serial.print("Abertura Corpo de Borboleta: ");
  Serial.print(pos_tbi);
  Serial.print(" %");
  //Serial.print("\n");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Abertura Corpo de Borboleta ");
  lcd.setCursor(4, 1);
  lcd.print(pos_tbi);
  lcd.print(" %");

  Serial.print("\n");
  delay(100);
  Serial.print("RPM Atual: ");
  Serial.print(rpm);
  Serial.print(" RPM");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM Atual: ");
  lcd.setCursor(4, 1);
  lcd.print(rpm);
  lcd.print(" RPM");
  
}
