// ---------------------------------------------------------------------------
// robot Madabot

#include <Servo.h>       //include la libreria per la gestione del servo
#include <NewPing.h>     //include la libreria per la gestione del sensore a ultrasuoni
#define TRIGGER_PIN  3  // Pin di Arduino collegato al pin Trigger del sensore ad Ultrasuoni
#define ECHO_PIN     2  // Pin di Arduino collegato al pin Echo del sensore ad Ultrasuoni
#define MAX_DISTANCE 300 // Massima distanza che sarà gestita dal ping. sopra questo valore i ping vengono ignorati
#define SERVOPIN     8  // Pin di arduino cui è collegato il servo
#define TONE_PIN     9
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // fai il setup del sensore


// Configurazioni:
// ---------------------------------------------------------------------------

int speedSin=255;
int speedDes=255;
int steerMaxAmt = 255;

int minDistance = 10;
int followDistance = 23;
int followDistanceTollerancePercentual = 30;
int followSteerMaxAngle = 30;

int scanAngle = 5;
int scanAngleRange = 5;
int scanAngleSteps = 5;

// ---------------------------------------------------------------------------


Servo uservo;            // definisci l'oggetto servo
int distMax=0;           // angolo di massima distanza                       
int distanza=0;          // valore della distanza in cm

// definiamo i pin del motore
// Motore sinistro  
int motoreDes1=5;  // Pin 1A del SN754410
int motoreDes2=6;  // Pin 2A del SN754410

// Motore destro
int motoreSin1=10;  // Pin 3A del SN754410
int motoreSin2=11; // Pin 4A del SN754410

// impostiamo la velocità - 0 (min) --> 255 (max)
// consigliato valore >= 150

int followDistanceTollerance;

int maxSpeedSin;
int maxSpeedDes;

int lastDistanza = 0;

// ******************************************************************
// funzione invocata alla partenza di Arduino 1 volta soltanto
// serve per impostare le variabili iniziali
void setup() {
  Serial.begin(115200);     // Abilitiamo il serial monitor per la misurazione della distanza
  
  // impostazione iniziale del sensore ad ultrasuoni e del servo
  uservo.attach(SERVOPIN); // collega il servo al suo pin di comando 
  uservo.write(20);        // metti il servo dritto a 90 gradi
  
  // set dei pin di Arduino collegati al motore come OUTPUT
  pinMode(motoreSin1, OUTPUT);
  pinMode(motoreSin2, OUTPUT);
  pinMode(motoreDes1, OUTPUT);
  pinMode(motoreDes2, OUTPUT);
  stop(); //ferma i motori

  //La potenza massima per ogni motore (in modo da compensare un motore più lento)
  maxSpeedSin = speedSin;
  maxSpeedDes = speedDes;
  
  followDistanceTollerance = followDistance + (followDistance/ 100 * followDistanceTollerancePercentual);
}


// ******************************************************************
// Funzione richiamata ciciclamente finchè l'Arduino è in funzione
void loop() {
  
  //Debug:
  if (Serial.available() > 0) {

    int angle = Serial.parseInt();
    if(angle != 0) {

      cambiaAngolo(angle);
      Serial.print(" sx: "); Serial.print(speedSin); Serial.print(" dx: "); Serial.println(speedDes);
    }
  }
  
  // comincia ad avanzare  
  cammina();
  
  //distanza=scandisciAngoli(uservo, scanAngle- scanAngleRange, scanAngle +scanAngleRange, scanAngle);            // leggi la distanza del sensore ad ultrasioni
  distanza = leggiDistanza();
  
  distanza -= minDistance;
  //Debug tone:
  //tone(TONE_PIN, map(distanza, 0, followDistance + followDistanceTollerance, 300, 4000), 5);
  
  if(distanza < followDistance) {
     //Avvicinamento a destra, gira a sinistra:
     cambiaAngolo(0 - (followSteerMaxAngle / followDistance) * (followDistance - distanza));
  }
  if(distanza >= followDistance && distanza <= followDistanceTollerance ) {
    //Dritto:
    cambiaAngolo(0);
  }
  if (distanza > followDistanceTollerance) {
    cambiaAngolo((followSteerMaxAngle / followDistance) * min(distanza - followDistanceTollerance, followDistance) );
  }
    
}


