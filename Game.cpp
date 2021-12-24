#include "pch.h"
#include "Game.h"

using Microsoft::WRL::ComPtr;

using namespace DirectX;
using namespace DirectX::SimpleMath;

extern void ExitGame() noexcept;

Game::Game() noexcept(false)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
}

void Game::Initialize(HWND window, int width, int height)
{
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();

	m_mouse->SetWindow(window);
	
	m_deviceResources->SetWindow(window, width, height);
	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

}

#pragma region Frame Update
void Game::Tick()
{
	m_timer.Tick([&]() 
		{ 
			Update(m_timer); 
		});

	Render();
}

void Game::Update(DX::StepTimer const& timer)
{
	auto keyState = m_keyboard->GetState();
	if (keyState.Escape)
	{
		ExitGame();
	}
}
#pragma endregion

#pragma region Message Handler
void Game::OnActivated()
{
}

void Game::OnDeActivated()
{
}

// 컴퓨터가 절전모드일 때
void Game::OnSuspending()
{
}

// 화면이 멈추었을 때
void Game::OnResuming()
{
	m_timer.ResetElapsedTime();
}

// 윈도우 창이 움직일 때
void Game::OnWindowMoved()
{
	auto rect = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(rect.right, rect.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
	{
		return;
	}

	CreateWindowSizeDependentResources();
}

void Game::GetDefaultSize(int& width, int& height) const noexcept
{
	width = 800;
	height = 600;
}
#pragma endregion

#pragma region Frame Render
void Game::Render()
{
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	// Draw
	m_deviceResources->PIXEndEveint();

	m_deviceResources->Present();
}

void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	auto context = m_deviceResources->GetD3DDeivceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEveint();
}
#pragma endregion

#pragma region Direct3D Resources
void Game::CreateDeviceDependentResources()
{

}

void Game::CreateWindowSizeDependentResources()
{

}

void Game::OnDeviceLost()
{

}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
#pragma endregion