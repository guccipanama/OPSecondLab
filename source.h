#include <Windows.h>
#include <iostream>

#ifndef UNTITLED_SOURCE_H
#define UNTITLED_SOURCE_H

union int_convert 
{
    int value = 0;
    BYTE bytes[sizeof(int)];
};

union double_convert 
{
    double value = 0.0;
    byte bytes[sizeof(double)];
};

DWORD WINAPI sum1_(LPVOID param);
DWORD WINAPI div1_(LPVOID param);
DWORD WINAPI sub_(LPVOID param);
DWORD WINAPI sqr_(LPVOID param);
DWORD WINAPI sum2_(LPVOID param);
DWORD WINAPI div2_(LPVOID param);

#endif
