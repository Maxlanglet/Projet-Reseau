all: main clean

main: main.o Fasta_To_Bits.o Score.o ouverture.o comparaison.o binaire.o Sequence.o Offsets.o blosum.o SwipeAlgo.o header.o
	g++ main.o Fasta_To_Bits.o Score.o ouverture.o comparaison.o binaire.o Sequence.o Offsets.o blosum.o SwipeAlgo.o header.o -o main

Fasta_To_Bits.o: Fasta_To_Bits.cpp Fasta_To_Bits.hpp
	g++ -c Fasta_To_Bits.cpp

Score.o: Score.cpp Score.hpp
	g++ -c Score.cpp

ouverture.o: ouverture.cpp ouverture.hpp
	g++ -c ouverture.cpp

comparaison.o: comparaison.cpp comparaison.hpp
	g++ -c comparaison.cpp

binaire.o: binaire.cpp binaire.h
	g++ -c binaire.cpp

Sequence.o: Sequence.cpp Sequence.hpp
	g++ -c Sequence.cpp
	
Offsets.o: Offsets.cpp Offsets.hpp
	g++ -c Offsets.cpp
	
blosum.o: blosum.cpp blosum.hpp
	g++ -c blosum.cpp
	
SwipeAlgo.o: SwipeAlgo.cpp SwipeAlgo.hpp
	g++ -c SwipeAlgo.cpp
	
header.o: header.cpp header.h
	g++ -c header.cpp

clean:
	rm -f *.o
