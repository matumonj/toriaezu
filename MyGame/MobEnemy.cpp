#include "MobEnemy.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
MobEnemy::MobEnemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MobEnemy::~MobEnemy()
{
	delete MobObject, MobModel;
}

DirectX::XMMATRIX MobEnemy::Getmatrot()
{
	return MobObject->GetMatrot();
}

//����������
bool MobEnemy::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	EnemyHP = 15.0f;
	//���f���̓Ǎ�
	MobModel = Model::CreateFromOBJ("subenemy");
	//���f�����蓖��
	//MobObject = new Object3d();
	MobObject = Object3d::Create(dxcomn, camera);
	MobObject->SetModel(MobModel);

	//
	Texture::LoadTexture(11, L"Resources/Sertch.png");
	SearchPlayerTexture = Texture::Create(11, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	SearchPlayerTexture->CreateTexture();
	//�p�����[�^�̃Z�b�g
	Scale = { 2,2,2 };
	Rotation = { 0,180,0 };
	Position = { -12,-2,0 };
	return true;
}

//�X�V����
void MobEnemy::Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)
{

	if (player->GetAttackFlag() == true) {
		//EnemyHP -= 3;
	}
	if (EnemyHP <= 0) {
		Position={900,900,900};
		Alive = false;
	}
	//�p�����[�^�̃Z�b�g
	//���u
	Rotation.y++;
		MobObject->SetPosition(Position);
		MobObject->SetScale({ 3,3,3 });
		MobObject->SetRotation(Rotation);

		SearchPlayerTexture->SetPosition({ Position.x,Position.y + 8,Position.z });
		SearchPlayerTexture->SetScale({ 0.4f,0.4f,0.4f });
		SearchPlayerTexture->Update(camera->GetViewMatrix(), camera->GetProjectionMatrix());

		MobObject->Update({ 1,1,1,1 }, dxcomn, camera);
	
		//MobObject->SetPosition({900,900,900});
	
}

//�`�揈��
void MobEnemy::Draw(DirectXCommon* dxcomn)
{
	if (Alive) {
		MobObject->PreDraw();
		MobObject->Draw();
		MobObject->PostDraw();
		Texture::PreDraw(dxcomn->GetCmdList());
		if (distance <= 30) {
			SearchPlayerTexture->Draw();
		}
		Texture::PostDraw();
	}
}

//�������
void MobEnemy::Finalize()
{
	delete SearchPlayerTexture;
	delete MobObject, MobModel;
}

float MobEnemy::Distance(Player* player)
{
	distance = sqrtf(((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x))
		+ ((player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y))
		+ ((player->GetPosition().z - Position.z) * (player->GetPosition().z - Position.z)));
	return distance;
}

void MobEnemy::EnemySearchPlayer(Player* player)
{
	//�v���C���[�ƓG�̋������v�Z
	float distance;
	distance = sqrtf(((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)) +
		((Position.y - player->GetPosition().y) * (Position.y - player->GetPosition().y)) +
		((Position.z - player->GetPosition().z) * (Position.z - player->GetPosition().z)));

	if (distance <= 30) {//��������萔�Ȃ�����v���C���[�����m
		SearchPlayerFlag = TRUE;
	} else {
		SearchPlayerFlag = FALSE;
	}

	XMVECTOR positionA = { player->GetPosition().x, player->GetPosition().y, player->GetPosition().z };
	XMVECTOR positionB = { Position.x,Position.y,Position.z };
	//�v���C���[�ƓG�̃x�N�g���̒���(��)�����߂�
	XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;
	if (SearchPlayerFlag == TRUE) {
		//�ǐ�
		Follow(player);
		//�p�x�̎擾 �v���C���[���G�̍��G�ʒu�ɓ�������������v���C���[�̕���
		rotx = atan2f(SubVector.m128_f32[0], SubVector.m128_f32[2]);

		Rotation.y = rotx * 60 + 180;//60=�p�x�����p 180=���]
	}

}

void MobEnemy::Follow(Player* player)
{
	float angleX, angleZ, angleR;
	float centerSpeed = 0.1f;
	angleX = (player->GetPosition().x - Position.x);
	angleZ = (player->GetPosition().z - Position.z);
	angleR = sqrtf((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)
		+ (Position.z - player->GetPosition().z) * (Position.z - player->GetPosition().z));
	Position.x += (angleX / angleR) * centerSpeed;
	Position.z += (angleZ / angleR) * centerSpeed;

}