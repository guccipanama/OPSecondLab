#pragma once
#include "source.h"

DWORD WINAPI sub_(LPVOID param)
{
    HANDLE pipe_a = CreateNamedPipe(L"\\\\.\\pipe\\pipe_a", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    HANDLE pipe_b = CreateNamedPipe(L"\\\\.\\pipe\\pipe_b", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    HANDLE pipe_c = CreateNamedPipe(L"\\\\.\\pipe\\pipe_c", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    HANDLE pipe_d = CreateNamedPipe(L"\\\\.\\pipe\\pipe_d", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

    HANDLE mutex_c = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_c");
    HANDLE mutex_d = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_d");

    while (true)
    {
        WaitForSingleObject(mutex_c, INFINITE);

        std::cout << std::endl << "DEBUG OUT: THIRD PROGRAM" << std::endl;
        std::cout << "DEBUG OUT: Program is calculating difference between a and b now!" << std::endl;

        int_convert received_a;
        int_convert received_b;
        int_convert received_c;
        int_convert received_d;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_b = 0;
        DWORD real_reading_c = 0;
        DWORD real_reading_d = 0;
        DWORD real_reading_sub = 0;

        auto tmp1 = ReadFile(pipe_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        auto tmp2 = ReadFile(pipe_b, &received_b.bytes, sizeof(int), &real_reading_b, NULL);
        auto tmp3 = ReadFile(pipe_c, &received_c.bytes, sizeof(int), &real_reading_c, NULL);
        auto tmp4 = ReadFile(pipe_d, &received_d.bytes, sizeof(int), &real_reading_d, NULL);

        HANDLE sub = CreateFile(L"\\\\.\\pipe\\sub", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        res.value = received_a.value - received_d.value;
        res.value = received_b.value - received_d.value;
        res.value = received_c.value - received_d.value;

        WriteFile(sub, res.bytes, sizeof(int), &real_reading_sub, NULL);

        CloseHandle(pipe_a);
        CloseHandle(pipe_b);

        std::cout << std::endl << "DEBUG OUT: Function result - a - b: " << res.value << std::endl;
        std::cout << "DEBUG OUT: Program is terminating now!" << std::endl;
    }

    return 0;
    /*
    HANDLE value_a = CreateMailslot(L"\\\\.\\mailslot\\a^2", 0, MAILSLOT_WAIT_FOREVER, NULL);
    HANDLE value_b = CreateMailslot(L"\\\\.\\mailslot\\b^2", 0, MAILSLOT_WAIT_FOREVER, NULL);

    HANDLE second_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"second_semafor");
    HANDLE third_semafor = OpenSemaphore(EVENT_ALL_ACCESS, TRUE, L"third_semafor");

    while (true) {
        WaitForSingleObject(second_semafor, INFINITE);

        std::cout << "\n" << "DEBUG OUT: SECOND PROGRAM" << std::endl;
        std::cout << "\n" << "DEBUG OUT: Program is calculating sum of a and b now!" << std::endl;

        int_convert received_a;
        int_convert received_b;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_b = 0;
        DWORD real_reading_sum = 0;

        ReadFile(value_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        ReadFile(value_b, &received_b.bytes, sizeof(int), &real_reading_b, NULL);

        HANDLE sum = CreateFile(L"\\\\.\\mailslot\\sum", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        res.value = (received_a.value + received_b.value);

        WriteFile(sum, res.bytes, sizeof(int), &real_reading_sum, NULL);

        CloseHandle(value_a);
        CloseHandle(value_b);

        std::cout << "\n" << "Function result - sum a*a and b*b: " << res.value << std::endl;
        std::cout << "\n" << "DEBUG OUT: SECOND PROGRAM is terminating now!" << std::endl;

        ReleaseSemaphore(third_semafor, 1, NULL);
    }
    return 0;
    */
}