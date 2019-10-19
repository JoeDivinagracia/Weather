#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include "includes/weather.h"
#include "includes/json.hpp"

using json = nlohmann::json;

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp){
  size_t realsize = size*nmemb;
  MemoryChunk* mem = (MemoryChunk*)userp;
  char* ptr = (char*)realloc(mem->getMemory(), mem->getSize()+realsize+1);
  if(ptr == NULL){
    std::cout << "Not enough memory (realloc returned NULL)" << std::endl;
    return 0;
  }
  mem->setMemory(ptr);
  memcpy(&(mem->getMemory()[mem->getSize()]), contents, realsize);
  mem->setSize(mem->getSize() + realsize);
  mem->getMemory()[mem->getSize()] = 0;

  return realsize;
}

void getWeather(std::string location){
  std::cout << "---------- Weather Monitor ----------\n\n";
  std::string APIKey = "3e55a2a5889bed168093214562f5f65b";
  std::string latitude = "40.153362";
  std::string longitude = "-76.604256";

  currentWeather("http://api.openweathermap.org/data/2.5/weather?appid="+APIKey+"&lat="+latitude+"&lon="+longitude);
  //getCooridinates();
  std::cout << "\nHave an absolutely Clawtacularly Clawsome day valued Blue Claws customer!\n";
}

void currentWeather(std::string URL){
  CURL* curl;
  CURLcode result;
  MemoryChunk chunk;
  curl_global_init(CURL_GLOBAL_ALL);
  
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  result = curl_easy_perform(curl);
  if(result != CURLE_OK){
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
  }
  else{
    parseJSON(chunk.getMemory());
  }
  curl_easy_cleanup(curl);
  free(chunk.getMemory());
}

void forecastWeather(std::string URL){
  CURL* curl;
  CURLcode result;
  MemoryChunk chunk;
  
  curl_global_init(CURL_GLOBAL_ALL);
  
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  result = curl_easy_perform(curl);
  if(result != CURLE_OK){
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
  }
  else{
    parseJSON(chunk.getMemory());
  }
  curl_easy_cleanup(curl);
  free(chunk.getMemory());
}

double KtoF(double kelvin){return (((kelvin - 273.15)*9)/5)+32;}

void parseJSON(char* chunkMemory){
  Weather* weather;
  auto jsonData = json::parse(chunkMemory);
  weather->setDescription(jsonData["weather"][0]["description"]);
  weather->setTemp(KtoF(jsonData["main"]["temp"]));
}
