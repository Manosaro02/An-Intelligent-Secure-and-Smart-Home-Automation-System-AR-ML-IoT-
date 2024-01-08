

#include&lt;LiquidCrystal.h&gt;
LiquidCrystal lcd(13,12,11,10,9,8);
/***************************************************************/
#include &lt;Servo.h&gt;
int servoPin = 3;
Servo Servo1;
/****************************************************************/
int PWM_out_pin = 6; // Must be one of 3, 5, 6, 9, 10, or 11

byte PWM_out_level;

#include &lt;Adafruit_Sensor.h&gt;
#include &quot;DHT.h&quot;
#define DHTPIN A0 // what pin we&#39;re connected to
#define DHTTYPE DHT11 // DHT 11

int t;
DHT dht(DHTPIN, DHTTYPE);


void setup()

{

Serial.begin(9600);
// put your setup code here, to run once:
lcd.begin(16,2);
dht.begin();
Servo1.attach(servoPin);

pinMode(A5,OUTPUT);///buzzer

lcd.setCursor(0,0);
lcd.print(&quot; Home &quot;);
lcd.setCursor(0,1);
lcd.print(&quot;Security System&quot;);

pinMode(PWM_out_pin, OUTPUT);
PWM_out_level = 255;
analogWrite( PWM_out_pin, PWM_out_level);


pinMode(A0,INPUT); //temperature

delay(2000);
lcd.clear();

}

void loop()
{
if(Serial.available()&gt;0)
{
char Y = Serial.read();
if (Y==&#39;1&#39;)
{

lcd.setCursor(0,1);
lcd.print(&quot;Buz ON Door Close &quot;);
Servo1.write(0);
digitalWrite(A5,HIGH);
delay(2000);



digitalWrite(A5,LOW);

}

if (Y==&#39;2&#39;)
{
lcd.setCursor(0,1);
lcd.print(&quot;Door Open &quot;);

digitalWrite(A5,LOW);
Servo1.write(180);
delay(5000);
Servo1.write(0);
}
}

dht11();
}
void dht11()
{



int h = dht.readHumidity();
t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f))
lcd.setCursor(0,0);
lcd.print(&quot;T:&quot;);
lcd.setCursor(2,0);
lcd.print(t);
lcd.print(&quot; &quot;);
if(t&gt;30 &amp;&amp; t&lt;40)
{
lcd.setCursor(5,0);
lcd.print(&quot;T:Low Speed &quot;);
PWM_out_level = 100;
analogWrite( PWM_out_pin, PWM_out_level);
}
else if(t&gt;40 &amp;&amp; t&lt;45)

{


lcd.setCursor(5,0);
lcd.print(&quot;T:Midium Speed &quot;);
PWM_out_level = 180;
analogWrite( PWM_out_pin, PWM_out_level);
}
else if(t&gt;45 &amp;&amp; t&lt;70)
{
lcd.setCursor(5,0);
lcd.print(&quot;T:High Speed &quot;);
PWM_out_level = 255;
analogWrite( PWM_out_pin, PWM_out_level)
}
}
