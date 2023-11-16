#include "Date.h"

using namespace std;

int main()
{
    Date d(2004, 5, 5, 13, 30, 0, true);
    Date d1(2004, 3, 2, 10, 0, 0, true);
    Date d2(2004, 5, 5, 13, 30, 0, true);
    // d -= d1;
    cout << "Hello world\n";
    cout << d.add(2004, 3, 2, 10, 0, 0, true) << endl;
}