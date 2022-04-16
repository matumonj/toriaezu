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
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
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
		NormalAttack,//通常攻撃
		MagicAttack,//魔法攻撃
	};
	bool attackflag = false;

	float ex, ey, ez;
	//プレイヤーの回転用
	float angle;
private:
	//エフェクト描画のフラグ
	bool drawf = false;
	//
	int timer = 0;
	XMFLOAT3 Effect_Rot;
	XMFLOAT3 Effect_SCl;
	static XMFLOAT3 Effect_Pos;
	Input* input = Input::GetInstance();
private:
	//キャラが4方向のどこを向いているか
	enum class RotationPrm {
		RIGHT,//右
		LEFT,//左
		FRONT,//前
		BACK,//後ろ
	};
	RotationPrm rotate;
	XMFLOAT3 EffectRot;
	//カメラに合わせたキャラクターの回転
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

