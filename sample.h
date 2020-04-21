#ifndef SAMPLE_H
#define SAMPLE_H

#include <map>
#include <vector>

// Sample è lo struct rappresentante una cellula
struct sample
{
	int id;
	std::string name;
	std::map<std::string, double> mapExpression;	// Chiave: Nome del gene. Valore: RPKM del gene rispetto al sample
	std::vector <double> genesExpression;	// Tutti gli RPKM relativi al sample
	// mostExpressed da implementare
};

#endif
