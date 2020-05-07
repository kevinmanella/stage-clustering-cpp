#include "measures.h"
#include <cmath>
#include <algorithm>

retScore* cosineSimilarity(std::vector<double> x,std::vector<double> y,int xi,int yi)
{
	retScore* ret=new retScore();
	double prod=0.0;
	double magnitude1=0.0;
	double magnitude2=0.0;

	for(int i=0;i<x.size();i++)
	{
		prod+=x[i]*y[i];
		magnitude1+=pow(x[i],2);
		magnitude2+=pow(y[i],2);
	}

	magnitude1=sqrt(magnitude1);
	magnitude2=sqrt(magnitude2);

	ret->i=xi;
	ret->j=yi;
	ret->score=prod/(magnitude1*magnitude2);

	return ret;
}

retScore* avgCosine(cluster* c1,cluster* c2,int ci,int cj)
{
	retScore* ret=new retScore();
	double denom=0.0;
	double avg=0.0;
	double score=0.0;
	int n=len(c1);
	int m=len(c2);
	
	for(int i=0;i<n+m;i++)
		for(int j=i+1;j<n+m;j++)
		{
			std::vector<double> ge1,ge2;

			if(i<n)
				ge1=c1->elements[i].genesExpression;
			else
				ge1=c2->elements[i-n].genesExpression;

			if(j<n)
				ge2=c1->elements[j].genesExpression;
			else
				ge2=c2->elements[j-n].genesExpression;

			score=cosineSimilarity(ge1,ge2,i,j)->score;
			avg+=score;
			denom++;
		}

		ret->i=ci;
		ret->j=cj;
		ret->score=avg/denom;

		return ret;
}

retScore* avgGenes(cluster* c1,cluster* c2,int ci,int cj)
{
	retScore* ret=new retScore();
	double denom=0.0;
	double avg=0.0;
	double score=0.0;
	int n=len(c1);
	int m=len(c2);

	for(int i=0;i<n+m;i++)
		for(int j=i+1;j<n+m;j++)
		{
			std::set<int> ge1,ge2,ge3,ge4;

			if(i<n)
				ge1=c1->elements[i].mostExpressed;
			else
				ge1=c2->elements[i-n].mostExpressed;

			if(j<n)
				ge2=c1->elements[j].mostExpressed;
			else
				ge2=c2->elements[j-n].mostExpressed;

			set_intersection(ge1.begin(),ge1.end(),ge2.begin(),ge2.end(),
							 std::inserter(ge3,ge3.begin()));
			set_union(ge1.begin(),ge1.end(),ge2.begin(),ge2.end(),
					  std::inserter(ge4,ge4.begin()));
			score=double(ge3.size())/double(ge4.size());
			avg+=score;
			denom++;
		}

		ret->i=ci;
		ret->j=cj;
		ret->score=avg/denom;

		return ret;
}
