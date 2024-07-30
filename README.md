# ESP32_Soil_Humidity
ESP32 WIFI implementation that measures the humidity of the soil and shows it in a graph in a webpage

## Dependencies

- LittleFS https://github.com/littlefs-project/littlefs
  - If you can`t compile due to an error on this library, just edit the variable name that appears in the library source code to the matching one, this should fix it. We had a lot of problems with this library, but it was the easiest way we found to upload .html files to ESP32
- ESPAsyncWebServer https://github.com/cotestatnt/async-esp-fs-webserver
- Board Manager https://resource.heltec.cn/download/package_heltec_esp32_index.json
