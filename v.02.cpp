#include "Mano.h"

using namespace std;


int main(){
clock_t pradzia;pradzia=clock();
//kursiokai.txt
//ivesti();
//issaugoti();
skaityti();//i ekrana isveda ir isrusiuoja
spausdinti();
clock_t start;start=clock();

failas="kursiokai1.txt";ivedimas=100;
ivesti();
issaugoti();
clock_t start1;start1=clock();

failas="kursiokai2.txt";ivedimas=1000;
ivesti();
issaugoti();
clock_t start2;start2=clock();

failas="kursiokai3.txt";ivedimas=10000;
ivesti();
issaugoti();
clock_t start3;start3=clock();

failas="kursiokai4.txt";ivedimas=100000;
ivesti();
issaugoti();
clock_t start4;start4=clock();



cout<<diffclock(start,pradzia)<<"ms\tkursiokai.txt"<<endl;
cout<<diffclock(start1,start)<<"ms\tkursiokai1.txt"<<endl;
cout<<diffclock(start2,start1)<<"ms\tkursiokai2.txt"<<endl;
cout<<diffclock(start3,start2)<<"ms\tkursiokai3.txt"<<endl;
cout<<diffclock(start4,start3)<<"ms\tkursiokai4.txt"<<endl;
cout<<diffclock(start4,pradzia)<<"ms\tvisa programa."<<endl;
return 0;
}

