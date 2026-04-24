#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lesstructures.h"
#include "prototype.h"

CLIENT* verifierCapaciteClients(CLIENT *clients, int *capaciteClients, int nbClients)
{
    if (nbClients == *capaciteClients)
    {
        *capaciteClients *= 2;
        clients = realloc(clients, (*capaciteClients) * sizeof(CLIENT));
        printf("Capacite doublee : %d\n", *capaciteClients);
    }
    return clients;
}

void ajouterClient(CLIENT **clients, int *nbClients, int *capaciteClients)
{
    *clients = verifierCapaciteClients(*clients, capaciteClients, *nbClients);

    CLIENT c;
    printf("\n--- Ajouter un client ---\n");

    printf("ID client : ");
    scanf("%d", &c.idClient);

    printf("Nom : ");
    scanf("%s", c.nom);

    printf("Prenom : ");
    scanf("%s", c.prenom);

    printf("CIN : ");
    scanf("%s", c.CIN);

    printf("Telephone : ");
    scanf("%s", c.telephone);

    printf("Email : ");
    scanf("%s", c.email);

    printf("Adresse : ");
    scanf("%s", c.adresse);

    c.nbComptes = 0;
    c.capaciteComptes = 2;
    c.comptes = malloc(c.capaciteComptes * sizeof(COMPTE));

    (*clients)[*nbClients] = c;
    (*nbClients)++;

    printf("Client ajoute avec succes !\n");
}

void rechercherClientAvecAffichage(CLIENT *clients, int nbClients, int idClient)
{
    for (int i = 0; i < nbClients; i++)
    {
        if (clients[i].idClient == idClient)
        {
            printf("\nClient trouve :\n");
            printf("Nom : %s %s\n", clients[i].nom, clients[i].prenom);
            printf("CIN : %s\n", clients[i].CIN);
            printf("Telephone : %s\n", clients[i].telephone);
            printf("Email : %s\n", clients[i].email);
            printf("Adresse : %s\n", clients[i].adresse);
            printf("Nombre de comptes : %d\n", clients[i].nbComptes);
            return;
        }
    }
    printf("Client introuvable.\n");
}

void modifierClient(CLIENT *clients, int nbClients, int idClient)
{
    for (int i = 0; i < nbClients; i++)
    {
        if (clients[i].idClient == idClient)
        {
            printf("\n--- Modifier Client ---\n");

            printf("Nouveau nom : ");
            scanf("%s", clients[i].nom);

            printf("Nouveau prenom : ");
            scanf("%s", clients[i].prenom);

            printf("Nouveau telephone : ");
            scanf("%s", clients[i].telephone);

            printf("Nouveau email : ");
            scanf("%s", clients[i].email);

            printf("Nouvelle adresse : ");
            scanf("%s", clients[i].adresse);

            printf("Modification effectuee.\n");
            return;
        }
    }
    printf("Client introuvable.\n");
}

void supprimerClient(CLIENT *clients, int *nbClients, int idClient)
{
    for (int i = 0; i < *nbClients; i++)
    {
        if (clients[i].idClient == idClient)
        {
            free(clients[i].comptes);
            clients[i] = clients[*nbClients - 1];
            (*nbClients)--;
            printf("Client supprime.\n");
            return;
        }
    }
    printf("Client introuvable.\n");
}

void afficherClient(CLIENT *c)
{
    printf("\n--- Infos Client ---\n");
    printf("ID : %d\n", c->idClient);
    printf("Nom : %s %s\n", c->nom, c->prenom);
    printf("CIN : %s\n", c->CIN);
    printf("Telephone : %s\n", c->telephone);
    printf("Email : %s\n", c->email);
    printf("Adresse : %s\n", c->adresse);
    printf("Nb comptes : %d\n", c->nbComptes);
}

void ouvrirCompte(CLIENT *c)
{
    if (c->nbComptes == c->capaciteComptes)
    {
        c->capaciteComptes *= 2;
        c->comptes = realloc(c->comptes, c->capaciteComptes * sizeof(COMPTE));
    }

    COMPTE *cp = &c->comptes[c->nbComptes];

    printf("Numero compte : ");
    scanf("%d", &cp->numCompte);

    cp->idClient = c->idClient;

    printf("Type de compte : ");
    scanf("%s", cp->type);

    cp->solde = 0;
    cp->solde_initial = 0;
    cp->nbOperations = 0;

    c->nbComptes++;
    printf("Compte ouvert avec succes !\n");
}

void depot(CLIENT *c, int numCompte, float montant)
{
    for (int i = 0; i < c->nbComptes; i++)
    {
        if (c->comptes[i].numCompte == numCompte)
        {
            c->comptes[i].solde += montant;
            int n = c->comptes[i].nbOperations;
            c->comptes[i].operations[n].montant = montant;
            strcpy(c->comptes[i].operations[n].type, "depot");
            c->comptes[i].operations[n].solde_apres = c->comptes[i].solde;
            c->comptes[i].nbOperations++;
            printf("Depot effectue !\n");
            return;
        }
    }
    printf("Compte introuvable.\n");
}

void retrait(CLIENT *c, int numCompte, float montant)
{
    for (int i = 0; i < c->nbComptes; i++)
    {
        if (c->comptes[i].numCompte == numCompte)
        {
            if (c->comptes[i].solde < montant)
            {
                printf("Solde insuffisant.\n");
                return;
            }
            c->comptes[i].solde -= montant;
            int n = c->comptes[i].nbOperations;
            c->comptes[i].operations[n].montant = montant;
            strcpy(c->comptes[i].operations[n].type, "retrait");
            c->comptes[i].operations[n].solde_apres = c->comptes[i].solde;
            c->comptes[i].nbOperations++;
            printf("Retrait effectue !\n");
            return;
        }
    }
    printf("Compte introuvable.\n");
}

void virement(CLIENT *c, int src, int dest, float montant)
{
    COMPTE *A = NULL, *B = NULL;

    for (int i = 0; i < c->nbComptes; i++)
    {
        if (c->comptes[i].numCompte == src)  A = &c->comptes[i];
        if (c->comptes[i].numCompte == dest) B = &c->comptes[i];
    }

    if (!A || !B)
    {
        printf("Compte source ou destination introuvable.\n");
        return;
    }

    if (A->solde < montant)
    {
        printf("Solde insuffisant.\n");
        return;
    }

    A->solde -= montant;
    B->solde += montant;
    printf("Virement effectue !\n");
}

void consulterSolde(CLIENT *c, int numCompte)
{
    for (int i = 0; i < c->nbComptes; i++)
    {
        if (c->comptes[i].numCompte == numCompte)
        {
            printf("Solde = %.2f\n", c->comptes[i].solde);
            return;
        }
    }
    printf("Compte introuvable.\n");
}

void afficherHistorique(COMPTE cp)
{
    printf("\n--- Historique du compte %d ---\n", cp.numCompte);
    for (int i = 0; i < cp.nbOperations; i++)
    {
        printf("%d) %s : %.2f | Solde apres : %.2f\n",
               i + 1,
               cp.operations[i].type,
               cp.operations[i].montant,
               cp.operations[i].solde_apres);
    }
}

void plusGrandeEtPetiteOperation(COMPTE *cp)
{
    if (cp->nbOperations == 0)
    {
        printf("Aucune operation.\n");
        return;
    }

    float min = cp->operations[0].montant;
    float max = cp->operations[0].montant;

    for (int i = 1; i < cp->nbOperations; i++)
    {
        if (cp->operations[i].montant < min) min = cp->operations[i].montant;
        if (cp->operations[i].montant > max) max = cp->operations[i].montant;
    }

    printf("Montant minimum : %.2f\n", min);
    printf("Montant maximum : %.2f\n", max);
}

void compteMaxMin(CLIENT *c)
{
    if (c->nbComptes == 0)
    {
        printf("Aucun compte.\n");
        return;
    }

    float min = c->comptes[0].solde;
    float max = c->comptes[0].solde;

    for (int i = 1; i < c->nbComptes; i++)
    {
        if (c->comptes[i].solde < min) min = c->comptes[i].solde;
        if (c->comptes[i].solde > max) max = c->comptes[i].solde;
    }

    printf("Solde minimum : %.2f\n", min);
    printf("Solde maximum : %.2f\n", max);
}

float soldeMoyen(COMPTE *cp)
{
    if (cp->nbOperations == 0)
        return cp->solde_initial;

    float total = 0;
    for (int i = 0; i < cp->nbOperations; i++)
        total += cp->operations[i].solde_apres;

    return total / cp->nbOperations;
}

void evaluationSoldeMoyen(COMPTE *cp, DATE d1, DATE d2)
{
    printf("Solde moyen : %.2f\n", soldeMoyen(cp));
}

void etatClient(CLIENT *c)
{
    printf("\n===== ETAT CLIENT =====\n");
    afficherClient(c);
    compteMaxMin(c);
}

void ajouterReclamation()
{
    char reclam[200];
    printf("\nEntrez votre reclamation : ");
    scanf(" %[^\n]", reclam);
    printf("Reclamation enregistree.\n");
}

void changerMotDePasse()
{
    char mdp[30];
    printf("Nouveau mot de passe : ");
    scanf("%s", mdp);
    printf("Mot de passe modifie avec succes.\n");
}

void activerDesactiverCompte(CLIENT *c, int numCompte)
{
    for (int i = 0; i < c->nbComptes; i++)
    {
        if (c->comptes[i].numCompte == numCompte)
        {
            printf("Compte %d active/desactive.\n", numCompte);
            return;
        }
    }
    printf("Compte introuvable.\n");
}

void afficherDate(DATE d)
{
    printf("%02d/%02d/%d", d.jour, d.mois, d.annee);
}

DATE saisirDate()
{
    DATE d;
    printf("Jour : ");   scanf("%d", &d.jour);
    printf("Mois : ");   scanf("%d", &d.mois);
    printf("Annee : ");  scanf("%d", &d.annee);
    return d;
}

int comparerDate(DATE d1, DATE d2)
{
    if (d1.annee != d2.annee) return d1.annee - d2.annee;
    if (d1.mois  != d2.mois)  return d1.mois  - d2.mois;
    return d1.jour - d2.jour;
}

void menuClient(CLIENT **clients, int *nbClients, int *capaciteClients)
{
    int choix;
    do {
        printf("\n===== MENU CLIENT =====\n");
        printf("1. Ajouter client\n");
        printf("2. Rechercher client\n");
        printf("3. Modifier client\n");
        printf("4. Supprimer client\n");
        printf("5. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        int id;
        switch (choix)
        {
            case 1:
                ajouterClient(clients, nbClients, capaciteClients);
                break;
            case 2:
                printf("ID : "); scanf("%d", &id);
                rechercherClientAvecAffichage(*clients, *nbClients, id);
                break;
            case 3:
                printf("ID : "); scanf("%d", &id);
                modifierClient(*clients, *nbClients, id);
                break;
            case 4:
                printf("ID : "); scanf("%d", &id);
                supprimerClient(*clients, nbClients, id);
                break;
        }
    } while (choix != 5);
}

void menuCompte(CLIENT *c)
{
    int choix;
    do {
        printf("\n===== MENU COMPTE =====\n");
        printf("1. Ouvrir compte\n");
        printf("2. Depot\n");
        printf("3. Retrait\n");
        printf("4. Virement\n");
        printf("5. Solde\n");
        printf("6. Historique\n");
        printf("7. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);

        int num, num2;
        float m;

        switch (choix)
        {
            case 1: ouvrirCompte(c); break;
            case 2:
                printf("Num compte : "); scanf("%d", &num);
                printf("Montant : ");    scanf("%f", &m);
                depot(c, num, m);
                break;
            case 3:
                printf("Num compte : "); scanf("%d", &num);
                printf("Montant : ");    scanf("%f", &m);
                retrait(c, num, m);
                break;
            case 4:
                printf("Compte source : ");      scanf("%d", &num);
                printf("Compte destination : "); scanf("%d", &num2);
                printf("Montant : ");            scanf("%f", &m);
                virement(c, num, num2, m);
                break;
            case 5:
                printf("Num compte : "); scanf("%d", &num);
                consulterSolde(c, num);
                break;
            case 6:
                printf("Num compte : "); scanf("%d", &num);
                for (int i = 0; i < c->nbComptes; i++)
                    if (c->comptes[i].numCompte == num)
                        afficherHistorique(c->comptes[i]);
                break;
        }
    } while (choix != 7);
}

void menuReclamation()
{
    printf("\n===== MENU RECLAMATION =====\n");
    ajouterReclamation();
}

void menuSecurite(CLIENT *clients, int *nbClients, int *capaciteClients)
{
    int choix;
    do {
        printf("\n===== MENU SECURITE =====\n");
        printf("1. Changer mot de passe\n");
        printf("2. Activer/Desactiver compte\n");
        printf("3. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        int id, numCompte;
        switch (choix)
        {
            case 1:
                changerMotDePasse();
                break;
            case 2:
                printf("ID client : ");  scanf("%d", &id);
                printf("Num compte : "); scanf("%d", &numCompte);
                for (int i = 0; i < *nbClients; i++)
                    if (clients[i].idClient == id)
                        activerDesactiverCompte(&clients[i], numCompte);
                break;
        }
    } while (choix != 3);
}

void menuPrincipal(CLIENT **clients, int *nbClients, int *capaciteClients)
{
    int choix;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Gestion clients\n");
        printf("2. Gestion comptes\n");
        printf("3. Reclamation\n");
        printf("4. Securite\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                menuClient(clients, nbClients, capaciteClients);
                break;
            case 2:
            {
                int id;
                printf("ID client : "); scanf("%d", &id);
                for (int i = 0; i < *nbClients; i++)
                    if ((*clients)[i].idClient == id)
                        menuCompte(&(*clients)[i]);
            }
            break;
            case 3:
                menuReclamation();
                break;
            case 4:
                if (*nbClients > 0)
                    menuSecurite(*clients, nbClients, capaciteClients);
                break;
        }
    } while (choix != 5);
}