#ifndef VEKTOR_H
#define VEKTOR_H

#include <windows.h>


template <typename T>
class vektor{

    public:
    	void push_back(T elem);
    	// void begin();
    	// void end();
    	unsigned int size();
    	unsigned int capacity();
    	unsigned int max_size();
    private:
    	T createNewArray(T *A,unsigned int skc, unsigned int added=10);
    	unsigned int total_size=0;//esamas dydis
    	unsigned int total_capacity=0;//max dydis dabar
    	T *A=new T[total_size]; 





};

template <typename T>
unsigned int vektor<T>::size(){
	return total_size;
}

template <typename T>
unsigned int vektor<T>::capacity(){
	return total_capacity;
}

template <typename T>
unsigned int vektor<T>::max_size(){

}

template <typename T>//sudaro nauja array kurio max size padidina per added
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



#endif // VEKTOR_H