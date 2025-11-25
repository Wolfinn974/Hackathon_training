
/**
 * Décrivez votre classe Row ici.
 *
 * @author Wolfin
 * @version (un numéro de version ou une date)
 */
public class Row
{
    // variables d'instance - remplacez l'exemple qui suit par le vôtre
    public int id; 
    public String gender;
    public String sport;
    public String style;
    public String color;
    public double budget;

    public Row(int id, String gender, String sport, String style, String color, double budget)
    {
        // initialisation des variables d'instance
        this.id = id;
        this.gender = gender;
        this.sport = sport;
        this.style = style;
        this.color = color;
        this.budget = budget;
      }
}