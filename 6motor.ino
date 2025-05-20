#include "CytronMotorDriver.h"
#include <Servo.h>


int val;
int avancer = 0;
int rotation = 0;
CytronMD ARD(PWM_PWM, 12, 13);  //ARD
CytronMD MG(PWM_PWM, 6, 7);  //MG
CytronMD MD(PWM_PWM, 10, 11);  //MD
CytronMD AVD(PWM_PWM, 9, 8);  //AVD
CytronMD ARG(PWM_PWM, 5, 4);  //ARG
CytronMD AVG(PWM_PWM, 2, 3);  //AVG
Servo AvantD;
Servo AvantG;
Servo ArriereD;
Servo ArriereG;


void setup() {
  // Communication avec le PC via USB
  Serial.begin(9600);
  while (!Serial); // Attendre que la connexion soit établie (utile avec certains IDEs)
  Serial.println("Test HC-05 avec Arduino Mega");

  // Communication avec le HC-05
  Serial1.begin(9600); // HC-05 en général fonctionne à 9600 bauds par défaut
  Serial.println("Attente de données Bluetooth...");

  /* pin des servo*/
  AvantD.attach(38);
  AvantG.attach(37);
  ArriereD.attach(40);
  ArriereG.attach(39);
  /*angle de base*/
  AvantD.write(90);
  AvantG.write(90);
  ArriereD.write(90+30);
  ArriereG.write(120);
}

void loop() {
  if (Serial1.available()) {
    val = Serial1.read();

    if (val == 53) {
      avancer = -1;
      Serial.println("recule");
      Serial.println(val);
    }

    if (val == 49) {
      avancer = 1;
      Serial.println("avancer");
      Serial.println(val);
    }

    if (val == 48) {
      avancer = 0;
      Serial.println("stop");
      Serial.println(val);
    }

    if (val == 52) {
      /*angle de base TOUT DROIT*/
      AvantD.write(90);
      AvantG.write(90);
      ArriereD.write(90+30);
      ArriereG.write(120);

      Serial.println("tout droit");
      Serial.println(val);
      rotation = 0;
    }

    if (val == 51) {
      /*GAUCHE*/
      AvantD.write(70);
      AvantG.write(45);
      ArriereD.write(101+30);
      ArriereG.write(150);

      Serial.println("tourner gauche");
      Serial.println(val);
      rotation = -1;
    }

    if (val == 50) {
      /*DROITE*/
      AvantD.write(135);
      AvantG.write(110);
      ArriereD.write(60+30);
      ArriereG.write(109);

      Serial.println("tourner droite");
      Serial.println(val);
      rotation = 1;
    }

    if (rotation == 0) {
      ARD.setSpeed(256 * avancer);
      MG.setSpeed(256 * avancer);
      MD.setSpeed(256 * avancer);
      AVD.setSpeed(256 * avancer);
      ARG.setSpeed(256 * avancer);
      AVG.setSpeed(256 * avancer);
    }
    if (rotation == -1) {
      ARD.setSpeed(247 * avancer);
      MG.setSpeed(92 * avancer);
      MD.setSpeed(245 * avancer);
      AVD.setSpeed(255 * avancer);
      ARG.setSpeed(104 * avancer);
      AVG.setSpeed(140 * avancer);
    }
    if (rotation == 1) {
      ARD.setSpeed(104 * avancer);
      MG.setSpeed(245 * avancer);
      MD.setSpeed(92 * avancer);
      AVD.setSpeed(140 * avancer);
      ARG.setSpeed(247 * avancer);
      AVG.setSpeed(255 * avancer);
    }
  }
}