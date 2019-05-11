#include "AVL.cpp"
using namespace chrono;

vector<int> randomKeys;
vector<int> sequentialKeys;
vector<int> recentAccessedKeys;

void loadThreeVectors()
{
    ifstream random("../random_keys.txt",ifstream::in);
    ifstream sequential("../sequential_keys.txt",ifstream::in);
    ifstream recent("../recentAccess_keys.txt",ifstream::in);
    int temp;
    for(int i = 0;i < 10000;i++)
    {
        random>>temp;
        randomKeys.push_back(temp);
    }
    for(int i = 0;i < 10000;i++)
    {
        sequential>>temp;
        sequentialKeys.push_back(temp);
    }
    for(int i = 0;i < 10000;i++)
    {
        recent>>temp;
        recentAccessedKeys.push_back(temp);
    }
}

void printThreeVectors()
{
    for(int i = 0;i < 10000;i++)
        cout<<randomKeys[i]<<" ";
    cout<<endl<<endl<<endl;
    for(int i = 0;i < 10000;i++)
        cout<<sequentialKeys[i]<<" ";
    cout<<endl<<endl<<endl;
    for(int i = 0;i < 10000;i++)
        cout<<recentAccessedKeys[i]<<" ";
    cout<<endl<<endl<<endl;
}

void test_randomKeys()
{
    AVL tree;
    tree.create();
    steady_clock::time_point t1,t2;

    t1 = steady_clock::now();
    for(int i = 0;i < randomKeys.size();i++)                //random keys insert time
        tree.insertKey(randomKeys[i]);

    t2 = steady_clock::now();
    auto duration = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < randomKeys.size();i++)                //random keys search time
        tree.searchKey(randomKeys[i]);

    t2 = steady_clock::now();
    auto duration2 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration2.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < randomKeys.size();i++)                //random keys delete time
        tree.deleteKey(randomKeys[i]);

    t2 = steady_clock::now();
    auto duration3 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration3.count()<<"\n";
}

void test_sequentialKeys()
{
    AVL tree;
    tree.create();
    steady_clock::time_point t1,t2;

    t1 = steady_clock::now();
    for(int i = 0;i < sequentialKeys.size();i++)                //sequential keys insert time
        tree.insertKey(sequentialKeys[i]);

    t2 = steady_clock::now();
    auto duration = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < sequentialKeys.size();i++)                //sequential keys search time
        tree.searchKey(sequentialKeys[i]);

    t2 = steady_clock::now();
    auto duration2 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration2.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < sequentialKeys.size();i++)                //sequential keys delete time
        tree.deleteKey(sequentialKeys[i]);

    t2 = steady_clock::now();
    auto duration3 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration3.count()<<"\n";
}

void test_recentAccessedKeys()
{
    AVL tree;
    tree.create();
    steady_clock::time_point t1,t2;

    t1 = steady_clock::now();
    for(int i = 0;i < recentAccessedKeys.size();i++)                //recentAccess keys insert time
        tree.insertKey(recentAccessedKeys[i]);

    t2 = steady_clock::now();
    auto duration = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < recentAccessedKeys.size();i++)                //recentAccess keys search time
        tree.searchKey(recentAccessedKeys[i]);

    t2 = steady_clock::now();
    auto duration2 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration2.count()<<"\n";

    t1 = steady_clock::now();
    for(int i = 0;i < recentAccessedKeys.size();i++)                //recentAccess keys delete time
        tree.deleteKey(recentAccessedKeys[i]);

    t2 = steady_clock::now();
    auto duration3 = duration_cast<nanoseconds>((t2 - t1));
    cout<<duration3.count()<<"\n";
}

int main()
{
    loadThreeVectors();
    //test_randomKeys();
    //test_sequentialKeys();
    test_recentAccessedKeys();
    return 0;
}

