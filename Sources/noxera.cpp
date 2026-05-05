//ts fucking ass and vibe coded
//by mrmalwar3 (skiddie ass name)

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "winmm.lib")

// 🎵 Bytebeat Sound Function
void playBytebeat(int seconds, int formulaID) {
    HWAVEOUT hWaveOut = nullptr;

    WAVEFORMATEX wfx = {};
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 1;
    wfx.nSamplesPerSec = 8000;
    wfx.wBitsPerSample = 8;
    wfx.nBlockAlign = 1;
    wfx.nAvgBytesPerSec = 8000;

    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        std::cerr << "Failed to open waveform output device.\n";
        return;
    }

    const DWORD sampleRate = 8000;
    const size_t bufferSize = sampleRate * seconds;  // Change to size_t
    char* buffer = new char[bufferSize];

    for (size_t t = 0; t < bufferSize; ++t) {  // Change to size_t
        unsigned char value = 0;
        if (formulaID == 1) {
            value = (5 * static_cast<int>(t) & (t >> 7)) | (3 * static_cast<int>(t) & (4 * (t >> 10)));
        }
        else if (formulaID == 2) {
            value = 2 * ((t >> 5) & static_cast<int>(t)) + (t >> 5) + t * ((t >> 10) & 23);
        }
        else if (formulaID == 3) {
            value = static_cast<unsigned char>((t * (3 + ((1 ^ (t >> 10)) & 5))) * (5 + ((3 * (t >> 14)))) >> (t >> 8 & 3)) % 256;
        }
        else if (formulaID == 4) {
            value = static_cast<unsigned char>((t * ((t & 4096 ? t % 65536 < 59392 ? 7 : t & 7 : 16) + (1 & t >> 14)) >>
                (3 & -static_cast<int>(t) >> (t & 2048 ? 2 : 10))) |
                (t >> (t & 16384 ? (t & 4096 ? 10 : 3) : 2)));
        }
        buffer[t] = value;
    }

    WAVEHDR header = {};
    header.lpData = buffer;
    header.dwBufferLength = static_cast<DWORD>(bufferSize);  // Casting to DWORD for wave header

    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(seconds * 1000);

    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    delete[] buffer;
}

void runBitBltEffect(int seconds) {
    srand(static_cast<unsigned>(time(0)));
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    ULONGLONG start = GetTickCount64();  // Use GetTickCount64 to avoid overflow

    while (GetTickCount64() - start < static_cast<ULONGLONG>(seconds * 1000)) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCAND);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

void runBouncingBall(int seconds) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int signX = 1, signY = 1;
    int x = 10, y = 10;
    int speed = 10;

    ULONGLONG start = GetTickCount64();  // Use GetTickCount64 to avoid overflow

    while (GetTickCount64() - start < static_cast<ULONGLONG>(seconds * 1000)) {
        HDC hdc = GetDC(0);
        x += speed * signX;
        y += speed * signY;

        int top_x = x;
        int top_y = y;
        int bottom_x = x + 100;
        int bottom_y = y + 100;

        HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SelectObject(hdc, brush);
        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        DeleteObject(brush);
        ReleaseDC(0, hdc);

        if (x <= 0 || x + 100 >= w) signX *= -1;
        if (y <= 0 || y + 100 >= h) signY *= -1;

        Sleep(10);
    }
}

void runPieEffect(int seconds) {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    ULONGLONG start = GetTickCount64();  // Use GetTickCount64 to avoid overflow

    while (GetTickCount64() - start < static_cast<ULONGLONG>(seconds * 1000)) {
        HDC hdc = GetDC(0);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);

        int r1 = rand() % x;
        int r2 = rand() % y;
        int r3 = rand() % x;
        int r4 = rand() % y;
        int r5 = rand() % x;
        int r6 = rand() % y;
        int r7 = rand() % x;
        int r8 = rand() % y;

        Pie(hdc, r1, r2, r3, r4, r5, r6, r7, r8);

        DeleteObject(brush);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

void runTextSpamEffect(int seconds) {
    LPCWSTR lptext = L"NOXERA";
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    ULONGLONG start = GetTickCount64();  // Use GetTickCount64 to avoid overflow

    while (GetTickCount64() - start < static_cast<ULONGLONG>(seconds * 1000)) {
        HDC hdc = GetWindowDC(GetDesktopWindow());

        SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
        SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));

        for (int i = 0; i < 5; ++i) {
            TextOutW(hdc, rand() % sw, rand() % sh, lptext, wcslen(lptext));
        }

        ReleaseDC(GetDesktopWindow(), hdc);
        Sleep(0);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int response = MessageBox(
        NULL,
        L"This is a GDI Only. Epilepsy warning. The creator (Mrmalwar3) is not liable for any damages!",
        L"Noxera.exe",
        MB_OKCANCEL | MB_ICONWARNING
    );

    if (response == IDCANCEL) {
        std::cout << "User canceled.\n";
        return 0;
    }

    std::cout << "Starting Stage 1...\n";
    std::thread sound1(playBytebeat, 30, 1);
    runBitBltEffect(30);
    sound1.join();

    std::cout << "Starting Stage 2...\n";
    std::thread sound2(playBytebeat, 30, 2);
    runBouncingBall(30);
    sound2.join();

    std::cout << "Starting Stage 3...\n";
    std::thread sound3(playBytebeat, 30, 3);
    runPieEffect(30);
    sound3.join();

    std::cout << "Starting Stage 4...\n";
    std::thread sound4(playBytebeat, 60, 4);
    runTextSpamEffect(60);
    sound4.join();

    std::cout << "Done!\n";
    return 0;
}
