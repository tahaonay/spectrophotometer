#include <AccelStepper.h>

const int LDR1_PIN = A0;
const int LDR2_PIN = A1;
const int LDR3_PIN = A2;
const int PHOTODIODE_PIN = A3;

const int OLED_SDA_PIN = A4;
const int OLED_SCL_PIN = A5;

const int DIR_PIN = 2;
const int STEP_PIN = 3;
const int MS2_PIN = 8;
const int MS1_PIN = 9;
const int ENABLE_PIN = 10;

const int ENDSTOP_PIN = 7;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
//------------------------------------------------------
String komut;
boolean kalibrasyonModu = false;
//------------------------------------------------------

void setup() {
  Serial.begin(9600);

  pinMode(LDR1_PIN, INPUT);
  pinMode(LDR2_PIN, INPUT);
  pinMode(LDR3_PIN, INPUT);
  pinMode(PHOTODIODE_PIN, INPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);
  pinMode(MS1_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(ENDSTOP_PIN, INPUT_PULLUP);
  
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop() {
  digitalWrite(ENABLE_PIN, HIGH);
  int ldr1Value = analogRead(LDR1_PIN);
  int ldr2Value = analogRead(LDR2_PIN);
  int ldr3Value = analogRead(LDR3_PIN);
  int photodiodeValue = analogRead(PHOTODIODE_PIN);
  int endstopState = digitalRead(ENDSTOP_PIN);


  // LDR1;LDR2;LDR3;PHOTOTRANSİSTOR;ENDSTOP
  Serial.print(ldr1Value);
  Serial.print(";");
  Serial.print(ldr2Value);
  Serial.print(";");
  Serial.print(ldr3Value);
  Serial.print(";");
  Serial.print(photodiodeValue);
  Serial.print(";");
  Serial.println(endstopState);
  
  delay(100);

  if(Serial.available() > 0){
    komut = Serial.readStringUntil('\n');
    Serial.println(komut);

    if(komut == "kalibre"){
      kalibrasyonModu = true;
    }
  }

  if(kalibrasyonModu){
    digitalWrite(ENABLE_PIN, LOW);

    while (digitalRead(ENDSTOP_PIN) == HIGH){   // tetiklenmediği sürece
      stepper.move(1);
      stepper.runToPosition();
    }
    kalibrasyonModu = false;
    stepper.setCurrentPosition(0); // Başlangıç konumunu sıfırla
  } 
}
