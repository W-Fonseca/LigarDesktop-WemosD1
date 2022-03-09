
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "ligarpc-35ba3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Rx7zH8Fr4cfjx3Rf18lqtVJfKh87hjSg7pW1zETo"
#define WIFI_SSID "AP_JuvyAnne_2.4G"
#define WIFI_PASSWORD ""

//Define FirebaseESP8266 data object
FirebaseData fbdo;

FirebaseJson json;
String resultado;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  fbdo.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  fbdo.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(fbdo, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(fbdo, "tiny");

  //Firebase.setString(fbdo, "/Test","ligado"); //Cria um Item chamado Test e coloca o valor de ligado

}
void loop()
{
if (Firebase.getString(fbdo, "/Desktop/Botao/Power")) {
    //if (fbdo.dataType() == "string") {  // codigo para saber se O dado de Power é umas string
      //Serial.println(fbdo.stringData()); // print no monitor de serial
      resultado = fbdo.stringData();
    }

  if (resultado == "ligado"){
    pinMode(D8, OUTPUT);
    digitalWrite(D8, LOW);
    // Arduino: turn the LED on (HIGH)
 }
 else if (resultado != "ligado"){ //se for igual a qualquer coisa ele desliga
  pinMode(D8, OUTPUT);
  digitalWrite(D8, HIGH); 
 }  
  delay(1000);  
}
