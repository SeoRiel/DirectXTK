#pragma once
// PCH = Pre Complied Header
// PCH�� Microsoft Windows������ ���
// Linux, MAC OS������ PCH�� ��õ���� ����
//	- �ٸ� ������� ������ �ӵ��� ���� ��ų �� ����

// ���ʿ��� ��� ������� ����
// ���� ����� �� �ִ� ���� ����
#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00	
// Windows7   0X0601
// Windows8	  0x0602
// Windows8.1 0x0603
// Windows10  0x0A00

// Windows�� min(), max() �Լ� ������� ����
#include <winsdkver.h>
#define MOMINMAX

// GDI�� ������� ����
#define NODRAWTEXT
#define NOGDI

// BITMAP ����� ������� ����
#define NOBITMAP

// ���� ������� ����
#define NOMCX

// Service = â�� ���� ������ ���α׷�
// Service ����� ������� ����
#define NOSERVICE

// ���� ������ - Depercated
#define NOHLEP

#define WIN32_LEAN_AND_MEAN

/* ======================================================= */
// ���� ����ϴ� ���

// Windows
#include <Windows.h>

// Direct3D
#include <wrl/client.h>
#include <d3d11_1.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
// ���Ǻ� ������
#ifdef _DEBUG	// ����� ����� ��
#include <dxgidebug.h>
#endif

// C++
#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>

// C
#include <stdio.h>

//
#pragma warning(push)
#pragma warning(disable:26812)

#include "Audio.h"
#include "CommonStates.h"
#include "WICTextureLoader.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"

#pragma warning(pop)

#include "StepTimer.h"

namespace DX
{
	class com_exception : public std::exception
	{
	private:
		HRESULT result;

	public:
		com_exception(HRESULT hr) noexcept : result{ hr } {}

		const char* what() const override
		{
			static char s_str[65]{};

			sprintf_s(s_str, "Failure whit HRESULT %08X", static_cast<unsigned int>(result));

			return s_str;
		}
	};

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}
}