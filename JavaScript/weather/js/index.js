function getWeather(data) {
  if(data.error === 0) {
    city.innerText=data.results[0].currentCity;
    rawdata=data.results[0].weather_data[0].date;
    var pos=rawdata.search('\d\d℃');
    temperature=rawdata.substr(pos-3,2);
    temperatureElement.innerText = temperature;
    var img = document.createElement('img');
    var hour = new Date().getHours();
    if ( hour >= 18 || hour < 6) {
        img.src = data.results[0].weather_data[0].nightPictureUrl;
    } else {
        img.src = data.results[0].weather_data[0].dayPictureUrl;
    }
    imgDiv.appendChild(img);
    weatherElement.innerText = data.results[0].weather_data[0].weather;
  }
}

var city=document.querySelector('[data-js-city]');
var temperatureElement=document.querySelector('[data-js-t]');
var weatherElement=document.querySelector('[data-js-weather]');
var imgDiv = document.querySelector('[data-js-image]');
var rawdata;
var temperature;
var flag=0;

var unitBtn = document.querySelector('[data-js-unit]');

unitBtn.onclick = function(){
  if(flag==0) {
    temperatureElement.innerText = (32+1.8*temperature).toPrecision(2);
    flag=1;
    this.innerText = "°F";
  }else {
    temperatureElement.innerText = temperature;
    flag=0;
    this.innerText = "°C";
  }
};
var head = document.head || document.getElementsByTagName('head')[0];
var script = document.createElement("script");
script.src = "http://api.jirengu.com/weather.php?callback=getWeather";
head.appendChild(script);
