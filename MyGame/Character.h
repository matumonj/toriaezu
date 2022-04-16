#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include"DirectXCommon.h"
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"

//すべてのオブジェクトの基底クラス
class Character :public Object3d
{
public:
	//Character() = default;
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	//生き死のフラグ
	bool AliveFlag = TRUE;
	//体力
	float HP;
	
protected:
	//接地フラグ
	bool onGround = true;
	//落下ベクトル
	XMVECTOR fallV;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(XMFLOAT4 color,DirectXCommon* dxcomn, DebugCamera* camera)override;

	/// <summary>
	/// コライダーのセットなど
	/// </summary>
	void  CollisionFieldSet();
	
	/// <summary>
	/// 排斥処理など
	/// </summary>
	void CollisionField(DirectXCommon* dxcomn, DebugCamera* camera);
	
	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Finalize();

	//攻撃処理
	virtual void Attack();
	
	//脂肪処理(破棄処理など入れる)
	virtual void Death();

	
public:
	
};

