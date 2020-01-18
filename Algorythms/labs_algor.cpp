#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <locale.h>
using namespace std;

// Дано натуральне число n. Серед чисел 1, ..., n знайти такі числа, запис
// яких співпадає з останніми цифрами запису їх квадрату. Наприклад, 6 (62 = 36), 25 (252 = 625) і т.д.
void automorph ()
{
    int n,x,s,m,o;
    cout << "n = ";
    cin>>n;
    for (x=n; x>0; --x)
    {
        s=x*x;
        for (m=10; m<x; m*=10);
            o=s%m;
            if (x==o)
            {
                cout << x << "\n";
            }
    }
}




void pochasovoy()
{
int const n=5;
 int A[n][n];
 int i=1,j,k,p=n/2;
 for(k=1;k<=p;k++)/*Цикл по номеру витка*/
 {
    for (j=k-1;j<n-k+1;j++) A[k-1][j]=i++;/*Определение значений верхнего гор столбца*/
    for (j=k;j<n-k+1;j++) A[j][n-k]=i++;/* --//-- По правому вертикальному столбцу*/
    for (j=n-k-1;j>=k-1;--j) A[n-k][j]=i++;/* --//-- по нижнему горизонтальному столбцу*/
    for (j=n-k-1;j>=k;j--) A[j][k-1]=i++;/* --//-- по левому вертикальному столбцу*/
 }
 if (n%2==1) A[p][p]=n*n;
 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
  {
   printf(" %4d ",A[i][j]);
   if(j==n-1) printf("\n");
  }
}

// Заповнити матрицю послідовністю чисел, кратних 3, починаючи із заданого k, у зазначеному порядку.
void lab2()
{
    const int n = 5;
    static int m[n][n];
    int numb;
    cout << "Give me k= ";
    cin >> numb;
    if (numb % 3 == 1)
    {
        numb += 2;
    }
    if (numb % 3 == 2)
    {
        numb += 1;
    }
    if (numb % 3 == 0)
    {
        for (int counter = 0; counter < n; ++counter) {
            for (int j = counter; j < n-counter; ++j) m[n-counter-1][j] = numb+=3; /*низ*/
            for (int i = n-counter-2; i >= counter; --i) m[i][n-counter-1] = numb+=3; /*правый*/
            for (int j = n-counter-2; j > counter; --j) m[counter][j] = numb+=3; /*верх*/
            for (int i = counter; i < n-counter-1; ++i) m[i][counter] = numb+=3; /*левый*/
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << setw(3) << m[i][j];
        cout << endl;
    }
}

int main ()
{
    // automorph();
    lab2();

    return(0);
}
