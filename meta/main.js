const currTime = document.getElementById("Time");
const currDate = document.getElementById("Date");
const windSpeed = document.getElementById("wind");
const weatherDesc = document.getElementById("desc");
const sunsetTime = document.getElementById("sunset");
const weatherImg = document.getElementById("weatherImg");

const weekday = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];

var today = new Date();

hh = today.getHours();
mm = today.getMinutes();
hh = hh < 10 ? "0" + hh : hh;
mm = mm < 10 ? "0" + mm : mm;

currTime.innerHTML = `${hh}:${mm}`;
currDate.innerHTML = `${weekday[today.getDay()]}, ${today.getDate()}`;

const url =
  "https://api.openweathermap.org/data/2.5/weather?q=Nagpur,india&appid=4f3ccf7eff9976e2fedac54dcf90129a&units=metric";

async function getWeatherData(url) {
  const response = await fetch(url);
  var data = await response.json();

  console.log(response);

  var sunset = new Date(data.sys.sunset * 1000);
  sunsetTime.innerHTML = `${sunset.getHours()}:${sunset.getMinutes()}`;

  windSpeed.innerHTML = `${data.wind["speed"]} km/hr`;
  weatherDesc.innerHTML = data.weather[0].main;

  icon = data.weather[0].icon;

  weatherImg.src = `http://openweathermap.org/img/wn/${icon}@2x.png`;
}

getWeatherData(url);
