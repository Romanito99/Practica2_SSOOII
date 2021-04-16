DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
LDLIBS := -lpthread -lrt
CC := g++
FILS = Log.txt
COPY = CopiaDeSeguridad

all:  clean dir SSOOIIGLE

dir:
	mkdir  exec

SSOOIIGLE:
	$(CC)  $(DIRSRC)SSOOIIGLE.cpp -o $(DIREXE)SSOOIIGLE.cpp -pthread -std=c++11

test:
	./$(DIREXE)SSOOIIGLE.cpp utils/books/21_leyes_del_liderazgo.txt aprender 4

test1:
	./$(DIREXE)SSOOIIGLE.cpp utils/books/Vive_tu_sueño.txt millón 6
test2:
	./$(DIREXE)SSOOIIGLE.cpp utils/books/Abe_Shana_La_ultima_sirena.txt supuesto 8

clean:

	rm -rf $(DIREXE)
	

