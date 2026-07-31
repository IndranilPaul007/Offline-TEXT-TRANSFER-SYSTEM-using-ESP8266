#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

// Set network name and password
const char* ssid = "Wifi_Name";
const char* password = "your_set_password";

ESP8266WebServer server(80);

// Function to handle reading saved text
String getSavedText() {
  if (LittleFS.exists("/clipboard.txt")) {
    File file = LittleFS.open("/clipboard.txt", "r");
    String content = file.readString();
    file.close();
    return content;
  }
  return "";
}

// Function to serve the main web page
void handleRoot() {
  String savedContent = getSavedText();
  
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Offline Vault</title>";
  html += "<style>";
  html += "body { font-family: sans-serif; background: #121212; color: #e0e0e0; text-align: center; margin: 0; padding: 20px; }";
  html += ".container { max-width: 500px; margin: auto; background: #1e1e1e; padding: 20px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0,0,0,0.5); }";
  html += "textarea { width: 95%; height: 200px; background: #2d2d2d; color: #00ffcc; border: 1px solid #444; border-radius: 5px; padding: 10px; font-family: monospace; font-size: 14px; margin-bottom: 15px; }";
  html += ".btn { background: #008cba; color: white; border: none; padding: 10px 20px; font-size: 16px; border-radius: 5px; cursor: pointer; margin: 5px; }";
  html += ".btn-danger { background: #d9534f; }";
  html += "</style></head><body>";
  html += "<div class='container'>";
  html += "<h2>📋 Offline Wireless Clipboard</h2>";
  html += "<form action='/save' method='POST'>";
  html += "<textarea name='clipboard_data' placeholder='Paste notes, code, or text here...'>" + savedContent + "</textarea><br>";
  html += "<input type='submit' value='Save to Board' class='btn'>";
  html += "</form>";
  html += "<form action='/clear' method='POST' style='display:inline;'>";
  html += "<input type='submit' value='Clear Vault' class='btn btn-danger'>";
  html += "</form>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

// Handle saving new text
void handleSave() {
  if (server.hasArg("clipboard_data")) {
    String data = server.arg("clipboard_data");
    File file = LittleFS.open("/clipboard.txt", "w");
    if (file) {
      file.print(data);
      file.close();
    }
  }
  // Redirect back to the main page
  server.sendHeader("Location", "/");
  server.send(303);
}

// Handle clearing saved text
void handleClear() {
  if (LittleFS.exists("/clipboard.txt")) {
    LittleFS.remove("/clipboard.txt");
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize LittleFS Flash Storage
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Start Access Point
  WiFi.softAP(ssid, password);
  Serial.println("\nVault Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Web Server Routes
  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/clear", HTTP_POST, handleClear);

  server.begin();
}

void loop() {
  server.handleClient();
}