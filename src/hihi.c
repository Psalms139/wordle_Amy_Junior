#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_MOTS 2309
#define TAILLE_MOT 6 


typedef struct {
    char mot[TAILLE_MOT];
} Mot;


int charger_mots(Mot mots[]) {
    FILE *fichier = fopen("ressource/bdd_wordle.txt", "r");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        exit(EXIT_FAILURE);
    }

    int nb_mots = 0;
    while (fgets(mots[nb_mots].mot, TAILLE_MOT, fichier) != NULL) {
        
        mots[nb_mots].mot[strcspn(mots[nb_mots].mot, "\n")] = '\0';
        nb_mots++;
    }

    fclose(fichier);
    return nb_mots;
}


bool verifier_mot(const char mot[]) {
    return strlen(mot) == 5;
}


void comparer_mots(const char mot_a_trouver[], const char mot_propose[]) {
    int lettres_correctes = 0;
    int lettres_bien_placees = 0;
    
    for (int i = 0; i < 5; i++) {
        if (mot_a_trouver[i] == mot_propose[i]) {
            lettres_bien_placees++;
        } else if (strchr(mot_a_trouver, mot_propose[i]) != NULL) {
            lettres_correctes++;
        }
    }
    
    printf("Lettres correctes : %d\n", lettres_correctes);
    printf("Lettres bien placées : %d\n", lettres_bien_placees);
}


void filtrer_par_lettre(Mot mots[], int nb_mots, char lettre) {
    for (int i = 0; i < nb_mots; i++) {
        if (strchr(mots[i].mot, lettre) != NULL) {
            printf("%s\n", mots[i].mot);
        }
    }
}

int main() {
    Mot mots[MAX_MOTS];
    int nb_mots = charger_mots(mots);

    
    srand(time(NULL));
    int index_mot_a_trouver = rand() % nb_mots;
    const char *mot_a_trouver = mots[index_mot_a_trouver].mot;

    printf("Bienvenue dans le jeu Wordle!\n");
    printf("Vous avez 6 propositions pour deviner un mot de 5 lettres.\n");

    char lettre_filtre;
    printf("Voulez-vous filtrer les mots par une lettre spécifique ? (O/N) : ");
    char choix_filtre;
    scanf(" %c", &choix_filtre);

    if (choix_filtre == 'O' || choix_filtre == 'o') {
        printf("Entrez la lettre pour filtrer les mots : ");
        scanf(" %c", &lettre_filtre);
        printf("Mots filtrés par la lettre '%c' :\n", lettre_filtre);
        filtrer_par_lettre(mots, nb_mots, lettre_filtre);
    } else {
        printf("Tous les mots sont affichés :\n");
        for (int i = 0; i < nb_mots; i++) {
            printf("%s\n", mots[i].mot);
        }
    }

    
    for (int essai = 1; essai <= 6; essai++) {
        char mot_propose[TAILLE_MOT];
        printf("\nEssai %d : Entrez votre proposition de mot : ", essai);
        scanf("%s", mot_propose);

        if (!verifier_mot(mot_propose)) {
            printf("Erreur : Veuillez entrer un mot de 5 lettres.\n");
            continue;
        }

        comparer_mots(mot_a_trouver, mot_propose);

        if (strcmp(mot_a_trouver, mot_propose) == 0) {
            printf("Félicitations! Vous avez trouvé le mot %s en %d essais.\n", mot_a_trouver, essai);
            return 0;
        }
    }

    printf("Désolé, vous n'avez pas trouvé le mot. Le mot à trouver était : %s\n", mot_a_trouver);
    return 0;
}
