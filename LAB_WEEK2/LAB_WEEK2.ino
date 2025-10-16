#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver idektep = Adafruit_PWMServoDriver(0x40);

// กำหนดช่วงของ PWM สำหรับเซอร์โว
#define SERVOMIN  100
#define SERVOMAX  600

// กำหนด Servo Channel
#define servo1 0
#define servo2 ____ // กำหนด Servo2 ให้เป็น Channel 1

// กำหนดขา Push Button
#define btn_up1    12   // ปุ่มเพิ่มมุม เซอร์โว 1
#define btn_down1  14   // ปุ่มลดมุม เซอร์โว 1
#define btn_up2    _____   // เพิ่มการกำหนดขา Pin G25 เป็นปุ่มเพื่อเพิ่มมุม เซอร์โว 2
#define btn_down2  _____   // เพิ่มการกำหนดขา Pin G26 เป็นปุ่มเพื่อลดมุม เซอร์โว 2
#define btn_home   17   // ปุ่มกลับ Home สำหรับทุกเซอร์โว

// เริ่มที่มุม 90 องศา (home)
int currentAngle1 = 90;  // มุมเริ่มต้นเซอร์โว 1
int currentAngle2 = 90;  // มุมเริ่มต้นเซอร์โว 2

// แปลงค่ามุมเป็นพัลส์
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

// ฟังก์ชันควบคุมเซอร์โวแต่ละตัว
void moveServo(uint8_t servo, int ang) {
  int pulse = angleToPulse(ang);
  idektep.setPWM(servo, 0, pulse);
  Serial.print("Servo ");
  Serial.print(servo);
  Serial.print(" Angle: ");
  Serial.println(ang);
}

void setup() {
  Serial.begin(115200);
  idektep.begin();
  idektep.setPWMFreq(60);

  // ตั้งค่าขา push button
  pinMode(btn_up1, INPUT_PULLUP);   // ตั้งค่าขา btn_up1 เป็น INPUT_PULLUP
  pinMode(btn_down1, INPUT_PULLUP); // ตั้งค่าขา btn_down1 เป็น INPUT_PULLUP
  pinMode(btn_up2, ___________);    // ตั้งค่าขา btn_up2 เป็น INPUT_PULLUP
  pinMode(btn_down2, ___________);  // ตั้งค่าขา btn_down2 เป็น INPUT_PULLUP
  pinMode(btn_home, INPUT_PULLUP); // ตั้งค่าขา btn_home เป็น INPUT_PULLUP

  // ตำแหน่งเริ่มต้น
  moveServo(servo1, currentAngle1);
  moveServo(servo2, currentAngle2);
}

void loop() {
  // ควบคุมเซอร์โว 1
  if (digitalRead(btn_up1) == LOW) {
    if (currentAngle1 < 180) {
      currentAngle1 += 10;
      moveServo(servo1, currentAngle1);
      delay(200);
    }
  }
  if (digitalRead(btn_down1) == LOW) {
    if (currentAngle1 > 0) {
      currentAngle1 -= 10;
      moveServo(servo1, currentAngle1);
      delay(200);
    }
  }

  // ควบคุมเซอร์โว 2
  if (digitalRead(btn_up2) == LOW) {
    if (currentAngle2 < 180) {
      currentAngle2 += 10;
      moveServo(servo2, currentAngle2);
      delay(200);
    }
  }
  if (digitalRead(btn_down2) == LOW) {
    if (currentAngle2 > 0) {
      currentAngle2 -= 10;
      moveServo(servo2, currentAngle2);
      delay(200);
    }
  }

  // ปุ่มกลับสู่ตำแหน่ง Home
  if (digitalRead(btn_home) == LOW) {
    currentAngle1 = 90;  // มุมเริ่มต้นเซอร์โว 1
    currentAngle2 = ___;  // เพิ่มมุมเริ่มต้นเซอร์โว 2 ที่ 90 องศา
    moveServo(servo1, currentAngle1);
    moveServo(servo2, currentAngle2);
    delay(200);
  }
}
