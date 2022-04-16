#pragma once
#include"TargetMarker.h"
#include"Sprite.h"
#include"Enemy.h"
#include"DebugTxt.h"
#include"Player.h"
class GameUI
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
	void Initialize();
	void Update(Enemy* enemy[], TargetMarker* target);
	void Draw(DirectXCommon* dxcomn,  Enemy* enemy[], TargetMarker* target, Player* player);
private:
	XMFLOAT2 EnemyHPGaugePosition;
	XMFLOAT2 EnemyHPGaugeScale;
	XMFLOAT2 EnemyHPGauge2Position;
	XMFLOAT2 EnemyHPGauge2Scale;

	XMFLOAT2 PlayerHPGaugePosition;
	XMFLOAT2 PlayerHPGaugeScale;
	XMFLOAT2 PlayerHPGauge2Position;
	XMFLOAT2 PlayerHPGauge2Scale;

	DebugTxt* debugText;
	Sprite* EnemyHPGauge2 = nullptr;
	Sprite* EnemyHPGauge = nullptr;
	Sprite* PlayerHPGauge2 = nullptr;
	Sprite* PlayerHPGauge = nullptr;
	Sprite* Eggreport = nullptr;
	Sprite* hint1 = nullptr;
	Sprite* GetEggCount[4];
	XMFLOAT2 hintscale = { 0,0 };
	XMFLOAT3 hintspot1 = { 14,-2,38 };
	bool hintf = false;
};

