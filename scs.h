// Contiene lo struct sample e la dichiarazione delle funzioni getMedian e buildExpressedSet2
#ifndef SCS_H
#define SCS_H

#include <map>
#include <vector>
#include <set>

// Sample è lo struct rappresentante una cellula
struct sample
{
	int id;
	std::string name;
	std::map<std::string, double> mapExpression;	// Chiave: Nome del gene. Valore: RPKM del gene rispetto al sample
	std::vector <double> genesExpression;	// Tutti gli RPKM relativi al sample
	std::set<int> mostExpressed;	// Insieme che contiene gli indici dei geni più espressi
};

// Per intersezione ed unione serve #include <algorithm>
// Codice per intersezione fra 2 set
// set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),std::inserter(s3,s3.begin()));

// Codice per unione fra 2 set
// set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),std::inserter(s3,s3.begin()));

double getMedian(std::vector <double> values);

void buildExpressedSet2(sample &s, double p);

#endif
