#include <iostream>
#include <vector>
using namespace std;

int main() {
  int goodName;
  wchar_t name;

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
