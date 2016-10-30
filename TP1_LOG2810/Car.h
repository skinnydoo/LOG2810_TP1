///////////////////////////////////////////////////////////////////////////////
/// @file Car.h
/// @author Ralph Simelus
/// @date 2016-10-24
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>


class Car {
public:
	Car (const std::string&, int, int);
	~Car ();

	void setFuelType ( const std::string& );
	void setMaxAutonomy ( int );
	void setCurrentAutonomy ( int );

	std::string getFuelType ();
	int getMaxAutonomy ();
	int getCurrentAutonomy ();

private :
	std::string fuelType_;
	int maxAutonomy_;
	int currentAutonomy_;
};

