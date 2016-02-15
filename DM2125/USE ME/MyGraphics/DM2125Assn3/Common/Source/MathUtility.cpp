#include "MathUtility.h"
#include <iostream>

int factorial(int n)
{
    if (n == 0 || n == 1)
        n = 1;
    else{
        if (n<0)
            n = -1;
            for (int i = n; i > 0; --i){
                if (i - 1 == 0)
                    break;
                n *= i - 1;
            
        }

    }
    
    return n;
}

int nCr(int n, int r)
{
    if (n < 0 || r < 0)
        return 0;
    if (n == 0 && r == 0)
        return 1;
    else if (n == 0)
        return 0;
    else if (r == 0)
        return 1;
    else
	return (factorial(n) / (factorial(r) * factorial(n-r)));
}

int nPr(int n, int r)
{
    if (n == 0 && r == 0)
        return 1;
    else if (r > 0 && n == 0)
        return 1;
    else if (r == 0 && n > 0)
        return 1;
    else if (r < 0 || n < 0)
        return 0;
    else
	return (factorial(n) / factorial (n - r));
}

int nTermAP(int a, int d, int n)
{
    
	return a + ((n-1) * d);
}

int summationAP(int a, int d, int n)
{
	return (n*(a + nTermAP(a,d,n)))/2;
}

int nTermGP(int a, int r, int n)
{
    if (a == 0 || n == 0 || r == 0)
        return 0;
   return a * pow(r,n-1);
}

int summationGP(int a, int r, int n)
{
    if (a == 0)
        return 0;
    if (a >= 0 && r >= 0 && n < 0)
        return -1;
	return (a * (1 - pow(r,n)))/(1 - r);
}