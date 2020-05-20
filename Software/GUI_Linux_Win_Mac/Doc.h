#ifndef DOC_H
#define DOC_H
/*      Protocole de communnication - commandes utilisees
 *      Arduino-Teensy ====> PC ou autre (port serie USB 115200-8-N-1 )
 *
 *          Le protocole et chaque commande commance par ! suivi d'une lettre ou d'un Octet (portard) suivi nombre en ascii
 *          et se termine par * ( l'etoile doit etre proscrite ailleurs qu'en fin de message )
 *
 *          Lettre : P  pour mesure Pression Relative Patient ( celle qui est asservie )
 *                 : c  pour consigne entree PID Pression Patient ( celle qu'on voudrait )
 *                 : C  pour consigne duree Cycle en ms
 *                 : R  pour Rapport  I/Cycle
 *                 : I  pour Consigne pression Inspiration ( Plateau Haut ) en hPa ou cmH2O
 *                 : E  pour Consigne pression Expiration ( Plateau Bas )   en hPa ou cmH2O
 *                 : V  pour Mesure VTE Patient en ml
 *                 : F  pour mesure Frequence patient en cycle/min
 *                 : D  pour mesure Debit L/min
 *                 : M  pour debit Moyen patient en L/min
 *                 : T pour trigger expiratoire en %/100
 *                 : m pour le mode
 *                 : A pour alarme
 *
 *          Une mesure de P est TOUJOURS suivi d'une Mesure de D (voire s'une donnee de la 3° courbes si 3 courbes)
 *
 *      PC ou autre ====> Arduino-Teensy (port serie USB 115200-8-N-1 )
 *
 *          Le protocole et chaque commande commance par ! suivi d'une lettre ou d'un Octet (portard) suivi nombre en ascii
 *          et se termine par * ( l'etoile doit etre proscrite ailleurs qu'en fin de message )
 *
 *          Les consignes sont tj passee par paquet de 4 exemple: !C1000R0.50I12.3E5.2T6.3M1A0*
 *              Avec
 *          Lettre : C pour consigne cycle en ms
 *                 : R pour Rapport temps inspiration/temps cycle
 *                 : I pour pression Plateau inspiration cmH2O
 *                 : E pour pression Plateau expiration cmH2O
 *
 *          Lettre : M pour mode de fct 0 VPC  - 1 VNI  - 2 VPC_AI - >=3 OFF
 *                 : A pour alarme
 *                 : T trigger debit inspiration
 *
 *          Les parametres PID ( standard un parametre a la fois )
 *          Lettre  : p pour gain proportionnel
 *                  : i pour inverse de constante de temps integrale en sec
 *                  : d pour constante de temps derivee en sec
 *
 */
#endif // DOC_H
