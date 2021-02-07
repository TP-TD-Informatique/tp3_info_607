#
# Fichier Makefile pour le TP3 d'info-607
#

#
# CONSIGNES :
#    - votre fichier principal devra s'appeler "prenom-nom.c"
#    - il faut modifier la variable "NOM" ci dessous pour qu'elle corresponde
#      au nom du fichier (sans le ".c")
#    - pour compiler, il suffit de faire
#      $ make
#      dans le répertoire qui contient les fichiers
#    - pendant le développement, vous pouvez supprimer ajouter l'option
#      "-Wno-unused-variable" pour supprimer quelques erreurs anodines. Vous
#      pouvez aussi autoriser les warnings en supprimant l'option "-Werror".
#      (Attention à bien remettre les options initiales pour tester votre
#      version finale.)
#
#


## à modifier
NOM = severus-snape

# CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu99  -O3
CFLAGS = -Wall -Wextra -pedantic -std=gnu99  -O3 -Wno-unused-parameter


#----------------------------------------------------------------------
#----- NE RIEN MODIFIER SOUS CETTE LIGNE ------------------------------
#----------------------------------------------------------------------

CC = gcc $(CFLAGS)
# CC = clang $(FLAGS)


all: generate crack

generate: generate_WEP.c
	$(CC) $< -o $@

crack: $(NOM).o tests-$(NOM).o main.o
	$(CC) $^ -o $@

lucien-tartempion.o: lucien-tartempion.c
ifeq ($(USER),hyvernat)
	$(CC) -c -o $@ $<
else
ifeq ($(USER),pierre)
	$(CC) -c -o $@ $<
else
	@echo
	@echo "CHANGEZ LE NOM DU FICHIER $< ET"
	@echo "MODIFIEZ LA VARIABLE 'NOM' DANS LE FICHIER Makefile"
	@echo
	@false
endif
endif

%.o: %.c tp3.h
	$(CC) -c -o $@ $<

clean:
	rm -f data_WEP
	rm -f generate crack *.o a.out
