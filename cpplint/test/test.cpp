#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;

  cout << "Enter an integer: ";cin >> n;

  const int xzxc = 1;
  cout << xzxc;

  if (n % 2 == 0) {
    cout << n << " is even.";
    if (n % 2 == 0) {
      cout << n << " is even.";
    } else {
      cout << n << " is odd.";
    }
  } else {
    cout << n << " is odd.";
  }

  return 0;
}
