#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct ListeVaccins{
    char* marque;
    int nombre_vaccins;
    struct ListeVaccins* suivant;

}T_ListeVaccins;

typedef struct ABR{
    char* date;
    T_ListeVaccins* liste_vaccins;
    struct ABR* fils_gauche;
    struct ABR* fils_droit;

}T_ABR;

//verifie si une date est correcte
int verifdate(char* date);
int compar_date(char* date1,char* date2);
void afficher_date(char* date);
int nb_vacc_liste(T_ListeVaccins* liste_vacc,char* marque);
T_ABR* creerNode(char* date, int nb_vaccins,char* marque);
T_ABR *smallerDroit(T_ABR* abr);
int trouver_Vacc(T_ListeVaccins* liste_vacc,char* marque);

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins);
void ajouterVaccinA(T_ABR** abr,char* date, char* marque, int nb_vaccins);
void afficherStockL(T_ListeVaccins* listeVaccins);
void afficherStockA(T_ABR* abr);
int compterVaccins(T_ABR* abr,char* marque);
void deduireVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins);
void deduireVaccinA(T_ABR** abr, char*marque, int** nb_vaccins);
void retirerNode(T_ABR** abr, char* marque);
