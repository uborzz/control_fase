#include <Arduino.h>
const byte ledPin = 13;
const byte relePin = 3;
const byte interruptPin = 2;

long interval = 3000;
long pulsos = 0;
long previousMillis = millis();

int tiempo = 2;

int dimming = 110; 
bool alterna = false;

// interrupcion externa: espera tiempo y genera pulso al moc-triac
void dimmer() {
    int dimtime = (75*dimming);  
    delayMicroseconds(dimtime);
    digitalWrite(relePin, HIGH);
    delayMicroseconds(10);
    digitalWrite(relePin, LOW);
}

// // interrupcion externa: pruebas interrupciones recibidas
// void cuentapulsos() {
//     pulsos+=1;
//     delay(tiempo);
//     Serial.print("CALLBACK t espera: ");
//     Serial.println(tiempo);
//     Serial.print("CALLBACK pulsos: ");
//     Serial.println(pulsos);
//     digitalWrite(relePin, HIGH);
//     delayMicroseconds(200); 
//     digitalWrite(relePin, LOW);
// }

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(relePin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    digitalWrite(relePin, LOW);
    // attachInterrupt(digitalPinToInterrupt(interruptPin), cuentapulsos, FALLING);
    attachInterrupt(digitalPinToInterrupt(interruptPin), dimmer, RISING);
}

void loop() {

    if ( alterna == false ){
        for (int i=5; i <= 110; i++){
            dimming=i;
            delay(20);
            if (i >= 110){alterna=true;}
        }
    }
    else {
        for (int i=110; i >= 5; i--){
            dimming=i;
            delay(20);
            if (i <= 5){alterna=false;}
        }
    }
}