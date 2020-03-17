//простой пример использования http запросов в C++
//программе на вход подается название города (на английском)
//после ввода открывается html страница с данными о погоде в введенном городе
//Компиляция и запуск:
// g++ -o program main.cpp -lwininet
// start program

#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"wininet")

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main()
{
    cout << "Enter you city name: " << endl;
    string City;
    getline(cin, City);
    City = "/" + City;
    const char *cstrCity = City.c_str();
    HINTERNET hInternet = ::InternetOpen(TEXT("Test Wininet"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hInternet != NULL)
    {
        HINTERNET hConnect = ::InternetConnect(hInternet, TEXT("wttr.in"), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1u);
        if (hConnect != NULL)
        {
            HINTERNET hRequest = ::HttpOpenRequest(hConnect, TEXT("GET"), TEXT(cstrCity), NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION, 1);
            if (hRequest != NULL)
            {
                BOOL bSend = ::HttpSendRequest(hRequest, NULL, 0, NULL, 0);
                if (bSend)
                {
                    ofstream example("wttr.html", ios::out | ios::binary);
                    if (example.is_open())
                        while (true)
                        {
                            char szData[1024];
                            DWORD dwBytesRead;
                            BOOL bRead = ::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwBytesRead);
                            if (bRead == FALSE  ||  dwBytesRead == 0)
                                break;
                            szData[dwBytesRead] = 0;
                            example << szData;
                        }
                }
            }
            ::InternetCloseHandle(hRequest);
        }
        ::InternetCloseHandle(hConnect);
    }
    ::InternetCloseHandle(hInternet);
    system("start wttr.html");
    return 0;
}
