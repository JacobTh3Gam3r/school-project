# Jednočlánková nabíjecí stanice s vizualizací dat v Grafaně
<p align="center">
    <a alt="Contributors">
        <img src="https://img.shields.io/github/contributors/JacobTh3Gam3r/school-project" /></a>
	<a alt="Stars">
        <img src="https://img.shields.io/github/stars/JacobTh3Gam3r/school-project" /></a>
	<a alt="Forks">
        <img src="https://img.shields.io/github/forks/JacobTh3Gam3r/school-project" /></a>
	<a alt="Issues">
        <img src="https://img.shields.io/github/issues/JacobTh3Gam3r/school-project" /></a>
	<a alt="License">
        <img src="https://img.shields.io/github/license/JacobTh3Gam3r/school-project" /></a>
	<a alt="Release">
        <img src="https://img.shields.io/github/release/JacobTh3Gam3r/school-project" /></a>
	<a alt="Code_coverage>
        <img src="https://img.shields.io/codecov/c/github/JacobTh3Gam3r/school-project" /></a>
	<a alt="Build">
        <img src="https://img.shields.io/travis/JacobTh3Gam3r/master" /></a>
</p>

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
- příklad konfigurace viz grafana_example.json
 ![image](https://github.com/JacobTh3Gam3r/school-project/assets/163784417/6860c032-a69f-4e4a-9a6c-5958000f85e2)


## Instalace

#### Docker
- nutno naintalovat Docker + Docker Compose, popř. použít Portainer
##### Docker + Docker Compose (nutnost zanlosti dockeru)
- nainstalování Docker + Docker compose
- poté pužíjte docker-compose.sh v powershellu
- vice info viz. https://docs.docker.com/

##### Portainer
- naintalování Portaineru
- použíjte docker compose:
```
  version: '3'

services:
  mosquitto:
    image: eclipse-mosquitto:latest
    container_name: mosquitto
    ports:
      - "1883:1883"
      - "9001:9001"
    volumes:
      - ./mosquitto/config:/mosquitto/config
      - ./mosquitto/data:/mosquitto/data
      - ./mosquitto/log:/mosquitto/log

  influxdb:
    image: influxdb:latest
    container_name: influxdb
    ports:
      - "8086:8086"
    volumes:
      - ./influxdb/data:/var/lib/influxdb
    environment:
      - INFLUXDB_DB=telegraf
      - INFLUXDB_USER=admin
      - INFLUXDB_ADMIN_ENABLED=true
      - INFLUXDB_ADMIN_USER=admin
      - INFLUXDB_ADMIN_PASSWORD=adminpassword
      - INFLUXDB_USER_PASSWORD=userpassword
      - INFLUXDB_HTTP_AUTH_ENABLED=true

  telegraf:
    image: telegraf:latest
    container_name: telegraf
    links:
      - influxdb
    volumes:
      - ./telegraf/telegraf.conf:/etc/telegraf/telegraf.conf:ro

  grafana:
    image: grafana/grafana:latest
    container_name: grafana
    ports:
      - "3000:3000"
    volumes:
      - ./grafana/data:/var/lib/grafana
    environment:
      - GF_SECURITY_ADMIN_USER=admin
      - GF_SECURITY_ADMIN_PASSWORD=adminpassword
    depends_on:
      - influxdb

volumes:
  mosquitto_data:
  mosquitto_log:
  influxdb_data:
  grafana_data:
```
#### Mosquitto
- nainstalovaní mosquitto brokeru
- úprava config filu
- nahrat soubor s hesly viz Mosquitto/password.txt

Školní projekt
Nabíjecí  stanice pomocí ESP32 s posíláním dat do grafany.
Martin Urban, Jakub Strakoš
