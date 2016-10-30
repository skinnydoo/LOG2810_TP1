///////////////////////////////////////////////////////////////////////////////
/// @file Graph.h
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include<string>
#include <vector>
#include "Vertex.h"

class Graph {
public:
	Graph ();
	~Graph ();

	void insertVertex ( const std::string&, const std::string& );
	void insertVertex ( const std::string&, Vertex* );

	void insertEdge ( const std::string&, const std::string&, int );

	int getNumberOfVertices () const;
	int getVertexIndex ( const std::string& ) const;
	std::string getVertexName ( int index ) const;

	std::string getVertexType ( int index ) const;
	
	Graph* dijkstra ( const std::string&, const std::string& );
	inline	int getMinimalDistanceLength () const {

		return minimalDistanceLenght_;
	}

	void printGraph () const;
	void printShortestPath () const;

private :
	std::map<std::string, Vertex*> graph_;
	int minimalDistanceLenght_ { 0 };
	
	// internal method
	Graph* extractGraph ( std::vector<int>, const std::string&, const std::string&);

	inline	void setMinimalDistanceLength ( int distance ) {

		minimalDistanceLenght_ = distance;
	}
};

