DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
LDLIBS := -lpthread -lrt
CC := gcc
FILS = Log.txt
COPY = CopiaDeSeguridad

all:  dir manager PA PB PC PD DAEMON run

dir:
	mkdir estudiantes $(COPY) exec

manager:
	$(CC) $(LDLIBS) $(DIRSRC)Manager.c -o $(DIREXE)Manager

PA:
	$(CC) $(CFLAGS) $(DIRSRC)Pa.c -o $(DIREXE)Pa

PB:
	$(CC) $(CFLAGS) $(DIRSRC)Pb.c -o $(DIREXE)Pb

PC:
	$(CC) $(CFLAGS) $(DIRSRC)Pc.c -o $(DIREXE)Pc

PD:
	$(CC) $(CFLAGS) $(DIRSRC)Pd.c -o $(DIREXE)Pd
DAEMON: 
	$(CC) $(CFLAGS) $(DIRSRC)daemon.c -o $(DIREXE)daemon


run:
	./$(DIREXE)Manager

test:
	ls -R $(FILS)

clean:
	rm -rf estudiantes
	rm -rf $(DIREXE)
	rm $(FILS)
daemon:
	rm -rf $(COPY)
	ps -e | grep daemon
