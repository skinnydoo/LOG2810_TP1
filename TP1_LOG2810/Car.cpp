///////////////////////////////////////////////////////////////////////////////
/// @file Car.cpp
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "Car.h"
using namespace std;



////////////////////////////////////////////////////////////////////////
///
/// @fn Car::Car (const string& fuelType, int maxAutonomy, int currentAutonomy)
///
/// Ne fait qu'initialiser les membres
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Car::Car (const string& fuelType, int maxAutonomy, int currentAutonomy)
	: fuelType_ (fuelType), maxAutonomy_ (maxAutonomy), currentAutonomy_ (currentAutonomy)
{}



////////////////////////////////////////////////////////////////////////
///
/// @fn 
///
/// Destructeur
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
Car::~Car () {}



////////////////////////////////////////////////////////////////////////
///
/// @fn void Car::setFuelType ( const std::string& fuelType )
///
/// assigne le type du carburant
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void Car::setFuelType ( const std::string& fuelType ) {

	fuelType_ = fuelType;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn tring Car::getFuelType () 
///
/// retourne le type du carburant
///
/// @return (string) 
///
////////////////////////////////////////////////////////////////////////
string Car::getFuelType () {

	return fuelType_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void Car::setMaxAutonomy ( int max )
///
/// assigne le l'autonomie maximale
///
/// @return aucune
///
////////////////////////////////////////////////////////////////////////
void Car::setMaxAutonomy ( int max ) {

	maxAutonomy_ = max;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn int Car::getMaxAutonomy ()
///
/// retourne l'autonomie maximale
///
/// @return (int) 
///
////////////////////////////////////////////////////////////////////////
int Car::getMaxAutonomy () {

	return maxAutonomy_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Car::setCurrentAutonomy ( int current )
///
/// assigne l'autonomie courrante
///
/// @return (aucune) 
///
////////////////////////////////////////////////////////////////////////
void Car::setCurrentAutonomy ( int current ) {

	currentAutonomy_ = current;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn int Car::getCurrentAutonomy () 
///
/// retoune l'autonomie courrante
///
/// @return (int) 
///
////////////////////////////////////////////////////////////////////////
int Car::getCurrentAutonomy () {

	return currentAutonomy_;
}