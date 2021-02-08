/**********************************************************************
 *** craque une clé WEP en utilisant l'attaque du Fluhrer, Mantin et
 *** Shamir.
 *** Les données sont récupérées dans un tube rempli par un
 *** générateur indépendant.
 *** TP3 d'info-607 : RC4, WEP et attaque FMS
 *** Kevin Traini
 *** Jules Geyer
 **********************************************************************/

#include "tp3.h"

/***
 * récupère un paquet de données dans le tube (variable globale tube_fd) :
 *   - IV est un tableau de IV_size (variable globale) octets qui contiendra
 *     le vecteur d'initialisation lu,
 *   - o1 et o2 seront les 2 premiers octets générés par RC4 à partir de la
 *     clé WEP (secrète) et le vecteur d'initialisation.
 * La fonction lit également un octet supplémentaire et vérifie qu'il est bien
 * égal à 0x00.
 * Si tout a fonctionné, la fonction renvoie IV_size ; sinon, elle renvoie un
 * nombre strictement négatif.
 */
int get_data(byte *IV, byte *o1, byte *o2) {
    byte buffer;
    // Lecture de IV
    for (int i = 0; i < IV_size; ++i) {
        if (read(tube_fd, &buffer, 1) == 1) // On vérifie si la lecture s'est bien passée
            IV[i] = buffer;
        else
            return -1;
    }

    // Lecture de o1
    if (read(tube_fd, &buffer, 1) == 1)
        *o1 = buffer;

    // Lecture de o2
    if (read(tube_fd, &buffer, 1) == 1)
        *o2 = buffer;

    // Vérification prochain octet à 0
    if (read(tube_fd, &buffer, 1) == 1)
        if (buffer == 0x00)
            return IV_size;

    return -1;
}

/***
 * récupère un paquet de données WEP générées et vérifie que la clé WEP passée
 * en argument génère bien le même premier octet avec le même vecteur
 * d'initialisation.
 * La fonction renvoie 1 lorsque c'est le cas, et 0 sinon.
 */
int check_byte(byte *cle_WEP) {
    // TODO...
    return 0;
}

/***
 * teste un vecteur d'initialisation :
 *   - "n" est la taille de la clé déjà connue
 *   - "o1" est le premier octet généré par RC4 avec "IV"
 *   - "o2" est le premier octet généré par RC4 avec "IV"
 *   - "key" contient les morceaux de la clé que l'on a déjà calculés
 *
 * La fonction renvoie 1 si le vecteur d'initialisation était faible,
 * et dans ce cas, la prédiction correspondante est renvoyée dans le
 * dernier paramètre "prediction".
 *
 * Si le vecteur d'initialisation n'était pas faible, cette fonction
 * renvoie 0.
 */
int weak(int n, byte *key, byte o1, byte o2, byte *prediction) {
    // KSA
    byte P[256];
    for (int i = 0; i < 256; ++i) { // Initialisation de la table RC4
        P[i] = i;
    }
    int j = 0;
    for (int i = 0; i < n; ++i) { // N premiers mélanges de la table
        j = (j + P[i] + key[i]) % 256;
        // Echange
        byte t = P[i];
        P[i] = P[j];
        P[j] = t;
    }

    // Vérification vecteur faible
    if (P[1] < n && (P[1] + P[P[1]] == n)) {
        // Cherche o1 dans P
        int i = 0;
        while (i < 256 && P[i] != o1) i++;

        *prediction = i - j - P[n];
        return 1;
    }

    return 0;
}

/***
 * craque une clé WEP complète
 * L'argument devra contenir la prédiction finale pour la clé complète.
 *
 * Pour chaque prédiction d'un octet de la clé, la fonction attend d'avoir
 * observé
 *   - soit expected_weak_IV (variable globale) vecteur faibles
 *   - soit expected_IV (variable globale) vecteurs
 * Lorsque c'est fait, une prédiction pour l'octet en cours est faite, et la
 * fonction passe à l'octet suivant.
 *
 * ====
 * Après une prédiction de la clé, la fonction devra faire nb_tests (variable
 * globale) vérifications avec la fonction check_byte.
 *   - Si tous les tests réussissent, la fonction renverra un nombre
 * strictement positif.
 *   - Si au moins un test échoue, la fonction renverra un nombre strictement
 *     négatif.
 *   - Si aucun test n'est fait, la fonction renverra 0.
 *
 * ====
 * Si un des tests précédent échoue, la fonction devra essayer d'améliorer la
 * prédiction pour tous les octets de la clé. Ce nombre d'essais
 * supplémentaire est borné par nb_retries (variable globale).
 * Si la clé prédite passe tous les tests avant cette borne, la fonction
 * pourra se terminer.
 */
int crack_WEP(byte *cle_WEP) {
    // TODO...

    // ATTENTION, cle_WEP ne contient que la partie fixe de la clé alors que
    // la fonction weak prend en argument la clé complète (partie variable +
    // partie fixe). Il faut donc déclarer une nouvelle variable pour contenir
    // la clé complète.

    return 0;
}
