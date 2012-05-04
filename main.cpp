// main.cpp: Oleksiy Ivanenko
// Description: Entry point of Boolean Functions lab, that analyses 2 bool functions

#include "field.h"
#include "function.h"

int main(){
	int N = (1<<10)+(1<<7)-1;
	int M = (1<<7)+(1<<3)-1;
	cout<<"\n*** Function N = "<<N<<" ***\n";
    Function MyFuncOne(N);
    MyFuncOne.analyze();
    cout<<"\n*** Function M = "<<M<<" ***\n";
    Function MyFuncTwo(M);
    MyFuncTwo.analyze();
    cout<<"\nThat's all Folks!\n";
    return 0;
}