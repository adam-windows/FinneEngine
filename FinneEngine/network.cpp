#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS // tylko jeœli u¿ywasz deprecated (tutaj niepotrzebne)
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "network.h"
#else
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

std::string FinneRawHTTPGet(const std::string& host, const std::string& path) {
    std::string response;

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return "";
    }
#endif

    struct addrinfo hints {}, * res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), "80", &hints, &res) != 0) {
        std::cerr << "Nie znaleziono hosta: " << host << std::endl;
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        std::cerr << "Nie mo¿na utworzyæ socketu!" << std::endl;
        freeaddrinfo(res);
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    if (connect(sockfd, res->ai_addr, (int)res->ai_addrlen) < 0) {
        std::cerr << "Nie mo¿na po³¹czyæ siê z serwerem!" << std::endl;
        freeaddrinfo(res);
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        return "";
    }

    freeaddrinfo(res); // adres ju¿ niepotrzebny

    std::string httpRequest =
        "GET " + path + " HTTP/1.0\r\n"
        "Host: " + host + "\r\n"
        "User-Agent: FinneEngine/1.0\r\n"
        "Connection: close\r\n\r\n";

    send(sockfd, httpRequest.c_str(), (int)httpRequest.length(), 0);

    char buffer[2048];
    int bytesReceived;
    while ((bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        response += buffer;
    }

#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif

    return response;
}
