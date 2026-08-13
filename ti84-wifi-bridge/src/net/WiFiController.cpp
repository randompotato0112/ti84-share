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
