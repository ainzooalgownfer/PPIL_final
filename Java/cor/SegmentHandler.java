package cor;

import java.awt.*;

/**
 * Gestionnaire concret pour le dessin de segments (lignes droites).
 * Ce maillon de la chaîne de responsabilité traite les requêtes commençant par "Segment".
 */
public class SegmentHandler extends ShapeHandler {

    /**
     * Initialise le gestionnaire de segment.
     * @param next Le successeur dans la chaîne de responsabilité.
     */
    public SegmentHandler(ShapeHandler next) { 
        super(next); 
    }

    /**
     * Analyse la requête et dessine un segment entre deux points si la commande correspond.
     * Le format attendu est : "Segment;couleur;(x1,y1);(x2,y2)"
     * * @param request La chaîne de caractères décrivant le segment et ses attributs.
     * @param g2d     Le contexte graphique Java2D utilisé pour le rendu.
     * @return true si le segment a été dessiné, sinon délègue au maillon suivant.
     */
    @Override
    public boolean handle(String request, Graphics2D g2d) {
        // Vérification du mot-clé initial
        if (request.startsWith("Segment")) {
            // Découpage des paramètres (type, couleur, point1, point2)
            String[] tokens = request.split(";");
            
            // Application de la couleur via la méthode héritée de ShapeHandler
            g2d.setColor(parseColor(tokens[1]));
            
            // Extraction des deux points d'extrémité du segment
            Point p1 = parsePoint(tokens[2]);
            Point p2 = parsePoint(tokens[3]);

            // Dessin de la ligne droite entre les coordonnées (x1,y1) et (x2,y2)
            g2d.drawLine(p1.x, p1.y, p2.x, p2.y);
            
            return true; // La requête a été consommée par ce maillon
        }
        
        // Transmission à l'élément suivant si la condition n'est pas remplie
        return (next != null) && next.handle(request, g2d);
    }
}