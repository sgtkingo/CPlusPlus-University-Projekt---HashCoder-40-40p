#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int main()
{
    vector <vector<int> > test(6);

    test[5].push_back(5);

    cout <<test[5][1]<< endl;

    int N=0;
    cout<<"N: ";
    cin>>N;
    while(cin.fail())
    {
        //getchar();
        cin.clear();
        cin.ignore(20,'\n');
        cout<<"Again: ";
        cin>>N;
    }
    return 0;
}
