/*
 * TP3 info607 : Maths pour l'informatique
 * RC4 et WEP
 *
 * Kevin Traini
 * Jules Geyer
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;

/**
 * Génère un octet en utilisant RC4
 * @param P La table RC4 mélangée
 * @param i L'index i
 * @param j L'index j
 * @return L'octet généré
 */
byte RC4_gen(byte *P, int *i, int *j) {
    *i = (*i + 1) % 256;
    *j = (*j + P[*i]) % 256;
    byte t = P[*i];
    P[*i] = P[*j];
    P[*j] = t;

    return P[(P[*i] + P[*j]) % 256];
}

/**
 * Chiffre message avec RC4 en passant n générations
 * @param cle La clé pour généré la table RC4
 * @param taille_cle La taille de la clé
 * @param message Le message à chiffrer
 * @param n Le nombres de générations à passer
 */
void code_RC4_drop(byte *cle, int taille_cle, char *message, int n) {
    printf("La clé est \"%s\" et le message clair est \"%s\"\n", cle, message);
    printf("Les %d premières étapes seront ignorées.\n", n);

    // Initialisation
    byte P[256];
    for (int i = 0; i < 256; ++i) {
        P[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + P[i] + cle[i % taille_cle]) % 256;
        // Echange
        byte t = P[i];
        P[i] = P[j];
        P[j] = t;
    }
    int index_i = 0, index_j = 0;

    // Passage des n premiers octets
    for (int i = 0; i < n; ++i) {
        RC4_gen(P, &index_i, &index_j);
    }

    // Chiffrage
    printf("Le code obtenu est :\n\t");
    for (long unsigned int i = 0; i < strlen(message); ++i) {
        byte t = RC4_gen(P, &index_i, &index_j);
        printf("%02X", t ^ message[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("RC4-drop[n], utilisation : %s cle message n\n", argv[0]);
        exit(-1);
    }
    code_RC4_drop((byte *) argv[1], strlen(argv[1]), argv[2], atoi(argv[3]));
    return 0;
}

// 863182CBEF7F85