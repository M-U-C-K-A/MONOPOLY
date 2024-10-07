#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*
ce fichier permet de tester 
pour l'affiche l'ajout de maisos
dans le but de le split en deux ou
de mettre un hotel si le nombre est a 5
*/



int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    int X;

    if (argc != 2) {
        printf("Usage: %s <entier>\n", argv[0]);
        return 1;
    }

    X = atoi(argv[1]);

    if (X == 5) {
        // Si X == 5, afficher un hôtel sur la première ligne et rien sur la seconde
        printf("Content: hotel\n");
        printf("Répartition sur deux lignes:\n");
        printf("🏨\n"); // Première ligne avec l'hôtel
        printf("\n");        // Deuxième ligne vide
    } else {
        // Sinon, afficher des maisons
        printf("Content: ");
        for (int i = 0; i < X; i++) {
            printf("🏠 ");
        }
        printf("\n");

        // Répartition des maisons sur deux lignes
        printf("Répartition sur deux lignes:\n");

        if (X % 2 == 0) {
            // Si X est pair, répartir également
            for (int i = 0; i < X / 2; i++) {
                printf("🏠 ");
            }
            printf("\n");
            for (int i = 0; i < X / 2; i++) {
                printf("🏠 ");
            }
            printf("\n");
        } else {
            // Si X est impair, répartir inégalement
            for (int i = 0; i < X / 2; i++) {
                printf("🏠 ");
            }
            printf("\n");
            for (int i = 0; i < X / 2 + 1; i++) {
                printf("🏠 ");
            }
            printf("\n");
        }
    }

    return 0;
}

