CC = g++
OPTIONS = -O3 -Wall -Wconversion 
#-static
OBJECTS = main.o readinput.o chicane.o transport.o methods.o

main_chi: $(OBJECTS)
	$(CC) $(OPTIONS) -o main_chi $(OBJECTS) 

main.o: readinput.h chicane.h transport.h methods.h
readinput.o: readinput.h
chicane.o: chicane.h
transport.o: transport.h chicane.h
methods.o: methods.h

.PHONY: clean pack
clean:
	-rm -rf $(OBJECTS)
pack:
	-tar cjvf chicane.tar.bz2 *.cpp *.h Makefile namelist.example
	-cp chicane.tar.bz2 ../source_bak
