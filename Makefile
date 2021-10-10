# Variables to control Makefile operation
 
CC = /usr/bin/g++
CFLAGS = -Wall -g
main = main
func1 = Carte
func2 = Deques
func3 = Joueur
func4 = mes_fonctions

# ****************************************************
all: $(main)

$(main): fichiers_objets/$(main).o fichiers_objets/$(func1).o fichiers_objets/$(func2).o fichiers_objets/$(func3).o fichiers_objets/$(func4).o
	$(CC) $(CFLAGS) -o $(main) fichiers_objets/$(main).o fichiers_objets/$(func1).o fichiers_objets/$(func2).o fichiers_objets/$(func3).o fichiers_objets/$(func4).o
 
fichiers_objets/$(main).o: $(main).cpp
	$(CC) $(CFLAGS) -c $(main).cpp
	mv $(main).o fichiers_objets/

fichiers_objets/$(func1).o: $(func1).cpp
	$(CC) $(CFLAGS) -c $(func1).cpp
	mv $(func1).o fichiers_objets/

fichiers_objets/$(func2).o: $(func2).cpp
	$(CC) $(CFLAGS) -c $(func2).cpp
	mv $(func2).o fichiers_objets/

fichiers_objets/$(func3).o: $(func3).cpp
	$(CC) $(CFLAGS) -c $(func3).cpp
	mv $(func3).o fichiers_objets/

fichiers_objets/$(func4).o: $(func4).cpp
	$(CC) $(CFLAGS) -c $(func4).cpp
	mv $(func4).o fichiers_objets/


clean:
	$(RM) $(main)
