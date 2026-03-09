/**
 * @file Connexion_m.h
 * @brief Singleton qui gere la connexion TCP/IP vers le serveur Java.
 */

#ifndef CONNEXION_MANAGER_H
#define CONNEXION_MANAGER_H

#include <string>
#include <iostream>
#include <stdexcept>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <cstring>          // pour memset
    #define SOCKET int
    #define INVALID_SOCKET (-1)
    #define SOCKET_ERROR (-1)
    #define closesocket close
#endif

/**
 * @class ConnexionManager
 * @brief Gere la connexion reseau vers le serveur de dessin.
 *
 * C'est un Singleton : il n'y a qu'une seule instance dans tout le programme.
 * Sur Windows, le constructeur initialise Winsock.
 * Si le serveur Java n'est pas lance, on affiche les messages en console
 * a la place (mode debug).
 */
class ConnexionManager {
private:
    static ConnexionManager* _instance;
    SOCKET _socket;
    bool _connecte;

    // Constructeur prive : c'est le principe du Singleton
    ConnexionManager() : _socket(INVALID_SOCKET), _connecte(false) {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Erreur : Impossible d'initialiser Winsock");
        }
#endif
    }

public:
    // Recupere l'instance unique, la cree si elle n'existe pas encore
    static ConnexionManager* getInstance() {
        if (_instance == nullptr) {
            _instance = new ConnexionManager();
        }
        return _instance;
    }

    // Ouvre la connexion TCP vers le serveur
    void connecter(const std::string& ip, int port) {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == INVALID_SOCKET) {
            throw std::runtime_error("Erreur : Creation du socket impossible");
        }

        sockaddr_in serveur;
        memset(&serveur, 0, sizeof(serveur));
        serveur.sin_family = AF_INET;
        serveur.sin_port = htons(port);

        if (inet_pton(AF_INET, ip.c_str(), &serveur.sin_addr) <= 0) {
            closesocket(_socket);
            throw std::runtime_error("Erreur : Adresse IP invalide : " + ip);
        }

        if (connect(_socket, (sockaddr*)&serveur, sizeof(serveur)) == SOCKET_ERROR) {
            closesocket(_socket);
            throw std::runtime_error("Erreur : Connexion au serveur " + ip + ":" + std::to_string(port) + " refusee");
        }

        _connecte = true;
        std::cout << "Connecte au serveur " << ip << ":" << port << std::endl;
    }

    // Envoie un message au serveur, ou l'affiche en console si pas connecte
    virtual void envoyer(const std::string& requete) {
        if (_connecte) {
            std::string msg = requete + "\n";
            send(_socket, msg.c_str(), msg.size(), 0);
        } else {
            std::cout << "[DEBUG] Envoi : " << requete << std::endl;
        }
    }

    void deconnecter() {
        if (_connecte) {
            closesocket(_socket);
            _connecte = false;
        }
    }

    ~ConnexionManager() {
        deconnecter();
#ifdef _WIN32
        WSACleanup();
#endif
    }

    bool estConnecte() const { return _connecte; }

    // Pas de copie pour un Singleton
    ConnexionManager(const ConnexionManager&) = delete;
    void operator=(const ConnexionManager&) = delete;
};

#endif