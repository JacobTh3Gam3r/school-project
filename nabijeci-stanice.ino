#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <INA3221.h>

// WiFi přihlašovací údaje
const char* ssid = "VAŠE_WIFI_SSID";
const char* password = "VAŠE_WIFI_HESLO";

// MQTT broker
const char* mqtt_server = "IP_ADRESA_VÁŠHO_MQTT_BROKERU";
const int mqtt_port = 1883;
const char* mqtt_user = "VAŠE_MQTT_UŽIVATELSKÉ_JMÉNO";
const char* mqtt_password = "VAŠE_MQTT_HESLO";
const char* mqtt_client_id = "ESP32_Klient";

// Adresa INA3221 na sběrnici I2C
const int INA3221_ADDRESS = 0x40;

WiFiClient espClient;
PubSubClient client(espClient);

INA3221 ina3221;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Připojuji se k síti ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi připojeno");
  Serial.println("IP adresa: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // zpracování přijaté zprávy
}

void reconnect() {
  // Pokud nejsme připojeni k MQTT, opakujeme připojení
  while (!client.connected()) {
    Serial.print("Pokus o připojení k MQTT...");
    // Pokus o připojení
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
      Serial.println("připojeno");
    } else {
      Serial.print("selhalo, kód chyby=");
      Serial.print(client.state());
      Serial.println(" opakování za 5 sekund");
      // Počkej 5 sekund před opakováním pokusu
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  ina3221.begin(INA3221_ADDRESS);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Čtení napětí a proudu baterie pomocí INA3221
  float batteryVoltage = ina3221.getBusVoltage_V(INA3221_CHANNEL_1);
  float batteryCurrent = ina3221.getCurrent_mA(INA3221_CHANNEL_1);

  Serial.print("Napětí baterie: ");
  Serial.print(batteryVoltage);
  Serial.println(" V");

  Serial.print("Proud baterie: ");
  Serial.print(batteryCurrent);
  Serial.println(" mA");

  // Publikování dat o baterii na MQTT brokeru
  char voltage_str[10];
  char current_str[10];
  dtostrf(batteryVoltage, 4, 2, voltage_str);
  dtostrf(batteryCurrent, 4, 2, current_str);
  client.publish("battery/voltage", voltage_str);
  client.publish("battery/current", current_str);

  delay(5000); // Publikovat každých 5 sekund
}
