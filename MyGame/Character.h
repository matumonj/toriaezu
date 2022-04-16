#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"DirectXCommon.h"
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"

//���ׂẴI�u�W�F�N�g�̊��N���X
class Character :public Object3d
{
public:
	//Character() = default;
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	//�������̃t���O
	bool AliveFlag = TRUE;
	//�̗�
	float HP;
	
protected:
	//�ڒn�t���O
	bool onGround = true;
	//�����x�N�g��
	XMVECTOR fallV;
public:
	/// <summary>
	/// ������
	/// </summary>
	virtual bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(XMFLOAT4 color,DirectXCommon* dxcomn, DebugCamera* camera)override;

	/// <summary>
	/// �R���C�_�[�̃Z�b�g�Ȃ�
	/// </summary>
	void  CollisionFieldSet();
	
	/// <summary>
	/// �r�ˏ����Ȃ�
	/// </summary>
	void CollisionField(DirectXCommon* dxcomn, DebugCamera* camera);
	
	/// <summary>
	/// �������
	/// </summary>
	virtual void Finalize();

	//�U������
	virtual void Attack();
	
	//���b����(�j�������ȂǓ����)
	virtual void Death();

	
public:
	
};

