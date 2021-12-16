#include "pch.h"

// Build 관리
// x86 : 32비트 -> 한번에 4byte 연산
//		 최대 메모리 : 3 GByte

// x64 : 64비트 -> 한번에 8byte 연산
//		 최대 메모리 : 2 TByte

// * 64비트 윈도우에서 32비트 앱 실행
//	- WOW64 윈도우 에뮬레이터 : 32비트 윈도우에서 실행되는 32비트 앱보다 느림!

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPCSTR lpCmdLine, _In_ int nShowCmd)
{
	return 0;
}