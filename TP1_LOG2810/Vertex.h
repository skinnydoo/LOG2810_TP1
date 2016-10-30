///////////////////////////////////////////////////////////////////////////////
/// @file Vertex.h
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef __VERTEX_H

#include <string>
#include <map>
#include <vector>
#include "Edge.h"

class Vertex {

public:
	Vertex (const std::string&, const std::string&);
	~Vertex ();

	std::string getIdentifier ();
	std::string getType ();

	void insertEdge ( const std::string&, int );
	std::vector<std::string> getVertex () const;
	int getEdgeWeight (const std::string&) const;

private :
	std::string identifier_;
	std::string type_;
	std::map<std::string, Edge*> vertex_;


};

#endif // __VERTEX_H

///////////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////////