#include <Servo.h>
#include <NewPing.h>

NewPing sonar(13,12,100);

const int ENA = 9;
const int IN1 = 7;
const int IN2 = 8;
const int ENB = 3;
const int IN3 = 5;
const int IN4 = 6;
const int trigPin = 13;
const int echoPin = 12;
const int RedPin = A0;
const int buzzerPin = A1;
const int servoPin = A2;
const int yellowPin = A3;
const int greenPin = A4;

Servo myservo;

void setup() {
 
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(90);
  Serial.begin(9600);
}

void loop() {
  float object = sonar.ping_cm();

  while(object >= 35 && object > 0){
    object = sonar.ping_cm();
    forward();
    digitalWrite(RedPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  while(object < 35 && object > 20){
    object = sonar.ping_cm();
    forward();
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(RedPin, HIGH);
  }     
      
  if(object <= 20 && object > 0){
    digitalWrite(yellowPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    stop();
    delay(400);
    backward();
    delay(700);
    stop();
    delay(200);
    newDirection();
    object = sonar.ping_cm();
  }

  while(object <= 19 && object > 0){
    digitalWrite(greenPin, HIGH);  
    digitalWrite(buzzerPin, LOW);   
    backward();
    delay(700);
    stop(); 
    delay(200);
    newDirection();      
    object = sonar.ping_cm();      
  }              


}
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

float checkDistanceWithServo(int angle) {
  myservo.write(105 + angle);
  delay(500);
  float distance = sonar.ping_cm();
  return distance;
}

void newDirection(){
  float dr1 = 1;
  float dr2 = 1;
  float dr3 = 1;
  float dr4 = 1;
  float dr5 = 1;
  float max = 1;
  
  dr1 = checkDistanceWithServo(-90);
  delay(100);
  dr2 = checkDistanceWithServo(-45);
  delay(100);
  dr3 = checkDistanceWithServo(0);
  delay(100);
  dr4 = checkDistanceWithServo(45);
  delay(100);
  dr5 = checkDistanceWithServo(90);
  delay(100);
  checkDistanceWithServo(0);
  
  int arr[5] = {dr1,dr2,dr3,dr4,dr5};

  for(int j = 0; j < 5; j++){
   if(arr[j] == 0){
     arr[j] = 99.0;
   } 
  }

  for(int k = 0; k < 5; k++){
   Serial.println(arr[k]); 
  }

  for(int i = 0; i < 5; i++){
    if(arr[i] > max || arr[i] == max){
      max = arr[i];
    }
  } 

  if(max == dr1){
    turnRight();
    delay(900);
    stop();
  }
  if(max == dr2){
    turnRight();
    delay(600);
    stop();
  }
  if(max == dr3){
    stop();
    delay(50);
  }
  if(max == dr4){
    turnLeft();
    delay(600);
    stop();
  }
  if(max == dr5){
    turnLeft();
    delay(900);
    stop();
  }
  
}