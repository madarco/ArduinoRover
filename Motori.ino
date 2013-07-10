// controllo dei motori
// avanti - indietro - destra - sinistra
// è possibile impostare la velocità da 0 (min ) --> 255 (max)



// ******************************************************************
// Metti a 0 la tensione dei motori così si fermano
void stop() {
  //motore sinistro
  analogWrite(motoreSin1,0);
  analogWrite(motoreSin2,0);

  //motore destro
  analogWrite(motoreDes1, 0);
  analogWrite(motoreDes2, 0);
}


// ******************************************************************
// fai andare avanti i motori con velocità valore 0 tra (min) --> 255 (max)
void avanti(int valore) {
  //motore sinistro
  analogWrite(motoreSin1, 0);
  analogWrite(motoreSin2, valore);

  //motore destro
  analogWrite(motoreDes1, 0);
  analogWrite(motoreDes2, valore);
 
}

// ******************************************************************
// fai andare indietro i motori con velocità valore tra 0 (min) --> 255 (max)
void indietro(int valore) {
  //motore sinistro
  analogWrite(motoreSin1, valore);
  analogWrite(motoreSin2, 0);
  
  //motore destro
  analogWrite(motoreDes1, valore);
  analogWrite(motoreDes2, 0);
}


// ******************************************************************
// fai andare a sinistra i motori con velocità valore tra 0 (min) --> 255 (max)
// un motore gira in un verso e l'altro motore nel verso opposto
void sinistra(int valore) {
  //motore sinistro
  analogWrite(motoreSin1, valore);
  analogWrite(motoreSin2, 0);
  
  //motore destro
  analogWrite(motoreDes1, 0);
  analogWrite(motoreDes2, valore);
}


// ******************************************************************
// fai andare a destra i motori con velocità valore tra 0 (min) --> 255 (max)
// un motore gira in un verso e l'altro motore nel verso opposto
void destra(int valore) {
  //motore sinistro
  analogWrite(motoreSin1, 0);
  analogWrite(motoreSin2, valore);
  
  //motore destro
  analogWrite(motoreDes1, valore);
  analogWrite(motoreDes2, 0);
}

void cammina() {
  //motore sinistro
  if(speedSin > 0) {
     
    analogWrite(motoreSin1, 0);
    analogWrite(motoreSin2, abs(speedSin));
  }
  else {
    analogWrite(motoreSin1, abs(speedSin));
    analogWrite(motoreSin2, 0);
  }
  //motore destro
  if(speedDes > 0) {
    analogWrite(motoreDes1, 0);
    analogWrite(motoreDes2, abs(speedDes));
  }
  else {
    analogWrite(motoreDes1, abs(speedDes));
    analogWrite(motoreDes2, 0);
  }
  
}

void cambiaAngolo(int angle) {

  speedDes = 255, speedSin = 255;
  if(angle < 0) {
     speedSin = maxSpeedSin - (steerMaxAmt / 90) * abs(angle);
  }
  if(angle > 0) {
     speedDes = maxSpeedDes - (steerMaxAmt / 90) * abs(angle);
  } 
  
    Serial.print("Nuovo angolo: "); Serial.print(angle);
    Serial.print(" sx: "); Serial.print(speedSin);
    Serial.print(" dx: "); Serial.println(speedDes);
  
}
