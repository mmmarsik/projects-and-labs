#pragma once
#include<bits/stdc++.h>
namespace NPointers {
    

    void Increment(int* a){
        (*a)++;
        
    }

    int Multiply(int a, int b, bool* flag){
        if(a > INT_MAX / b){
            (*flag) = true;
            return 0;
        }
        else
        {
            (*flag) = false;
            return a*b;
        }
    
    }

    int ScalarProduct(const int* a,const int* b,int n){
        int ans = 0;
        for (int i = 0; i < n; i++){
            ans += a[i] * b[i];
        }
        return ans;
    }

   int SizeOfMaximumSquareOfCrosses(const char* a, int sizei, int sizej)
    {
        int m=1;
        int b[sizei][sizej];
        b[0][0]=0;
        for(int i=1; i<sizei; i++)
        {    if(*a+i*sizej=='+')
                b[i][0]=1;
            else
                b[i][0]=0;
        }
        for(int j=1; j<sizej; j++)
        {    if(*a+j=='+')
                b[0][j]=1;
            else
                b[0][j]=0;
        }
        for(int i=1; i<sizei; i++)
        {
            for(int j=1; j<sizej; j++)
            {
                if(*a+i*sizej+j=='.')
                    b[i][j]=0;
                else
                {
                    if(b[i-1][j-1]!=0 && b[i-1][j]!=0 && b[i][j-1]!=0)
                    {
                        b[i][j]=b[i-1][j-1]+1;
                        if(m<b[i][j])
                            m=b[i][j];
                    }
                    else if(b[i-1][j-1]==0)
                    {
                        b[i][j]=1;
                    }
                    else if(b[i-1][j-1]!=0 && (b[i-1][j]=0 || b[i][j-1]==0))
                    {
                        b[i][j]=1;
                    }
                }
            }
        }
        return m;
    }

    long long *MultiplyToLongLong(int a, int b){
        long long *res = new long long();
        *res = (long long) a * b;
        return res;
    }

    

}

namespace NReferences {

    void MultiplyInplace(int &a, int b){
        a *= b;
    }

    int CompareArraysByAverage(const int* a, int n, const int* b)
    {
        int summa1 = 0, summa2 = 0;
        for (int i = 0; i < n; i++){
            summa1 += a[i];
        }

        for (int i = 0; i < 5; i++){
            summa2 += b[i];
        }

        if (5 * summa1 > n * summa2){
            return 1;
        }
        else if (5 * summa1 == n * summa2){
            return 0;
        }
        else{
            return -1;
        }
    }
}
