main.exe: main.o scs.o importCSV.o cluster.o measures.o vectorOperations.o stat.o clustering.o
	g++ main.o scs.o importCSV.o cluster.o measures.o vectorOperations.o stat.o clustering.o -fopenmp -o main.exe

main.o: main.cpp
	g++ -c -std=c++17 -fopenmp main.cpp

scs.o: scs.cpp
	g++ -c -std=c++17 -fopenmp scs.cpp

importCSV.o: importCSV.cpp
	g++ -c -std=c++17 -fopenmp importCSV.cpp

cluster.o: cluster.cpp
	g++ -c -std=c++17 -fopenmp cluster.cpp

measures.o: measures.cpp
	g++ -c -std=c++17 -fopenmp measures.cpp

vectorOperations.o: vectorOperations.cpp
	g++ -c -std=c++17 -fopenmp vectorOperations.cpp

stat.o: stat.cpp
	g++ -c -std=c++17 -fopenmp stat.cpp

clustering.o: clustering.cpp
	g++ -c -std=c++17 -fopenmp clustering.cpp

.PHONY: clean

clean:
	rm *.exe *.o
