package cor;

import java.awt.*;

/**
 * Classe abstraite de base définissant un maillon de la chaîne de responsabilité.
 * Elle permet de traiter des requêtes de dessin de formes géométriques ou de les
 * transmettre au gestionnaire suivant.
 */
public abstract class ShapeHandler {
    /** Le prochain gestionnaire dans la chaîne. */
    protected ShapeHandler next;

    /**
     * Construit un gestionnaire de formes.
     * * @param next Le successeur dans la chaîne (peut être null si c'est le dernier maillon).
     */
    public ShapeHandler(ShapeHandler next) {
        this.next = next;
    }

    /**
     * Traite la requête de dessin ou la transmet au gestionnaire suivant.
     * * @param request La chaîne de caractères décrivant la forme à dessiner.
     * @param g2d     L'objet graphique permettant d'effectuer le rendu.
     * @return true si la requête a été traitée avec succès, false sinon.
     */
    public abstract boolean handle(String request, Graphics2D g2d);

    /**
     * Convertit les noms de couleurs (provenant du C++) en objets Color de Java.
     * * @param colorName Le nom de la couleur (ex: "red", "blue").
     * @return L'objet {@link Color} correspondant, ou {@link Color#BLACK} par défaut.
     */
    protected Color parseColor(String colorName) {
        switch (colorName.toLowerCase()) {
            case "black":  return Color.BLACK;
            case "blue":   return Color.BLUE;
            case "red":    return Color.RED;
            case "green":  return Color.GREEN;
            case "yellow": return Color.YELLOW;
            case "cyan":   return Color.CYAN;
            default:       return Color.BLACK;
        }
    }

    /**
     * Méthode utilitaire pour extraire des coordonnées à partir d'une chaîne
     * au format "(x,y)" générée par la classe Vecteur2D (C++).
     * * @param pointStr La chaîne représentant le point (ex: "(10.5, 20.0)").
     * @return Un objet {@link Point} contenant les coordonnées entières.
     */
    protected Point parsePoint(String pointStr) {
        // Nettoie la chaîne en supprimant les parenthèses et les espaces
        String clean = pointStr.replaceAll("[() ]", "");
        String[] parts = clean.split(",");
        
        // Conversion des doubles en entiers pour le rendu Java AWT
        int x = (int) Double.parseDouble(parts[0]);
        int y = (int) Double.parseDouble(parts[1]);
        
        return new Point(x, y);
    }
}