#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <chrono>
#include <functional>

using namespace std;

stack<int> sortStack(stack<int> &input)
{
    stack<int> tmpStack;

    while (!input.empty())
    {
        // pop out the first element
        int tmp = input.top();
        input.pop();

        // while temporary stack is not empty and top
        // of stack is greater than temp
        while (!tmpStack.empty() && tmpStack.top() > tmp)
        {
            // pop from temporary stack and push
            // it to the input stack
            input.push(tmpStack.top());
            tmpStack.pop();
        }

        // push temp in tempory of stack
        tmpStack.push(tmp);
    }

    return tmpStack;
}

int main(){


string vardas="";
string pavarde="";
cout<<"Iveskite savo varda:";
cin>>vardas;
cout<<"Iveskite savo pavarde:";
cin>>pavarde;
cout<<"Jus esate:"<<vardas<<" "<<pavarde<<endl;
cout<<"Iveskite egzamino pazymi:"<<endl;
int egzas=0;cin>>egzas;cout<<"Jusu ivestas egzamino ivertinimas:"<<egzas<<endl;


cout<<"Veskite gautus pazymius,neteisingi simboliai nebus imami.Veliau bus sugeneruota tiek pat random skaiciu kiek ivedete. Noredami baigti spauskite '/' ."<<endl;
string symbo="/";//baigimo simbolis
stack<int>vedimas;
string stringas="";
float Vid=0;float VidSum=0;int skait=0;

while (stringas.compare(symbo) !=0){
cin>>stringas;
int result=0;
int result1=0;

stringstream(stringas)>>result;

//error testins
if((result>0)&&(result<=10)){
        result1=result;
 vedimas.push(result1);
 VidSum=VidSum+result1;
skait=skait+1;
}
}

if(skait%2==1)
{
int mediana=0;
div_t divresult;
divresult = div (skait,2);
cout<<"Jusu ivesti pazymiai:";

stack<int> tmpStack = sortStack(vedimas);


for(int i=0;i<divresult.quot;i++){
    cout << tmpStack.top()<< " ";
        tmpStack.pop();
}
mediana=tmpStack.top();

 while (!tmpStack.empty()){
        cout << tmpStack.top()<< " ";
        tmpStack.pop();
    }
cout<<"\nMediana:"<<mediana;
}

if(skait%2==0)
{
float mediana=0;float mediana1=0;
div_t divresult;
divresult = div(skait,2);
cout<<"Jusu ivesti pazymiai:";

stack<int> tmpStack = sortStack(vedimas);


for(int i=0;i<(divresult.quot)-1;i++){
    cout << tmpStack.top()<< " ";
        tmpStack.pop();
}
mediana1=tmpStack.top();
cout << tmpStack.top()<< " ";
        tmpStack.pop();
mediana=tmpStack.top();
mediana=(mediana+mediana1)/2;

 while (!tmpStack.empty()){
        cout << tmpStack.top()<< " ";
        tmpStack.pop();
    }
cout<<"\nMediana:"<<mediana;
}



Vid=VidSum/skait;
float galBalas=0.4*Vid+0.6*egzas;
cout.precision(3);
cout<<"\nGalBalas="<<galBalas<<endl;


while (!vedimas.empty())
  {
    vedimas.top();
     vedimas.pop();
  }


  for(int i=0;i<skait;i++)
  {
mt19937 mt(time(NULL));
uniform_int_distribution<int> skaicius(1,10);
vedimas.push(skaicius(mt));
  }

  while (!vedimas.empty())
  {
  cout<<vedimas.top()<<" ";
     vedimas.pop();
  }

return 0;
}
