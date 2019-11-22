all: main clean

main: main.o Fasta_To_Bits.o Score.o ouverture.o
	g++ main.o Fasta_To_Bits.o Score.o ouverture.o -o main

Fasta_To_Bits.o: Fasta_To_Bits.cpp Fasta_To_Bits.hpp
	g++ -c Fasta_To_Bits.cpp

Score.o: Score.cpp Score.hpp
	g++ -c Score.cpp

ouverture.o: ouverture.cpp ouverture.hpp
	g++ -c ouverture.cpp

clean:
	rm -f *.o
