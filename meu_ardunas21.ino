#include <LiquidCrystal.h>   
#include "RTClib.h"       
#include <Wire.h>  
#include <EEPROM.h>
#include <Stepper.h>
#include <Ultrasonic.h>

#define pino_trigger 12 
#define pino_echo 13 
#define menu_max 4 

//*HC_SR04 sensor1(pino_trigger, pino_echo);  *//

const int stepsPerRevolution = 512;
const int pino_rele = 11;

Stepper myStepper(stepsPerRevolution, 0, 2, 1, 3);

RTC_DS1307 rtc;


void keyboardRead();
void keyboard();
void despejo1();
void despejo2();
void ultra();
void epson();
void menu1();
void menu2();
void menu3();
void menu4();



// --- Variáveis Globais ---
int adc_value = 0x00;                  


boolean right  = 0x00, butt01 = 0x00,
        up     = 0x00, butt02 = 0x00,
        down   = 0x00, butt03 = 0x00,
        left   = 0x00, butt04 = 0x00,
        select = 0x00, butt05 = 0x00;
  
int menu_num = 1, sub_menu = 1;

int AH, AM, AS, DI=1, ME=1, AN=2020, H1=0, H2=0, M1=0, M2=0, S1=0, S2=0, HH1=0, HH2=0, MM1=0, MM2=0, SS1=0, SS2=0;
        
// --- Hardware do LCD ---
LiquidCrystal lcd (8,  
                   9,  
                   4,  
                   5,  
                   6,  
                   7); 
        
        
void setup(){   
    
     myStepper.setSpeed(50);
     epson();
     lcd.begin(16,2);
     rtc.begin();      
     //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));              
     lcd.setCursor(0,0);                                 
     lcd.print("Alimentador 3000");   
     pinMode(pino_rele, OUTPUT);
     digitalWrite(pino_rele, HIGH);
     delay(3000);                     

} // setup cabou

void loop(){
  epson();
  keyboardRead();
  keyboard();
  despejo1();
  despejo2();
  switch(menu_num){
    case 1: menu1(); break;
    case 2: menu2(); break;
    case 3: menu3(); break;
    case 4: menu4(); break;
    
  }    
} //end loop

void menu1(){
       DateTime now = rtc.now();
       lcd.setCursor(0,0);
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
       if (now.hour()<10){
        lcd.print("0");
        lcd.print(now.hour());
        }
       else {lcd.print(now.hour());
       }
       lcd.print(":");
       if (now.minute()<10){
        lcd.print("0");
        lcd.print(now.minute());
        }
       else {lcd.print(now.minute());
       }
       lcd.print(":");
       if (now.second()<10){
        lcd.print("0");
        lcd.print(now.second());
        }
       else {lcd.print(now.second());
       }
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");

       lcd.setCursor(0,1);
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
       if (now.day()<10){
        lcd.print("0");
        lcd.print(now.day());
        }
       else {lcd.print(now.day());
       }
       lcd.print("/");
       if (now.month()<10){
        lcd.print("0");
        lcd.print(now.month());
        }
       else {lcd.print(now.month());
       }
       lcd.print("/");
       lcd.print(now.year());
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
       lcd.print(" ");
}

void menu2(){
       switch(sub_menu){
      case 1:
       lcd.setCursor(0,0);
       lcd.print("<Ajustar a Hora>");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
      case 2:
       lcd.setCursor(0,0);
       lcd.print(">>Ajuste Horas<<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(AH);
       lcd.print("       ");
       if (up == 0x01){
        AH += 1;
        up = 0x00;
        if (AH>23){
          AH=0;
          
        }
       }
       if (down == 0x01){
        AH -= 1;
        down = 0x00;
        if (AH<0){
          AH=23;
        }
       } 
       break;
      case 3:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Minutos<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(AM);
       lcd.print("       ");
       if (up == 0x01){
        AM += 1;
        up = 0x00;
        if (AM>59){
          AM=0;
          
        }
       }
       if (down == 0x01){
        AM -= 1;
        down = 0x00;
        if (AM<0){
          AM=59;
        }
       } 
       break;
      case 4:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Segundo<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(AS);
       lcd.print("       ");
       if (up == 0x01){
        AS += 1;
        up = 0x00;
        if (AS>59){
          AS=0;
          
        }
       }
       if (down == 0x01){
        AS -= 1;
        down = 0x00;
        if (AS<0){
          AS=59;
        }
       } 
       break;
      case 5:
       lcd.setCursor(0,0);
       lcd.print(">Que dia e hoje<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(DI);
       lcd.print("       ");
       if (up == 0x01){
        DI += 1;
        up = 0x00;
        if (DI>31){
          DI=1;
          
        }
       }
       if (down == 0x01){
        DI -= 1;
        down = 0x00;
        if (DI<1){
          DI=31;
        }
       } 
       break;
      case 6:
       lcd.setCursor(0,0);
       lcd.print("Qual o mes atual");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(ME);
       lcd.print("       ");
       if (up == 0x01){
        ME += 1;
        up = 0x00;
        if (ME>12){
          ME=1;
          
        }
       }
       if (down == 0x01){
        ME -= 1;
        down = 0x00;
        if (ME<1){
          ME=12;
        }
       } 
       break;
      case 7:
       lcd.setCursor(0,0);
       lcd.print("Qual o ano atual");
       lcd.setCursor(0,1);
       lcd.print("      ");
       lcd.print(AN);
       lcd.print("      ");
       if (up == 0x01){
        AN += 1;
        up = 0x00;
        if (AN>2099){
          AN=2020;
          
        }
       }
       if (down == 0x01){
        AN -= 1;
        down = 0x00;
        if (AN<2020){
          AN=2099;
        }
       } 
       break;
      case 8:
       menu_num=1;
       sub_menu=1;
       lcd.setCursor(0,1);
       lcd.print("                ");
       rtc.adjust(DateTime(AN, ME, DI, AH, AM, AS));
       break;
  }
}

void menu3(){
  switch(sub_menu){
     case 1:
       lcd.setCursor(0,0);
       lcd.print("Ajuste 1 Despejo");
       lcd.setCursor(0,1);
       lcd.print("    ");
       if (HH1<10){
        lcd.print("0");
        lcd.print(HH1);
       }
       else{
       lcd.print(HH1); 
       }
       lcd.print(":");
       if (MM1<10){
        lcd.print("0");
        lcd.print(MM1);
       }
       else{
       lcd.print(MM1); 
       }
       lcd.print(":");
       if (SS1<10){
       lcd.print("0");
       lcd.print(SS1);
       }
       else {
       lcd.print(SS1); 
       }
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print(">>Ajuste Horas<<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(H1);
       lcd.print("       ");
       if (up == 0x01){
        H1 += 1;
        up = 0x00;
        if (H1>23){
          H1=0;
          
        }
       }
       if (down == 0x01){
        H1 -= 1;
        down = 0x00;
        if (H1<0){
          H1=23;
        }
       } 
       break;
       case 3:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Minutos<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(M1);
       lcd.print("       ");
       if (up == 0x01){
        M1 += 1;
        up = 0x00;
        if (M1>59){
          M1=0;
          
        }
       }
      if (down == 0x01){
        M1 -= 1;
        down = 0x00;
        if (M1<0){
          M1=59;
        }
       } 
       break;
       case 4:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Segundo<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(S1);
       lcd.print("       ");
       if (up == 0x01){
        S1 += 1;
        up = 0x00;
        if (S1>59){
          S1=0;
          
        }
       }
       if (down == 0x01){
        S1 -= 1;
        down = 0x00;
        if (S1<0){
          S1=59;
        }
       }
       break;
       case 5:
        HH1=H1;
        MM1=M1;
        SS1=S1;
        EEPROM[1]=HH1;
        EEPROM[2]=MM1;
        EEPROM[3]=SS1;  
        menu_num=1;
        sub_menu=1;
        
       break;
  }
} 

void menu4(){
  
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("Ajuste 2 Despejo");
       lcd.setCursor(0,1);
       lcd.print("    ");
       if (HH2<10){
        lcd.print("0");
        lcd.print(HH2);
       }
       else{
       lcd.print(HH2); 
       }
       lcd.print(":");
       if (MM2<10){
        lcd.print("0");
        lcd.print(MM2);
       }
       else{
       lcd.print(MM2); 
       }
       lcd.print(":");
       if (SS2<10){
       lcd.print("0");
       lcd.print(SS2);
       }
       else {
       lcd.print(SS2); 
       }
       break;
          case 2:
       lcd.setCursor(0,0);
       lcd.print(">>Ajuste Horas<<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(H2);
       lcd.print("       ");
       if (up == 0x01){
        H2 += 1;
        up = 0x00;
        if (H2>23){
          H2=0;
          
        }
       }
       if (down == 0x01){
        H2 -= 1;
        down = 0x00;
        if (H2<0){
          H2=23;
        }
       }
       break;
       case 3:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Minutos<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(M2);
       lcd.print("       ");
       if (up == 0x01){
        M2 += 1;
        up = 0x00;
        if (M2>59){
          M2=0;
          
        }
       }
       if (down == 0x01){
        M2 -= 1;
        down = 0x00;
        if (M2<0){
          M2=59;
        }
       }
       break;
       case 4:
       lcd.setCursor(0,0);
       lcd.print(">Ajuste Segundo<");
       lcd.setCursor(0,1);
       lcd.print("       ");
       lcd.print(S2);
       lcd.print("       ");
       if (up == 0x01){
        S2 += 1;
        up = 0x00;
        if (S2>59){
          S2=0;
          
        }
       }
       if (down == 0x01){
        S2 -= 1;
        down = 0x00;
        if (S2<0){
          S2=59;
        }
       }
       break;
       case 5:
        HH2=H2;
        MM2=M2;
        SS2=S2;
        EEPROM[4]=HH2;
        EEPROM[5]=MM2;
        EEPROM[6]=SS2;
        menu_num=1;
        sub_menu=1;

        
       
       break;
  }
}

void keyboard(){
  
   if(right == 0x01 && sub_menu == 1)
   {
      if(menu_num < menu_max) 
      menu_num += 1;
      right = 0x00;
   } 

   if(left == 0x01 && sub_menu == 1)
   {
      if(menu_num >= 2) 
      menu_num -= 1;
      left = 0x00;
   } 
   if(select == 0x01 && sub_menu == 1 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 2 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 3 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 4 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 5 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 6 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 7 && menu_num == 2)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 1 && menu_num == 3)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 2 && menu_num == 3)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 3 && menu_num == 3)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 4 && menu_num == 3)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 1 && menu_num == 4)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 2 && menu_num == 4)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 3 && menu_num == 4)
   {
    sub_menu += 1;
    select = 0x00;
   }
   if(select == 0x01 && sub_menu == 4 && menu_num == 4)
   {
    sub_menu += 1;
    select = 0x00;
   }
   
   if(select == 0x01)
   {
    select = 0x00;
   }

   if(right == 0x01)
   {
    right = 0x00;
   }   
   
   if(left == 0x01)
   {
    left = 0x00;
   }    
}

void keyboardRead(){
          adc_value = analogRead(A0);                       //Variável para leitura recebe valor AD de A0

     // --- Testa se os botões foram pressionados ---
     // Se foi pressionado, seta a respectiva flag
     if      (adc_value <  70)                    butt01 = 0x01;
     else if (adc_value > 93 && adc_value < 210)  butt02 = 0x01;
     else if (adc_value > 230 && adc_value < 379) butt03 = 0x01;
     else if (adc_value > 395 && adc_value < 610) butt04 = 0x01;
     else if (adc_value > 630 && adc_value < 800) butt05 = 0x01;
     
    

     // --- Testa se os botões foram liberados ---
     //
     if (adc_value > 70 && butt01)             //Botão right solto e flag butt01 setada?
     {                                         //Sim...
         butt01 = 0x00;                        //Limpa flag butt01
         right  = 0x01;                        //Seta flag right
         
     } //end right
     if (adc_value > 210 && butt02)            //Botão up solto e flag butt02 setada?
     {                                         //Sim...
         butt02 = 0x00;                        //Limpa flag butt02
         up     = 0x01;                        //Seta flag up
      
     } //end up
     if (adc_value > 399 && butt03)            //Botão down solto e flag butt03 setada?
     {                                         //Sim...
         butt03 = 0x00;                        //Limpa flag butt03
         down   = 0x01;                        //Seta flag down
       
     } //end down
     if (adc_value > 600 && butt04)            //Botão left solto e flag butt04 setada?
     {                                         //Sim...
         butt04 = 0x00;                        //Limpa flag butt04
         left   = 0x01;                        //Seta flag left
       
     }
     if (adc_value > 800 && butt05)            //Botão left solto e flag butt04 setada?
     {                                         //Sim...
         butt05 = 0x00;                        //Limpa flag butt04
         select = 0x01;                        //Seta flag left
       
     }
} 

void epson(){
  if  (EEPROM[0]!= 23){
      EEPROM[0]=23;
      EEPROM[1]=HH1;
      EEPROM[2]=MM1;
      EEPROM[3]=SS1;
      EEPROM[4]=HH2;
      EEPROM[5]=MM2;
      EEPROM[6]=SS2;

     
     }
      else{
        HH1=EEPROM[1];
        MM1=EEPROM[2];
        SS1=EEPROM[3];
        HH2=EEPROM[4];
        MM2=EEPROM[5];
        SS2=EEPROM[6];

      }
     
}

void despejo1(){
  DateTime now = rtc.now();
  if (HH1 == now.hour() && MM1 == now.minute() && SS1 == now.second())
  {   
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALIMENTADOR 3000");
      lcd.setCursor(0,1);
      lcd.print("    INICIADO    ");
      digitalWrite(11, LOW);
      delay(500);
      myStepper.step(-5120);
      myStepper.step(-5120);
      myStepper.step(-5120);
      digitalWrite(11, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALIMENTADOR 3000");
      lcd.setCursor(0,1);
      lcd.print("   FINALIZADO   ");
      delay(2000);
  }
}

void despejo2(){
  DateTime now = rtc.now();
  if (HH2 == now.hour() && MM2 == now.minute() && SS2 == now.second())
  {  
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALIMENTADOR 3000");
      lcd.setCursor(0,1);
      lcd.print("    INICIADO    ");
      digitalWrite(11, LOW);
      delay(500);
      myStepper.step(-5120);
      myStepper.step(-5120);
      myStepper.step(-5120);
      digitalWrite(11, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALIMENTADOR 3000");
      lcd.setCursor(0,1);
      lcd.print("   FINALIZADO   ");
      delay(2000);
      
  }
}





