#pragma once
#include "source.h"

DWORD WINAPI div2_(LPVOID param)
{
    HANDLE pipe_a = CreateNamedPipe(L"\\\\.\\pipe\\sum2", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    //HANDLE pipe_b = CreateNamedPipe(L"\\\\.\\pipe\\pipe_b", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

    HANDLE mutex_f = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_c");
    HANDLE mutex_g = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_d");

    while (true)
    {
        WaitForSingleObject(mutex_f, INFINITE);

        std::cout << std::endl << "DEBUG OUT: SIXTH PROGRAM" << std::endl;
        std::cout << "DEBUG OUT: Program is calculating the result of dividing a by 3 now!" << std::endl;

        int_convert received_a;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_div1 = 0;

        auto tmp1 = ReadFile(pipe_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);

        HANDLE result = CreateFile(L"\\\\.\\pipe\\result", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        res.value = received_a.value / 2;

        WriteFile(result, res.bytes, sizeof(int), &real_reading_div1, NULL);

        CloseHandle(pipe_a);

        std::cout << std::endl << "DEBUG OUT: Function result - a / b: " << res.value << std::endl;
        std::cout << "DEBUG OUT: Program is terminating now!" << std::endl;

        ReleaseMutex(mutex_g);
    }
    return 0;
}