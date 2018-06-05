CC = g++
CFLAGS = -g -Wall
all:imc

imc:imc.cc 
	$(CC) $(CFLAGS) -o imc imc.cc

clean:
	rm imc
