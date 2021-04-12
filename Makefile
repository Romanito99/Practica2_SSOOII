DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
LDLIBS := -lpthread -lrt
CC := g++
FILS = Log.txt
COPY = CopiaDeSeguridad

all:  dir manager PA PB PC PD DAEMON run

dir:
	mkdir estudiantes $(COPY) exec

SSOOIIGLE:
	$(CC)  $(DIRSRC)SSOOIIGLE.cpp -o $(DIREXE)SSOOIIGLE.cpp -pthread -std=c++11




run:
	./$(DIREXE)SSOOIIGLE.cpp /home/cesar/Escritorio/CURSSOCOVID/SSOO2/Practica2_SSOOII/utils/books/17_leyes_del_trabajo_en_equipo.txt libre 4

test:
	ls -R $(FILS)

clean:
	rm -rf estudiantes
	rm -rf $(DIREXE)
	rm $(FILS)
daemon:
	rm -rf $(COPY)
	ps -e | grep daemon
