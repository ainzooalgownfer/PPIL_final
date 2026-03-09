package cor;

import java.awt.*;

/**
 * Gestionnaire spécifique pour le dessin de cercles.
 * Ce maillon de la chaîne intercepte les requêtes commençant par "Cercle"
 * et effectue le rendu graphique correspondant.
 */
public class CercleHandler extends ShapeHandler {

    /**
     * Initialise le gestionnaire de cercle avec un successeur.
     * @param next Le prochain gestionnaire dans la chaîne de responsabilité.
     */
    public CercleHandler(ShapeHandler next) { 
        super(next); 
    }

    /**
     * Tente de traiter la requête de dessin si elle concerne un cercle.
     * Le format attendu de la requête est : "Cercle;couleur;point_centre;rayon"
     * * @param request La chaîne de caractères décrivant la forme.
     * @param g2d     Le contexte graphique Java2D pour le dessin.
     * @return true si le cercle a été dessiné, sinon passe la main au suivant.
     */
    @Override
    public boolean handle(String request, Graphics2D g2d) {
        // Vérifie si la requête est destinée à ce gestionnaire
        if (request.startsWith("Cercle")) {
            // Découpage de la requête selon le séparateur ";"
            String[] tokens = request.split(";");
            
            // Configuration de la couleur du pinceau
            g2d.setColor(parseColor(tokens[1]));
            
            // Extraction des données géométriques
            Point center = parsePoint(tokens[2]);
            int r = (int) Double.parseDouble(tokens[3]);

            /* * La méthode drawOval(x, y, width, height) d'AWT dessine à partir 
             * du coin supérieur gauche. On ajuste donc les coordonnées :
             * x = centre.x - rayon
             * y = centre.y - rayon
             */
            g2d.drawOval(center.x - r, center.y - r, 2 * r, 2 * r);
            
            return true; // Requête traitée
        }
        
        // Si ce n'est pas un cercle, on transmet au maillon suivant de la chaîne
        return (next != null) && next.handle(request, g2d);
    }
}