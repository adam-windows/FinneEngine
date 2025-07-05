#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

void LoadEngineConfig(const std::string& filename) {
    XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        std::cerr << "Nie mo¿na za³adowaæ " << filename << std::endl;
        return;
    }

    XMLElement* root = doc.FirstChildElement("EngineConfig");
    if (root) {
        const char* coreVersion = root->FirstChildElement("CoreVersion")->GetText();
        const char* network = root->FirstChildElement("Network")->GetText();
        const char* useProxy = root->FirstChildElement("UseProxy")->GetText();
        const char* port = root->FirstChildElement("Port")->GetText();

        std::cout << "Wczytano z Engine.xml:\n";
        std::cout << "CoreVersion: " << coreVersion << "\n";
        std::cout << "Network: " << network << "\n";
        std::cout << "UseProxy: " << useProxy << "\n";
        std::cout << "Port: " << port << "\n";
    }
    else {
        std::cerr << "Brak elementu EngineConfig." << std::endl;
    }
}
