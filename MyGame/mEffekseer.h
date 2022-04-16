//#pragma once
//#include <d3d12.h>
//#include <dxgi1_6.h>
//#include <wrl.h>
//#include <d3dx12.h>
//#include <cstdlib>
//#include<cassert>
//#include"DirectXCommon.h"
//
//#pragma comment(lib,"d3d12.lib")
//
//#pragma comment(lib,"dxgi.lib")
//#include<Effekseer.h>
//#include<EffekseerRendererDX12.h>
////Effekseer/Dev/CppEffekseer
////Effekseer\Dev\Cpp\EffekseerRendererDX12\EffekseerRenderer
////Effekseer\Dev\Cpp\3rdParty\LLGI\src\Release
//#pragma comment(lib,"Dev/Cpp/EffekseerRendererDX12/Release/EffekseerRendererDX12.lib")
//#pragma comment(lib,"Dev/Cpp/Effekseer/Release/Effekseer.lib")
//#pragma comment(lib,"Dev/Cpp/3rdParty/LLGI/src/Release/LLGI.lib")
//#include"DebugCamera.h"
//class mEffekseer
//{
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::���ȗ�
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//	using XMVECTOR = DirectX::XMVECTOR;
//
//public:
//
//	//�G�t�F�N�g�����_��
//	EffekseerRenderer::RendererRef _efkRenderer = nullptr;
//	//�G�t�F�N�g�}�l�W��
//	Effekseer::ManagerRef _efkManager = nullptr;
//
//	//�������v�[��
//	Effekseer::RefPtr<EffekseerRenderer::SingleFrameMemoryPool> _efkMemoryPool = nullptr;
//	//�R�}���h���X�g(DX12�Ƃ�Vulkan�ւ̑Ή��̂���)
//	Effekseer::RefPtr<EffekseerRenderer::CommandList> _efkCmdList = nullptr;
//
//	//�G�t�F�N�g�{��(�G�t�F�N�g�t�@�C���ɑΉ�)
//	Effekseer::EffectRef _effect = nullptr;
//	// �G�t�F�N�g�n���h��(�Đ����̃G�t�F�N�g�ɑΉ�)
//	Effekseer::Handle _efkHandle;
//
//	void SyncronizeEffekseerCamera(DirectXCommon* dxCommon, DebugCamera* camera);
//	void EffekseerUpdate(DirectXCommon* dxCommon, DebugCamera* camera);
//	void EffekseerDraw(ID3D12GraphicsCommandList* cmdList);
//	void EffekseerSetting(DirectXCommon* dxCommon, DebugCamera* camera, const EFK_CHAR* name1, const EFK_CHAR* name2);
//	bool EffectReset();
//	//void EffekseerFinalize(;)
//private:
//	float positionx = 0;
//	float positiony = 0;
//	float positionz = 0;
//	float rotationx = 0;
//	float rotationy = 0;
//	float rotationz = 0;
//	float scalex = 1;
//	float scaley = 1;
//	float scalez = 1;
//	int timer=0;
//public:
//	float GetPositionx() { return positionx; }
//	float GetPositiony() { return positiony; }
//	float GetPositionz() { return positionz; }
//
//	int GetInstanceCount() { return _efkManager->GetInstanceCount(_efkHandle); }
//	void Load_Effect();
//	void Stop_Effect();
//	void SetPosition(float px, float py, float pz) { positionx = px; positiony = py; positionz = pz; };
//	void SetRotation(float rx, float ry, float rz) { rotationx = rx; rotationy = ry; rotationz = rz; }
//	void SetScale(float sx, float sy, float sz) { scalex = sx; scaley = sy; scalez = sz; }
//};
//
