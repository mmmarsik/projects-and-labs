#include "tasks.h"

#include <cmath>

int NOuter::NInner::DoSomething(int lhs, int rhs) {
    return lhs+rhs;
}

int NOuter::DoSomething(int lhs, int rhs) {
    return lhs-rhs;
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
    return lhs+rhs;
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
    return std::max(lhs, rhs);
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
    return lhs-rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
    return lhs+rhs;
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
    return lhs-rhs;
}

int NLoop::SumInRange(const int lhs, const int rhs) {
    int64_t sum=lhs;
    for(int64_t i=lhs+1; i<rhs; ++i)
        sum+=i;
    return sum;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
    int64_t cnt=0, c, c1;
    for(int64_t i=from+1; i<to; ++i)
    {
        c=i;
        c1=0;
        while(c>0)
        {
            c1+=c%2;
            c/=2;
        }
        if(c1==bitsCnt)
            cnt++;
    }
    return cnt;
}

double NMath::ComputeMathFormula(const double arg) {
    return std::abs((std::sin(arg)/2 + std::cos(arg))*(std::sin(arg)/2 + std::cos(arg))+std::tan(arg)*std::atan(arg));
}

bool NMath::IsPositive(int arg) {
    if(arg>0)
        return true;
    else
        return false;
}

int NRecursion::CalculateFibonacci(const int arg) {
    int64_t a[arg];
    a[0]=1;
    a[1]=1;
    for(int64_t i=2; i<arg; ++i)
    {
        a[i]=a[i-1]+a[i-2];
    }
    return a[arg-1];
}