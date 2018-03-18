#include "ManoFunkcijos.h"

using std::cout;


int main(){
clock_t pradzia;pradzia=clock();

SafeToFile();//kursiokai.txt , 10
clock_t start;start=clock();

SafeToFile("kursiokai1.txt",100);
clock_t start1;start1=clock();

SafeToFile("kursiokai2.txt",1000);
clock_t start2;start2=clock();

SafeToFile("kursiokai3.txt",10000);
clock_t start3;start3=clock();

SafeToFile("kursiokai4.txt",100000);
clock_t start4;start4=clock();



cout<<diffclock(start,pradzia)<<"ms\tkursiokai.txt"<<endl;
cout<<diffclock(start1,start)<<"ms\tkursiokai1.txt"<<endl;
cout<<diffclock(start2,start1)<<"ms\tkursiokai2.txt"<<endl;
cout<<diffclock(start3,start2)<<"ms\tkursiokai3.txt"<<endl;
cout<<diffclock(start4,start3)<<"ms\tkursiokai4.txt"<<endl;
cout<<diffclock(start4,pradzia)<<"ms\tvisa programa."<<endl;
return 0;
}

