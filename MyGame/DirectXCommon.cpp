#include "DirectXCommon.h"
#include<imgui.h>
DirectXCommon* DirectXCommon::GetInstance()
{
	static DirectXCommon instance;

	return &instance;
}

void DirectXCommon::Initialize(WinApp* winapp)
{

	//でバッグレイヤーのやつ
#ifdef _DEBUG
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif

	assert(winapp);
	this->winapp = winapp;
	//デバイスの生成
	InitializeDevice();
	//コマンド関連の初期化
	InitializeCommand();
	//スワップチェーン周りの初期化
	InitializeSwapchain();

	InitImgui();
	//レンダーターゲットビュー当たりの初期化
	InitializeRenderTargetView();
	//深度バッファの初期化
	InitializeDepthBuffer();
	//フェンス生成
	InitializeFence();
}
#pragma region デバイスの生成
void DirectXCommon::InitializeDevice() {

	HRESULT result;
	//dxgiファクトリーの生成
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

	//アダプタの列挙用
	std::vector<ComPtr<IDXGIAdapter1>>adapters;

	//ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter1>tmpAdapter;
	for (int i = 0; dxgiFactory->EnumAdapters1(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; i++) {
		adapters.push_back(tmpAdapter);
	}
	//グラフィックボードのアダプタを列挙2
	for (int i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC1 adesc;
		adapters[i]->GetDesc1(&adesc);
		if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		std::wstring strDesc = adesc.Description;
		if (strDesc.find(L"Intel") == std::wstring::npos) {
			tmpAdapter = adapters[i];
			break;
		}
	}

	//デバイスの生成
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;
	for (int i = 0; i < _countof(levels); i++) {
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
		if (result == S_OK) {
			featureLevel = levels[i];
			break;
		}
	}

}
#pragma endregion

#pragma region コマンド関連の初期化
void DirectXCommon::InitializeCommand()
{
	HRESULT result;
	result = dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));

	//コマンドリストの生成
	result = dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&cmdList));

	//コマンドキューの生成
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));

}
#pragma endregion

#pragma region スワップチェーンの初期化
void DirectXCommon::InitializeSwapchain()
{

	//スワップチェーンの生成
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
	swapchainDesc.Width = 1900;
	swapchainDesc.Height = 1020;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgiFactory->CreateSwapChainForHwnd(cmdQueue.Get(), winapp->GetHwnd(), &swapchainDesc, nullptr, nullptr, &swapchain1);
	swapchain1.As(&swapchain);
	//swapchain->Present(1, 0);
}
#pragma endregion

#pragma region レンダーターゲット周りの初期化
void DirectXCommon::InitializeRenderTargetView()
{
	HRESULT result;
	//でスクリプタヒープの生成
	//D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = 2;
	dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));

	//レンダーターゲットviewの生成
	backbuffers.resize(2);
	for (int i = 0; i < 2; i++) {
		result = swapchain->GetBuffer(i, IID_PPV_ARGS(&backbuffers[i]));
		auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(),
			i, dev->GetDescriptorHandleIncrementSize(heapDesc.Type));
		//D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
		//handle.ptr += i * dev->GetDescriptorHandleIncrementSize(heapDesc.Type);
		dev->CreateRenderTargetView(backbuffers[i].Get(), nullptr, handle);
	}
}
#pragma endregion

#pragma region 深度バッファ関連設定
void DirectXCommon::InitializeDepthBuffer()
{
	HRESULT result;

	depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_D32_FLOAT, window_width, window_height, 1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
	);
	//リソース生成
	result = dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
		&depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0), IID_PPV_ARGS(&depthBuffer));

	//深度view用でスクリプタヒープ作成
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	//深度ビュー作成
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(depthBuffer.Get(), &dsvDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());

}
#pragma endregion

#pragma region フェンス生成
void DirectXCommon::InitializeFence()
{
	HRESULT result;
	result = dev->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}
#pragma endregion

#pragma region 描画前処理
void DirectXCommon::BeginDraw()
{
	
	//バックバッファの番号取得
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//リソースバリアを書き込み用に
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backbuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	//描画先指定
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeaps->GetCPUDescriptorHandleForHeapStart(),
		bbIndex, dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

	//シャドーマップ用のテクスチャを深度書き込みに設定
//	SetResourceBarrier(shadow_buffer_.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE);

	//ルートシグネチャとPSOの設定
	//cmdList->SetPipelineState(shadow_map_pso_.Get());


	//深度ステンシルビュー用でスクリプタヒープ
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
	//深度バッファの設定
	//cmdList->OMSetRenderTargets(0, nullptr, FALSE, &dh_shadow_buffer_->GetCPUDescriptorHandleForHeapStart());
	//ライトの設定
	//cmdList->SetGraphicsRootConstantBufferView(1, light_buffer_->GetGPUVirtualAddress());

	//画面クリア　描画色の指定
	float clearColor[] = { 0.3,0.3,0.3,1 };
	//レンダーターゲット　クリア
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//深度バッファ　クリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//シャドーマップ用の深度バッファをクリア
	//cmdList->ClearDepthStencilView(dh_shadow_buffer_->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


	//viewポート領域の設定
	cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::window_width, WinApp::window_height));
	//シザー短形の設定
	cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, WinApp::window_width, WinApp::window_height));

}
#pragma endregion

#pragma region 描画後処理
void DirectXCommon::EndDraw()
{
	//SetResourceBarrier(shadow_buffer_.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ);

	//SetResourceBarrier()
	//バックバッファの番号取得
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();
	// imgui描画
	ImGui::Render();
	ID3D12DescriptorHeap* ppHeaps[] = { imguiHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);

	//リソースバリアを表示用に
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backbuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	//命令をクローズ
	cmdList->Close();
	//コマンドリストの実行
	ID3D12CommandList* cmdLists[] = { cmdList };
	cmdQueue->ExecuteCommandLists(1, cmdLists);
	//実行待ち
	cmdQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	//アロケーターをクリア
	cmdAllocator->Reset();
	//コマンドリストのリセット
	cmdList->Reset(cmdAllocator.Get(), nullptr);
	//画面フリップ
	swapchain->Present(1, 0);
}
#pragma endregion
//
bool DirectXCommon::InitImgui()
{
	HRESULT result = S_FALSE;

	// デスクリプタヒープを生成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = 1;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	result = dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&imguiHeap));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// スワップチェーンの情報を取得
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	result = swapchain->GetDesc(&swcDesc);
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(winapp->GetHwnd());
	ImGui_ImplDX12_Init(
		GetDev(),
		swcDesc.BufferCount,
		swcDesc.BufferDesc.Format,
		imguiHeap.Get(),
		imguiHeap->GetCPUDescriptorHandleForHeapStart(),
		imguiHeap->GetGPUDescriptorHandleForHeapStart()
	);

	return true;
}
void DirectXCommon::ClearDepthBuffer(ID3D12GraphicsCommandList* cmdList)
{
	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvHeap->GetCPUDescriptorHandleForHeapStart());
	// 深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

HRESULT DirectXCommon::CreateShadowBuffer()
{
	HRESULT hr;


	D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc{};
	descriptor_heap_desc.NumDescriptors = 1;
	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descriptor_heap_desc.NodeMask = 0;
	hr = dev->CreateDescriptorHeap(&descriptor_heap_desc, IID_PPV_ARGS(&dh_shadow_buffer_));
	if (FAILED(hr)) {
		return hr;
	}

	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	hr = dev->CreateDescriptorHeap(&descriptor_heap_desc, IID_PPV_ARGS(&dh_shadow_texture_));
	if (FAILED(hr)) {
		return hr;
	}


	D3D12_HEAP_PROPERTIES heap_properties{};
	D3D12_RESOURCE_DESC resource_desc{};
	D3D12_CLEAR_VALUE clear_value{};
	heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;


	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resource_desc.Width = 1024;
	resource_desc.Height = 1024;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 0;
	resource_desc.Format = DXGI_FORMAT_R32_TYPELESS;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	clear_value.Format = DXGI_FORMAT_D32_FLOAT;
	clear_value.DepthStencil.Depth = 1.0f;
	clear_value.DepthStencil.Stencil = 0;

	hr = dev->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, &clear_value, IID_PPV_ARGS(&shadow_buffer_));
	if (FAILED(hr)) {
		return hr;
	}


	//深度バッファのビューの作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc{};
	dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
	dsv_desc.Texture2D.MipSlice = 0;
	dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
	dev->CreateDepthStencilView(shadow_buffer_.Get(), &dsv_desc, dh_shadow_buffer_->GetCPUDescriptorHandleForHeapStart());



	D3D12_SHADER_RESOURCE_VIEW_DESC resourct_view_desc{};
	resourct_view_desc.Format = DXGI_FORMAT_R32_FLOAT;
	resourct_view_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	resourct_view_desc.Texture2D.MipLevels = 1;
	resourct_view_desc.Texture2D.MostDetailedMip = 0;
	resourct_view_desc.Texture2D.PlaneSlice = 0;
	resourct_view_desc.Texture2D.ResourceMinLODClamp = 0.0F;
	resourct_view_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	dev->CreateShaderResourceView(shadow_buffer_.Get(), &resourct_view_desc, dh_shadow_texture_->GetCPUDescriptorHandleForHeapStart());

	return hr;
}

//リソースの設定変更用
HRESULT DirectXCommon::SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES BeforeState, D3D12_RESOURCE_STATES AfterState) {
	D3D12_RESOURCE_BARRIER resource_barrier{};

	resource_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	resource_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	resource_barrier.Transition.pResource = resource;
	resource_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	resource_barrier.Transition.StateBefore = BeforeState;
	resource_barrier.Transition.StateAfter = AfterState;

	cmdList->ResourceBarrier(1, &resource_barrier);
	return S_OK;
}
