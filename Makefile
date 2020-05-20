main.exe: main.o scs.o importCSV.o cluster.o measures.o
	g++ main.o scs.o importCSV.o cluster.o measures.o -o main.exe

main.o: main.cpp
	g++ -c -std=c++17 main.cpp

scs.o: scs.cpp
	g++ -c -std=c++17 scs.cpp

importCSV.o: importCSV.cpp
	g++ -c -std=c++17 importCSV.cpp

cluster.o: cluster.cpp
	g++ -c -std=c++17 cluster.cpp

measures.o: measures.cpp
	g++ -c -std=c++17 measures.cpp

.PHONY: clean

clean:
	rm *.exe *.o
# 0x
