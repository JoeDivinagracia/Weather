#ifndef WEATHER_H
#define WEATHER_H

class MemoryChunk{
 private:
  char* memory;
  size_t size;
 public:
  MemoryChunk(){
    size = 0;
    memory = (char*)malloc(1);
  }

  void setSize(int Size){
    size = Size;
  }
  void setMemory(char* Memory){
    memory = Memory;
  }
  
  int getSize(){ return size; }
  char* getMemory(){ return memory; }
};

class CurrentWeather{
 private:
  std::string description;
  double temperature, maxTemp, minTemp, windSpeed;
  
 public:
  void setDescription(std::string description){ this->description = description; }
  void setTemp(double temperature){this->temperature = temperature;}
  void setMinTemp(double minTemp){this->minTemp = minTemp;}
  void setMaxTemp(double maxTemp){this->maxTemp = maxTemp;}
  void setWindSpeed(double windSpeed){this->windSpeed = windSpeed;}
  
  std::string getDescription(){return description;}
  double getTemperature(){return temperature;}
  double getMinTemp(){return minTemp;}
  double getMaxTemp(){return maxTemp;}
  double getWindSpeed(){return windSpeed;}
};

class ForecastWeather{
 private:
  std::string dateTime;

 public:
  void setDateTime(std::string dateTime){this->dateTime = dateTime;}

  std::string getDateTime(){return dateTime;}
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);
void getWeather(std::string location);
CurrentWeather currentWeather(std::string URL);
ForecastWeather forecastWeather(std::string URL);

#endif
