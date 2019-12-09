all: main clean

main: main.o Fasta_To_Bits.o Score.o ouverture.o comparaison.o binaire.o Sequence.o Offsets.o blosum.o SwipeAlgo.o header.o
	g++ main.o Fasta_To_Bits.o Score.o ouverture.o comparaison.o binaire.o Sequence.o Offsets.o blosum.o SwipeAlgo.o header.o -o main

Fasta_To_Bits.o: Fasta_To_Bits.cpp Fasta_To_Bits.hpp
	g++ -c -O3 Fasta_To_Bits.cpp

Score.o: Score.cpp Score.hpp
	g++ -c -O3 Score.cpp

ouverture.o: ouverture.cpp ouverture.hpp
	g++ -c -O3 ouverture.cpp

comparaison.o: comparaison.cpp comparaison.hpp
	g++ -c -O3 comparaison.cpp

binaire.o: binaire.cpp binaire.h
	g++ -c -O3 binaire.cpp

Sequence.o: Sequence.cpp Sequence.hpp
	g++ -c -O3 Sequence.cpp
	
Offsets.o: Offsets.cpp Offsets.hpp
	g++ -c -O3 Offsets.cpp
	
blosum.o: blosum.cpp blosum.hpp
	g++ -c -O3 blosum.cpp
	
SwipeAlgo.o: SwipeAlgo.cpp SwipeAlgo.hpp
	g++ -c -O3 SwipeAlgo.cpp
	
header.o: header.cpp header.h
	g++ -c -O3 header.cpp

clean:
	rm -f *.o
