#pragma once
#include "DeviceResources.h"
#include "StepTimer.h"

// final : �� �̻� �ڽ��� ��� ���� ����
class Game final : public DX::IDeviceNotify
{
private:
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	DX::StepTimer m_timer;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;


public:
	Game() noexcept(false);
	~Game();

	// 
	Game(Game&&) = default;
	Game& operator =(Game&&) = default;

	// ���� �Ұ�
	Game(Game const&) = delete;
	Game& operator=(Game const&) = delete;

	void Initialize(HWND window, int width, int height);
	void Tick();

	void OnDeviceLost() override;
	void OnDeviceRestored() override;

	void OnActivated();
	void OnDeActivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	void GetDefaultSize(int& width, int& height) const noexcept;

private:
	void Update(DX::StepTimer const& timer);
	void Render();
	void Clear();
	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();
};
