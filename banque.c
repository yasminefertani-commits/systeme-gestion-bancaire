
#include <stdio.h>
#include <stdlib.h>
#include "lesstructures.h"
#include "prototype.h"

int main()
{
    int capaciteClients = 2;
    int nbClients = 0;

    CLIENT *clients = malloc(capaciteClients * sizeof(CLIENT));
    if (!clients)
    {
        printf("Erreur allocation memoire !\n");
        return 1;
    }

    printf("===== SYSTEME DE GESTION BANCAIRE =====\n");

    menuPrincipal(&clients, &nbClients, &capaciteClients);

    for (int i = 0; i < nbClients; i++)
        free(clients[i].comptes);

    free(clients);
    printf("\nMerci d'avoir utilise notre systeme !\n");
    return 0;
}