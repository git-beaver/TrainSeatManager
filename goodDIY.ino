#include <SPI.h>
#include <MFRC522.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h> // 블루투스 통신을 위한 SoftwareSerial 라이브러리를 불러온다.

#define SDA_PIN 10
#define RST_PIN 5

SoftwareSerial BTSerial(2, 3); // SoftwareSerial(RX, TX)

int pressPin4 = A0; //pressure sensor to Arduino A2
int pressPin5 = A1;
int pressPin6 = A2;
int pinLED = 8;
int count = 3;
int what = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
int ledValue;
int reading1, reading2, reading3; //variable for storing current pressure reading


MFRC522 rfid(SDA_PIN,RST_PIN);

void setup()
{

  Serial.begin(9600); //Setup a serial connection for debug.
  SPI.begin();
  reading1 = analogRead(pressPin4); //Reading equals the value, returned by the sensor.
  reading2 = analogRead(pressPin5);
  reading3 = analogRead(pressPin6);
  rfid.PCD_Init();
  pinMode(pinLED, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  //블루투스 코드
  BTSerial.begin(9600);
}
void loop()
{
  digitalWrite(pinLED, LOW);
  int count = 6;
  int a[] = {1,2,3,4,5,6};
  reading1 = analogRead(A0); //Reading equals the value, from the sensor
  reading2 = analogRead(A1);
  reading3 = analogRead(A2);
  ledValue = analogRead(8);
a[3] = 0; count--;
a[4] = 0; count--;


  if(reading1 > 50) //If reading is less than 90%,
  { //of the initial sensor value,
    String sendMessage = "1";
    BTSerial.println(sendMessage); 
    Serial.println(sendMessage);
    a[0] = 0; 
    count--;
  } else if(reading1 <50) BTSerial.println("4");

  if(reading2 > 50)
  {
    String sendMessage = "2";
    BTSerial.println(sendMessage); 
    Serial.println(sendMessage);
    a[1] = 0;
    count--;     
  }  else if(reading2 <50)BTSerial.println("5");

  if(reading3 > 50) {
    if(!rfid.PICC_IsNewCardPresent()) {
      if(!rfid.PICC_ReadCardSerial()) {
        String sendMessage = "3";
        BTSerial.println(sendMessage); 
        Serial.println(sendMessage);
        digitalWrite(pinLED, HIGH);
      a[2] = 0; 
      count--;
    }
  } else {
    String sendMessage = "3";
    BTSerial.println(sendMessage); 
    Serial.println(sendMessage);
    digitalWrite(pinLED, HIGH);
    a[2] = 0;
     count--;



  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

String strID = "";
for(byte i = 0; i < 4; i++){
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "")+
    String(rfid.uid.uidByte[i], HEX)+
    (i != 3 ? ":" : "");
  }
  strID.toUpperCase();

 if(strID.indexOf("F6 : 90 : B9 : F8")){
    digitalWrite(pinLED,LOW);
  }
  else{
      digitalWrite(pinLED,HIGH);
    }
   
rfid.PICC_HaltA();
  }
} else if(reading3 <50)BTSerial.println("6");

    lcd.setCursor(1,0);           // 1번째 줄 2번째 셀부터 입력하게 합니다.
    lcd.print("There are");
    lcd.setCursor(1,1);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print(count); // count는 남은 좌석 갯수
    lcd.setCursor(2,1);
    lcd.print("seats left");

    delay(1000); // 2초간 대기
    lcd.clear(); // lcd 초기화

    lcd.setCursor(1,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("Empty seats");
    lcd.setCursor(1,1);
    lcd.print(":");
    for ( int i = 0; i<6;i++){
      
      if( a[i] != 0 ){
      lcd.print(" ");
      lcd.print(a[i]);}
      
    }
    
    delay(1000); // 2초간 대기
    lcd.clear(); // lcd 초기화

    
}
