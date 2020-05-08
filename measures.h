#include "cluster.h"
#include <vector>

struct retScore
{
	int i;
	int j;
	double score;
};

typedef retScore* (*similarityFunction) (std::vector<double> x,std::vector<double> y,int xi,int yi);

typedef retScore* (*clusterSimilarityFunction) (cluster* c1,cluster* c2,int ci,int cj);

std::string string(retScore* r);

retScore* cosineSimilarity(std::vector<double> x,std::vector<double> y,int xi,int yi);

retScore* avgCosine(cluster* c1,cluster* c2,int ci,int cj);

retScore* avgGenes(cluster* c1,cluster* c2,int ci,int cj);

retScore* euclideanSimilarity(std::vector<double> x,std::vector<double> y,int xi,int yi);

retScore* minkowskiSimilarity(std::vector<double> x,std::vector<double> y,int xi,int yi);

retScore* geneExpressed(std::vector<double> x,std::vector<double> y,int xi,int yi);
