#include "BossEnemy.h"

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
	delete BossObject, BossModel;
}

//����������
bool BossEnemy::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	EnemyHP = 10;
	//���f���̓Ǎ�
	BossModel = Model::CreateFromOBJ("egg");
	//���f�����蓖��
	//BossObject = new Object3d();
	BossObject = Object3d::Create(dxcomn, camera);
	BossObject->SetModel(BossModel);

	//�p�����[�^�̃Z�b�g
	Scale = { 20,20,20 };
	Rotation = { 0,180,0 };
	Position = { 15,-2,0 };
	return true;
}

//�X�V����
void BossEnemy::Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)
{
	if (EnemyHP <= 0) {
		Alive = false;
	}
	//�p�����[�^�̃Z�b�g
	//���u
	BossObject->SetPosition(Position);
	BossObject->SetScale({ 1,1,1 });
	BossObject->SetRotation(Rotation);
	BossObject->Update({ 1,1,1,1 }, dxcomn, camera);
}

//�`�揈��
void BossEnemy::Draw(DirectXCommon* dxcomn)
{
	BossObject->PreDraw();
	BossObject->Draw();
	BossObject->PostDraw();
}

//�������
void BossEnemy::Finalize()
{
	delete BossObject, BossModel;
}

float BossEnemy::Distance(Player* player)
{
	distance = sqrtf(((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x))
		+ ((player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y))
		+ ((player->GetPosition().z - Position.z) * (player->GetPosition().z - Position.z)));
	return distance;
}

void BossEnemy::EnemySearchPlayer(Player* player)
{

}