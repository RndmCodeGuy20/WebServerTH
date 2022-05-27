/**
 * @file WebServerTH.ino
 * @author Shantanu Mane (@RndmCodeGuy20) (shantanu.mane.200@outlook.com)
 * @brief Takes data from ESP32 and OpenWeatherMap API and displays a weather card.
 * @version  1.3.2
 * @date 2022-05-27
 *
 * @copyright Copyright (c) 2022
 * @license MIT License
 *
 */

#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT11 // DHT 11

const char *ssid = "************";        // Enter SSID here
const char *password = "***************"; // Enter Password here

WebServer server(80);

// DHT Sensor
uint8_t DHTPin = 15; // Connect D15 pin to DHT11's `data` pin

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  // connect to your local wi-fi network
  WiFi.begin(ssid, password);

  // check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected...!");
  Serial.print("Server alive on IP : ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.print("HTTP server started! Head onto ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  server.handleClient();
}

void handle_OnConnect()
{

  Temperature = dht.readTemperature(); // Gets the values of temperature
  Humidity = dht.readHumidity();       // Gets the values of humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity));
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat, float Humiditystat)
{
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html lang = \"en\"><head><meta charset = \"UTF-8\" /><meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\" /><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\" />\n";
  ptr += "<link href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css\" rel=\"stylesheet\"/>\n";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Roboto:300,400,500,700&display=swap\" rel=\"stylesheet\"/>\n";
  ptr += "<link href=\"https://cdnjs.cloudflare.com/ajax/libs/mdb-ui-kit/4.0.0/mdb.min.css\" rel=\"stylesheet\"/>\n";
  ptr += "<link href=\"https://unicons.iconscout.com/release/v4.0.0/css/line.css\" rel=\"stylesheet\"/>\n";
  ptr += "<script type=\"text/javascript\" src=\"https://cdnjs.cloudflare.com/ajax/libs/mdb-ui-kit/4.0.0/mdb.min.js\"></script>\n";
  ptr += "<title>IoT Weather App</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<section class=\"vh-100\" style=\"background-image: url(https://images.unsplash.com/photo-1496450681664-3df85efbd29f?crop=entropy&cs=tinysrgb&fm=jpg&ixlib=rb-1.2.1&q=80&raw_url=true&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1600); background-repeat: no-repeat;\">\n";
  ptr += "<div class=\"container py-5 h-100\">\n";
  ptr += "<div class=\"row d-flex justify-content-center align-items-center h-100\">\n";
  ptr += "<div class=\"col-md-8 col-lg-6 col-xl-4\">\n";
  ptr += "<div class=\"card\" style=\"color: #4b515d; border-radius: 35px\">\n";
  ptr += "<div class=\"card-body p-4\">\n";
  ptr += "<div class=\"d-flex\">\n";
  ptr += "<h6 class=\"flex-grow-1\">Nagpur, IN</h6>\n";
  ptr += "<h6 id=\"Time\">15:07</h6>\n";
  ptr += "&emsp;\n";
  ptr += "<h6 id=\"Date\">Wed, 20</h6>\n";
  ptr += "</div>";
  ptr += "<div class=\"d-flex flex-column text-center mt-5 mb-4\">\n";
  ptr += "<h6 class=\"display-4 mb-0 font-weight-bold\" style=\"color: #1c2331\">";
  ptr += (int)Temperaturestat;
  ptr += "°C</h6>";
  ptr += "<span class=\"small\" style=\"color: #868b94\" id=\"desc\">Sunny</span>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"d-flex align-items-center\">\n";
  ptr += "<div class=\"flex-grow-1\" style=\"font-size: 1rem\">\n";
  ptr += "<div><i class=\"fas fa-wind fa-fw\" style=\"color: #868b94\"></i> <span class=\"ms-1\" id=\"wind\"> 40 km/h</span></div>\n";
  ptr += "<div><i class=\"fas fa-tint fa-fw\" style=\"color: #868b94\"></i><span class=\"ms-1\">";
  ptr += (int)Humiditystat;
  ptr += "%</span></div>\n";
  ptr += "<div><i class=\"uil uil-sunset\" style=\"color: #868b94\"></i><span class=\"ms-1\" id=\"sunset\"> 0.2h </span></div>\n";
  ptr += "</div>\n";
  ptr += "<div><img src=\"https://mdbcdn.b-cdn.net/img/Photos/new-templates/bootstrap-weather/ilu1.webp\" width=\"100px\" id=\"weatherImg\"/></div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</section>\n";
  ptr += "<script>const currDate = document.getElementById(\"Date\");const currTime = document.getElementById(\"Time\");const windSpeed = document.getElementById(\"wind\");const weatherDesc = document.getElementById(\"desc\");const sunsetTime = document.getElementById(\"sunset\");const weatherImg = document.getElementById(\"weatherImg\");const weekday = [\"Sun\", \"Mon\", \"Tue\", \"Wed\", \"Thu\", \"Fri\", \"Sat\"]; var today = new Date();currDate.innerHTML = `${weekday[today.getDay()]}, ${today.getDate()}`;hh = today.getHours();mm = today.getMinutes();hh = hh < 10 ? \"0\" + hh : hh;mm = mm < 10 ? \"0\" + mm : mm;currTime.innerHTML = `${hh}:${mm}`;const url =\"https://api.openweathermap.org/data/2.5/weather?q=Nagpur,india&appid=4f3ccf7eff9976e2fedac54dcf90129a&units=metric\";async function getWeatherData(url){const response = await fetch(url);var data = await response.json();var sunset = new Date(data.sys.sunset * 1000);sunsetTime.innerHTML = `${sunset.getHours()}:${sunset.getMinutes()}`;windSpeed.innerHTML = `${data.wind[\"speed\"]} km/hr`;weatherDesc.innerHTML = data.weather[0].main;icon = data.weather[0].icon;icon = data.weather[0].icon; weatherImg.src = `http://openweathermap.org/img/wn/${icon}@2x.png`;};getWeatherData(url);</script>\n";
  ptr += "</body>\n";
  ptr += "</html>";

  return ptr;
}
