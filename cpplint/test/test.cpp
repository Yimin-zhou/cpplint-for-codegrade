#include <iostream>
#include <vector>
using namespace std;

class myClass {     
  public:           
    int myNum;      
    string myString;
};

int Main() {
  int goodName;
  wchar_t Name;

  cout << "Enter an integer: ";
  cin >> goodName;

  const int xzxc = 1;
  cout << xzxc;

  if (goodName % 2 == 0) {
    cout << goodName << " is even.";
    if (goodName % 2 == 0) {
      cout << goodName << " is even.";
    } else {
      cout << goodName << " is odd.";
    }
  } else {
    cout << goodName << " is odd.";
  }

  return 0;
}
