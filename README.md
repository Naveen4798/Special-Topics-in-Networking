# Special-Topics-in-Networking
Walking behaviour monitoring using shoe sensor

We have implemented the code in arduino (latest version)

This code is a program written for the ESP8266 microcontroller to detect human motion using a sensor, count the number of steps taken, calculate the distance covered, and calories burned. It also sends this data to the Blynk app using the BlynkSimpleEsp8266 library.

The code first defines the Blynk template ID, name, and authentication token to be used to connect to the Blynk app. It also defines the pin to which the infrared sensor is connected, the walking and running thresholds, and the size of the sliding window used for signal smoothing.

The countSteps() function reads the analog sensor value and checks if it is above a certain threshold value (WALKING_THRESHOLD + 50) to detect a step. It returns the number of steps taken since the last call.

The calculateDistance() function calculates the distance covered based on the number of steps taken and the assumed step length of 70cm.

The calculateCaloriesBurned() function calculates the calories burned based on the distance covered, the assumed weight of 70kg, the metabolic equivalent, and the calorie burn rate.

The setup() function initializes the sensor pin as an input and starts the serial communication at 9600 baud. It also connects to the Blynk app using the specified authentication token and WiFi credentials.

The loop() function continuously reads the sensor value and adds it to a sliding window array. It then calculates the mean and standard deviation of the window to detect the current state of the user (Standing, Walking, or Running). It calls the countSteps(), calculateDistance(), and calculateCaloriesBurned() functions to calculate the number of steps taken, distance covered, and calories burned, respectively. It then sends this data to the Blynk app using virtual pins V1, V2, V3, and V4. Finally, it prints the current state to the serial monitor and waits for 100ms before reading the sensor again.

Make sure that the blynk auth code used is properly copied into code.
