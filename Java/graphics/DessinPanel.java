package graphics;

import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;

/**
 * Panneau de dessin personnalisé basé sur un tampon d'image (BufferedImage).
 * Cette classe permet de dessiner "hors écran" et de conserver le rendu
 * même lors du redimensionnement ou du rafraîchissement de la fenêtre.
 */
public class DessinPanel extends JPanel {
    /** L'image en mémoire qui stocke tout le contenu dessiné. */
    private BufferedImage canvas;
    
    /** Le contexte graphique lié à l'image pour effectuer les opérations de dessin. */
    private Graphics2D g2d;

    /**
     * Constructeur du panneau de dessin.
     * @param width  Largeur du panneau en pixels.
     * @param height Hauteur du panneau en pixels.
     */
    public DessinPanel(int width, int height) {
        setPreferredSize(new Dimension(width, height));
        
        // Création d'une image hors écran pour dessiner (gestion de la transparence avec ARGB)
        canvas = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        g2d = canvas.createGraphics();
        
        // Initialisation de l'arrière-plan en blanc
        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, width, height);
        
        // Amélioration de la qualité du rendu (lissage des bords / anti-aliasing)
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
    }

    /**
     * Fournit l'accès au contexte graphique pour dessiner sur ce panneau.
     * @return L'objet {@link Graphics2D} associé au tampon d'image.
     */
    public Graphics2D getContext() {
        return g2d;
    }

    /**
     * Méthode de rendu interne de Swing. 
     * Elle est déclenchée automatiquement pour afficher le contenu à l'écran.
     * @param g Le contexte graphique système.
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // Dessine l'image tamponnée sur le panneau à la position (0,0)
        g.drawImage(canvas, 0, 0, null);
    }
}