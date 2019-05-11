#include<bits/stdc++.h>
using namespace std;

int main()
{
    ofstream out("random_keys.txt");
    srand(time(0));
    for(int i = 0;i < 10000;i++)
    {
        out<<rand()%10000<<endl;
    }
}
