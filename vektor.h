#ifndef VEKTOR_H
#define VEKTOR_H

#include <windows.h>
#include <iostream>


template <typename T>
class vektor{

    public:
    	// vektor(){total_size=0;total_capacity=0;};
    	void push_back(T );//+
    	void pop_back();
    	// int* begin(){if(total_size!=0)return &A[0];else std::cerr<<"Empty vektor!"<<std::endl;};//+
    	// int* end(){if(total_size!=0)return &A[total_size-1]; else std::cerr<<"Empty vektor!"<<std::endl;};//+
    	T back();
    	//gett'ers
    	unsigned int size() const{return total_size;};//+
    	unsigned int capacity() const{return total_capacity;};//+
    	unsigned int max_size();//+
    	//class iterator
    	//class reverse_iterator
    private:
    	T createNewArray(T *A,unsigned int skc, unsigned int added=10);
    	unsigned int total_size=0;//esamas dydis
    	unsigned int total_capacity=0;//max galimas dydis dabar
    	T *A=new T[total_size]; 
};

template <typename T>
unsigned int vektor<T>::max_size() {
	const  unsigned int dydis= sizeof(T);

	MEMORYSTATUSEX statex;

	GlobalMemoryStatusEx (&statex);
	return (statex.ullAvailPhys/dydis);

}

//sudaro nauja array kurio max size padidina per added
template <typename T>
T vektor<T>::createNewArray(T *A,unsigned int skc,unsigned int added ){//commitas c3ef694  on Feb 21
	T *B=new T[skc+added];
	for(unsigned int i=0;i<skc;i++){//skc==total_size
		B[i]=A[i];
	}
	delete[] A;
	return *B;
}


template <typename T>
void vektor<T>::push_back(T elem){//exception del pasiekto max_size
	if(total_size==total_capacity){
		if(total_capacity!=0){
			createNewArray(A,total_size,total_capacity*2);
			total_capacity*=2;
			A[total_size]=elem;
			total_size+=1;
		}else{
			total_capacity=1;
			createNewArray(A,total_size,total_capacity+1);//
			A[total_size]=elem;
			total_capacity+=1;
			total_size+=1;
		}
	}
	else{
		A[total_size]=elem;
	}
}


template <typename T>
void vektor<T>::pop_back(){
	if(total_size!=0){
		total_size--;//delete butu visam vektoriui
	}
	else {delete[] A;
	std::cerr<<"Empty vektor!"<<std::endl;
	}
}

template <typename T>
T vektor<T>::back(){
	if(total_size!=0){
		return A[total_size-1];
	}
	else std::cerr<<"Empty vektor!"<<std::endl;
}



#endif // VEKTOR_H