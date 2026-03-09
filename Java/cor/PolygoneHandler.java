package cor;

import java.awt.*;

/**
 * Gestionnaire concret pour l'analyse et le dessin de polygones.
 * Ce maillon de la chaîne traite les requêtes commençant par le mot-clé "Polygone".
 */
public class PolygoneHandler extends ShapeHandler {
    
    /**
     * Initialise le gestionnaire de polygone avec un lien vers le suivant.
     * @param next Le prochain gestionnaire dans la chaîne de responsabilité.
     */
    public PolygoneHandler(ShapeHandler next) {
        super(next);
    }

    /**
     * Tente de traiter la requête si elle correspond à un polygone.
     * Le format attendu, basé sur le visiteur C++, est : "Polygone;couleur;(x1,y1);(x2,y2);..."
     * * @param request La chaîne de caractères contenant les données de la forme.
     * @param g2d     L'instance Graphics2D pour effectuer le rendu.
     * @return true si le polygone a été dessiné, sinon délègue au suivant dans la chaîne.
     */
    @Override
    public boolean handle(String request, Graphics2D g2d) {
        // Selon votre visiteur C++, le format est : "Polygone;color;(x1,y1);(x2,y2);..."
        if (request.startsWith("Polygone")) {
            String[] tokens = request.split(";");
            
            // 1. Applique la couleur envoyée par le client C++
            g2d.setColor(parseColor(tokens[1]));

            // 2. Construction de l'objet Polygon de Java AWT
            Polygon p = new Polygon();
            
            // Les sommets commencent à l'indice 2 jusqu'à la fin du tableau
            for (int i = 2; i < tokens.length; i++) {
                Point pt = parsePoint(tokens[i]);
                p.addPoint(pt.x, pt.y);
            }

            // 3. Rendu de la forme géométrique
            g2d.drawPolygon(p);
            
            System.out.println("Java Server: Polygon drawn with " + p.npoints + " vertices.");
            return true; // Requête traitée avec succès
        }
        
        // Passe au gestionnaire suivant si ce n'est pas un polygone
        return (next != null) && next.handle(request, g2d);
    }
}