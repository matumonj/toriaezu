#pragma once

#include"Character.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
class Enemy;
class TargetMarker;
class Player :public Character
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static Player* Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera);
public:
	bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

	void Update(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camera)override;
	
	
	void Action(DirectXCommon* dxcomn, TargetMarker* target, DebugCamera* camera);
private:
	enum class Attack {
		NormalAttack,//�ʏ�U��
		MagicAttack,//���@�U��
	};
	bool attackflag = false;

	float ex, ey, ez;
	//�v���C���[�̉�]�p
	float angle;
private:
	//�G�t�F�N�g�`��̃t���O
	bool drawf = false;
	//
	int timer = 0;
	XMFLOAT3 Effect_Rot;
	XMFLOAT3 Effect_SCl;
	static XMFLOAT3 Effect_Pos;
	Input* input = Input::GetInstance();
private:
	//�L������4�����̂ǂ��������Ă��邩
	enum class RotationPrm {
		RIGHT,//�E
		LEFT,//��
		FRONT,//�O
		BACK,//���
	};
	RotationPrm rotate;
	XMFLOAT3 EffectRot;
	//�J�����ɍ��킹���L�����N�^�[�̉�]
	float CharaRotation = 0;
	float cooldowntime = 0;
	bool coolflag = false;
	const float CoolTime = 50;
private:
	
public:
	void AttackCoolTime();
	bool GetAttackFlag() { return attackflag; }
	void RotationStatus();
	void SetCharaRotation(float angle) { rotation.y = angle; rotate = RotationPrm::FRONT; }
	XMFLOAT3 Getpoi() { return Effect_Pos; }
	void normalAttack(DirectXCommon* dxcomn, TargetMarker* target,Enemy* enemy[], DebugCamera* camera);
};

