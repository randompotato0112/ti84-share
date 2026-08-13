#include "net/GitHubClient.hpp"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "base64.h"

GitHubClient::GitHubClient(const String& token, const String& apiUrl) 
    : _token(token), _apiUrl(apiUrl) {}

String GitHubClient::fetchSha() {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    https.begin(client, _apiUrl);
    https.addHeader("Authorization", "token " + _token);
    
    String sha = "";
    if (https.GET() == HTTP_CODE_OK) {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, https.getString());
        sha = doc["sha"].as<String>();
    }
    https.end();
    return sha;
}

String GitHubClient::fetchPayload() {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    https.begin(client, _apiUrl);
    https.addHeader("Authorization", "token " + _token);
    
    if (https.GET() == HTTP_CODE_OK) {
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, https.getString());
        String encoded = doc["content"].as<String>();
        encoded.replace("\n", "");
        https.end();
        return base64::decode(encoded);
    }
    https.end();
    return "ERR";
}

bool GitHubClient::pushPayload(const String& payload) {
    String sha = fetchSha();
    if (sha == "") return false;

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    
    String jsonBody = "{\"data\":\"" + payload + "\"}";
    DynamicJsonDocument putDoc(1024);
    putDoc["message"] = "calc update";
    putDoc["content"] = base64::encode(jsonBody);
    putDoc["sha"] = sha;
    
    String putPayload;
    serializeJson(putDoc, putPayload);

    https.begin(client, _apiUrl);
    https.addHeader("Authorization", "token " + _token);
    int code = https.PUT(putPayload);
    https.end();
    
    return (code == HTTP_CODE_OK);
}
