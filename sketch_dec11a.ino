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
  private:
  int valoare;
  public:
    button_sw(int p,int val):comp_sistem(p)
    {
      valoare=val;
      }
  };
button power(11,0);
temp senzor(0,0);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
pinMode(11,INPUT);
sensor0.begin();

}
int state=0,oldbutton=0;

void loop() {

 power.valoare=digitalRead(11);
 if(power.valoare && !oldbutton) 
 {
   
  if(state == 0)
   {
     lcd.setCursor(0,0);
     lcd.clear();
     lcd.print("Pornit");
     state = 1;
     sensor0.wakeup();
     senzor.valoarec=sensor0.readTempC();
     senzor.valoaref=sensor0.readTempF();
     lcd.setCursor(0,1);
     lcd.print(senzor.valoarec);
     lcd.print(senzor.valoaref);
   }
   else 
   {
    
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
