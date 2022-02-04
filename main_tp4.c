#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include <string.h>
#define NMAX 80


int main()
{

    T_ABR** abr = NULL;
    int nb_vacc=0;
    int* nb_vacc_supp=NULL;
    nb_vacc_supp = (int*)malloc(sizeof(int));
    *nb_vacc_supp=150;

    printf("%d",*nb_vacc_supp);
    // char brand[NMAX] = {'P', 'f', 'i', 'z', 'e', 'r', '\0'};

    T_ListeVaccins* liste=malloc(sizeof(T_ListeVaccins));
    liste->marque="Coco";
    liste->nombre_vaccins=20;
    liste->suivant=NULL;
    deduireVaccinL(&liste,"Coco",nb_vacc);
    printf("yo");
    if(liste==NULL)
        printf("sa marche");
    //printf("%s %d \n",liste->marque,liste->nombre_vaccins);


    char marque[NMAX];


    char choix = '0';
    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Initialiser l'ABR.");
        printf("\n2. Ajouter un nombre de vaccins d une marque dans l'ABR par une date indiquee.");
        printf("\n3. Afficher tous les stocks disponibles dans un ABR.");
        printf("\n4. Compter le nombre de vaccins disponible pour une marque indiquee.");
        printf("\n5. Deduire un nombre de vaccins d une marque indiquee dans un ABR.");
        printf("\n6. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer();
        *nb_vacc_supp=150;
        switch (choix) {
            case '1' :
                ajouterVaccinA(&abr, "2021-05-29", "Pfizer", 100);

                ajouterVaccinA(&abr, "2021-05-29", "Moderna", 200);

                ajouterVaccinA(&abr, "2021-05-29", "Astra", 50);

                ajouterVaccinA(&abr, "2021-05-28", "Pfizer", 120);
                printf("yo");
                afficherStockA(abr);

                ajouterVaccinA(&abr, "2021-05-28", "Pfizer", 120);
                ajouterVaccinA(&abr, "2021-06-07", "Moderna", 200);
                ajouterVaccinA(&abr, "2021-03-04", "Moderna", 500);
                ajouterVaccinA(&abr, "2021-02-14", "Astra", 300);
                printf("L'arbre est initialise comme cela : \n");
                afficherStockA(abr);
                printf("\n\n\n");

                //deduireVaccinL(abr->liste_vaccins,"Pfizer",100);
                deduireVaccinA(&abr,"Pfizer",100);
                afficherStockA(abr);
                break;

            case '2' :
                // TODO : menu 2
                break;

            case '3' :
                printf("Voici le stock des vaccins : \n");
                afficherStockA(abr);
                break;

            case '4' :
                printf("Veuillez indiquer une marque : ");
                scanf("%s",marque);
                printf("yo %s",marque);
                printf("\n nombre de vaccin de la marque %s : %d \n",marque,compterVaccins(abr,marque));
                break;

            case '5' :
                printf("entrez une marque de vaccins a retirer\n");
                gets(marque);
                deduireVaccinA(&abr, marque, &nb_vacc_supp);
                //deduireVaccinL((*abr)->liste_vaccins, "Pfizer", 100);
                afficherStockA(abr);
                break;

            case '6' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");

        }
        printf("\n\n\n");

    }

    return 0;
}
