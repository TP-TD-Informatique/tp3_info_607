/***
 *
 * VOUS NE DEVEZ PAS RENDRE CE FICHIER
 *
 */
#include "tp3.h"

/***
 * fonction de tests, appelée par la ligne de commandes avec l'option -T
 */
int perform_tests(int argc, char **argv) {
    if (argc > 0) {
        int n = atoi(argv[0]);

        if (n == 2) {
            printf("\n\nfonction get_data\n"
                   "-----------------\n"
                   "affichage des %d premiers paquets :\n\n",
                   8);
            byte IV[IV_size];
            byte o1, o2;
            for (int i = 0; i < 8; i++) {
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
        } else if (n == 3) {
            byte prediction = 0;
            byte key3[] = {0x78, 0x89, 0xec, 0x01, 0x02, 0x03, 0x04};
            int faible = weak(3, key3, 0x2b, 0x00, &prediction);
            printf("3 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key4[] = {0x5a, 0xa4, 0xcb, 0x01};
            prediction = 0;
            faible = weak(4, key4, 0xd7, 0x00, &prediction);
            printf("4 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key6[] = {0xd8, 0x77, 0x9e, 0x01, 0x02, 0x03};
            prediction = 0;
            faible = weak(6, key6, 0xfa, 0x00, &prediction);
            printf("6 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key7[] = {0x78, 0x89, 0xec, 0x01, 0x02, 0x03, 0x04};
            prediction = 0;
            faible = weak(7, key7, 0x21, 0x00, &prediction);
            printf("7 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key8[] = {0x82, 0x7f, 0xe2, 0x01, 0x02, 0x03, 0x04, 0x05};
            prediction = 0;
            faible = weak(8, key8, 0x83, 0x00, &prediction);
            printf("8 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key10[] = {0xf8, 0x0b, 0xe2, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
            prediction = 0;
            faible = weak(10, key10, 0x2e, 0x00, &prediction);
            printf("10 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key12[] = {0x22, 0xe0, 0xba, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
            prediction = 0;
            faible = weak(12, key12, 0x29, 0x00, &prediction);
            printf("12 -> faible : %d\tprediction : %02X\n", faible, prediction);
            byte key14[] = {0xf7, 0x3b, 0xe1, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
            prediction = 0;
            faible = weak(14, key14, 0x03, 0x00, &prediction);
            printf("14 -> faible : %d\tprediction : %02X\n", faible, prediction);
        }
    }

    return 0;
}
