#include "ManoFunkcijos.h"



int main(){

std::vector<node>pagr;

std::vector<node> vargsiukai;//balas maziau uz 50 % FeelsBadMan
std::vector<node> kietakai;//balas >=50 %


clock_t pradzia;pradzia=clock();

saveToFile(pagr,vargsiukai,kietakai,"kursiokai.txt",10);//kursiokai.txt , 10
clock_t start;start=clock();

saveToFile(pagr,vargsiukai,kietakai,"kursiokai1.txt",100);
clock_t start1;start1=clock();

saveToFile(pagr,vargsiukai,kietakai,"kursiokai2.txt",1000);
clock_t start2;start2=clock();

saveToFile(pagr,vargsiukai,kietakai,"kursiokai3.txt",10000);
clock_t start3;start3=clock();

saveToFile(pagr,vargsiukai,kietakai,"kursiokai4.txt",100000);
clock_t start4;start4=clock();



std::cout<<diffclock(start,pradzia)<<"ms\tkursiokai.txt"<<std::endl;
std::cout<<diffclock(start1,start)<<"ms\tkursiokai1.txt"<<std::endl;
std::cout<<diffclock(start2,start1)<<"ms\tkursiokai2.txt"<<std::endl;
std::cout<<diffclock(start3,start2)<<"ms\tkursiokai3.txt"<<std::endl;
std::cout<<diffclock(start4,start3)<<"ms\tkursiokai4.txt"<<std::endl;
std::cout<<diffclock(start4,pradzia)<<"ms\tvisa programa."<<std::endl;
return 0;
}
//reikia skaitymo ir rusiavimo funkciju su list ir deque
