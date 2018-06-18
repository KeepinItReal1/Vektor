#ifndef SINGLE_H
#define SINGLE_H

#include "math.h"
#include "vektor.h"



class Single{

	public:
		std::string pavarde;
		std::string vardas;
        virtual inline std::string getLastName() const=0;
        virtual inline std::string getName() const=0;
};

#endif //SINGLE_H
