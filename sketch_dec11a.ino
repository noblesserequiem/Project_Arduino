#include <SparkFunTMP102.h>
#include <LiquidCrystal.h>
TMP102 sensor0(0x48);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
class comp_sistem
{
public:
 int pin;
  comp_sistem(int p)
  {
    pin=p;
  }
   
   
};

class temp
{
  
    
   public:
    float valoarec,valoaref;
    
   temp(float valc,float valf)
   {
    
    valoarec=valc;
    valoaref=valf;
    }
  
     
    
};
class button:public comp_sistem
{
   
  public:
  int valoare;
    button(int p,int val):comp_sistem(p)
    {
      valoare=val;
     }
     
      
};
class button_sw:public comp_sistem
{
 
  public:
    int valoare;
    button_sw(int p,int val):comp_sistem(p)
    {
      valoare=val;
      }
  };
class led
{
  public:
    int pin1,pin2;
    led(int p1,int p2)
    {
      p1=pin1;
      p2=pin2;
    }  
};  
button power(11,0);   //declarari componente
temp senzor(0,0);
button_sw switcher(10,2);
led led1(3,4);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
pinMode(11,INPUT);    //input butoane etc; output leds;
pinMode(10,INPUT);
pinMode(led1.pin1,OUTPUT);
pinMode(led1.pin2,OUTPUT);
sensor0.begin();

}
int state=0,oldbutton=0;   //state verifica daca este oprit/pornit; oldbutton verifica daca a fost inainte apasat sau nu, butonul ->pentru a functiona ca un switch

void loop() {

 power.valoare=digitalRead(11); //citim butonul start/stop
 if(power.valoare && !oldbutton)  //daca butonul este apasat si nu a fost deja apasat inainte; 
 {
   
  if(state == 0)  //verificam daca este pornit/oprit programul
   {
     analogWrite(led1.pin1,255);  //leduri, setare culoare
     analogWrite(led1.pin2,0);
     lcd.setCursor(0,0);
     lcd.clear();    
     lcd.print("Pornit");  
     state = 1;  //modifica state ->pornit
     sensor0.wakeup();   //porneste senzorul de temperatura
     senzor.valoarec=sensor0.readTempC();  //citeste temperatura
     senzor.valoaref=sensor0.readTempF();
     lcd.setCursor(0,1); 
     switcher.valoare=digitalRead(10);  //citim switchul
     if(switcher.valoare)
     lcd.print(senzor.valoarec);  //afisam temperaturile
     else
     lcd.print(senzor.valoaref);
   }
   else 
   {
    analogWrite(led1.pin1,0);
     analogWrite(led1.pin2,255);
     state = 0;
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Oprit");
   }
   oldbutton = 1;
 }
 else if(!power.valoare && oldbutton) 
 {
   
   oldbutton = 0;    
 }
}
