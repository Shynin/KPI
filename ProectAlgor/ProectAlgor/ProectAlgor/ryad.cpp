#include <iostream>
#include <cmath>
using namespace std;

double ln(double x, int threshold){
        double result=0;
        for (int i=1;i<threshold;i++)
                result += (i%2==0?-1:1) * pow(x,i)/i;
        return result;
}

int main ()
{
    double x;
    int n;
    cout << "Input x: ";
    cin >> x;
    cout << "\nInput n: ";
    cin >> n;
    cout << "\n\nln = " << ln(x,n);
    return 0;
}