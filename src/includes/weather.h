#ifndef WEATHER_H
#define WEATHER_H

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);
void getWeather(std::string location);
void currentWeather(std::string URL);
void forecastWeather(std::string URL);
void parseJSON(char* chunkMemory);

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

#endif
