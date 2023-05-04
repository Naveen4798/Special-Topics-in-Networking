#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPL2lzXlzplk"
#define BLYNK_TEMPLATE_NAME "standingorwalking"
#define BLYNK_AUTH_TOKEN "jLS45DeE87rlmlkvQz7NP2tuykQe61EN"

#define SENSOR_PIN D1 // the pin connected to the sensor
#define WALKING_THRESHOLD 500 // the threshold value to determine walking or standing
#define RUNNING_THRESHOLD 900 // the threshold value to determine running
#define WINDOW_SIZE 10 // the size of the sliding window for signal smoothing

char auth[] = "jLS45DeE87rlmlkvQz7NP2tuykQe61EN"; // your Blynk authentication token
char ssid[] = "Naveen"; // your WiFi SSID
char pass[] = "12345678"; // your WiFi password

int window[WINDOW_SIZE]; // a sliding window for signal smoothing
int windowIndex = 0; // the current index in the sliding window
int lastSensorValue = 0; // the last sensor value

// count the number of steps taken
int countSteps() {
  int steps = 0;
  int threshold = WALKING_THRESHOLD + 50; // add some hysteresis to avoid false steps
  int sensorValue = analogRead(SENSOR_PIN);
  if (sensorValue > threshold && lastSensorValue <= threshold) {
    steps++;
  }
  lastSensorValue = sensorValue;
  return steps;
}

// calculate the distance covered based on the number of steps taken
float calculateDistance(int steps) {
  float stepLength = 0.7; // assume a step length of 70 cm
  return steps * stepLength;
}

// calculate the calories burned based on the distance covered and other factors
float calculateCaloriesBurned(float distance) {
  float weight = 70; // assume a weight of 70 kg
  float metabolicEquivalent = 3.5; // assume a metabolic equivalent of 3.5 for walking
  float caloriesPerKgPerMinute = 0.0175; // assume a calorie burn rate of 0.0175 kcal/kg/min for walking
  float minutes = distance / 5; // assume a walking speed of 5 km/h
  float calories = weight * metabolicEquivalent * caloriesPerKgPerMinute * minutes;
  return calories;
}



void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  window[windowIndex] = sensorValue;
  windowIndex = (windowIndex + 1) % WINDOW_SIZE;
  
  
  // calculate the mean and standard deviation of the sliding window
  float mean = 0, std_dev = 0;
  for (int i = 0; i < WINDOW_SIZE; i++) {
    mean += window[i];
  }
  mean /= WINDOW_SIZE;
  for (int i = 0; i < WINDOW_SIZE; i++) {
    std_dev += pow(window[i] - mean, 2);
  }
  std_dev = sqrt(std_dev / WINDOW_SIZE);
  
  // detect the state based on the mean and standard deviation
 // detect the state based on the mean and standard deviation
String state;
if (std_dev < 50) {
  state = "Standing";
} else if (mean > WALKING_THRESHOLD && mean <= RUNNING_THRESHOLD) {
  state = "Walking";
} else if (mean > RUNNING_THRESHOLD) {
  state = "Running";
}

// count steps, distance, and calories burned
int steps = countSteps();
float distance = calculateDistance(steps);
float calories = calculateCaloriesBurned(distance);

// send the values to Blynk app
Blynk.virtualWrite(V1, state);
Blynk.virtualWrite(V2, steps);
Blynk.virtualWrite(V3, distance);
Blynk.virtualWrite(V4, calories);

Serial.println(state);
delay(100); // wait for 100ms before reading the sensor again

 
    
   // wait for 100ms before reading the sensor again
}
