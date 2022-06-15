#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <Stepper.h>
int i = 0;
int step_number = 0;
int relayInput = 2;         //D4
const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 16, 5, 4, 0);


boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);


// WiFi Credentials
const char* ssid = "VillageLAN"; //<----------------------- Wifi details
const char* password = "abracadabra11";

// device names
String Device_1_Name = "b";


boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  myStepper.setSpeed(50);
  Serial.begin(115200);


  pinMode(relayInput, OUTPUT);

  if(digitalRead(relayInput) == HIGH){
    Serial.println("\nWe have an error.");
    digitalWrite(relayInput, LOW);
  }

  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if (wifiConnected)
  {
    
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off


    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
void spmOn() {
  int a=1;
  Serial.println("\nspm");
  for (int i = 1; i <= 5; i++) {
  Serial.print("run ");
  Serial.println(a);
  myStepper.step(stepsPerRevolution);
  a++;
  delay(100);
  }
}
void spmOff() {
  int a=1;
  Serial.println("\nspm");
  for (int i = 1; i <= 5; i++) {
  Serial.print("run ");
  Serial.println(a);
  myStepper.step(-stepsPerRevolution);
  a++;
  delay(100);
  }
}
void loop()
{
  espalexa.loop();
  delay(100);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  
  
  //Control the device
  if (brightness == 255)
  {
    Serial.print("asd1 ");
    delay(100);
    digitalWrite(relayInput, HIGH);
    delay(500);
    spmOn();
    Serial.println("dsa1");
    delay(100);
    digitalWrite(relayInput, LOW);  
    digitalWrite(relayInput, LOW); 
    
    
    delay(500);
  }
  else
  {
    Serial.print("asd2 ");
    delay(100);
    digitalWrite(relayInput, HIGH);
    delay(500);
    spmOff();
    Serial.println("dsa2");
    delay(100);
    digitalWrite(relayInput, LOW);
    digitalWrite(relayInput, LOW); 
    

    delay(500);
  }

  
}




boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 60) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
