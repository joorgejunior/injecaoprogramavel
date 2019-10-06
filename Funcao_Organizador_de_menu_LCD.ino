//#include <LiquidCrystal.h>  //Importar a LCD library.<br><br>//Definir os pinos de comunicação e informação do LCD.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27,20,4);

int Botao_mais = 2; //Variável para selecção do pino digital (Botão 1).
int Botao_menu = 3; //Variável para selecção do pino digital (Botão 2).
int Botao_menos = 4;  //Variável para selecção do pino digital (Botão 3).

int Num_Menu = 0;       //Variável para selecção da página.
int Num_titulo = 1;     //Variável para selecção do titulo da página.

//Variável para os títulos das páginas.
char* Titulo_Menu[] = {"Menu - 0",
                       
                       "Pagina - 1",                   
                       "Menu - 2",
                       "Menu - 3",
                       "Pagina - 4",
                       
                       "Pagina - 2.1", "Pagina - 2.2",
                       "Pagina - 3.1", "Pagina - 3.2", "Pagina - 3.3"};

//Correr a função SETUP apenas uma vez após ser pressionado Reset:
void setup(){
  //Iniciar a Comunicação com LCD de 16x2:
  lcd.begin(4, 20);
  
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_mais, INPUT);
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_menu, INPUT);
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_menos, INPUT);
}

//Correr a função LOOP repetidamente:
void loop(){
  //Correr a função:
  Pagina_Menu_0();
  //Correr a função:
  Pagina_1();
  //Correr a função:
  Pagina_Menu_2();
  //Correr a função:
  Pagina_2_1();
  //Correr a função:
  Pagina_2_2();
  //Correr a função:
  Pagina_Menu_3();
  //Correr a função:
  Pagina_3_1();
  //Correr a função:
  Pagina_3_2();
  //Correr a função:
  Pagina_3_3();
  //Correr a função:
  Pagina_4();
  
  //Atraso para o próximo passo:
  delay(800);
}

//Página do Menu - 0:
void Pagina_Menu_0(){
  //Condição para abrir página:
  if (Num_Menu == 0){
    //Apaga a informação do LCD.
    lcd.clear();
    //Condição para escrever no LCD os nomes das páginas:
    if (Num_titulo > 0 & Num_titulo < 3){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[1]);
            
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[2]);
    }
    //Condição para escrever no LCD os nomes das páginas:
    else if (Num_titulo > 2 & Num_titulo < 5){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[3]);
      
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[4]);
    }
        
    //Condição para selecionar página 1 e 3:
    if (Num_titulo == 1 || Num_titulo == 3){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar página 2 e 4:
    else if (Num_titulo == 2 || Num_titulo == 4){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
  
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo >= 1){
        //Altera o valor de selecção do título do menu.
        Num_titulo = Num_titulo + 1;
      }
      //Condição para selecionar página:
      if (Num_titulo > 4){
        //Altera o valor de selecção do título do menu.
        Num_titulo = 4;
      } 
    }  
      
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo < 1){
        //Altera o valor de selecção do título do menu.
        Num_titulo = 1;
      }
      //Condição para selecionar página:
      if (Num_titulo <= 4){
        //Altera o valor de selecção do título do menu.
        Num_titulo = Num_titulo - 1;
      }
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo == 1){
        //Altera o valor de selecção do menu.
        Num_Menu = 1;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 2){
        //Altera o valor de selecção do título do menu.
        Num_titulo = 5;
        //Altera o valor de selecção do menu.
        Num_Menu = 2;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 3){
        //Altera o valor de selecção do título do menu.
        Num_titulo = 7;
        //Altera o valor de selecção do menu.
        Num_Menu = 3;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 4) {
        //Altera o valor de selecção do menu.
        Num_Menu = 4;
      }
    }
  }
}

//Pagina do Menu - 1:
void Pagina_1(){
  //Condição para abrir página:
  if (Num_Menu == 1){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[Num_titulo]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH){
      //Altera o valor de selecção do menu.
      Num_Menu = 0;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH){
      //Não realiza nenhuma acção.
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH){
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 2:
void Pagina_Menu_2(){
  //Condição para abrir página:
  if (Num_Menu == 2){
    //Apaga a informação do LCD.
    lcd.clear();     
    //Condição para escrever no LCD os nomes das páginas:
    if (Num_titulo == 5 || Num_titulo == 6){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[5]);
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[6]);
    }
    //Condição para selecionar página 2.1:
    if (Num_titulo == 5){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar página 2.2:
    else if (Num_titulo == 6){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH){      
      //Condição para selecionar página:
      if (Num_titulo == 5){
        //Altera o valor de selecção do título do menu.
        Num_titulo = Num_titulo + 1;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 6){
        //Altera o valor de selecção do título do menu.
        Num_titulo = Num_titulo - 1;
      } 
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH){
      //Altera o valor de selecção do título do menu.
      Num_titulo = 2;
      //Altera o valor de selecção do menu.
      Num_Menu = 0;
    }
        
    //Atraso para o próximo passo:
    delay(800);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo == 5){
        //Altera o valor de selecção do menu.
        Num_Menu = 5;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 6){
        //Altera o valor de selecção do menu.
        Num_Menu = 6;  
      }
    }
  }
}

//Página do Menu - 2.1:
void Pagina_2_1(){
  //Condição para abrir página:
  if (Num_Menu == 5){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[5]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
        
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH) {
      //Altera o valor de selecção do menu.
      Num_Menu = 2;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 2.2:
void Pagina_2_2() {
  //Condição para abrir página:
  if (Num_Menu == 6){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[6]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH) {
      //Altera o valor de selecção do menu
      Num_Menu = 2;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH) {
      //Não realiza nenhuma acção.
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 3:
void Pagina_Menu_3(){
  //Condição para abrir página:
  if (Num_Menu == 3){
    //Apaga a informação do LCD.
    lcd.clear();
    //Condição para escrever no LCD os nomes das páginas:
    if (Num_titulo > 6 & Num_titulo < 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[7]);
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[8]);
    }
    //Condição para escrever no LCD os nomes das páginas:
    else if (Num_titulo == 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[9]);
    }
    //Condição para selecionar pagina 3.1:
    if (Num_titulo == 7 || Num_titulo == 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar pagina 3.2:
    else if (Num_titulo == 8){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo >= 7){
        //Altera o valor de selecção do título do menu.
        Num_titulo = Num_titulo + 1;
      }
      //Condição para selecionar página:
      if (Num_titulo > 9){
        //Altera o valor de selecção do título do menu.
        Num_titulo = 7;
      } 
    }  
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH){
      //Altera o valor de selecção do titulo do menu.
      Num_titulo = 3;
      //Altera o valor de selecção do menu.
      Num_Menu = 0;
    }
    
    //Atraso para o próximo passo:
    delay(800);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH){
      //Condição para selecionar página:
      if (Num_titulo == 7){
        //Altera o valor de selecção do menu.
        Num_Menu = 7;
      }
      //Condição para selecionar página:
      else if (Num_titulo == 8){
        //Altera o valor de selecção do menu.
        Num_Menu = 8;
      }
      //Condição para selecionar pagina:
      else if (Num_titulo == 9){
        //Altera o valor de selecção do menu.
        Num_Menu = 9;
      }
    }
  }
}

//Página do Menu - 3.1:
void Pagina_3_1() {
  //Condição para abrir página:
  if (Num_Menu == 7){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[7]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH) {
      //Altera o valor de selecção do menu.
      Num_Menu = 3;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH) {
      //Não realiza nenhuma acção.
    }
  }
}
//Página do Menu - 3.2:
void Pagina_3_2() {
  //Condição para abrir página:
  if (Num_Menu == 8){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[8]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH) {
      //Altera o valor de selecção do menu.
      Num_Menu = 3;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do menu - 3.3:
void Pagina_3_3() {
  //Condição para abrir página:
  if (Num_Menu == 9){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[9]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH) {
      //Altera o valor de selecção do menu.
      Num_Menu = 3;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 4:
void Pagina_4() {
  //Condição para abrir página:
  if (Num_Menu == 4){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[Num_titulo]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Info:TEXTO...");

    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menos) == HIGH){
      //Altera o valor de selecção do menu.
      Num_Menu = 0;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_menu) == HIGH){
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_mais) == HIGH){
      //Não realiza nenhuma acção.
    }
  }
}
