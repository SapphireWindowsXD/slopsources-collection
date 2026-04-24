//this malware is absolute ass (its made by ultradasher's brother TELEPATHII)
//and what the fuck is with the weird naming and obviously vibe coded "DrawScene" function???

typedef struct IUnknown IUnknown;
#include <windows.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#define POINT_COUNT 200
#define ICON_SIZE 32

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //947th time i have seen this shit in gdi malwares
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}

typedef struct {
    FLOAT h, s, l;
} HSL;

namespace Colors {
    HSL rgb2hsl(RGBQUAD rgb) {
        HSL hsl;
        BYTE r = rgb.rgbRed;
        BYTE g = rgb.rgbGreen;
        BYTE b = rgb.rgbBlue;
        FLOAT _r = (FLOAT)r / 255.f;
        FLOAT _g = (FLOAT)g / 255.f;
        FLOAT _b = (FLOAT)b / 255.f;
        FLOAT rgbMin = min(min(_r, _g), _b);
        FLOAT rgbMax = max(max(_r, _g), _b);
        FLOAT fDelta = rgbMax - rgbMin;
        FLOAT deltaR;
        FLOAT deltaG;
        FLOAT deltaB;
        FLOAT h = 0.f;
        FLOAT s = 0.f;
        FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);
        if (fDelta != 0.f) {
            s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
            deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);
            if (_r == rgbMax)      h = deltaB - deltaG;
            else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
            else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
            if (h < 0.f)           h += 1.f;
            if (h > 1.f)           h -= 1.f;
        }
        hsl.h = h; hsl.s = s; hsl.l = l;
        return hsl;
    }

    RGBQUAD hsl2rgb(HSL hsl) {
        RGBQUAD rgb;
        FLOAT r = hsl.l;
        FLOAT g = hsl.l;
        FLOAT b = hsl.l;
        FLOAT h = hsl.h;
        FLOAT sl = hsl.s;
        FLOAT l = hsl.l;
        FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);
        FLOAT m;
        FLOAT sv;
        FLOAT fract;
        FLOAT vsf;
        FLOAT mid1;
        FLOAT mid2;
        INT sextant;
        if (v > 0.f) {
            m = l + l - v;
            sv = (v - m) / v;
            h *= 6.f;
            sextant = (INT)h;
            fract = h - sextant;
            vsf = v * sv * fract;
            mid1 = m + vsf;
            mid2 = v - vsf;
            switch (sextant) {
            case 0:
                r = v; g = mid1; b = m;
                break;
            case 1:
                r = mid2; g = v; b = m;
                break;
            case 2:
                r = m; g = v; b = mid1;
                break;
            case 3:
                r = m; g = mid2; b = v;
                break;
            case 4:
                r = mid1; g = m; b = v;
                break;
            case 5:
                r = v; g = m; b = mid2;
                break;
            }
        }
        rgb.rgbRed = (BYTE)(r * 255.f);
        rgb.rgbGreen = (BYTE)(g * 255.f);
        rgb.rgbBlue = (BYTE)(b * 255.f);
        return rgb;
    }
}

struct Vec3 { float x, y, z; };

std::vector<Vec3> points;
HICON icons[5];
float angleX = 0.0f, angleY = 0.0f;
int centerX, centerY;
int vx = 10, vy = 1;

void trianglegeneration() {
    points.clear();
    int w = GetSystemMetrics(0);

    float size = w / 10;

    Vec3 A = { -size, -size, 0 };
    Vec3 B = { size, -size, 0 };
    Vec3 C = { 0,     size, 0 };

    for (int i = 0; i < POINT_COUNT; i++) {
        float r1 = (float)rand() / RAND_MAX;
        float r2 = (float)rand() / RAND_MAX;

        if (r1 + r2 > 1.0f) {
            r1 = 1.0f - r1;
            r2 = 1.0f - r2;
        }

        Vec3 p;

        p.x = A.x + r1 * (B.x - A.x) + r2 * (C.x - A.x);
        p.y = A.y + r1 * (B.y - A.y) + r2 * (C.y - A.y);
        p.z = 0;

        points.push_back(p);
    }
}

void DrawScene(HDC hdc) { //im fucking laughing what the fuck is ts :sob:
    float cosX = cosf(angleX), sinX = sinf(angleX);
    float cosY = cosf(angleY), sinY = sinf(angleY);

    for (int i = 0; i < (int)points.size(); i++) {
        Vec3 p = points[i];

        float y1 = p.y * cosX - p.z * sinX;
        float z1 = p.y * sinX + p.z * cosX;
        float x2 = p.x * cosY + z1 * sinY;
        float z2 = -p.x * sinY + z1 * cosY;

        float fov = 4000.0f;
        float scale = fov / (fov + z2);

        int sx = (int)(x2 * scale + centerX);
        int sy = (int)(y1 * scale + centerY);

        DrawIconEx(hdc,
            sx - ICON_SIZE / 2,
            sy - ICON_SIZE / 2,
            icons[i % 5],
            ICON_SIZE,
            ICON_SIZE,
            0,
            NULL,
            DI_NORMAL);
    }
}

void sound1(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (((t | t >> 10) >> (t * t)) + t) & 128
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
            (((((t >> 2) * (t & (t & 32768 ? 16 : 24) | t >> (t >> 8 & 28)) | t >> 9) * 10) + 11) ^ t) & 128
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
            ((((t % 280) + (t % 270)) ^ t) * (t >> 11)) >> 1
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
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        int x = rand() % w;
        int y = rand() % h;
        int size = 300 + rand() % 100;
        int dist = 10 - rand() % 21;
        int dist2 = 10 - rand() % 21;
        int dist3 = 10 - rand() % 21;
        int dist4 = 10 - rand() % 21;
        BitBlt(hdc, x + dist, y + dist2, size, size, hdc, x + dist3, y + dist4, SRCINVERT);
        BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI hsl(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;


    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;

                int fx = (i * 10) * (sin(x / 100.f) + sin(y / 100.f));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 1000.f + y / screenHeight * .2f, 1.f);
                hslcolor.s = 1.f;
                if (hslcolor.l > 0.3f) {
                    hslcolor.l += 0.2f;
                }

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        StretchBlt(hdc, 10, 10, screenWidth + 10, screenHeight + 20, hdc, 0, 0, screenWidth, screenHeight, SRCERASE);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI payload2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    BITMAPINFO bmpi = { 0 };
    BLENDFUNCTION blur;
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
    SelectObject(hdcCopy, bmp);

    RECT rect;
    POINT lpt[3];

    while (1)
    {
        hdc = GetDC(0);
        INT counter = 10;
        GetWindowRect(GetDesktopWindow(), &rect);

        lpt[0].x = rect.left + counter;
        lpt[0].y = rect.top - counter;
        lpt[1].x = rect.right + counter;
        lpt[1].y = rect.top + counter;
        lpt[2].x = rect.left - counter;
        lpt[2].y = rect.bottom - counter;


        PlgBlt(hdcCopy, lpt, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0);
        BLENDFUNCTION blend = { 0, 0, 25, 0 };
        AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blend);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI hsl2(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;


    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;

                int fx = (i * 10) * (sin((x * x) / 10000.f) * sin((y * y) / 10000.f));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 100.f + y / screenHeight * .2f, 1.f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI triangle(LPVOID lpParam) {
    srand((unsigned)time(NULL));

    trianglegeneration();

    icons[0] = LoadCursor(NULL, IDC_ARROW);
    icons[1] = LoadCursor(NULL, IDC_NO);
    icons[2] = LoadCursor(NULL, IDC_HELP);
    icons[3] = LoadCursor(NULL, IDC_SIZEALL);
    icons[4] = LoadCursor(NULL, IDC_WAIT);

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    centerX = screenW / 2;
    centerY = screenH / 2;

    HDC hdc = GetDC(NULL);

    while (true) {
        centerX += vx;
        centerY += vy;

        if (centerX - 150 < 0 || centerX + 150 > screenW) vx = -vx;
        if (centerY - 150 < 0 || centerY + 150 > screenH) vy = -vy;

        angleX += 0.003f;
        angleY += 0.1f;

        DrawScene(hdc);
    }

    ReleaseDC(NULL, hdc);
    return 0;
}

DWORD WINAPI payload3(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    BITMAPINFO bmpi = { 0 };
    BLENDFUNCTION blur;
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
    SelectObject(hdcCopy, bmp);

    RECT rect;
    POINT lpt[3];

    while (1)
    {
        hdc = GetDC(0);
        INT counter = 10;
        GetWindowRect(GetDesktopWindow(), &rect);

        lpt[0].x = rect.left - counter;
        lpt[0].y = rect.top - counter;
        lpt[1].x = rect.right - counter;
        lpt[1].y = rect.top + counter;
        lpt[2].x = rect.left - counter;
        lpt[2].y = rect.bottom - counter;


        PlgBlt(hdcCopy, lpt, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0);
        BLENDFUNCTION blend = { 0, 0, 100, 0 };
        AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blend);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI hsl3(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;


    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;

                int fx = (i * 10) * (tan((x * x) / 10000.f) + tan((y * y) / 10000.f));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 100.f + y / screenHeight * .2f, 1.f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	if (MessageBoxW(0, L"click yes to proceed, idgaf about your data", L"systemverflüssiger.exe", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    HANDLE thread = CreateThread(0, 0, payload1, 0, 0, 0);
    HANDLE threaddot1 = CreateThread(0, 0, hsl, 0, 0, 0);
    sound1(11025, 30);
    TerminateThread(thread, 0);
    CloseHandle(thread);
    TerminateThread(threaddot1, 0);
    CloseHandle(threaddot1);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
    HANDLE thread2dot1 = CreateThread(0, 0, hsl2, 0, 0, 0);
    CreateThread(0, 0, triangle, 0, 0, 0);
    sound2(44100, 30);
    TerminateThread(thread2, 0);
    CloseHandle(thread2);
    TerminateThread(thread2dot1, 0);
    CloseHandle(thread2dot1);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
    HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
    HANDLE thread3dot1 = CreateThread(0, 0, hsl3, 0, 0, 0);
    sound3(44100, 30);
    TerminateThread(thread3, 0);
    CloseHandle(thread3);
    TerminateThread(thread3dot1, 0);
    CloseHandle(thread3dot1);
    RedrawWindow(0, 0, 0, 133);
    Sleep(100);
}
