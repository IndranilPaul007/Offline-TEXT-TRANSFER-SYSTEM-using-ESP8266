# ESP8266 Offline Wireless Vault 🗄️

A local, off-the-grid web clipboard and file-sharing vault built with the ESP8266 and LittleFS.

This project turns an ESP8266 into a standalone Wi-Fi Access Point that hosts a web-based text vault. Users can connect to the network, paste notes, links, or code snippets from their phone, and instantly retrieve them on a laptop (or vice versa). Everything is saved directly to the microcontroller's internal flash memory, requiring zero internet connection.

## Features
* **100% Offline:** Operates entirely on its own local Wi-Fi network (`ESP_Vault`).
* **Flash Memory Storage:** Uses the `LittleFS` file system to safely store text data across reboots.
* **Cross-Device Sharing:** Easily pass text/code between phones, tablets, and laptops without Bluetooth or messaging apps.
* **Mobile-Responsive UI:** Clean, dark-mode web interface built directly into the C++ code.

## Hardware Required
* ESP8266 Development Board (e.g., NodeMCU 1.0 / ESP-12E)
* Micro-USB Cable (for data and power)

## Software & Libraries Used
* `ESP8266WiFi.h` (For the Access Point)
* `ESP8266WebServer.h` (For hosting the HTML page)
* `LittleFS.h` (For reading/writing to the internal flash memory)

## How to Use
1. Flash the code to your ESP8266 using the Arduino IDE. 
2. Connect your phone or laptop to the **ESP_Vault** Wi-Fi network (Password: `password123`).
3. Open a web browser and navigate to `http://192.168.4.1`.
4. Type or paste your text and click **Save to Board**. 
5. Connect another device to the same Wi-Fi network and refresh the page to retrieve the saved text!
