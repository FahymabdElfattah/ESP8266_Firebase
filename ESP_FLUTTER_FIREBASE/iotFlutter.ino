/*
    ____   ____   .    .  .     . .    .
   |      |    |  |    |   \   /  |\  /|
   |____  |____|  |____|    \ /   | \/ |    __   
   |      |    |  |    |     /    |    |   |__| 
   |      |    |  |    |    /     |    | . |  |BD ELFATTAH
                                           
*/

/*  
    EspFlutter
          LED1:0
          LED2:0
          LED3:0
          minutes:0
          readData1:"fahym"
          readData2:222
          sendData1:"abd el fattah"
          sendData2:88

*/
//___________________IMPORT LIBRARY____________________________________________
#include<Arduino.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
//_____________________________________________________________________________
FirebaseData firebaseData ;
FirebaseData AfirebaseData, BfirebaseData , CfirebaseData ;
unsigned long duration = 0 ;
int minutes=1 ;
//___________________NETWORK CREDENTIALS_______________________________________
const char* ssid = "FH-WIFI";
const char* password = "Yy123456";
#define FIREBASE_HOST "" 
#define FIREBASE_AUTH ""

//_--_--_--_--_--_--_--_--_-- setup -_--_--_--_--_--_--_--_--_--_--_--_--_--_--
void setup() {
  //____________SERIAL PORT FOR DEBUGGING PURPOSES_____________________________
  Serial.begin(115200);
  //____________CONNECT TO Wi-Fi_______________________________________________
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("_");
     Serial.print("-");
  }
  //___________ PRINTESP LOCAL IP ADDRESS _____________________________________
  Serial.print("The IP  device : ");
  Serial.println(WiFi.localIP());
  //________________START THE Firebase___________________________________________
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  duration = millis();
  Firebase.setString(firebaseData,"/EspFlutter/minutes",(String) minutes);
}

//_--_--_--_--_--_--_--_--_-- loop -_--_--_--_--_--_--_--_--_--_--_--_--_--_--_
void recievData(){
  if (Firebase.getString(firebaseData, "/EspFlutter/LDR1")){
    String ledState1 = firebaseData.stringData();
  }
  if (Firebase.getString(firebaseData, "/EspFlutter/LDR2")){
    String ledState2 = firebaseData.stringData();
  }
  if (Firebase.getString(firebaseData, "/EspFlutter/LDR3")){
    String ledState3 = firebaseData.stringData();
  }
 

  Firebase.getString(AfirebaseData, "/dailySpecial/readData2");
  Firebase.getString(CfirebaseData, "/dailySpecial/readData1");
  
  int val1 = (AfirebaseData.stringData()).toInt();
  String val3 = (CfirebaseData.stringData());
  Serial.println(val1);
  Serial.println(val3);
}
//__________________________________________________________________________
void sendData(){
  String AnalogVal = (String) random(0,99);
  int AnalogVal3 = random(0,99);
  Firebase.setString(firebaseData,"/ESP/temp" , AnalogVal);
  Firebase.setString(firebaseData,"/ESP/humd" ,(String) AnalogVal3);
}
//__________________________________________________________________________
void sendTime(){
  if ((millis()-duration)>= 60000){
    duration = millis();
    Firebase.getString(firebaseData, "/EspFlutter/minutes");
    minutes = firebaseData.stringData().toInt();
    minutes ++ ;
    Firebase.setString(firebaseData,"/EspFlutter/minutes",(String) minutes);  
  }
}
void loop() {
  //recievData();
  sendData();
  sendTime();
}
