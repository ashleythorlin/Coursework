#include <iostream>
#include <vector>

using namespace std;
int main ()
{
  vector<int> myvector;
  vector<int>::iterator it;

  cout << "Vector gets the elements 1, 5, 10" << endl;
  myvector.push_back(1);
  myvector.push_back(5);
  myvector.push_back(10);

  it = myvector.begin();
  myvector.insert(it+1, 85);
  
  cout << "myvector contains:";
  for (size_t i=0; i<myvector.size(); i++)
     cout << ' ' << myvector.at(i);
  
  return 0;
}