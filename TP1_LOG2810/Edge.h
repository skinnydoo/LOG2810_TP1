///////////////////////////////////////////////////////////////////////////////
/// @file Edge.h
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef __EDGE_H

#include <string>
//#include "Vertex.h"


class Edge {
public:
	Edge (int);
	~Edge ();

	void setDistance ( int distance );
	int getDistance ();

private :
	int distance_ { 0 };
};

#endif //  __EDGE_H

