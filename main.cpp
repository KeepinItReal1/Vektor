//#include "ManoFunkcijos.h"
#include "vektor.h"
#include <iostream>



int main(){
	std::cout<<"Hello world!"<<std::endl;
	vektor<int> v;
	v.push_back(1);
	v.push_back(2);
	std::cout<<"begin "<<v.begin()<<std::endl;
	std::cout<<"end "<<v.end()<<std::endl;
	std::cout<<"v.back "<<v.back()<<std::endl;
	v.pop_back();
	std::cout<<"begin "<<v.begin()<<std::endl;
	std::cout<<"end "<<v.end()<<std::endl;
	return 0;
}


