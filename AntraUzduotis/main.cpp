#include "ManoFunkcijos.hpp"



int main(){/*
saveToFile();
saveToFile("kursiokai1.txt",100);//sugeneruoja visus failus
saveToFile("kursiokai2.txt",1000);
saveToFile("kursiokai3.txt",10000);
saveToFile("kursiokai4.txt",100000);*/

clock_t pradzia;pradzia=clock();
readFromFileDeque();
readFromFileDeque("kursiokai1.txt");
readFromFileDeque("kursiokai2.txt");
readFromFileDeque("kursiokai3.txt");
readFromFileDeque("kursiokai4.txt");//crashina nezinia kodel
clock_t start;start=clock();

std::cout<<diffclock(start,pradzia)<<"ms\tDeque."<<std::endl;

clock_t start1;start1=clock();
readFromFileList();
readFromFileList("kursiokai1.txt");
readFromFileList("kursiokai2.txt");
readFromFileList("kursiokai3.txt");
readFromFileList("kursiokai4.txt");
clock_t start2;start2=clock();

std::cout<<diffclock(start2,start1)<<"ms\tList."<<std::endl;


clock_t start3;start3=clock();
readFromFile();
readFromFile("kursiokai1.txt");
readFromFile("kursiokai2.txt");
readFromFile("kursiokai3.txt");
readFromFile("kursiokai4.txt");
clock_t start4;start4=clock();
std::cout<<diffclock(start4,start3)<<"ms\tVector."<<std::endl;

std::cout<<diffclock(start4,pradzia)<<"ms\tvisa programa."<<std::endl;
return 0;
}

