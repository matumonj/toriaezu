#pragma once

#include "f_Model.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"DirectXCommon.h"
#include"DebugCamera.h"
class f_Object3d
{
protected:
	//Microosoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static void SetDevice(ID3D12Device* device) { f_Object3d::device = device; }
	static void SetCamera(Camera* camera) { f_Object3d::camera = camera; }

	
	///�O���t�B�b�N�p�C�v���C���̐���
	static void CreateGraphicsPipeline();

private:	
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

public:	
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;		//���[���h�s��
		XMFLOAT3 cameraPos;	//�J�����s��
	};

public:
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera);

	/// <summary>
	/// ���t���[��
	/// </summary>
	void Updata(XMFLOAT4 color,DirectXCommon* dxcomn, DebugCamera* camerabool,bool animeloop);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	void SetModel(f_Model* model) { this->model = model; }

	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void PlayAnimation();

protected:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	//�X�P�[��
	XMFLOAT3 scale = { 1, 1, 1 };
	//��]
	XMFLOAT3 rotation = { 0, 0, 0 };
	//���W
	XMFLOAT3 position = { 0, -50, 0 };
	//���[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	f_Model* model = nullptr;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffSkin;
	//1�t���[��
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;

public:	
	void Setpos(XMFLOAT3 pos) { position = pos; }
	//�{�[���̍ő吔
	static const int MAX_BONES = 180;
	XMFLOAT3 GetPosition() { return position; }
	//�萔�o�b�t�@�p�f�[�^�\���́i�X�L�j���O�j
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
};
