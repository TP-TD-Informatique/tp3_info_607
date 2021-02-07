/***
 *
 * VOUS NE DEVEZ PAS RENDRE CE FICHIER
 *
 */
#include "tp3.h"

/***
 * fonction de tests, appelée par la ligne de commandes avec l'option -T
 */
int perform_tests(int argc, char** argv)
{
    int n = 10;
    if (argc > 0) {
        n = atoi(argv[0]);
    }

    printf("\n\nfonction get_data\n"
           "-----------------\n"
           "affichage des %d premiers paquets :\n\n",
        n);
    byte IV[IV_size];
    byte o1, o2;
    for (int i = 0; i < n; i++) {
        if (get_data(IV, &o1, &o2) == IV_size) {
            printf("paquet %2d : ", i + 1);
            for (int k = 0; k < IV_size; k++)
                printf("%02x ", IV[k]);
            printf(" =>  %02x  %02x\n", o1, o2);
        } else {
            printf("***\n"
                   "*** Problème lors de la lecture d'un paquet...\n"
                   "*** Abandon\n"
                   "***\n");
            exit(1);
        }
    }

    return 0;
}
