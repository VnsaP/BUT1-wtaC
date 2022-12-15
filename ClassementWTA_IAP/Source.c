#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//déclaration de constante
#define LGMOT 30 //nombre (nb) de caractère
#define MAXIMUM_DE_TOURNOI 10 //nb maximum de tournoi 
#define NOMBRE_DE_MATCH_PAR_TOURNOI 127 //nb de match par tournoi
#define NOMBRE_DE_JOUEUSES_PAR_TOURNOI 128 //nb de joueuses par tournoi

// Déclaration d'un type Mot, chaine de caractère utilisee pour un nom, une date
typedef char Mot[LGMOT + 1];

//Déclaration des structures

//Déclaration d'un type Joueuse
typedef struct {
    Mot nomJoueuse; //nom de la joueuse
    unsigned int pointsCumules; //points cumulés de la joueuse
} Joueuse;

//Déclaration d'un type Match
typedef struct {
    Joueuse joueuseGagnante; //joueuse gagnante du match
    Joueuse joueusePerdante; //joueuse perdante du match
} Match;

//Déclaration d'un type Tournoi
typedef struct {
    Mot nom; //nom du tournoi
    unsigned int date; //date du tournoi
    Match dataMatch[NOMBRE_DE_MATCH_PAR_TOURNOI]; //tableau des 127 matchs du tournoi
    unsigned int nbMatchTournoi; //nb de match du tournoi
} Tournoi;

//Déclaration d'un type TournoiWTA
typedef struct {
    Tournoi dataTournois[MAXIMUM_DE_TOURNOI]; //tableau des 10 tournois de TournoiWTA
    Joueuse dataJoueuses[MAXIMUM_DE_TOURNOI * NOMBRE_DE_JOUEUSES_PAR_TOURNOI]; //tableau de toutes les joueuses du tournoiWTA
    unsigned int nbTournois; //nb de tournois
    unsigned int idxT; //index d'un tournoi
    unsigned int idxJ; //index d'une joueuse
} TournoiWTA;


//Prototypage des fonctions

// (a)
void definir_nombre_tournois(TournoiWTA* t, unsigned int nombreDeTournois); //void definir_nombre_tournois(TournoiWTA*, unsigned int)

// (b)
void enregistrement_tournoi(Tournoi* t); //void enregistrement_tournoi(Tournoi*)

// (c)
void affichage_matchs_tournoi(const Tournoi* t); //void affichage_matchs_tournoi(const Tournoi*)

// (Sprint 2)
void affichage_matchs_joueuse(const TournoiWTA* t); //void affichage_matchs_joueuse(const TournoiWTA*)

void afficherMatchDeLaJoueuse(int incrementeurDuOutput, Match  output[127]); //void afficherMatchDeLaJoueuse(int incrementeurDuOutput, Match)

void ajoutTournoiATournoiWTA(TournoiWTA* tWTA, Tournoi* t); //void ajoutTournoiATournoiWTA(TournoiWTA* tWTA, Tournoi*)



// Lancement du main

int main() {
    Mot mot;
    TournoiWTA tWTA; //une variable tWTA de type tournoiWTA
    Tournoi t; //une variable t de type Tournoi
    t.nbMatchTournoi = 0; // initialise de suite le nb de match du tournoi

    while (1) {

        scanf("%s", mot);

        if (strcmp(mot, "definir_nombre_tournois") == 0) {
            scanf("%s", mot);
            definir_nombre_tournois(&tWTA, atoi(mot));
        }

        if (strcmp(mot, "enregistrement_tournoi") == 0) {
            enregistrement_tournoi(&t);
            ajoutTournoiATournoiWTA(&tWTA, &t);
        }


        if (strcmp(mot, "affichage_matchs_tournoi") == 0) {
            affichage_matchs_tournoi(&t);
        }

        if (strcmp(mot, "afficher_matchs_joueuse") == 0) {
            affichage_matchs_joueuse(&tWTA);
        }

        if (strcmp(mot, "exit") == 0) {
            exit(0); // sortie du programme principal
        }

    }
    system("pause");
}

// Fin du main



// Les fonctions sont ci-dessous

/* Définit le nombre de tournoi
* t [in-out] un tournoi t de TournoiWTA
* nombreDeTournois [in] un nombre de tournois
*/
void definir_nombre_tournois(TournoiWTA* t, unsigned int nombreDeTournois) {
    assert(nombreDeTournois >= 0 && nombreDeTournois <= MAXIMUM_DE_TOURNOI);
    t->nbTournois = nombreDeTournois;
}

/* Enregistre les données du tournoi t, nom, date, joueuses (gagnante et perdante) des matchs
* t [in-out] un tournoi t
*/
void enregistrement_tournoi(Tournoi* t) {
    // enregistrement_tournoi Paris 2021
    Mot mot;
    scanf("%s", t->nom); // nom du tournoi
    scanf("%s", mot);
    t->date = atoi(mot); // annee du tournoi

    unsigned int i;
    Mot gagnante;
    Mot perdante;
    for (i = 0; i < NOMBRE_DE_MATCH_PAR_TOURNOI; i++)
    {
        scanf("%s", gagnante);
        scanf("%s", perdante);
        strcpy(t->dataMatch[i].joueuseGagnante.nomJoueuse, gagnante);
        strcpy(t->dataMatch[i].joueusePerdante.nomJoueuse, perdante);
    }
}

/*Affiche les données enregistrés du tournoi càd affiche les niveaux atteints, et le nom de la gagnante puis la perdante d'un match
* t [in-out] un tournoi t
*/
void affichage_matchs_tournoi(const Tournoi* t) {
    printf("%s %d\n", t->nom, t->date);
    unsigned int i;
    for (i = 0; i < NOMBRE_DE_MATCH_PAR_TOURNOI; i++)
    {
        if (i == 0) { printf("64emes de finale\n"); }
        else if (i == 64) { printf("32emes de finale\n"); }
        else if (i == 96) { printf("16emes de finale\n"); }
        else if (i == 112) { printf("8emes de finale\n"); }
        else if (i == 120) { printf("quarts de finale\n"); }
        else if (i == 124) { printf("demi-finales\n"); }
        else if (i == 126) { printf("finale\n"); }
        printf("%s %s\n", t->dataMatch[i].joueuseGagnante.nomJoueuse, t->dataMatch[i].joueusePerdante.nomJoueuse);
        /*if (i != 126)
        {
            printf("\n");
        }*/
    }
}

/*Enregistre les données du tournoi dans le tournoi WTA
* tWTA [in-out] le tournoi tWTA
* t [in-out] un tournoi t, le dataTournois[0] de tWTA prendra la valeur de *t 
*/
void ajoutTournoiATournoiWTA(TournoiWTA* tWTA, Tournoi* t) {
    tWTA->dataTournois[0] = *t;
}

/*Affichage des matchs dans lesquels une joueuse en particulier à participer
* t [in-out] un tournoi tWTA
*/
void affichage_matchs_joueuse(const TournoiWTA* t) {
    // afficher_matchs_joueuse Paris 2021 Badosa
    Mot nomTournoi;
    Mot anneeTournoi;
    Mot nomJoueuse;
    scanf("%s", nomTournoi); // nom du tournoi
    scanf("%s", anneeTournoi);
    scanf("%s", nomJoueuse);
    int anTournoi = atoi(anneeTournoi); // annee du tournoi

    Match output[NOMBRE_DE_MATCH_PAR_TOURNOI];
    int i; int x; int incrementeurDuOutput = 0;
    for ( i = 0; i < t->nbTournois; i++)
    {
        if (strcmp(t->dataTournois[i].nom, nomTournoi) == 0 && t->dataTournois[i].date == anTournoi)
        {
            for (x = 0; x < NOMBRE_DE_MATCH_PAR_TOURNOI; x++)
            {
                if (strcmp(t->dataTournois[i].dataMatch[x].joueuseGagnante.nomJoueuse, nomJoueuse) == 0 ||
                    strcmp(t->dataTournois[i].dataMatch[x].joueusePerdante.nomJoueuse, nomJoueuse) == 0)
                {
                    strcpy(output[incrementeurDuOutput].joueuseGagnante.nomJoueuse, t->dataTournois[i].dataMatch[x].joueuseGagnante.nomJoueuse);
                    strcpy(output[incrementeurDuOutput].joueusePerdante.nomJoueuse, t->dataTournois[i].dataMatch[x].joueusePerdante.nomJoueuse);
                    incrementeurDuOutput++;
                } 
           } if (incrementeurDuOutput == 0)
            {
              /*  printf("joueuse inconnue");*/
               return 0;
            }
        }
        /*else
        {
            printf("tournoi inconnu\n");
        }*/
    }
    afficherMatchDeLaJoueuse(incrementeurDuOutput, output);
}

/*Affiche les matchs de la joueuse en particulier  
* incrementeurDuOutput [in] nb de match dans lequel la joueuse à participer
* output [in-out] les matchs dans lesquels la joueuse à participer (+ son adversaire)
*/
void afficherMatchDeLaJoueuse(int incrementeurDuOutput, Match  output[127])
{
    int z;
    for (z = 0; z < incrementeurDuOutput; z++)
    {
        printf("%s %s\n", output[z].joueuseGagnante.nomJoueuse, output[z].joueusePerdante.nomJoueuse);
        /*if (z != incrementeurDuOutput - 1)
        {
            printf("\n");
        }*/
    }
}