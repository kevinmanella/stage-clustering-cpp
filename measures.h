#include "cluster.h"
#include <vector>

struct retScore
{
	int i;
	int j;
	double score;
};

retScore* cosineSimilarity(std::vector<double> x,std::vector<double> y,int xi,int yi);

retScore* avgCosine(cluster* c1,cluster* c2,int ci,int cj);

retScore* avgGenes(cluster* c1,cluster* c2,int ci,int cj);
