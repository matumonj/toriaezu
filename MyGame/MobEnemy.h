#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"Player.h"
#include"Texture.h"
#include"Sprite.h"
class MobEnemy :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MobEnemy();

    /// <summary>
    /// デストラクタ
    /// </summary> 
    ~MobEnemy();

private:
    //オブジェクトのインスタンス
    Object3d* MobObject = nullptr;
    //モデルのインスタンス
    Model* MobModel = nullptr;
    //
    Texture* SearchPlayerTexture = nullptr;
public:
    XMMATRIX Getmatrot()override;// { return MobObject->GetMatrot(); }
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
    /// <summary>
    /// 
    /// </summary>
    /// 
    void EnemySearchPlayer(Player* player)override;

    void Follow(Player*player);

    float Distance(Player* player)override;

private:
    bool SearchPlayerFlag = false;
    float GetDistance() { return distance; }

};

