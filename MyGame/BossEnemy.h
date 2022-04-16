#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
class BossEnemy :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemy();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemy();

private:
    //オブジェクトのインスタンス
    Object3d* BossObject = nullptr;
    //モデルのインスタンス
    Model* BossModel = nullptr;

private:
    //パラメータ
    //XMFLOAT3 Boss_Pos;
    //XMFLOAT3 Boss_Rot;
    //XMFLOAT3 Boss_Scl;

public:
    /// <summary>
   /// 初期化
   /// </summary>
    bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw(DirectXCommon* dxcomn)override;

    /// <summary>
    /// 解放処理
    /// </summary>
    void Finalize()override;

    float Distance(Player* player)override;

    void EnemySearchPlayer(Player* player)override;

public:
    /// <summary>
   /// アクセッサ
   /// </summary>
   /// <returns></returns>
   //座標
   // XMFLOAT3 GetPosition() { return Boss_Pos; }
    //回転
    //XMFLOAT3 GetRotation() { return Boss_Rot; }
    //スケール
    //XMFLOAT3 GetScale() { return Boss_Scl; }

};

