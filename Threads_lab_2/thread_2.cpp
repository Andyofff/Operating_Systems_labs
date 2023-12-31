#include <iostream>
#include <windows.h>

int* arr;
int arr_size;
int sum = 0;
int avg = 0;
int Min = INT_MAX;
int Max = INT_MIN;
CRITICAL_SECTION cs;

DWORD WINAPI minmax(LPVOID par) {
    for (int i = 1; i < arr_size; i++)
    {
        if (Min > arr[i]) {
            Min = i;
        }

        Sleep(7);
        if (Max < arr[i]) {
            Max = i;
        }

        Sleep(7);
    }

    EnterCriticalSection(&cs);

    std::cout << "Min: " << Min << " Max: " << Max << '\n';

    LeaveCriticalSection(&cs);
    return 0;
}
DWORD WINAPI average(LPVOID par)
{
    for (int i = 0; i < arr_size; i++)
    {
        sum += arr[i];
        Sleep(12);
    }

    avg = sum / arr_size;
    EnterCriticalSection(&cs);

    std::cout << "Avg: " << avg << std::endl;

    LeaveCriticalSection(&cs);
    return 0;
}
int main()
{
    std::cout << "Enter size of array: ";
    std::cin >> arr_size;
    arr = new int[arr_size];
    std::cout << "Enter ellements of array: ";
    for (int i = 0; i < arr_size; i++){
        std::cin >> arr[i];
    }

    InitializeCriticalSection(&cs);

    HANDLE mm = CreateThread(NULL, 0, minmax, NULL, 0, NULL);
    HANDLE avrg = CreateThread(NULL, 0, average, NULL, 0, NULL);

    WaitForSingleObject(mm, INFINITE);
    WaitForSingleObject(avrg, INFINITE);

    std::cout << "Source array: ";
    for (int i = 0; i < arr_size; i++){
        std::cout << arr[i] << " ";
    }

    std::cout << '\n';
    
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == Min || arr[i] == Max) {
            arr[i] = avg;
        }
    }
    
    std::cout << "New array: ";
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    
    DeleteCriticalSection(&cs);
    CloseHandle(mm);
    CloseHandle(avrg);
    delete[] arr;
    return 0;
}
