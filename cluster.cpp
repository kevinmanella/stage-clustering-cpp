#include "cluster.h"
#include <bits/stdc++.h>

// Funzione che, dati un vector di samples e un vector di int, crea un nuovo cluster
// Funzione da riguardare e completare
cluster* newCluster(std::vector<sample> cells,std::vector<int> indices)
{
	cluster* c=new cluster;
	std::vector<std::string> strindices;
	sort(indices.begin(),indices.end());
	for(std::vector<int>::iterator it=indices.begin();it!=indices.end();it++)
	{
		c->elements.push_back(cells[*it]);
		c->indices.push_back(*it);
		strindices.push_back(std::to_string(*it));
	}

	c->tm=-1.0;
	
	for(std::vector<std::string>::iterator it=strindices.begin();it!=strindices.end();it++)
	{
		c->id+=*it;
		if(it!=strindices.end()-1)
			c->id+=',';
	}

	return c;
}

// Funzione che, dato un puntatore a cluster, restituisce una stringa formata concatenando i nomi dei samples presenti nel cluster
// La stringa inizia e termina con il carattere " e i nomi dei samples sono separati dal carattere ,
std::string string(cluster* c)
{
	std::vector<std::string> elementsName;

	for(std::vector<sample>::iterator it=c->elements.begin();it!=c->elements.end();it++)
		elementsName.push_back((*it).name);

	std::string s="";
	s+='"';

	for(std::vector<std::string>::iterator it=elementsName.begin();it!=elementsName.end();it++)
	{
		s+=*it;
		if(it!=elementsName.end()-1)
			s+=',';
	}

	s+='"';

	return s;
}

// Funzione che, dato un puntatore a cluster, restituisce il numero di elementi presenti nel cluster
int len(cluster* c)
{
	return c->elements.size();
}
