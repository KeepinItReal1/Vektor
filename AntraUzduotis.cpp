#include <iostream>
#include <string>
#include <stack>
#include <sstream>

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


cout<<"Veskite gautus pazymius,neteisingi simboliai nebus imami. Noredami baigti spauskite '/' ."<<endl;
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

}
}

cout<<"Jusu ivesti pazymiai:";
//spausdinimas

stack<int> tmpStack = sortStack(vedimas);

 while (!tmpStack.empty())
    {
        cout << tmpStack.top()<< " ";
        tmpStack.pop();
         skait=skait+1;
    }


Vid=VidSum/skait;

float galBalas=0.4*Vid+0.6*egzas;
cout.precision(3);
cout<<"\nGalBalas="<<galBalas;


while (!vedimas.empty())
  {
     cout << ' ' << vedimas.top();
     vedimas.pop();
  }
return 0;
}
