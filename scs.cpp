#include "scs.h"
#include <bits/stdc++.h>

// Funzione che, dato un vector di double, ne restituisce la mediana
double getMedian(std::vector <double> values)
{
	std::vector <double> tmp=values;

	std::vector <double>::iterator it=tmp.begin();
	while(it!=tmp.end())
	{
		if(*it==0)
			it=tmp.erase(it);
		else
			it++;
	}

	sort(tmp.begin(),tmp.end());

	int middle=tmp.size()/2;

	if(tmp.size()%2==0)
		return (tmp[middle-1]+tmp[middle])/2;

	return tmp[middle];
}

// Funzione che, dati un sample e un double, costruisce l'insieme di geni che sono p volte più espressi rispetto alla mediana (escludendo gli zeri)
void buildExpressedSet2(sample &s, double p)
{
	double median=getMedian(s.genesExpression);
	int i=0;
	
	while(s.mostExpressed.size()<=10)
	{
		i=0;
		for(std::vector<double>::iterator it=s.genesExpression.begin();
			it!=s.genesExpression.end();it++)
		{
			if(*it>p*median)
				s.mostExpressed.insert(i);

			i++;
		}
		p*=0.9;
	}
}
