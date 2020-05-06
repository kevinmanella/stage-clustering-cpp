// Contiene lo struct cluster e la dichiarazione delle funzioni newCluster, string e len
#ifndef CLUSTER_H
#define CLUSTER_H

#include "scs.h"
#include <vector>
#include <map>

// cluster è lo struct rappresentante un cluster
struct cluster
{
	std::string id;
	std::vector<sample> elements;
	std::vector<int> indices;
	std::map<int,std::vector<double>> rhn;
	double tm;
	double intraSim;
	// Da vedere intraScore
	std::vector<std::string> splittedWith;
};

cluster newCluster(std::vector<sample> cells,std::vector<int> indices);

std::string string(cluster c);

int len(cluster c);

#endif
