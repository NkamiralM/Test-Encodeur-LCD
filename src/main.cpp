#include <Arduino.h>

// Initialisation des variables nécessaires
int Compteur = 0;
boolean Direction;
int Pin_clk_Letzter;
int Pin_clk_Aktuell;

// Définition des broches d'entrées
int pin_clk = 1;
int pin_dt = 7;
int button_pin = 0;


void setup()
{
   // Initialisation des broches d'entrées...
   pinMode (pin_clk,INPUT);
   pinMode (pin_dt,INPUT);
   pinMode (button_pin,INPUT);

   // ...et activation de leurs résistances de PULL-UP
   digitalWrite(pin_clk, true);
   digitalWrite(pin_dt, true);
   digitalWrite(button_pin, true);

   // Lecture initiale de Pin_CLK
   Pin_clk_Letzter = digitalRead(pin_clk);
   Serial.begin (115200);
   delay(3000);
 }

// Le programme vérifie si un changement des états des broches a eu lieu,
// et selon la broche qui est modifiée en premier, détermine le sens de rotation.
// Cette information est obtenue par la comparaison des signaux présents sur les 2 sorties.
// Une fois que la direction a été déterminée, on compte les mouvements depuis la position
// de départ et on les envoie vers la sortie série.
// Une pression sur le bouton de l'encodeur réinitialise la position actuelle.

void loop()
{
   // Lecture des statuts actuels
   Pin_clk_Aktuell = digitalRead(pin_clk);

   // Vérification de changement
   if (Pin_clk_Aktuell != Pin_clk_Letzter)
   {

        if (digitalRead(pin_dt) != Pin_clk_Aktuell)
        {
            // Pin_CLK a changé en premier
            Compteur ++;
            Direction = true;
        }

        else
        {       // Sinon Pin_DT achangé en premier
            Direction = false;
            Compteur--;
        }
        Serial.println ("Rotation detectee: ");
        Serial.print ("Sens de rotation: ");

        if (Direction)
        {
           Serial.println ("dans le sens des aiguilles d'une montre");
        }
        else
        {
           Serial.println("dans le sens contraire des aiguilles d'une montre");
        }

        Serial.print("Position actuelle: ");
        Serial.println(Compteur);
        Serial.println("------------------------------");

   }

   // Préparation de la prochaine exécution:
   Pin_clk_Letzter = Pin_clk_Aktuell;

   // fonction Reset remise à la position actuelle
   if (!digitalRead(button_pin) && Compteur!=0)
     {
       Compteur = 0;
       Serial.println("Position reset");
     }

 }
