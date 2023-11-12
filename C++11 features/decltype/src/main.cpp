#include <iostream>
#include <type_traits>

using namespace std;
int main(int argc, const char** argv) {

    const int i = 0;
    cout << decltype(i) << endl;
    return 0;
}   