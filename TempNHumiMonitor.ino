#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>

const char *ssid = "My Wifi Network"; // enter your wifi network name here
const char *password = "iLove2Code!"; // enter the password here

WebServer server(80);
DHT dht(26, DHT11);

void handleRoot() {
  char msg[1500];
  float temperature = readDHTTemperature();
  float humidity = readDHTHumidity();
  
  const char* temperatureColor = (temperature > 70.0) ? "red" : (temperature < 60.0) ? "blue" : "black";
  float fillPercentage = map(temperature, 0, 100, 0, 100);

  snprintf(msg, 1500,
           "<html>\
  <head>\
    <meta http-equiv='refresh' content='4'/>\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>\
    <title>Weather Monitoring Station</title>\
    <style>\
      html { font-family: Sans-serif; display: inline-block; margin: 0px auto; text-align: center; background: #ffdea8;}\
    h2 { font-size: 3.0rem; }\
    p { font-size: 3.0rem; }\
    .temperature-info {\
      font-size: 2.5rem;\
      margin-top: 20px;\
    }\
    .temperature-label {\
      font-size: 1.5rem;\
      color: %s;\
    }\
    .humidity-label {\
      font-size: 1.5rem;\
      color: #187bcd;\
    }\
    </style>\
  </head>\
  <body>\
      <h2>Temperature & Humidity Monitor</h2>\
      <h5>ESP32 DHT Server</h5>\
      <div class='temperature-info'>\
        <p>\
          <i class='fas fa-thermometer-half' style='color:%s;'></i>\
          <span class='temperature-label' style='color:%s;'>Temperature</span>\
          <span>%.2f</span>\
          <sup class='units'>&deg;F</sup>\
        </p>\
        <p>\
          <i class='fas fa-tint' style='color:#187bcd;'></i>\
          <span class='humidity-label'>Humidity</span>\
          <span>%.2f</span>\
          <sup class='units'>&percnt;</sup>\
        </p>\
      </div>\
      <h5><em>*Planning to update in the near future and add other measurements such as Barometric Pressure and Altitude. - Tyler </em></h5>\
  </body>\
</html>",
           temperatureColor, temperatureColor, temperatureColor, temperature, humidity
          );
  server.send(200, "text/html", msg);
}

void setup(void) {

  Serial.begin(115200);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // wait for a secure connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(3); // allow the CPU to switch to other tasks
}

float readDHTTemperature() {
  // sensor readings may also be up to 3 seconds
  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    float f = (t * 9.0 / 5.0) + 32.0; // converts celsius to fahrenheit
    Serial.println(f);
    return f;
  }
}

float readDHTHumidity() {
  // sensor readings may also be up to 3 seconds
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("*There has been an error trying to read from the DHT sensor*");
    return -1;
  }
  else {
    Serial.println(h);
    return h;
  }
}
