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
    /// �R���X�g���N�^
    /// </summary>
    MobEnemy();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary> 
    ~MobEnemy();

private:
    //�I�u�W�F�N�g�̃C���X�^���X
    Object3d* MobObject = nullptr;
    //���f���̃C���X�^���X
    Model* MobModel = nullptr;
    //
    Texture* SearchPlayerTexture = nullptr;
public:
    XMMATRIX Getmatrot()override;// { return MobObject->GetMatrot(); }
    /// <summary>
    /// ������
    /// </summary>
    bool Initialize(DirectXCommon* dxcomn, DebugCamera* camera)override;

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw(DirectXCommon* dxcomn)override;

    /// <summary>
    /// �������
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

