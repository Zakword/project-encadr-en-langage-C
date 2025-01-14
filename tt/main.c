#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car_rental.h"

#define MAX_CARS 100
#define MAX_STRING 50
void chargerVoituresDepuisFichier(Car voitures[], int *nombreVoitures) {
    FILE *fichier = fopen("voiture.txt", "r");
    if (!fichier) {
        *nombreVoitures = 0;
        return;
    }
    *nombreVoitures = 0;
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &voitures[*nombreVoitures].id, voitures[*nombreVoitures].brand, voitures[*nombreVoitures].user, voitures[*nombreVoitures].model, voitures[*nombreVoitures].fuelType, &voitures[*nombreVoitures].seats, voitures[*nombreVoitures].transmission, &voitures[*nombreVoitures].rentalPrice, &voitures[*nombreVoitures].isAvailable) == 9) {
        (*nombreVoitures)++;
    }
    fclose(fichier);
}
void sauvegarderVoituresDansFichier(Car voitures[], int nombreVoitures) {
    FILE *fichier = fopen("voiture.txt", "w");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier pour l'�criture.\n");
        return;
    }

    for (int i = 0; i < nombreVoitures; i++) {
        fprintf(fichier, "%d,%s,%s,%s,%s,%d,%s,%.2f,%d\n", voitures[i].id, voitures[i].brand, voitures[i].user, voitures[i].model, voitures[i].fuelType, voitures[i].seats, voitures[i].transmission, voitures[i].rentalPrice, voitures[i].isAvailable);
    }

    fclose(fichier);
}
void afficherVoitures() {
    FILE *fichier = fopen("voiture.txt", "r");
    if (!fichier) {
        printf("Aucune donn�e disponible.\n");
        return;
    }

    printf("\nVoitures disponibles :\n");
    printf("ID | Marque | Utilisateur | Mod�le | Type de carburant | Places | Transmission | Prix/jour | Disponibilit�\n");
    printf("---------------------------------------------------------------------------------------------\n");

    int id, seats, isAvailable;
    char brand[MAX_STRING], user[MAX_STRING], model[MAX_STRING], fuelType[MAX_STRING], transmission[MAX_STRING];
    float rentalPrice;

    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &id, brand, user, model, fuelType, &seats, transmission, &rentalPrice, &isAvailable) == 9) {
        printf("%d | %s | %s | %s | %s | %d | %s | %.2f | %s\n", id, brand, user, model, fuelType, seats, transmission, rentalPrice, isAvailable ? "Disponible" : "Indisponible");
    }

    fclose(fichier);
}
void ajouterVoiture() {
    FILE *fichier = fopen("voiture.txt", "a");
    if (!fichier) {
        fichier = fopen("voiture.txt", "w");
        if (!fichier) {
            printf("Impossible de cr�er le fichier pour l'ajout.\n");
            return;
        }
    }

    Car nouvelleVoiture;
    printf("Entrez les d�tails de la voiture :\n");
    printf("ID : ");
    scanf("%d", &nouvelleVoiture.id);
    printf("Marque : ");
    scanf("%s", nouvelleVoiture.brand);
    printf("Utilisateur : ");
    scanf("%s", nouvelleVoiture.user);
    printf("Mod�le : ");
    scanf("%s", nouvelleVoiture.model);
    printf("Type de carburant : ");
    scanf("%s", nouvelleVoiture.fuelType);
    printf("Nombre de places : ");
    scanf("%d", &nouvelleVoiture.seats);
    printf("Transmission : ");
    scanf("%s", nouvelleVoiture.transmission);
    printf("Prix de location par jour : ");
    scanf("%f", &nouvelleVoiture.rentalPrice);
    printf("Disponibilit� (1 pour disponible, 0 pour indisponible) : ");
    scanf("%d", &nouvelleVoiture.isAvailable);
    fprintf(fichier, "%d,%s,%s,%s,%s,%d,%s,%.2f,%d\n", nouvelleVoiture.id, nouvelleVoiture.brand, nouvelleVoiture.user, nouvelleVoiture.model, nouvelleVoiture.fuelType, nouvelleVoiture.seats, nouvelleVoiture.transmission, nouvelleVoiture.rentalPrice, nouvelleVoiture.isAvailable);
    fclose(fichier);
    printf("Voiture ajout�e avec succ�s !\n");
}
void modifierVoiture() {
    Car voitures[MAX_CARS];
    int nombreVoitures;
    chargerVoituresDepuisFichier(voitures, &nombreVoitures);
    if (nombreVoitures == 0) {
        printf("Aucune voiture disponible � modifier.\n");
        return;
    }
    int id, trouve = 0;
    printf("Entrez l'ID de la voiture � modifier : ");
    scanf("%d", &id);
    for (int i = 0; i < nombreVoitures; i++) {
        if (voitures[i].id == id) {
            trouve = 1;
            printf("Entrez les nouveaux d�tails pour la voiture (ID : %d) :\n", id);
            printf("Marque : ");
            scanf("%s", voitures[i].brand);
            printf("Utilisateur : ");
            scanf("%s", voitures[i].user);
            printf("Mod�le : ");
            scanf("%s", voitures[i].model);
            printf("Type de carburant : ");
            scanf("%s", voitures[i].fuelType);
            printf("Nombre de places : ");
            scanf("%d", &voitures[i].seats);
            printf("Transmission : ");
            scanf("%s", voitures[i].transmission);
            printf("Prix de location par jour : ");
            scanf("%f", &voitures[i].rentalPrice);
            printf("Disponibilit� (1 pour disponible, 0 pour indisponible) : ");
            scanf("%d", &voitures[i].isAvailable);
            break;
        }
    }
    if (!trouve) {
        printf("Voiture avec l'ID %d introuvable.\n", id);
    } else {
        sauvegarderVoituresDansFichier(voitures, nombreVoitures);
        printf("D�tails de la voiture mis � jour avec succ�s !\n");
    }
}
void supprimerVoiture() {
    Car voitures[MAX_CARS];
    int nombreVoitures;
    chargerVoituresDepuisFichier(voitures, &nombreVoitures);
    if (nombreVoitures == 0) {
        printf("Aucune voiture disponible � supprimer.\n");
        return;
    }
    int id, trouve = 0;
    printf("Entrez l'ID de la voiture � supprimer : ");
    scanf("%d", &id);
    for (int i = 0; i < nombreVoitures; i++) {
        if (voitures[i].id == id) {
            trouve = 1;
            for (int j = i; j < nombreVoitures - 1; j++) {
                voitures[j] = voitures[j + 1];
            }
            nombreVoitures--;
            break;
        }
    }
    if (!trouve) {
        printf("Voiture avec l'ID %d introuvable.\n", id);
    } else {
        sauvegarderVoituresDansFichier(voitures, nombreVoitures);
        printf("Voiture supprim�e avec succ�s !\n");
    }
}
int main() {
    int choix;
    printf("Bienvenue dans le syst�me de gestion de location de voitures !\n");
    while (1) {
        printf("\nMenu :\n");
        printf("1. Afficher les voitures\n");
        printf("2. Ajouter une voiture\n");
        printf("3. Modifier une voiture\n");
        printf("4. Supprimer une voiture\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                afficherVoitures();
                break;
            case 2:
                ajouterVoiture();
                break;
            case 3:
                modifierVoiture();
                break;
            case 4:
                supprimerVoiture();
                break;
            case 5:
                printf("Sortie du syst�me. Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    }
}
