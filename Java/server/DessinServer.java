package server;

import cor.*;
import graphics.DessinFenetre;
import java.io.*;
import java.net.*;

/**
 * Classe principale du serveur pour le projet de synthèse L3.
 * Responsable de l'écoute du port réseau, de l'acceptation des connexions TCP multi-clients
 * et de la coordination globale du dessin.
 */
public class DessinServer {
    private int port;
    private DessinFenetre fenetre;
    private ShapeHandler chain;

    /**
     * Initialise le serveur de dessin.
     * @param port    Le port TCP sur lequel le serveur va écouter (ex: 8080).
     * @param fenetre La fenêtre d'affichage (JFrame) où les formes seront tracées.
     * @param chain   La chaîne de responsabilité configurée pour parser les formes reçues.
     */
    public DessinServer(int port, DessinFenetre fenetre, ShapeHandler chain) {
        this.port = port;
        this.fenetre = fenetre;
        this.chain = chain;
    }

    /**
     * Démarre le serveur et entre dans une boucle d'écoute infinie.
     * Pour chaque nouvelle connexion, un thread dédié est lancé pour ne pas bloquer le serveur.
     */
    public void start() {
        // Utilisation du try-with-resources pour garantir la fermeture du ServerSocket
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Java Server listening on port " + port + "...");

            while (true) {
                // Attente bloquante d'une connexion client C++
                Socket clientSocket = serverSocket.accept();
                System.out.println("C++ Client connected: " + clientSocket.getInetAddress());

                /* * Lancement d'un thread dédié pour chaque client.
                 * Cela permet de gérer plusieurs clients C++ dessinant simultanément 
                 * sur la même instance du serveur Java.
                 */
                new Thread(new ClientHandler(clientSocket, fenetre, chain)).start();
            }
        } catch (IOException e) {
            // Gestion des erreurs liées à l'ouverture du port ou à l'acceptation des sockets
            System.err.println("Server Error: " + e.getMessage());
        }
    }
}