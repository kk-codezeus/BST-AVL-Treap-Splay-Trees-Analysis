#include<bits/stdc++.h>
using namespace std;

int main()
{
    ofstream out("recentAccess_keys.txt");
    vector<int> _100randomKeys;
    for(int i = 0;i < 100;i++)
    {
        int temp = rand()%10000;
        _100randomKeys.push_back(temp);
    }
    for(int i = 0;i < 10000;i++)
    {
        int index = rand()%100;
        out<<_100randomKeys[index]<<endl;
    }
    return 0;
}
