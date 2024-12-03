#define Right1 6
#define Right2 11
#define Left1 10
#define Left2 9

#define SensorTrig 3
#define SensorEco 2
#define SensorTrigR 5
#define SensorEcoR 4
#define SensorTrigL 7
#define SensorEcoL 12
#define IRL 8
#define IRR 13

int Minimumdist = 10; // 5cm from object will detect
int turningdelay = 500; //1 second
//int PWMSpeed = 255; // Set a PWM speed (0-255)

long time;
int distance, distanceR, distanceL;

void updateDistance(){
    digitalWrite(SensorTrig, LOW); //Trigger servo
    delayMicroseconds(2);
    digitalWrite(SensorTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorTrig, LOW);

    time = pulseIn(SensorEco, HIGH); // Read Pulse
    
    distance = time * 0.034 / 2; //Calculate distance
    
    Serial.print("Distance: ");
    Serial.println(distance);
}

void updateDistanceR(){
    digitalWrite(SensorTrigR, LOW); //Trigger servo
    delayMicroseconds(2);
    digitalWrite(SensorTrigR, HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorTrigR, LOW);

    time = pulseIn(SensorEcoR, HIGH); // Read Pulse
    
    distanceR = time * 0.034 / 2; //Calculate distance
    
    Serial.print("DistanceR: ");
    Serial.println(distanceR);
}

void updateDistanceL(){
    digitalWrite(SensorTrigL, LOW); //Trigger servo
    delayMicroseconds(2);
    digitalWrite(SensorTrigL, HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorTrigL, LOW);

    time = pulseIn(SensorEcoL, HIGH); // Read Pulse
    
    distanceL = time * 0.034 / 2; //Calculate distance
    
    Serial.print("DistanceL: ");
    Serial.println(distanceL);
}

void Front(){
  if(digitalRead(IRL) == LOW) {
      analogWrite(Right1, 255); 
      digitalWrite(Right2, LOW);
      analogWrite(Left1, 150); 
      digitalWrite(Left2, LOW);
      Serial.println("Adjusting Right to avoid Left wall");
      delay(10);
  } else if(digitalRead(IRR) == LOW) {
      analogWrite(Right1, 150); // Normal speed
      digitalWrite(Right2, LOW);
      analogWrite(Left1, 255); // Reduced speed to move slightly
      digitalWrite(Left2, LOW);
      Serial.println("Adjusting Left to avoid Right wall");
      delay(10);
  } else {
      analogWrite(Right1, 255); // Full speed
      digitalWrite(Right2, LOW);
      analogWrite(Left1, 255); // Full speed
      digitalWrite(Left2, LOW);
      Serial.println("Moving Forward");
  }
}
void Right(){
    analogWrite(Right1,255);//FWD
    digitalWrite(Right2,0);
    analogWrite(Left1,0);//REV
    digitalWrite(Left2,255);
    delay(turningdelay);
    STOP();
}

void Left(){
    analogWrite(Right2,255);//REV
    digitalWrite(Right1,LOW);
    analogWrite(Left2,0);//FWD
    digitalWrite(Left1,HIGH);
    delay(660);
    STOP();
}

void STOP(){
    analogWrite(Right1,0);//STP
    analogWrite(Right2,0);
    analogWrite(Left1,0);//STP
    analogWrite(Left2,0);
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(Right1,OUTPUT);
    pinMode(Right2,OUTPUT);
    pinMode(Left1,OUTPUT);
    pinMode(Left2,OUTPUT);

    pinMode(SensorTrig,OUTPUT);
    pinMode(SensorEco,INPUT);
    pinMode(SensorTrigR,OUTPUT);
    pinMode(SensorEcoR,INPUT);
    pinMode(SensorTrigL,OUTPUT);
    pinMode(SensorEcoL,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDistance();
  if(distance < Minimumdist){
    STOP();
    updateDistanceR();
    distance = distanceR;
    updateDistanceL();
    distance = distanceL;
    if(distanceR > distanceL){
      Right();
    }
    else if (distanceL > distanceR){
      Left();
    }
    else{
      STOP(); 
    }
  }
  else{
      Front();
  }
}
