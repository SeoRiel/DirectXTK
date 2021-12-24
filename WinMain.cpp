#include "pch.h"
#include "Game.h"

// Build ����
// x86 : 32��Ʈ -> �ѹ��� 4byte ����
//		 �ִ� �޸� : 3 GByte

// x64 : 64��Ʈ -> �ѹ��� 8byte ����
//		 �ִ� �޸� : 2 TByte

// * 64��Ʈ �����쿡�� 32��Ʈ �� ����
//	- WOW64 ������ ���ķ����� : 32��Ʈ �����쿡�� ����Ǵ� 32��Ʈ �ۺ��� ����!

using namespace DirectX;

namespace
{
	std::unique_ptr<Game> g_game;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ���̺귯���� ���� ����
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ������� ���� �Ű�����
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