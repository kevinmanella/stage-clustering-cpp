main.exe: main.o importCSV.o
	g++ main.o importCSV.o -o main.exe

main.o: main.cpp
	g++ -c -std=c++0x main.cpp

importCSV.o: importCSV.cpp
	g++ -c -std=c++0x importCSV.cpp

.PHONY: clean

clean:
	rm *.exe *.o
