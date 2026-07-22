// 라이브러리설치(koco 검색하여 kocoafab 설)
//  부저(4), 서보모터(6~7), LED(9~10), LCD
//  적외선(ir,3), 온습도(dht,5),  터치센서(8), 조도(cds,A1)

#include <DHT.h>      //온습도센서 사용 라이브러리(설치가 필요함)
#include <Servo.h>    //온습도센서 사용 라이브러리
#include <Wire.h>     // LCD 사용 라이브러리
#include <LiquidCrystal_I2C.h>  // LCD 사용 라이브러리(설치가 필요함)

DHT dht(5, DHT11);   // DHT11 온습도센서 사용위한 핀 번호와 센서 종류 지정 객체 생성
LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C방식의 16x2 LCD를 주소 0x27에 연결해 사용하는 객체 생성
Servo myservo1;  // 서보모터 제어위한 Servo 객체를 생성하는 코드
Servo myservo2;  // 서보모터 제어위한 Servo 객체를 생성하는 코드


void setup() {
  Serial.begin(9600);            
  dht.begin();                   // 온습도센서 사용 준비 
  lcd.init();  lcd.backlight();  // LCD 사용 준비
  pinMode(3, INPUT);        // 적외선장애물감지센서 핀모드 설정
  pinMode(5, INPUT);       //온습도센서
  myservo1.attach(6);      // 서보모터 사용 준비
  myservo2.attach(7);      // 서보모터 사용 준비
  pinMode(8, INPUT);       //터치센서
    }

void loop() {
  int cds = analogRead(A1);       // 조도센서 값 cds에 저장 (0 ~ 1023)
  int ir = digitalRead(3);        // 적외선장애물감지센서 값 ir에 저장(0, 1)
  int touch = digitalRead(8); // 터치센서값 touch에 저장
  float t = dht.readTemperature();  // 온도 값 temp에 저장
  float h = dht.readHumidity();      // 습도 값 hum에 저장

  Serial.println(touch);

  if (cds >= 700) { analogWrite(9, 255);  }   //스마트전등 구현
    else { analogWrite(9, 0);  }

  // LCD에 온습도 값 출력(온습도센서, LCD)
  lcd.setCursor(0, 0);  lcd.print("Temp : ");  lcd.print(t);  
  lcd.setCursor(0, 1);  lcd.print("humi : ");  lcd.print(h);   
 
  if (t>=30 or h>=70) { analogWrite(11, 255);  }  //에이컨 켜기
    else { analogWrite(11, 0);  }

   if (ir == 0) { tone(4, 220);   }    //장애물 위험 감지
    else { noTone(4);    }

  if (정해진 시간이 되면 ) { tone(4, 220); myservo1.write(90); }    //약먹을시간 서랍장 열기
   else {  noTone(4);  myservo1.write(0);    }

    if (touch == 1) { myservo2.write(90);  }     // 로봇과 공감 위로
    else { myservo2.write(0);   }

  delay(200);
}