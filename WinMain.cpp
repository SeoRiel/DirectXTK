#include "pch.h"

// Build ����
// x86 : 32��Ʈ -> �ѹ��� 4byte ����
//		 �ִ� �޸� : 3 GByte

// x64 : 64��Ʈ -> �ѹ��� 8byte ����
//		 �ִ� �޸� : 2 TByte

// * 64��Ʈ �����쿡�� 32��Ʈ �� ����
//	- WOW64 ������ ���ķ����� : 32��Ʈ �����쿡�� ����Ǵ� 32��Ʈ �ۺ��� ����!

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPCSTR lpCmdLine, _In_ int nShowCmd)
{
	return 0;
}