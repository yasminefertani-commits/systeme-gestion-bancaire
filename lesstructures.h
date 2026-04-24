#define MAX_OPS 200

struct date {
    int jour;
    int mois;
    int annee;
};
typedef struct date DATE;

struct operation {
    DATE date;
    char type[20];
    float montant;
    float solde_apres;
};
typedef struct operation OPERATION;

struct compte {
    int numCompte;
    int idClient;
    char type[20];
    float solde;
    float solde_initial;
    OPERATION operations[MAX_OPS];
    int nbOperations;
};
typedef struct compte COMPTE;

struct client {
    int idClient;
    char nom[30];
    char prenom[30];
    char CIN[20];
    char telephone[15];
    char email[40];
    char adresse[60];
    COMPTE *comptes;
    int nbComptes;
    int capaciteComptes;
};
typedef struct client CLIENT;