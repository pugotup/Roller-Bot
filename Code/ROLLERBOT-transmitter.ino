#include <esp_now.h>
#include <WiFi.h>

const int LEFT_JOY_PIN = 0;
const int RIGHT_JOY_PIN = 1;
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;

uint8_t robotMacAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct PacketData {
  int leftJoystickValue;
  int rightJoystickValue
  bool trickButton1;
  bool trickButton2;
};

PacketData txData;
esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);

  pinMode(Button_1_PIN, INPUT_PULLUP);
  pinMode(Button_2_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK){
    return;
  }

  memcpy(peerInfo.peer_addr,robotMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    return;
  }
}

void loop(){
  txData.leftJoystickValue = analogRead(LEFT_JOY_PIN);
  txData.rightJoystickValue = analogRead(RIGHT_JOY_PIN);

  txData.trickButton1 = (digitalRead(BUTTON_1_PIN) == LOW);
  txData.trickButton2 = (digitalRead(BUTTON_2_PIN) == LOW);

  esp_now_send(robotMacAddress, (uint8_t *) &txData, sizeof(txData));

  delay(20);
}