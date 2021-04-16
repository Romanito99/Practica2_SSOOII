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

run:
	./$(DIREXE)SSOOIIGLE.cpp Practica2_SSOOII/utils/books/21_leyes_del_liderazgo.txt navegación 4


clean:

	rm -rf $(DIREXE)
	

