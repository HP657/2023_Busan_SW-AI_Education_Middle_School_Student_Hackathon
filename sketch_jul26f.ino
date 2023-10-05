#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial BT06(12, 13);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int RED = 11; //RED 11번핀
int GREEN = 10; //GREEN 10번핀
int BLUE = 9; //BLUE 9번핀

void setup()
{
  pinMode(5,OUTPUT); //부저는 5번핀
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
  lcd.init();      //LCD모니터 초기화
  lcd.backlight(); //LCD모니터 배경설정
  Serial.begin(9600); //시리얼 모니터
  BT06.begin(9600); //블루투스 연결
}

void loop(){
  int a = digitalRead(2); //변수 a는 수위센서(2번핀)
  int b = digitalRead(3); //변수 b는 수위센서(3번핀)
    lcd.init(); //LCD모니터 초기화
  if(a==0){      // 만약 a가 0이라면
    noTone(5);     //페에조 부저 소리 끄기
    lcd.setCursor(6,0); //LCD모니터 6,0 좌표에서부터 출력
    lcd.print("GOOD");    //LCD모니터 출력
    Serial.println("GOOD"); //시리얼 모니터에 "GOOD"출력
    analogWrite(RED,0);   //RED LED 끄기
    analogWrite(GREEN,0); //GREEN LED 끄기
    analogWrite(BLUE,0); //BLUE LED 끄기
    delay(1000); //1초 기다리기
  }
  else{ //만약 a가 0이 아니라면
    if(b==0){ //만약 b가 0이라면
    lcd.setCursor(5,1); //LCD모니터 (6,0) 좌표에서부터 출력
    lcd.print("WARNING"); //LCD모니터에 "WARNING" 출력
    Serial.println("WARNING"); //시리얼 모니터에 "WARNING" 출력
    analogWrite(RED,255); //RED LED 끄기
    analogWrite(GREEN,255); //GREEN LED 끄기
    analogWrite(BLUE,255); //BLUE LED 끄기
    tone(5,329);   //피에조 부저로 4옥타브 미 소리내기
    delay(500); //0.5초 기다리기
    tone(5,783); //피에조 부저로 5옥타브 솔 소리내기
    }
    else{ //만약 b가 0이 아니라면
    BT06.print(1);// 블루투스로 1 보내기
    lcd.setCursor(5,1);  //LCD모니터 (6,0) 좌표에서부터 출력
    lcd.print("DANGER"); //LCD모니터에 "DANGER" 출력
    Serial.println("DANGER"); //시리얼 모니터에 "WARNING" 출력
    analogWrite(RED,255); //RED LED 켜기
    analogWrite(GREEN,0); //GREEN LED 끄기
    analogWrite(BLUE,0); //BLUE LED 끄기 
    tone(5,1318);  // 피에조 부저로 6옥타브 미 소리내기
    delay(500); //0.5초 기다리기
    tone(5,1567); //피에조 부저로 7옥타브 솔 소리내기
    }
    }
  } 