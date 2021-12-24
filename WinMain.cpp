#include "pch.h"
#include "Game.h"

// Build 관리
// x86 : 32비트 -> 한번에 4byte 연산
//		 최대 메모리 : 3 GByte

// x64 : 64비트 -> 한번에 8byte 연산
//		 최대 메모리 : 2 TByte

// * 64비트 윈도우에서 32비트 앱 실행
//	- WOW64 윈도우 에뮬레이터 : 32비트 윈도우에서 실행되는 32비트 앱보다 느림!

using namespace DirectX;

namespace
{
	std::unique_ptr<Game> g_game;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 라이브러리의 변수 변경
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// 사용하지 않은 매개변수
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// XM : DirectX Math
	// SIMD
	if (!XMVerifyCPUSupport())
	{
		return 1;
	}

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return 1;
	}

	g_game = std::make_unique<Game>();

	{

	}

	CoUninitialize();

	return 0;
}