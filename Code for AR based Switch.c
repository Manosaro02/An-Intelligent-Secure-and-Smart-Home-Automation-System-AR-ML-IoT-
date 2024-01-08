

#define BLYNK_PRINT Serial
#include &lt;ESP8266WiFi.h&gt;
#include &lt;BlynkSimpleEsp8266.h&gt;

//Define the relay pins
#define relay1 16 //D0
#define relay2 5 //D1

//Define the manual switch pins
#define switch1 12 //D6
#define switch2 14 //D5

#define BLYNK_AUTH_TOKEN &quot;TcDvZ1D7m5CRhryc95cN2GDb3rYr_Iie&quot;
//Enter your blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = &quot;Mano&quot;; //Enter your WIFI name
char pass[] = &quot;101211012&quot;; //Enter your WIFI password


// Variables to store the manual switch states
bool manualSwitchState1 = HIGH;
bool manualSwitchState2 = HIGH;

//Get the button values
BLYNK_WRITE(V0) {
bool value1 = param.asInt();
// Check these values and turn the relay1 ON and OFF
if (value1 == 1) {
digitalWrite(relay1, LOW);
} else {
digitalWrite(relay1, HIGH);
}
}

//Get the button values
BLYNK_WRITE(V1) {
bool value2 = param.asInt();
// Check these values and turn the relay2 ON and OFF
if (value2 == 1) {



digitalWrite(relay2, LOW);
} else {
digitalWrite(relay2, HIGH);
}
}

void setup() {
//Set the relay pins as output pins
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);

// Set the switch pins as input pins
pinMode(switch1, INPUT_PULLUP);
pinMode(switch2, INPUT_PULLUP);

// Turn OFF the relay
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);

//Initialize the Blynk library


Blynk.begin(auth, ssid, pass, &quot;blynk.cloud&quot;, 80);
}

void loop() {
// Read the state of the manual switches
bool newSwitchState1 = digitalRead(switch1);
bool newSwitchState2 = digitalRead(switch2);

// Update the relay state if manual switch state has changed
if (newSwitchState1 != manualSwitchState1) {
manualSwitchState1 = newSwitchState1;
if (manualSwitchState1 == LOW) {
digitalWrite(relay1, LOW);
Blynk.virtualWrite(V0, 1); // Update Blynk button state
} else {
digitalWrite(relay1, HIGH);
Blynk.virtualWrite(V0, 0); // Update Blynk button state
}
}


if (newSwitchState2 != manualSwitchState2) {
manualSwitchState2 = newSwitchState2;
if (manualSwitchState2 == LOW) {
digitalWrite(relay2, LOW);
Blynk.virtualWrite(V1, 1); // Update Blynk button state
} else {
digitalWrite(relay2, HIGH);
Blynk.virtualWrite(V1, 0); // Update Blynk button state
}
}

// Run the Blynk library
Blynk.run();
}
