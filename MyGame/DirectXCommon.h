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

class DirectXCommon
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
	//���\�[�X�ݒ�
	ComPtr<ID3D12Resource>depthBuffer;
	CD3DX12_RESOURCE_DESC depthResDesc;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	//�[�xview�p�ŃX�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	UINT64 fenceVal = 0;
	//�E�B���h�E�T�C�Y�̎w��
	int window_width = 1900;
	int  window_height = 1020;

	//�[�x�e�X�g�p
public:
	//�e�평��������
	void Initialize(WinApp* winapp);
	void InitializeDevice();
	void InitializeCommand();
	void InitializeSwapchain();
	void InitializeRenderTargetView();
	void InitializeDepthBuffer();
	void InitializeFence();
	//�`��O�E�㏈��
	void BeginDraw();
	void EndDraw();
	//�Q�b�^�[
	ID3D12Device* GetDev() { return dev.Get(); }
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList; }
	ID3D12CommandQueue* GetcmdQue() { return cmdQueue.Get(); };
	//
private:

	ComPtr<ID3D12DescriptorHeap>ImGuiDescriptor();

public:
	static ID3D12DescriptorHeap* GetDsvheap();
	static DirectXCommon* GetInstance();
	ComPtr<ID3D12DescriptorHeap>heapforimgui();
	ComPtr<ID3D12DescriptorHeap>imguiHeap;
	ComPtr<ID3D12DescriptorHeap>GetimguiDescriptorHeap() { return imguiHeap; };
	bool InitImgui();
public:
	void ClearDepthBuffer(ID3D12GraphicsCommandList* cmdList);
	HRESULT CreateShadowBuffer();
	HRESULT SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES BeforeState, D3D12_RESOURCE_STATES AfterState);

private:
	ComPtr<ID3D12Resource>	shadow_buffer_;
	ComPtr<ID3D12DescriptorHeap>dh_shadow_buffer_;	//�V���h�E�}�b�v�p�[�x�o�b�t�@�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>dh_shadow_texture_;	//�V���h�E�}�b�v�p�[�x�e�N�X�`���p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12PipelineState>			shadow_map_pso_;
	ComPtr<ID3D12Resource>				light_buffer_;		//���C�g�p�̒萔�o�b�t�@
};


