/*
* BFHM
* потоки одного процесса
* мьютексы
* каналы
* выборочная дисперсия трех чисел
*/

#include "source.h"
#include <iostream>

int main()
{
    std::cout << "DEBUG OUT: MAIN" << std::endl;

    DWORD info_1;
    DWORD info_2;
    DWORD info_3;
    DWORD info_4;
    DWORD info_5;
    DWORD info_6;
    CreateMutex(NULL, TRUE, L"mutex_a");
    CreateMutex(NULL, TRUE, L"mutex_b");
    CreateMutex(NULL, TRUE, L"mutex_c");
    CreateMutex(NULL, TRUE, L"mutex_d");
    CreateMutex(NULL, TRUE, L"mutex_e");
    CreateMutex(NULL, TRUE, L"mutex_f");
    CreateMutex(NULL, TRUE, L"mutex_g");

    CreateThread(NULL, 0, &sum1_, NULL, 0, &info_1);
    CreateThread(NULL, 0, &div1_, NULL, 0, &info_2);
    CreateThread(NULL, 0, &sub_, NULL, 0, &info_3);
    CreateThread(NULL, 0, &sqr_, NULL, 0, &info_4);
    CreateThread(NULL, 0, &sum2_, NULL, 0, &info_5);
    CreateThread(NULL, 0, &div2_, NULL, 0, &info_6);

    HANDLE res = CreateNamedPipe(L"\\\\.\\pipe\\result", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

    int a = 0;
    int b = 0;
    int c = 0;

    std::cout << "Please enter a: " << std::endl;
    std::cin >> a;
    std::cout << "Please enter b: " << std::endl;
    std::cin >> b;
    std::cout << "Please enter b: " << std::endl;
    std::cin >> c;


    /// ------- ÇÀÏÈÑÜ à è b --------- ///
    HANDLE value_a = CreateFile(L"\\\\.\\pipe\\a", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HANDLE value_b = CreateFile(L"\\\\.\\pipe\\b", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HANDLE value_c = CreateFile(L"\\\\.\\pipe\\c", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    int_convert received_a;
    int_convert received_b;
    int_convert received_c;
    received_a.value = a;
    received_b.value = b;
    received_c.value = c;

    DWORD real_read_a = 0;
    DWORD real_read_b = 0;
    DWORD real_read_c = 0;

    WriteFile(value_a, received_a.bytes, sizeof(int), &real_read_a, NULL);
    WriteFile(value_b, received_b.bytes, sizeof(int), &real_read_b, NULL);
    WriteFile(value_c, received_c.bytes, sizeof(int), &real_read_c, NULL);

    HANDLE mutex_a = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_a");
    HANDLE mutex_g = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_g");

    WaitForSingleObject(mutex_g, INFINITE);
    Sleep(1);

    double_convert result;
    result.value = 0;

    DWORD real_write_result = 0;
    ReadFile(res, &result.bytes, sizeof(double), &real_write_result, NULL);
    CloseHandle(res);

    std::cout << "\n" << "ALL RESULT CALCULATIONS - sqrt(a^2 + b^2) = " << result.value << std::endl;
    std::cout << "\n" << "DEBUG OUT: MAIN is terminating now!" << std::endl;

    return 0;
}