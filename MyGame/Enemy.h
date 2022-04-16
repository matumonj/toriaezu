#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include"Input.h"
#include"Player.h"
/// <summary>
/// �G�L�����̊��N���X
/// </summary>
/// 
class Enemy
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Enemy();

protected:
	//Microosoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
protected:
	float EnemyHP;
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;
	float rotx;
	float rotz;
	XMVECTOR positionA;
	XMVECTOR positionB;
	XMVECTOR SubVector;
	bool Alive=true;
public:
	bool GetAlive() { return Alive; };
	float GetHP() { return EnemyHP; };
	void SetHP(float hp) { EnemyHP = hp; }
	float getrotc() { return rotx; }
	virtual void EnemySearchPlayer(Player* player)=0;
	
	static Enemy* Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera);

	/// <summary>
	/// ������
	/// </summary>
	virtual bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera) { return true; }

	/// <summary>
	/// �X�V����
	/// </summary>
	/// 3�������v���C���[���WXMFLOAt�^�ɒu���������ق�������
	/// �p�������G�ɂȂ邩��
	virtual void Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)=0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw(DirectXCommon*dxcomn)=0;

	/// <summary>
	/// �������
	/// </summary>
	virtual void Finalize()=0;

	float distance;

	float GetDistance() { return distance; }

	virtual float Distance(Player* player);

	XMFLOAT3 GetPosition() { return Position; }
	void Getposition(float* x, float* y, float* z) {
		*x = this->Position.x;
		*y = this->Position.y;
		*z = this->Position.z;
	};

	virtual XMMATRIX Getmatrot() {
		return Getmatrot();
	}
	void SetPosition(XMFLOAT3 position) { Position = position; }

	XMFLOAT3 GetRotation() { return Rotation; }

	void SetRotation(XMFLOAT3 rotation) { Rotation = rotation; }

	XMFLOAT3 GetScale() { return Scale; }

	void SetScale(XMFLOAT3 scale) { Scale = scale; }

};

