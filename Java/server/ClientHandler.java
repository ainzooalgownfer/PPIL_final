package server;

import cor.ShapeHandler;
import graphics.DessinFenetre;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * Gère la communication pour une connexion client C++ individuelle.
 * Implémente {@link Runnable} pour permettre une exécution multi-threadée,
 * assurant ainsi que chaque client dispose de son propre flux de traitement.
 */
public class ClientHandler implements Runnable {
    private Socket socket;
    private DessinFenetre fenetre;
    private ShapeHandler chain;

    /**
     * Initialise un nouveau gestionnaire de client.
     * @param socket  Le socket réseau lié au client connecté.
     * @param fenetre La fenêtre de dessin sur laquelle effectuer le rendu.
     * @param chain   Le premier maillon de la chaîne de responsabilité pour le parsing des formes.
     */
    public ClientHandler(Socket socket, DessinFenetre fenetre, ShapeHandler chain) {
        this.socket = socket;
        this.fenetre = fenetre;
        this.chain = chain;
    }

    /**
     * Boucle principale d'écoute du client.
     * Lit les messages entrant ligne par ligne et déclenche les actions de rendu ou de nettoyage.
     */
    @Override
    public void run() {
        // Utilisation d'un try-with-resources pour fermer automatiquement le flux d'entrée
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
            String request;
            
            // Lecture continue tant que le client est connecté
            while ((request = in.readLine()) != null) {
                if (request.isEmpty()) continue;

                /* * Cas particulier : Commande de nettoyage de l'écran.
                 * On appelle la méthode effacer() de la fenêtre pour vider l'historique 
                 * et blanchir le canvas.
                 */
                if (request.trim().equalsIgnoreCase("CLEAR")) {
                    fenetre.effacer(); 
                    continue; // On ne transmet pas "CLEAR" à la chaîne de responsabilité
                } 

                /* * Déclenche immédiatement la logique de rendu actif (Active Rendering).
                 * La requête est ajoutée à l'historique et la scène complète est redessinée.
                 */
                fenetre.renderRequest(chain, request);
            }
        } catch (Exception e) {
            // Journalisation des erreurs réseau ou de parsing
            System.err.println("Error: " + e.getMessage());
        } finally {
            try {
                // Fermeture propre du socket à la déconnexion du client
                socket.close();
            } catch (Exception ignored) {}
        }
    }
}