///////////////////////////////////////////////////////////////////////////////
/// @file Graph.cpp
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "Graph.h"
#include<functional>
#include <queue>
#include <iostream>
#include<set>
using namespace std;


////////////////////////////////////////////////////////////////////////
///
/// @fn Graph::Graph ()
///
/// Constructeur par defaut. Ne fait rient
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Graph::Graph () {}

////////////////////////////////////////////////////////////////////////
///
/// @fn Graph::~Graph ()
///
/// Destructeur.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Graph::~Graph () {}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Graph::insertVertex ( const string& identifier, const string& type )
///
/// Insert un sommiet dans le graphe en lui passant son identifiant
/// et son type.
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Graph::insertVertex ( const string& identifier, const string& type ) {
	
	Vertex* vertex { new Vertex ( identifier, type ) };
	insertVertex ( identifier, vertex );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Graph::insertVertex ( const string& identifier, Vertex* vertex )
///
/// Insert un sommiet dans le graphe en lui passant son identifant et un sommet
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Graph::insertVertex ( const string& identifier, Vertex* vertex ) {

	graph_.insert ( { identifier, vertex } );
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Graph::insertEdge ( const string& source, const string& target, int distance ) 
///
/// Insert un arc dans le graphe en lui passant le sommet source, la destination
/// et le poid de celui ci
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Graph::insertEdge ( const string& source, const string& target, int distance ) {

	if ( source == target )	// no loop
		return;

	auto it = graph_.find ( source );
	if ( it == graph_.end () )
		return;
	
	it->second->insertEdge ( target, distance );

}


//////////////////////////////////////////////////////////////////////////
///
/// @fn int Graph::getNumberOfVertices () const
///
/// Methode permettant de connaitre le nombre de sommet que contien le graphe
///
/// @return int
///
////////////////////////////////////////////////////////////////////////
int Graph::getNumberOfVertices () const {

	return graph_.size ();
}


//////////////////////////////////////////////////////////////////////////
///
/// @fn int Graph::getVertexIndex ( const string& vertex ) const
///
/// Methode permettant de retouner l'index ou position d'un sommet dans la map
///
/// @return int
///
////////////////////////////////////////////////////////////////////////
int Graph::getVertexIndex ( const string& vertex ) const {
	
	int number = 0;
	for ( auto& value : graph_ ) {

		if ( value.first == vertex )
			return number;

		++number;
	}

	return number;
}


//////////////////////////////////////////////////////////////////////////
///
/// @fn string Graph::getVertexName ( int index ) const
///
/// Methode permettant de retrouver le nom d'un sommet en connaissant son index
///
/// @return string
///
////////////////////////////////////////////////////////////////////////
string Graph::getVertexName ( int index ) const {

	int i = 0;
	for ( auto& graph : graph_ ) {
		if ( i == index )
			return graph.first;

		++i;
	}

	return "";
}

//////////////////////////////////////////////////////////////////////////
///
/// @fn string Graph::getVertexType ( int index ) const
///
/// Methode permettant de retrouver le type d'un sommet en connaissant son index
///
/// @return string
///
////////////////////////////////////////////////////////////////////////
string Graph::getVertexType ( int index ) const {

	int i = 0;
	for ( auto& graph : graph_ ) {
		if ( i == index )
			return graph.second->getType ();

		++i;
	}

	return "";
}


//////////////////////////////////////////////////////////////////////////
///
/// @fn Graph* Graph::dijkstra ( const string& source, const string& target )
///
/// Cette methode utilise l'algorithme de dijstra pour determiner le
/// plus court chemin dans un graph en lui passant la source et la destination
/// elle appelle ensuite le methode 
/// extractGraph ( vector<int> path, const string& source, const string& target )
/// pour extraire le chemin
/// @return un graph
///
////////////////////////////////////////////////////////////////////////
Graph* Graph::dijkstra ( const string& source, const string& target ) {

	vector<int> distance ( getNumberOfVertices(), INT_MAX ); 
	vector<int> previous ( getNumberOfVertices(), -1 );	// Previous node in optimal path from source
	vector<string> vertex;	// to hold all the vertices from the graph
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair <int, int> > > priorities;

	priorities.push ( { 0, getVertexIndex ( source ) } );
	distance[ getVertexIndex ( source ) ] = 0;
	
	while ( !priorities.empty () ) {

		int u = priorities.top ().second;
		
		// test permettant d'extraire le graphe resultant aussitot
		// quon arrive a la destination
		if ( u == getVertexIndex ( target ) ) {
		
			Graph* newGraph = extractGraph ( previous, source, target );
			newGraph->setMinimalDistanceLength ( distance[ u ] );

			return newGraph;
		}
		
		priorities.pop (); 

		// Parcourir le graphe
		for ( auto& graph : graph_ ) {
			
			// geting all adjacent vertices of the current node
			vertex = graph.second->getVertex ();
			bool found = false;
			
			// If the current vertex in the graph
			// is our current 'u' node
			if ( graph.first == getVertexName(u) ) {
					
				found = true;
				// looping and working with all adjacent vertices of 'u'
				for ( auto& neighbors : vertex ) {

					int v = getVertexIndex ( neighbors );	// get vertex index(label) of current adjacent of u
					int weight = 0;

					auto& it = graph_.find ( getVertexName ( u ) );
					if ( it != graph_.end () )
						weight = it->second->getEdgeWeight ( neighbors );	// get vertex weight of current incident edge of u


					// if there is a shortest path from u to v
					if ( distance[ v ] > distance[ u ] + weight ) {

						// distance of v gets updated
						distance[ v ] = distance[ u ] + weight;
						previous[ v ] = u;	// by setting previous[v] we will remember what is the previous node on path from  the source
						priorities.push ( { distance[ v ], v } );
					}
				}
			}

			// if our current node already found in the graph 
			// then there's no need to check the other vertices
			if ( found )
				break;
		
		}// end outter for loop
	
	} // end while

	return nullptr;
}


//////////////////////////////////////////////////////////////////////////
///
/// @fn Graph* Graph::extractGraph ( vector<int> path, const string& source, const string& target )
///
/// Methode interne appele par l'algorithme de dijstra pour extraire le
/// le plus cour chemin. Elle procede par une iteration inverse
///
/// @return Graph
///
////////////////////////////////////////////////////////////////////////
Graph* Graph::extractGraph ( vector<int> path, const string& source, const string& target ) {

	/*Reading the shortest path from source to target by reverse iteration*/

	vector<int> tmpPath;
	int v = getVertexIndex ( target );	// v take the index of the target position

	while ( v != getVertexIndex (source) ) {	
		tmpPath.push_back ( v );
		v = path[ v ];
	}

	tmpPath.push_back ( getVertexIndex ( source ) );
	reverse ( tmpPath.begin (), tmpPath.end () );

	

	Graph* newGraph { new Graph () };

	/// inserter les sommet a partir des index du vecteur chemin
	for ( size_t i = 0; i < tmpPath.size (); ++i ) {

		newGraph->insertVertex ( getVertexName ( tmpPath[ i ] ), graph_.find ( getVertexName ( tmpPath[ i ] ) )->second->getType () );
	}

	/// inserer les arcs 
	vector<string> vertex;
	for ( size_t i = 0; i < tmpPath.size (); ++i ) {

		for ( auto& graph : graph_ ) {

			vertex = graph.second->getVertex ();
			bool found = false;

			if ( graph.first == getVertexName ( tmpPath[ i ] ) ) {

				found = true; 
				for ( size_t j = 0; j < vertex.size () && j < tmpPath.size (); ++j ) {

					// Find the current vertex in the old graph
					auto& it = graph_.find ( getVertexName ( tmpPath[ i ] ) );
					int weight;
					
					if ( it != graph_.end () ) { // found

						size_t k = j;
						if ( ++k < tmpPath.size () ) {

							auto& locate = find ( vertex.begin (), vertex.end (), getVertexName ( tmpPath[k] ) ); // locating vertex in the path in the
							if ( locate != vertex.end () ) { // found

								weight = it->second->getEdgeWeight ( *locate );	// find the distance between the current vertex and its adjacent vertex
								
								newGraph->insertEdge ( getVertexName ( tmpPath[ j ] ), *locate, weight );
							}
							
						}
						
					}
					
				} // end inner for loop
			}

			if ( found )
				break;
		} // end outter for loop
	}

	return newGraph;
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn void Graph::printGraph () const
///
/// imprime le graph
///
/// @return Graph
///
////////////////////////////////////////////////////////////////////////
void Graph::printGraph () const {

	vector<string> vertex;
	int i = 0;
	for ( auto& vertices : graph_ ) {

		vertex = vertices.second->getVertex ();

		cout << "( " << vertices.first + ", " << vertices.second->getType () + ", (";
		for ( auto& neighbors : vertex ) {

			++i;
			if ( i > 1 )
				cout << "; ";

			cout << neighbors;
			auto it = graph_.find ( neighbors );
			if ( it != graph_.end () )
				cout << ", " + it->second->getType ();

		}

		cout << "))" << endl;
		i = 0;
	}
}


/////////////////////////////////////////////////////////////////////////
///
/// @fn void Graph::printShortestPath () const
///
/// utilise un algorithme different pour imprimer le chemin le plus court
///
/// @return Graph
///
////////////////////////////////////////////////////////////////////////
void Graph::printShortestPath () const {

	vector<string> vertex;
	vector<string> tmp;

	for ( auto& graph : graph_ ) {

		vertex = graph.second->getVertex ();
		

		if ( vertex.size () > 0 ) {
			
			auto it = find ( tmp.begin (), tmp.end (), graph.first );
			
			if ( it == tmp.end () ) {
				cout << graph.first;
				
			}	
		}

		for ( auto& neighbor : vertex ) {
			
			cout << "-->" << neighbor;
			tmp.push_back ( neighbor );
		}
	}
}