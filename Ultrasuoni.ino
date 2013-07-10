// ******************************************************************************************
// leggi la distanza con il servo ad ultrasuoni in cm
int leggiDistanza(){
  unsigned int uS = sonar.ping_median(1);        //  manda un ping e conta il tempo di risposta (uS).
  if(uS == 0) return lastDistanza;
  int distanzaCM = uS / US_ROUNDTRIP_CM; // converti il tempo in distanza (0 = fuori dal range di distanza, nessun echo del ping)
  
  lastDistanza = distanzaCM;
  Serial.println(distanzaCM);
  return(distanzaCM);                    // restituisci la distanza al chiamante
  
} 


void muoviEAspettaServo(Servo uservo, int angle) {
  int current = uservo.read();
  uservo.write(angle);
  delay(abs(current - angle) * 2);
}

// ******************************************************************************************
// controlla gli ostacoli ogni 30 gradi 
int scandisciAmbiente()
{
  int ang=0, angolo=0;        //indice angolo usato per la scansione
  int angoloMax=0;  //angolo con la distanza max di uscita
  distMax=0;   // imposta la distanza di uscita migliore a zero 
  for (angolo=0; angolo <= 180; angolo += 30) // fai un ciclo per controllare dove sono gli ostacoli 
  {
    
    uservo.write(angolo); // imposta il servo degli ultrasuoni sul valore assunto da ang 
    delay(100); //attendi allineamento servo ultrasuoni 
    int distanzaAngolo=leggiDistanza(); //leggi la distanza per questo angolo
    Serial.print("Angolo: ");
    Serial.print(angolo);
    Serial.print(" Gradi"); 
    Serial.print("  Ping: "); 
    Serial.print(distanzaAngolo); 
    Serial.println("cm");
    if (distanzaAngolo > distMax) // verifica che la distanza letta sia maggiore del max 
    {
      angoloMax=angolo;  // se e' maggiore del max imposta il nuovo angolo max e
      distMax=distanzaAngolo;  // la nuova distanza max 
    }
  } //fine ciclo for
  uservo.write(90); //rimetti il servo degli ultrasuoni dritto 
   
  return(angoloMax); 

}

int scandisciAngoli(Servo servo, int angoloDa, int angoloA, int angoliStep) {
  int avg = 0;
  int num = 0;
  for(int angolo = angoloDa; angolo <= angoloA; angolo += angoliStep) {
      muoviEAspettaServo(servo, angolo);
      int distanza = leggiDistanza();
      avg += distanza;
      num++;
      //tone(TONE_PIN, map(distanza, 0, followDistance + followDistanceTollerance, 300, 4000), 8);
  }
  
  return avg / num;
}

