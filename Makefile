main.exe: main.o importCSV.o scs.o cluster.o
	g++ main.o importCSV.o scs.o cluster.o -o main.exe

main.o: main.cpp
	g++ -c -std=c++0x main.cpp

importCSV.o: importCSV.cpp
	g++ -c -std=c++0x importCSV.cpp

scs.o: scs.cpp
	g++ -c -std=c++0x scs.cpp

cluster.o: cluster.cpp
	g++ -c -std=c++0x cluster.cpp

.PHONY: clean

clean:
	rm *.exe *.o
