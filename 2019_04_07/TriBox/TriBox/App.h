#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

class App
{
public:
	App();
	~App();
	bool InitD3D();
	static LRESULT WndProc(HWND hWnd, UINT umsg, LPARAM lp, WPARAM wp);
};

