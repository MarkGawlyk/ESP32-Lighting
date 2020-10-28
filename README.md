# ESP32-Lighting
WiFi controlled Lighting using ESP32 Dev Board and WS2812 LEDs.

## Libraries and Template Code

I used the [FastLED Library](https://github.com/FastLED/FastLED) to communicate with the LEDs and snippets from a [demo program](https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100) in my project.

I used the [Blynk Library](https://github.com/blynkkk/blynk-library) and the [Blynk App on iOS](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481) to create a connection between my iPhone and the ESP32, allowing me to control the LEDs from my phone.

## Hardware

I used an ESP32 Dev Board as the micro controller as it has an in-built Wifi module as well as enough processing power to both fetch data and send data to the LEDs. It is also integrated natively into the Blynk app and Library meaning it was simple to establish the connection.

I used WS2812 LEDs which are unique due to them being individually addressable. This means each LED is given 3 Bytes indicating the brightness of each (Red, Green and Blue) LED within them; each LED can be its own colour and brightness allowing the creation of patters and effects.

To power the project I used a 10A 5V PSU to ensure there was enough power to run the LEDs. They each have a max current draw of 60mA which I multiplied by the number of LEDs to calculate the Max Draw.

## How to use

Changing the SSID and WiFi Password will allow the ESP32 to connect to the specified wifi, and changing the Blynk application code will allow it to connect to the device running the app, on the same network. The Blynk code can be found within the app itself. 

You also need to specify the number of LEDs you have running which will allow the animations to run properly.