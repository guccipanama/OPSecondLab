#pragma once
#include "source.h"

DWORD WINAPI div1_(LPVOID param)
{
    HANDLE pipe_a = CreateNamedPipe(L"\\\\.\\pipe\\sum1", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    //HANDLE pipe_b = CreateNamedPipe(L"\\\\.\\pipe\\pipe_b", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

    HANDLE mutex_b = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_c");
    HANDLE mutex_c = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_d");

    while (true)
    {
        WaitForSingleObject(mutex_b, INFINITE);

        std::cout << std::endl << "DEBUG OUT: SECOND PROGRAM" << std::endl;
        std::cout << "DEBUG OUT: Program is calculating the result of dividing a by 3 now!" << std::endl;

        int_convert received_a;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_div1 = 0;

        auto tmp1 = ReadFile(pipe_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);

        HANDLE div = CreateFile(L"\\\\.\\pipe\\div1", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        res.value = received_a.value / 3;

        WriteFile(div, res.bytes, sizeof(int), &real_reading_div1, NULL);

        CloseHandle(pipe_a);

        std::cout << std::endl << "DEBUG OUT: Function result - a / b: " << res.value << std::endl;
        std::cout << "DEBUG OUT: Program is terminating now!" << std::endl;

        ReleaseMutex(mutex_c);
    }

    return 0;
/*
DWORD WINAPI sqrt_(LPVOID lpParameter)
{
    HANDLE result = CreateMailslot(L"\\\\.\\mailslot\\sum", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE third_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"third_semafor");
    HANDLE fourth_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"fourth_semafor");

    while (true) {
        WaitForSingleObject(third_semafor, INFINITE);

        std::cout << "\n" << "DEBUG OUT: THIRD PROGRAM" << std::endl;
        std::cout << "\n" << "DEBUG OUT: Program is calculating sqrt of sum of a and b now!" << std::endl;

        int_convert received_sum;
        double_convert mresult;

        DWORD real_reading_sum = 0;
        DWORD real_writing_res = 0;

        ReadFile(result, &received_sum.bytes, sizeof(int), &real_reading_sum, NULL);

        HANDLE res = CreateFile(L"\\\\.\\mailslot\\res", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        mresult.value = sqrt(received_sum.value);

        WriteFile(res, mresult.bytes, sizeof(double), &real_writing_res, NULL);

        CloseHandle(result);

        std::cout << "\n" << "Function result - sqrt of (a*a + b*b): " << mresult.value << std::endl;
        std::cout << "\n" << "DEBUG OUT: THIRD PROGRAM is terminating now!" << std::endl;

        ReleaseSemaphore(fourth_semafor, 1, NULL);
    }
    return 0;
}
Footer

*/
}