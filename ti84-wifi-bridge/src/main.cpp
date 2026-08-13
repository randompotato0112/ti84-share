#include <Arduino.h>
#include "config/AppConfig.hpp"
#include "config/secrets.hpp"
#include "hw/TILink.hpp"
#include "net/WiFiController.hpp"
#include "net/GitHubClient.hpp"
#include "core/Application.hpp"

// Global instances
TILink tiLink(9600);
WiFiController wifi(WIFI_SSID, WIFI_PASS);
GitHubClient github(GITHUB_PAT, Config::getApiUrl());
Application app(tiLink, github, wifi);

namespace Config {
    const char* REPO_OWNER = "username";
    const char* REPO_NAME = "ti84-wifi-bridge";
    const char* FILE_PATH = "db.json";
    
    String getApiUrl() {
        return "https://api.github.com/repos/" + String(REPO_OWNER) + "/" + 
               String(REPO_NAME) + "/contents/" + String(FILE_PATH);
    }
}

void setup() {
    app.init();
}

void loop() {
    app.tick();
}
