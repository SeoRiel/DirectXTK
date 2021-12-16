#pragma once
// PCH = Pre Complied Header
// PCH는 Microsoft Windows에서만 사용
// Linux, MAC OS에서는 PCH를 추천하지 않음
//	- 다른 방법으로 컴파일 속도를 증가 시킬 수 있음

// 불필요한 기능 사용하지 않음
// 앱을 사용할 수 있는 버전 지정
#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00	
// Windows7   0X0601
// Windows8	  0x0602
// Windows8.1 0x0603
// Windows10  0x0A00

// Windows의 min(), max() 함수 사용하지 않음
#include <winsdkver.h>
#define MOMINMAX

// GDI를 사용하지 않음
#define NODRAWTEXT
#define NOGDI

// BITMAP 기능을 사용하지 않음
#define NOBITMAP

// 모뎀을 사용하지 않음
#define NOMCX

// Service = 창이 없는 윈도우 프로그램
// Service 기능을 사용하지 않음
#define NOSERVICE

// 도움말 사용안함 - Depercated
#define NOHLEP

#define WIN32_LEAN_AND_MEAN

/* ======================================================= */
// 자주 사용하는 헤더

// Windows
#include <Windows.h>

// Direct3D
#include <wrl/client.h>
#include <d3d11_1.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
// 조건부 컴파일
#ifdef _DEBUG	// 디버그 모드일 때
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