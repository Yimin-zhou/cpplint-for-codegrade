#include <iostream>

using namespace std;

class xcasd{}

void two(xcasd x)
{
    int myNum = 2;
    const int mYCONST = 3;
    bool myBool;

    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
    std::cout << mYCONST << std::myNum << endl;
}

int main()
{
    two();
    return 1;
}
