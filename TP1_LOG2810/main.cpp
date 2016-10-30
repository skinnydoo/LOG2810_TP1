#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Graph.h"
#include "Car.h"
using namespace std;

int enterChoice ();	// Prototype
Graph* createGraph ( const string& );
void readGraph ( Graph* );
void shortestPath (Graph*, Car*, const string&, const string& );

enum Choices {CAR_SPECS = 1, READMAP, SHORTESTPATH, EXIT} Choix;


int main () {

	Graph* graph = nullptr;
	Car* myCar = nullptr;
	bool optionA = false;
	
	int choice;	// store the user's choice
	while ( ( choice = enterChoice () ) != EXIT ) {

		switch ( choice ) {

			case CAR_SPECS: {

					string carType;
					int maxAutonomy, currentAutonomy;
					bool ChoiceOk = false;

					/**
					* CAR TYPE
					*/
					do {

						cout << "\nInserer le type du vehicule.\nLes options sont : " << endl
							<< "\t - essence" << endl
							<< "\t - hybrid" << endl
							<< "\t - electrique" << endl;

						cout << "? : ";
						cin >> carType;
						cin.ignore ();

						if ( ( carType == "essence" ) || ( carType == "hybrid" ) || ( carType == "electrique" ) ) {
							cout << "Votre choix : " << carType << endl;
							ChoiceOk = true;
						} else
							cout << "Votre choix '" << carType << "' est invalide. Assurez vous de bien ecrire votre choix." << endl;


					} while (!ChoiceOk );


					/**
					* MAX AUTONOMY
					*/
					do {

						cout << "\nInserer un chiffre indiquant l'autonomie maximale du vehicule." << endl;
						cout << "? : ";
						cin >> maxAutonomy;

						if ( cin.fail () ) {

							cout << "Error. Not an integer" << endl;
							cin.clear ();
						} else
							cout << "Autonomie maximale insere : " << maxAutonomy << endl;

				
					} while ( cin.fail () );


					/**
					* CURRENT AUTONOMY
					*/
					do {

						cout << "\nInserer un chiffre indiquant l'autonomie courrante du vehicule." << endl;
						cout << "? : ";
						cin >> currentAutonomy;

						if ( cin.fail () ) {

							cout << "Error. Not an integer" << endl;
							cin.clear ();
						} else
							cout << "Autonomie courrante insere : " << currentAutonomy << endl;


					} while ( cin.fail () );

					/// Creation of the car
					myCar = new Car ( carType, maxAutonomy, currentAutonomy );
					optionA = true;

					break;
				}
			
			
			case READMAP: {

					string fileName;
					cout << "\nEntrez le nom du ficher(sans extension) : ";
					cin >> fileName;
					cin.ignore ();

					graph = createGraph ( fileName );
					readGraph ( graph );
					
					break;
				}

			
			case SHORTESTPATH: {

					if ( optionA ) {

						cout << "\nPoint de depart (un seul caractere en MAJ): ";
						string source;

						while ( !( cin >> source ) ) {

							cin.clear ();
							cin.ignore ( 256, '\n' );
							cout << "\n\nERROR! Expecting a character" << endl
								<< "Insert your starting point again : ";
						}


						cout << "\nDestination (un seul caractere en MAJ): ";
						string target;

						while ( !( cin >> target ) ) {

							cin.clear ();
							cin.ignore ( 256, '\n' );
							cerr << "\n\nERROR! Expecting a character" << endl
								<< "Insert your destination again : ";
						}

						/// check if graph exist
						if ( graph == nullptr ) {

							cerr << "\n\nErreur! Aucune carte predefinie" << endl;
							break;
						}

						// Find the shortest path
						shortestPath ( graph, myCar, source, target);

					} else

						cout << "\n\nERROR! L'option 1 'Caracteristiques du vehicule' est necessaire a la recherche d'un itineraire" << endl;
					
					
					break;
				}

			default: cerr << "invalid choice" << endl;
				break;

		} // end switch
	} // end outer while

	cout << "Program terminated!" << endl;
}// end main



// enable menu choice
int enterChoice () {

	// Display available options
	cout << "\nChoose one of the following options" << endl
		<< "(1) - Caracteristiques du vehicule" << endl
		<< "(2) - Lire la carte" << endl
		<< "(3) - Obtenir le plus court chemin" << endl
		<< "(4) - Quitter" << endl;

	cout << "\nEnter your choice : ";
	
	int choice;
	while ( !( cin >> choice ) ) {
		
		cin.clear ();
		cin.ignore ( 256, '\n' );
		cout << "\nERROR! Expecting an integer!" << endl
			<< "Enter your choice again : ";
	}
	
	return choice;
}


/// enable Graph creation
Graph* createGraph ( const string& fileName ) {

	ifstream inMapFile ( fileName + ".txt" );
	Graph* graph { new Graph () };

	// exit program if ifstream can't open the file
	if ( !inMapFile ) {

		cerr << "\nERROR! The map file could not be opened!" << endl;
		exit ( EXIT_FAILURE );
	}

	string verticesLine;
	getline ( inMapFile, verticesLine );

	istringstream inputVertexString ( verticesLine );
	string identifier;
	string type;

	cout << endl;
	int i = 0;
	while ( !inputVertexString.eof () ) {

		++i;
		getline ( inputVertexString, identifier, ',' );
		getline ( inputVertexString, type, ';' );

		if ( identifier == "" )
			break;

		//cout << "Vertex " << i << " identifier : " << identifier << ", type : " << type << endl;
		graph->insertVertex ( identifier, type );
			
	}


	string edgesLine;
	getline ( inMapFile, edgesLine );
	istringstream inputEdgesString ( edgesLine );
	string sourceVertex, targetVertex;
	string weight;

	cout << endl << endl;
	while ( !inputEdgesString.eof () ) {

		getline ( inputEdgesString, sourceVertex, ',' );
		getline ( inputEdgesString, targetVertex, ',' );
		getline ( inputEdgesString, weight, ';' );

		if ( sourceVertex == "" )
			break;

		//cout << "Vertex " << sourceVertex << " --> " << targetVertex << ", distance : " << weight << endl;
		graph->insertEdge ( sourceVertex, targetVertex, stoi(weight) );
	}

	cout << "\nGraph Created!" << endl;
	return graph;
}


// enable graph reading
void readGraph ( Graph* graph ) {

	cout << "\nReading Graph..." << endl;
	graph->printGraph ();
}


// enable finding shortest path 
void shortestPath ( Graph* graph, Car* myCar, const string& source, const string& target ) {

 Graph* newGraph = graph->dijkstra ( source, target );

 if ( newGraph != nullptr ) {
	
	 //if ( newGraph->getVertexType ( newGraph->getNumberOfVertices () - 1 ) == myCar->getFuelType () ) {

		 if ( myCar->getCurrentAutonomy () >= newGraph->getMinimalDistanceLength () ) {

			 cout << "\nTotal distance length : " << newGraph->getMinimalDistanceLength () << endl
				 << "Current autonomy of your vehicule : " << myCar->getCurrentAutonomy () << endl;

			 // Printing the shortest path
			 newGraph->printShortestPath ();

			 int newCurrAutonomy = myCar->getCurrentAutonomy () - newGraph->getMinimalDistanceLength ();
			 myCar->setCurrentAutonomy ( newCurrAutonomy );
			 cout << "\nYour current autonomy is now : " << myCar->getCurrentAutonomy () << endl;
		 } else {

			 cout << "\nYou won't be able to get to that station" << endl
				 << "Total distance length : " << newGraph->getMinimalDistanceLength () << endl
				 << "Your current autonomy is : " << myCar->getCurrentAutonomy () << endl
				 << "Your max autonomy is : " << myCar->getMaxAutonomy () << endl;
		 }
	 /*} else {

		 cout << "This station has no fuel type compatible with your vehicule." << endl
			 << "Station fuel type : " << newGraph->getVertexType ( newGraph->getNumberOfVertices () - 1 ) << endl
			 << "Your vehicule fuel type : " << myCar->getFuelType () << endl;
	 }*/

		 return;
 }

 cout << "\n\nERROR! No path exist from " << source << " to " << target << endl;
 

}
