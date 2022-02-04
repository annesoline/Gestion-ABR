#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tp4.h"

T_ABR* creerNode(char* date, int nb_vaccins,char* marque){

    if (nb_vaccins <= 0)
    {
        printf("vaccins pas bon \n");
        return NULL;
    }
    if (strlen(marque)>20)
    {
        printf("marque trop longue \n");
        return NULL;
    }
    if (verifdate(date)==0)
    {
        printf("date non valide \n");
        return NULL;
    }

    T_ABR* node = (T_ABR*) malloc(sizeof(T_ABR));
    if(node==NULL) {
        printf("Fatal Error: No enough memory!\n");
        return NULL;
    }

    T_ListeVaccins* liste_vac=(T_ListeVaccins*)malloc(sizeof(liste_vac));

    if (liste_vac==NULL)
    {
        printf("Fatal Error: No enough memory!\n");
        return NULL;
    }

    liste_vac->marque=strdup(marque);
    liste_vac->nombre_vaccins=nb_vaccins;
    liste_vac->suivant=NULL;

    node->liste_vaccins=liste_vac;
    node->date=strdup(date);
    node->fils_gauche=NULL;
    node->fils_droit=NULL;

    return node;
}


int verifdate(char* date)
{
    int annee=1000*(date[0]-'0');
    annee+=100*(date[1]-'0');
    annee+= 10*(date[2]-'0');
    annee+= (date[3]-'0');
    if (annee < 2021 || annee > 2100)
        return 0; //faux

    int mois=10*(date[5]-'0');
    mois+=(date[6]-'0');
    if (mois < 0 || mois > 12)
        return 0;

    int jours=10*(date[8]-'0');
    jours+=(date[9]-'0');
    if (jours < 1 || jours > 31)
        return 0;

    return 1;
}

int compar_date(char* date1,char* date2)
/*  renvoie 0 si date1 < date2
    renvoie 1 si date1 > date2
    renvoie 2 si date1 = date2
*/
{
    int annee1=1000*(date1[0]-'0');
    annee1+=100*(date1[1]-'0');
    annee1+= 10*(date1[2]-'0');
    annee1+= (date1[3]-'0');

    int annee2=1000*(date2[0]-'0');
    annee2+=100*(date2[1]-'0');
    annee2+= 10*(date2[2]-'0');
    annee2+= (date2[3]-'0');
    if (annee1 > annee2)
        return 1;
    if (annee1 < annee2)
        return 0;

    int mois1=10*(date1[5]-'0');
    mois1+=(date1[6]-'0');
    int mois2=10*(date2[5]-'0');
    mois2+=(date2[6]-'0');
    if (mois1 > mois2)
        return 1;
    if (mois1 < mois2)
        return 0;

    int jours1=10*(date1[8]-'0');
    jours1+=(date1[9]-'0');
    int jours2=10*(date2[8]-'0');
    jours2+=(date2[9]-'0');
    if (jours1 > jours2)
        return 1;
    if (jours1 < jours2)
        return 0;

    return 2;//date1=date2

}

void ajouterVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins)
{
    if (strlen(marque) > 20)
    {
        printf("marque trop longue \n");
        return;
    }

    if (nb_vaccins <= 0)
    {
        printf("nombre vaccins negatif \n");
        return;
    }

    T_ListeVaccins** ptr = listeVaccins;
    T_ListeVaccins** prec_ptr = NULL;
    while(ptr != NULL)
    {
        if (strcmp((*ptr)->marque,marque)==0)//on trouve la marque
        {
            (*ptr)->nombre_vaccins+=nb_vaccins;
            return;
        }
        prec_ptr=ptr;
        ptr=(*ptr)->suivant;
    }

    T_ListeVaccins* newt_Vacc=malloc(sizeof(T_ListeVaccins));
    if(newt_Vacc==NULL) {
        printf("Fatal Error: No enough memory!\n");
        return NULL;
    }
    newt_Vacc->marque=strdup(marque);
    newt_Vacc->nombre_vaccins=nb_vaccins;
    newt_Vacc->suivant=NULL;
    (*prec_ptr)->suivant=newt_Vacc;
}


// Insert a new node with a given value into the BST, the T_ABR can be empty.
void ajouterVaccinA(T_ABR** abr,char* date, char* marque, int nb_vaccins){
    //printf("ajouterVaccinA DEBUT\n");
    // If root is empty, that means the T_ABR is empty or reach the proper position.
    if(*abr==NULL){
        printf("abr NULL\n");
        *abr = creerNode(date,nb_vaccins,marque);
        return;
    }
    if(compar_date((*abr)->date,date)== 2){
        printf("meme date\n");
        ajouterVaccinL(&((*abr)->liste_vaccins),marque,nb_vaccins);
    return;
    }

    // If the value is bigger than the current node, then insert into its fils_droit side sub-T_ABR.
    if(compar_date((*abr)->date,date)== 0){
        //printf("fils_droit side sub T_ABR\n");
        ajouterVaccinA(&((*abr)->fils_droit), date,marque,nb_vaccins);
    }
    // Otherwise, insert it into fils_gauche side sub-T_ABR.
    else{
        //printf("fils_gauche side sub T_ABR\n");
        ajouterVaccinA(&((*abr)->fils_gauche), date,marque,nb_vaccins);
    }

    printf("ajouterVaccinA FIN\n");
}


void afficherStockL(T_ListeVaccins* listeVaccins){
    //printf("afficherStockL DEBUT\n");

    if(listeVaccins==NULL){
        //printf("liste vacc null\n");
        printf("Le stock de %s est vide.\n", listeVaccins->marque);
        return;
    }

    T_ListeVaccins* ptr = listeVaccins;

    while(ptr != NULL){
        printf("- %s : %d\n",ptr->marque,ptr->nombre_vaccins);
        ptr=ptr->suivant;
    }
    //printf("afficherStockL FIN\n");
}

void afficherStockA(T_ABR* abr){
    //printf("afficherStockA DEBUT\n");
    // Display all nodes in the BST by Deepth - first search and infix order .
    // reach the leaf node or the T_ABR is empty .
    if(abr == NULL) return ;
    // go to the fils_gauche node .
    afficherStockA (abr->fils_gauche);
    // display the value at the current node .
    printf("%s :\n", abr->date);
    afficherStockL(abr->liste_vaccins);
    printf("\n");
    // go to the fils_droit node .
    afficherStockA (abr->fils_droit);

    //printf("afficherStockA FIN\n");
}

int compterVaccins(T_ABR* abr,char* marque){

    if (abr==NULL)
        return 0;
    return nb_vacc_liste(abr->liste_vaccins,marque)+compterVaccins(abr->fils_gauche,marque)+compterVaccins(abr->fils_droit,marque);

    //printf("afficherStockA FIN\n");
}


int nb_vacc_liste(T_ListeVaccins* liste_vacc,char* marque)
{
    while (liste_vacc!=NULL)
    {
        if(strcmp(liste_vacc->marque,marque)==0)
            return liste_vacc->nombre_vaccins;
        liste_vacc=liste_vacc->suivant;
    }
    return 0;
}


void deduireVaccinL(T_ListeVaccins** listeVaccins, char* marque, int nb_vaccins){
    printf("deduireVaccinLDEBUT\n");
    /*if((*listeVaccins) == NULL){
        printf("Il n'y a pas de vaccins a cette date.\n");
        return;
    }
    else{*/

    if (strlen(marque) > 20)
    {
        printf("marque trop longue \n");
        return;
    }

    if (nb_vaccins <= 0)
    {
        printf("nombre vaccins negatif \n");
        return;
    }

    T_ListeVaccins** ptr = listeVaccins;
    T_ListeVaccins** prec_ptr = NULL;

    printf("g\n");

        //Parcours liste
        while(ptr != NULL)
        {
                printf("1\n");
            if(strcmp((*ptr)->marque,marque)==0)
            {
                printf("marque trouvee\n");
                if((*ptr)->nombre_vaccins > nb_vaccins){ //soustraction positive
                    printf("e");
                    (*ptr)->nombre_vaccins -= nb_vaccins;
                    return;
                }
                else{
                    //Cas 1 : Deduction en ddl
                    if(prec_ptr==NULL){printf("ddl\n");
                        *ptr=(*ptr)->suivant;
                        return;
                    }
                    //Cas 2 : Deduction en mdl
                    else if(prec_ptr!=NULL && (*ptr)->suivant!=NULL){printf("mdl\n");
                        (*prec_ptr)->suivant = (*ptr)->suivant;
                        (*ptr)->suivant = NULL;
                        return;
                    }

                    //Cas 3: Deduction en fdl
                    else if((*ptr)->suivant == NULL){printf("dfl\n");
                        (*prec_ptr)->suivant=NULL;
                        return;
                    }
                }
            }
            printf("2\n");
            prec_ptr=ptr;
            ptr=(*ptr)->suivant;
        }
    if(ptr==NULL) printf("\n La marque en question n'existe pas");


        printf("deduireVaccinLFIN\n");
}

int trouver_Vacc(T_ListeVaccins* liste_vacc,char* marque)
{
    while (liste_vacc!=NULL)
    {
        if (strcmp(liste_vacc->marque,marque)==0)
        {
            return 0; //on trouve la marque dans la liste vaccin
        }
        liste_vacc=liste_vacc->suivant;
    }
    return 1; //on trouve pas la marque dans la liste vaccin
}



void deduireVaccinA(T_ABR** abr, char* marque, int** nb_vaccins)
{
    if(**nb_vaccins <= 0)
        return ;
    if(*abr==NULL){
        printf("T_ABR is empty or the node to be deleted not found in T_ABR\n");
        return;
    }

    printf("g \n");
    deduireVaccinA(&((*abr)->fils_gauche), marque, nb_vaccins);

    printf("nombre_vaccins a retirer restant %d \nnombre de vaccins actuelle dans le noeud %d\ndifference entre nb_vaccins a retirer et "
           "vaccin actuelle noeud %d\n",**nb_vaccins,compterVaccins(*abr, marque),**nb_vaccins-compterVaccins(*abr,marque));

    printf("test : %d",trouver_Vacc((*abr)->liste_vaccins,marque));
    if(trouver_Vacc((*abr)->liste_vaccins,marque)==0)
    {
        if((**nb_vaccins-compterVaccins(*abr, marque))>0)//CAS 1
        {
            //printf("yo \n");
            deduireVaccinL(&((*abr)->liste_vaccins),marque,**nb_vaccins);
            **nb_vaccins=**nb_vaccins-compterVaccins(*abr, marque);
            if ((*abr)->liste_vaccins==NULL) retirerNode(&(*abr), marque);// The node is empty

        }
        if((**nb_vaccins-compterVaccins(*abr, marque))<=0){ //CAS 2
            printf("\nyo\n1");

            deduireVaccinL(&((*abr)->liste_vaccins),marque,**nb_vaccins);
            **nb_vaccins=0;
            if ((*abr)->liste_vaccins==NULL) retirerNode(&(*abr), marque);
            //if ((*abr)->liste_vaccins==NULL) retirerNode(&(*abr), marque);// The node is empty : n'arivera pas ici

        }
    }

    deduireVaccinA(&((*abr)->fils_droit),marque, nb_vaccins);
    printf("y");
    //deduireVaccinA(&((*abr)->fils_droit),marque, nb_vaccins);
}

void retirerNode(T_ABR** abr, char* marque){
    // Node has no fils_gauche child.
    if((*abr)->fils_gauche==NULL){
        T_ABR* ElementSup = *abr;
        *abr = (*abr)->fils_droit;
        ElementSup->fils_gauche = NULL;
        ElementSup->fils_droit = NULL;
        Desallouer(ElementSup);
        return;
    }
    // Node has no fils_droit child.
    if((*abr)->fils_droit==NULL){
        T_ABR* ElementSup = *abr;
        *abr = (*abr)->fils_gauche;
        ElementSup->fils_gauche = NULL;
        ElementSup->fils_droit = NULL;
        Desallouer(ElementSup);
        return;
    }
    // Node has two children.
    // Find the smallest value node at fils_droit side sub-T_ABR.
    printf("smaller");
    T_ABR* smaller = smallerDroit((*abr)->fils_droit);
    // Copy the info of corresponding node to the node to be deleted.
    (*abr)->date = smaller->date;
    (*abr)->liste_vaccins = smaller->liste_vaccins;
    // Delete the smallest value node at fils_droit side sub-T_ABR.
    deduireVaccinA(&((*abr)->fils_droit), marque,smaller->liste_vaccins->nombre_vaccins);
}




void Desallouer(T_ABR* element_sup){
    // Release the resource allocated in the structure for T_ABR.
    // Release the structure itself.
    free(element_sup);
}

T_ABR *smallerDroit(T_ABR* abr){
    // If the tree is empty
    if(abr==NULL){
        return NULL;
    }
    // Else if find the smallest node.
    if(abr->fils_gauche==NULL){
        return abr;
    }
    // Otherwise, pass handle to the fils_gauche side sub-tree of current node.
    return smallerDroit(abr->fils_gauche);
}


/* ----------------------------------
 *   UTILITAIRES
 ---------------------------------- */


void viderBuffer(){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


