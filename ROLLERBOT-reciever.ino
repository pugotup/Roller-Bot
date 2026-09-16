#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo leftServo;
Servo rightServo;

const int LEFT_SERVO-PIN = 0;
const int RIGHT_SERVO_PIN = 1;

struct PacketData {
  int leftJoystickValue;
  int rightJoystickValue;
  bool trickButton1;
  bool trickButton2;
};

PacketData incomingData;

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingByte, int len) {
  int leftSpeed = map (incomingData.leftJoystickValue, 0, 4095, 0, 180);
  int rightSpeed = map (incomingData.rightJoystickValue, 0, 4095, 0, 180);

  if (incomingData.trickButton1 == false && incomingData.trickButton2 == false){
    leftServo.write(leftSpeed);
    rightServo.write (rightSpeed);
  }
  else if (incomingData.trickButton1 == true) {
    leftServo.write(180)
    rightServo.write (0);
  }
  else if (incomingData.trickButton2 == true) {
    leftServo.write(0)
    rightServo.write (180);
  }
}

void setup() {
  Serial.begin(115200);

  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  leftServo.write (90);
  rightServo.write(90);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK){
    return:
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

}

void loop(){
}






























void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
