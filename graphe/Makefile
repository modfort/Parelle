CC=g++
CFLAGS=-std=c++14 -O3 -Wall -lpthread -lsfml-graphics -lsfml-window -lsfml-system
EXEC=MEHDI
DotH=Graph.hpp
COPIE= *.cpp *.hpp Makefile *.txt
COPIEBACK=../$(COPIE)
FILE = TMP
$(EXEC) : tp.o $(DotH) 
	$(CC) -o $@ tp.o  $(CFLAGS)
tp.o:tp.cpp $(DotH)
	$(CC) -o tp.o -c tp.cpp  $(CFLAGS)


cp :
	cp $(COPIE) $(FILE)
recu:
	cp 	-f $(COPIEBACK) .
mk:
	mkdir $(FILE)


clean:
	rm $(EXEC) *.o 
cleantotal:
	sudo rm -r $(FILE) $(EXEC) *.o  

resume:
	echo "code qui a partir d'un fichier creer un graph et fait circuler des voiture selon le nombre de thread"
