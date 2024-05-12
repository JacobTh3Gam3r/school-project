# Jednočlánková nabíjecí stanice s vizualizací dat v Grafaně

## Hardware
#### ESP32
- měření stavu Li-Ion článku (vhodné pouze pro články s maxinálním napětí 3,3 V)
- MQTT client odesílající informace o stavu nabíjeného článku

#### TP4056
- nabíjení Li-Ion článku
- https://www.hadex.cz/m401e-nabijecka-li-ion-clanku-1a-s-ochranou-modul-s-io-tp4056-usb-c/ nebo https://www.hadex.cz/m401a-nabijecka-li-ion-clanku-1a-s-ochranou-modul-s-io-tp4056-micro-usb/

#### INO3221
- měření napětí baterie (popř. proudu)
- komunikace s ESP32 přes I2C

#### Držák článku 18650 s vývody
- pro jednoduché zapojení článku do obvodu
- https://www.hadex.cz/l038b-drzak-clanku-18650-s-vyvody/

#### Server
- jako server mužete využít:  vlastní server, Rasberry Pi, VPS (cloudové řešení)

## Software

#### Eclipse Mosquitto
- MQTT broker
- zběr dat z nabíjecí stanice
- https://mosquitto.org/

#### Telegraf
- serverový agent
- přenos dat z MQTT brokeru do InfluxDB
- krátkodobé uchování dat
- https://github.com/influxdata/telegraf

#### InfluxDB
- databáze
- dlouhodobé uchování dat
- https://github.com/influxdata/influxdb

#### Grafana
- dashboard
- vizualizace dat uložených v databázi
- https://github.com/grafana/grafana

## Instalace

#### Docker
- nutno naintalovat Docker + Docker Compose, popř. použít Portainer
##### Docker + Docker Compose
- nainstalování Docker + Docker compose
- poté pužíjte docker-compose.sh v powershellu
- 

Školní projekt
Nabíjecí  stanice pomocí ESP32 s posíláním dat do grafany.
Martin Urban, Jakub Strakoš
