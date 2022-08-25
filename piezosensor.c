
//---------------------including all required libraries---------------------------------------
//#include<Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h> // for lcd
#include <Adafruit_MPU6050.h> // for mpu6050 all 3 libraries are necessary
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

//----------------------------------------declaring pins and variables------------------------------


int buz_pin=13;  //output pins definition.
int red_led=8;
int green_led=9;

//initilizig lcd with constrcutor..
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // 
int Piezo_pin = A0;   //
int frequncy;

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void setup() {  
  Serial.begin(115200);
   while (!Serial);
   pinMode(buz_pin, OUTPUT);
   pinMode(red_led, OUTPUT);
  Serial.println("MPU6050 OLED demo");
///---------------//
  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  //-----------------------//
   lcd.begin(16, 2);
}
//-----------------------lopppp part starts here-----------------------------------------------------------

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
int val=analogRead(Piezo_pin);
float voltage = val * (5.0 / 1023.0);
digitalWrite(green_led,HIGH);

//------------------------piezo lcd  start----------------------
if(voltage>1) //threshold voltage excedded....
  {
    
     digitalWrite(red_led, HIGH);
     digitalWrite(buz_pin,HIGH);
//    Serial.print("Buzzzzzzzzzzzzzzzzerrr");
    digitalWrite(green_led,LOW);
    delay(500);
    digitalWrite(buz_pin,LOW);
    digitalWrite(green_led,HIGH);
    digitalWrite(red_led, LOW);
    
  }
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("piezo:");
  lcd.setCursor(10, 0);
   lcd.print(voltage);
//------------------------piezo lcd  end----------------------
//  Serial.print("Accelerometer ");
//  Serial.print("X: ");
//  Serial.print(a.acceleration.x, 1);
//  Serial.print(" m/s^2, ");
//  Serial.print("Y: ");
//  Serial.print(a.acceleration.y, 1);
//  Serial.print(" m/s^2, ");
//  Serial.print("Z: ");
//  Serial.print(a.acceleration.z, 1);
//  Serial.println("m/s^2");
//

//------------------------This is for accelerometer values in lcd-----------------------------------------
  delay(500);
   lcd.clear();
   lcd.setCursor(0, 0); 
 
   lcd.print("Acc:");
   lcd.setCursor(7, 0);
   lcd.print(a.acceleration.x, 1);
   lcd.setCursor(0, 1);
   lcd.print(a.acceleration.y, 1);
   lcd.setCursor(6, 1);
   lcd.print(a.acceleration.z, 1);
   lcd.setCursor(11, 1);
   lcd.print("m/s^2");

   //----------------------------------end Accelero--------------------------------------------
//  Serial.print("Gyroscope ");
//  Serial.print("X: ");
//  Serial.print(g.gyro.x, 1);
//  Serial.print(" rps, ");
//  Serial.print("Y: ");
//  Serial.print(g.gyro.y, 1);
//  Serial.print(" rps, ");
//  Serial.print("Z: ");
//  Serial.print(g.gyro.z, 1);
//  Serial.println(" rps");

//------------------------This is for gyro values in lcd-----------------------------------------
    delay(500);

   lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Gyro");
    lcd.setCursor(8, 0);
   lcd.print(g.gyro.x, 1);
   lcd.setCursor(0, 1);
   lcd.print(g.gyro.y, 1);
   lcd.setCursor(6, 1);
   lcd.print(g.gyro.z, 1);
   lcd.setCursor(11, 1);
   lcd.print("rps");
}
