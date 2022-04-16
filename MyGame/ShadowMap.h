#pragma once
#include <d3dcompiler.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"Model.h"
#include"Object3d.h"
#pragma comment(lib, "d3dcompiler.lib")
using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;
struct Vertex3D {
	XMFLOAT3 Position;	//�ʒu
	XMFLOAT3 Normal;	//�@��
	XMFLOAT2 UV;		//UV���W
};
class ShadowMap
{
private:
	//Microosoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	HRESULT Initialize(ID3D12Device* device);
	HRESULT ShadowMap::CreateRootSignature(ID3D12Device* device);

	void Update();
	HRESULT ShadowMap::CreatePSO(ID3D12Device* device);
	HRESULT ShadowMap::Draw(ID3D12GraphicsCommandList* command_list, ID3D12DescriptorHeap* dh_sm);
	void CreateShadowBuffer(ID3D12Device* device);
	void CreateLight();
	void SetShadowModel();
	void ShadowDraw();
private:
	ComPtr<ID3D12Resource>	shadow_buffer_;		//�V���h�E�}�b�v�p�[�x�o�b�t�@
	ComPtr<ID3D12PipelineState>	shadow_map_pso_;	//�V���h�E�}�b�v�p�̃p�C�v���C��

	ComPtr<ID3D12Resource>	light_buffer_;		//���C�g�p�̒萔�o�b�t�@
	ComPtr<ID3D12DescriptorHeap>dh_shadow_buffer_;	//�V���h�E�}�b�v�p�[�x�o�b�t�@�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>dh_shadow_texture_;	//�V���h�E�}�b�v�p�[�x�e�N�X�`���p�f�X�N���v�^�q�[�v
	D3D12_RECT		scissor_rect_sm_;
	D3D12_VIEWPORT	viewport_sm_;

	Model* shadowModel = nullptr;
	Object3d* shadowObj = nullptr;

	float ClearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	//	Rendertarget
private:
	ComPtr<ID3D12RootSignature>		root_sugnature_;
	ComPtr<ID3D12PipelineState>		pso_;
	ComPtr<ID3D12Resource>			vertex_buffer_;
	ComPtr<ID3D12Resource>			constant_buffer_;

};


