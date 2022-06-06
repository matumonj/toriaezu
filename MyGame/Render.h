#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include<cassert>
//#include"imgui.h"
#include"imgui_impl_dx12.h"
#include"imgui_impl_win32.h"
#include "WinApp.h"

//using namespace DirectX;
#pragma comment(lib,"d3d12.lib")

#pragma comment(lib,"dxgi.lib")
using namespace Microsoft::WRL;

class Render
{
private:
	WinApp* winapp = nullptr;
	ComPtr<IDXGIFactory6>dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<IDXGISwapChain1> swapchain1;
	ComPtr<ID3D12CommandAllocator>cmdAllocator;
	ID3D12GraphicsCommandList* cmdList;
	ComPtr<ID3D12CommandQueue>cmdQueue;
	ComPtr<ID3D12DescriptorHeap>rtvHeaps;
	ComPtr<ID3D12DescriptorHeap>dsvHeap;
	ComPtr<ID3D12Fence>fence;
	std::vector<ComPtr<ID3D12Resource>>backbuffers;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	//深度view用でスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
public:
	void initRender();
};

