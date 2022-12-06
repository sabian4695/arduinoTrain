#include <Adafruit_NeoPixel.h>

#define LEDsOP 6
#define motorPWM 5
#define motorFW 4
#define motorBW 7
#define potIP A0
#define topSpeed 200
#define lowPot 0.55

Adafruit_NeoPixel pixels(12, LEDsOP, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(motorPWM, OUTPUT);
  pinMode(motorFW, OUTPUT);
  pinMode(motorBW, OUTPUT);
  pinMode(13, INPUT);
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(50);
  TCCR0B = 0b00000001; // x1
  TCCR0A = 0b00000011; // fast pwm
}

int forward;
int reverse;

void trainDirection(bool directIP) {
  if (directIP == true) {forward = HIGH;} else {forward = LOW;}
  reverse = !forward;
  digitalWrite(motorFW, forward); digitalWrite(motorBW, reverse);
}

void setTrain(float percentIP) {
  float bottomConv = ((percentIP/100)*lowPot)+lowPot;
  float converted = bottomConv*topSpeed;
  analogWrite(motorPWM, converted);
  pixelPerc(percentIP/100);
  Serial.println("Percent Power: " + String(percentIP) + "%");
}

void loop() {
  trainDirection(true);
  //setTrain(convertPot());
  
  startStop(10,80,true);
  myDelay(1000*10);
  startStop(10,80,false);
  myDelay(1000*10);
  //Serial.println("print");
}

float convertPot() {
  return 1-(analogRead(potIP)/1023);
}

void myDelay(int amount) {
  long end_time = (millis()/50)+amount;
  do {//Serial.println("waiting");
   } while((millis()/50)<end_time);
}

void pixelPerc(float percent) {
  int pixelCount = percent*12;
  int red = percent*255;
  int green = 255-(percent*255);
  for (int i = 0; i < 12; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  for (int i = 0; i < pixelCount; i++) {
    pixels.setPixelColor(i, red, green, 0);
  }
  pixels.show();
}

void startStop(int duration, float inputSpeed, bool opType) {
  int scaler = 15;
  float lowVal = 124/255;
  float outputVal;
  float spInt;
  if (opType) {
    outputVal = lowVal;
    spInt = (inputSpeed - outputVal)/(duration*scaler);
  } else if (!opType) {
    outputVal = inputSpeed;
    spInt = (lowVal - inputSpeed)/(duration*scaler);
  }
  for (int i = 0; i < (duration*scaler); i++) {
    outputVal = outputVal + spInt;
    setTrain(outputVal);
    myDelay(10*scaler+((10*scaler*scaler)/(i+1)));
  }
}
