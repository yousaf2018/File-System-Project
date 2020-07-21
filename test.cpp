#include <iostream>
#include "fstream"
#include <string>
using namespace std;
int main()
{
    ifstream read;
    char a;
    string b;
    read.open("test.txt");
    read >> a;
    cout << a;
    while(!read.eof()){
        read >> a;
        if(a=='*'){
            cout << " ";
            continue;
        }
        else{
        cout << a;

        }
    }
    read.close();
}