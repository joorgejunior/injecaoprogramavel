/*

   PROGRAMA CRONOMETRO PARA ARDUINO
  
   SDA é a serial de dados
   SCL é a serial relógio

   GND --> GND 
   VCC --> 5V  
   SDA --> A4  
   SCL --> A5  

   Pinos I2C:
   Uno, Ethernet    A4 (SDA), A5 (SCL)
   Mega2560         20 (SDA), 21 (SCL)
   Leonardo          2 (SDA),  3 (SCL)
   Due              20 (SDA), 21 (SCL) of SDA1, SCL1

*/

//// GERAL ////

// Variável para o número de milissegundos desde o início do Arduino
unsigned long mili_Atual = 0;       

//// LCD SCHERM ////

// Biblioteca para comunicação com dispositivos I2C / TWI
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int LCDWidth = 20;
const int LCDHeight = 4;

/*
Link para gerador de icones para o LCD
    https://maxpromer.github.io/LCD-Character-Creator/
*/
const byte icone_relogio[] = {
  0x0E,
  0x11,
  0x15,
  0x15,
  0x17,
  0x11,
  0x11,
  0x0E
};

const byte icone_Bandeira[] = {
  0x1F,
  0x15,
  0x1B,
  0x15,
  0x1F,
  0x11,
  0x11,
  0x11
};

const int intervalLCD = 250;                // atualiza a tela LCD a cada 250ms
unsigned long milisegundos_LCD_Anterior = 0;       // tempo em milissegundos da atualização anterior do LCD

//// DRUKKNOPPEN ////
const int intervalo_Leitura_Botao = 100;         // tempo em milissegundos entre a leitura do botão
unsigned long botao_Mili_Anterior = 0;   // tempo em milissegundos do último tempo de leitura do botão

const int pino_Botao_Iniciar = 12;             // pino do botão iniciar / parar
int botao_Inicia = LOW;                 // estado do botão iniciar / parar
int botao_IniciaPrevious = LOW;        // estado anterior do botão iniciar / parar

const int buttonResetPin = 10;              // pino do botão de redefinição
int botao_Reset = LOW;                // estado do botão de reset
int botao_ResetPrevious = LOW;         // estado anterior do botão de reset

bool redesenha_LCD = true;                     // indica se a tela precisa ser atualizada


//// CRONOMETRO ////
bool cronometro_Ativo = false;                // indica se o cronômetro está em execução
unsigned long cronometro_mili = 0;          // tempo em milissegundos em que o cronômetro começou a funcionar
unsigned long tempo_Cronometro_Decorrido = 0;     // tempo decorrido em milissegundos desde que o cronômetro começou a ser executado

// Inicia o cronometro
void Inicia_cronometro() {
  cronometro_mili = mili_Atual;
  cronometro_Ativo = true;
  redesenha_LCD = true;
}

// Para o cronometro
void cronometro_Para() {
  tempo_Cronometro_Decorrido = mili_Atual - cronometro_mili;
  cronometro_Ativo = false;
  redesenha_LCD = true;
}

// Reset do cronometro
void cronometro_Reset() {
  cronometro_Ativo = false;
  cronometro_mili = 0;
  tempo_Cronometro_Decorrido = 0;
  botao_Inicia = LOW;                  
  botao_IniciaPrevious = LOW;
  botao_Reset = LOW;                  
  botao_ResetPrevious = LOW;
  redesenha_LCD = true;
}

//// FUNÇÕES DE LAYOUT ////

// Garante que números abaixo de 10 obtenham um 0 extra, então 8 se tornará 08, 1 se tornará 01 etc.
String formatZeros(int number) {

  if (number < 10) {
    return "0" + String(number);
  } else {
    return String(number);
  }
}

// Faz o tempo em ms. uma String, por exemplo, "0: 01: 23.495" por 0 horas, 1 minuto, 23 segundos e 495 centésimos.
String formata_Tempo_para_String(unsigned long time) {

  unsigned long tempo_segundos = time / 1000;       // converte os milissegundos em segundos dividindo por 1000
  int msegundos = time % 1000;                    // os milissegundos restantes que permanecem após o compartilhamento

  int hours = tempo_segundos / 3600;                // calcula as horas dividindo por 3600 (3600 segundos = 60 segundos x 60 minutos)
  int restante = tempo_segundos % 3600;            // calcula os segundos restantes dividindo por 3600. (3600 segundos = 60 segundos x 60 minutos)

  int minutos = restante / 60;                  // calcula os minutos dividindo por 60 (1 minuto = 60 segundos)
  int segundos = restante % 60;                 // calcula os segundos dividindo por 60 (1 minuto = 60 segundos)

 // Marca de 9 -> "009" e de 87 -> "087"
  if (msegundos < 10) {
    msegundos = "00" + msegundos;
  } else if (msegundos < 100) {
    msegundos = "0" + msegundos;
  }

  return String(hours) + ":" + formatZeros(minutos) + ":" + formatZeros(segundos) + "." + String(msegundos);
}

/*
  * Calcula quanto espaço você tem que deixar ao lado para chegar ao meio
  * Defina sua tela com 20 de largura e seu texto com 16 de largura. Você quer manter 2 posições livres nos dois lados
  * Você pode usar o deslocamento se, por exemplo, colocar outro símbolo na frente do seu texto.
  */
int obter_Margem_Centro_LCD(String text, int offset) {
  int margem = LCDWidth - (text.length() + offset);
  return margem / 2;
}

// Função para ler o botão
void leitura_Posicao_Botao() {

 // Se a diferença horária com a leitura anterior for maior que intervalo_Leitura_Botao
  if (mili_Atual - botao_Mili_Anterior > intervalo_Leitura_Botao) {

  // Leia os valores digitais dos interruptores (BAIXO / ALTO)
    botao_Inicia = digitalRead(pino_Botao_Iniciar);
    botao_Reset = digitalRead(buttonResetPin);

   // Quando o botão Iniciar é pressionado
    if (botao_Inicia == HIGH && botao_IniciaPrevious == LOW) {

     // Se o cronômetro ainda não estiver funcionando, ele será iniciado. Se o cronômetro estiver funcionando, pare-o.
      if (!cronometro_Ativo) {
        Inicia_cronometro();
      } else {
        cronometro_Para();
      }

      botao_IniciaPrevious = HIGH;

    }

   // Quando o botão Iniciar é liberado e o cronômetro está em execução
    if (botao_Inicia == LOW && botao_IniciaPrevious == HIGH && cronometro_Ativo) {
      botao_IniciaPrevious = LOW;
    }

  // Se o botão de reset for pressionado, o cronômetro será redefinido
    if (botao_Reset == HIGH) {
      cronometro_Reset();
    }

    // salva a hora atual em botao_Mili_Anterior
    botao_Mili_Anterior = mili_Atual;

  }
}


// Função para atualizar a tela LCD
void atualiza_LCD() {

 // Se a diferença horária com a leitura anterior for maior que intervalLCD
  if (mili_Atual - milisegundos_LCD_Anterior > intervalLCD) {

    if (redesenha_LCD || cronometro_Ativo) {

      lcd.clear();

    // Se o stopwacth não estiver em execução e o tempo decorrido for 0
      if (!cronometro_Ativo && tempo_Cronometro_Decorrido == 0) {
        lcd.setCursor(0, 0);                 // move o cursor para a posição 1, linha 1
        lcd.print("     RACING MODE");
        lcd.setCursor(0, 2);                // move o cursor para a posição 1, linha 3
        lcd.print("  INICIAR / PAUSAR");
      }

      // Quando o cronômetro está funcionando
      if (cronometro_Ativo) {

       // Calcule o tempo decorrido e formate-o no formato U: MM: SS.m
        String hora_Formatada = formata_Tempo_para_String(mili_Atual - cronometro_mili);
        
       /* Calcule o centro do texto com obter_Margem_Centro_LCD (hora_Formatada, 4)
         // O deslocamento de 4 é devido às seguintes posições:
         // 1. o ícone do relógio
         // 2. o espaço atrás do ícone do relógio
         // 3. ms m
         // 4. ms s */
        lcd.setCursor(obter_Margem_Centro_LCD(hora_Formatada, 4), 1);

        lcd.write(0);                // desenha o ícone do relógio da posição de memória 0
        lcd.print(" ");              // escreve um espaço
        lcd.print(hora_Formatada);    // escreve o tempo decorrido
        lcd.print("ms");            // escreve ms
      }

   // Quando o cronômetro está parado
      if (!cronometro_Ativo && tempo_Cronometro_Decorrido > 0) {

     /* Calcular o centro do texto com obter_Margem_Centro_LCD (formata_Tempo_para_String (tempo_Cronometro_Decorrido), 2)
         // O deslocamento de 2 é devido às seguintes posições:
         // 1. o ícone final
         // 2. o espaço atrás do ícone de acabamento */
        lcd.setCursor(obter_Margem_Centro_LCD(formata_Tempo_para_String(tempo_Cronometro_Decorrido), 2), 1);

        lcd.write(1);                                 // desenha o ícone de acabamento da posição de memória 0
        lcd.print(" ");                               // escreve um espaço
        lcd.print(formata_Tempo_para_String(tempo_Cronometro_Decorrido));  // escreve o tempo decorrido passado
        lcd.setCursor(0, 3);                          // move o cursor para a posição 1, linha 4
        lcd.print("   TEMPO DA VOLTA");             
      }

      redesenha_LCD = false;
      
    }

  // salva a hora atual no milisegundos_LCD_Anterior
    milisegundos_LCD_Anterior = mili_Atual;

  }

}

void setup() {
  Serial.begin(9600);                  // define o monitor serial

  // LCD
  lcd.init();                          // inicializa a tela LCD
  lcd.backlight();                     // acende a luz de fundo
  lcd.createChar(0, icone_relogio);        // define um símbolo na posição 0 da memória
  lcd.createChar(1, icone_Bandeira);   // define um símbolo na posição 0 da memória
}

void loop() {

  mili_Atual = millis();            // salva a hora atual
  leitura_Posicao_Botao();                   // lê o estado atual dos fechos de pressão
  atualiza_LCD();                         // atualiza a tela LCD

}
