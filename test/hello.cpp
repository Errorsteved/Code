#include <iostream>
using namespace std;
int main(){
    double temp;
    double ar[8];
    int i;
    for(i=0;i<5;i++){
        cout<<"enter number: ";
        cin>>temp;
        if(!cin){
            cin.clear();
            while(cin.get()!='\n');
                //continue;
            cout<<"bad";
            break;
        }
        else if(temp<0) break;
        cout<<"you put in: "<<temp<<endl;
    }
}