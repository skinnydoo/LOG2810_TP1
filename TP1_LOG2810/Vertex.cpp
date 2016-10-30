///////////////////////////////////////////////////////////////////////////////
/// @file Vertex.cpp
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////

#include "Vertex.h"
using namespace std;


////////////////////////////////////////////////////////////////////////
///
/// @fn Vertex::Vertex (const string& identifier, const string& type) 
///
/// Ne fait qu'initialiser les 
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Vertex::Vertex (const string& identifier, const string& type) 
	: identifier_(identifier), type_(type) {}



////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::~ArbreRendu()
///
/// Détruit les 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Vertex::~Vertex () {}


////////////////////////////////////////////////////////////////////////
///
/// @fn string Vertex::getIdentifier ()
///
/// Retourne l'identifiant
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
string Vertex::getIdentifier () {

	return identifier_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn string Vertex::getType ()
///
/// Retourne le type 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
string Vertex::getType () {

	return type_;
}


void Vertex::insertEdge ( const string &target, int distance ) {

	Edge* edge { new Edge(distance) };
	vertex_.insert ( { target, edge } );

	/*delete edge;
	edge = nullptr;*/
}

vector<string> Vertex::getVertex () const {

	std::vector<string> vertex;
	for ( auto& value : vertex_ )
		vertex.push_back ( value.first );

	return vertex;
}

int Vertex::getEdgeWeight (const string& vertex) const {

	for ( auto& value : vertex_ )

		if ( value.first == vertex )
			return value.second->getDistance ();

	return 0;
	
}