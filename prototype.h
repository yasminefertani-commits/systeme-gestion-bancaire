
#include "lesstructures.h"

// Capacite
CLIENT* verifierCapaciteClients(CLIENT *clients, int *capaciteClients, int nbClients);

// Gestion clients
void ajouterClient(CLIENT **clients, int *nbClients, int *capaciteClients);
void rechercherClientAvecAffichage(CLIENT *clients, int nbClients, int idClient);
void modifierClient(CLIENT *clients, int nbClients, int idClient);
void supprimerClient(CLIENT *clients, int *nbClients, int idClient);
void afficherClient(CLIENT *c);

// Gestion comptes
void ouvrirCompte(CLIENT *c);
void depot(CLIENT *c, int numCompte, float montant);
void retrait(CLIENT *c, int numCompte, float montant);
void virement(CLIENT *c, int src, int dest, float montant);
void consulterSolde(CLIENT *c, int numCompte);
void afficherHistorique(COMPTE cp);

// Traitements
void plusGrandeEtPetiteOperation(COMPTE *cp);
void compteMaxMin(CLIENT *c);
float soldeMoyen(COMPTE *cp);
void evaluationSoldeMoyen(COMPTE *cp, DATE d1, DATE d2);
void etatClient(CLIENT *c);

// Reclamation
void ajouterReclamation();

// Securite
void changerMotDePasse();
void activerDesactiverCompte(CLIENT *c, int numCompte);

// Dates
void afficherDate(DATE d);
DATE saisirDate();
int comparerDate(DATE d1, DATE d2);

// Menus
void menuClient(CLIENT **clients, int *nbClients, int *capaciteClients);
void menuCompte(CLIENT *c);
void menuReclamation();
void menuSecurite(CLIENT *clients, int *nbClients, int *capaciteClients);
void menuPrincipal(CLIENT **clients, int *nbClients, int *capaciteClients);
