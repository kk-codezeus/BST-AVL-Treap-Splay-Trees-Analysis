#include<bits/stdc++.h>
using namespace std;

int main()
{
    ofstream out("sequential_keys.txt");
    for(int i = 0;i < 10000;i++)
    {
        out<<i + 1<<endl;
    }
}
