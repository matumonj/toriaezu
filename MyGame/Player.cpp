#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"TargetMarker.h"

#define PI 3.145265
using namespace DirectX;
XMFLOAT3 Player::Effect_Pos = { -50,-10,-100 };
Player* Player::Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera)
{
	Player* instance = new Player();	//�C���X�^���X�𐶐�

	if (instance == nullptr) {
		return nullptr;
	}

	//������
	instance->Initialize(dxcomn, camera);//	delete instance;
	//	assert(0);

	if (model) {
		instance->SetModel(model);
	}
	return instance;
}

bool Player::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	rotate = RotationPrm::FRONT;
	//effect = new mEffekseer();
	//effect->Initialize(dxcomn, camera);

	//�G�t�F�N�g�̃Z�b�g(3��������)
	//effect->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/attack.efk", (const EFK_CHAR*)L"effect/10");

	if (!Object3d::Initialize(dxcomn, camera))
	{
		return false;
	}
	position = { -20,10,20 };
	//aaaaaaa
	// �R���C�_�[�̒ǉ�
	//character
	CollisionFieldSet();
	return true;
}
void Player::Update(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camera)
{

	//�G�t�F�N�g�̃p�����[�^�Z�b�g
	//effect->SetRotation(0, 0, 0);
	//effect->SetScale(0.5, 0.5, 0.5);

	RotationStatus();

	
	//�G�t�F�N�g�̍Đ�
	//effect->Load_Effect();
	//�G�t�F�N�g�̃A�j���[�V�����~�߂�
	if (Input::GetInstance()->Pushkey(DIK_C)) {
	//	effect->Stop_Effect();
	}
	scale = { 1,1,1 };
	//�ړ��x�N�g����y������̊p�x�ŉ�]
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	//�����Ă�����Ɉړ�
	if (input->Pushkey(DIK_W) || input->Pushkey(DIK_A) || input->Pushkey(DIK_D) || input->Pushkey(DIK_S)) {
		position.x += move.m128_f32[0]*2 ;
		position.z += move.m128_f32[2]*2;
	}
	//effect->EffekseerUpdate(dxcomn, camera);

	CollisionField(dxcomn,camera);
	//character
	
	
}


void Player::normalAttack(DirectXCommon* dxcomn,TargetMarker*target, Enemy* enemy[], DebugCamera* camera)
{
	//float ex, ey, ez;
	//Effect_Pos.x = position.x;
	//Effect_Pos.y = position.y;
	//Effect_Pos.z = position.z;
	//
	//	EffectRot.y = rotation.y;
	//	EffectRot.z = 70;
	//	effect->SetScale(3, 3, 3);
	//effect->SetRotation(EffectRot.x, EffectRot.y, EffectRot.z);
	////effect->SetPosition(ex,ey,ez);
	//effect->SetPosition(Effect_Pos.x, Effect_Pos.y, Effect_Pos.z);

	//effect->EffekseerUpdate(dxcomn, camera);
	if (input->TriggerKey(DIK_SPACE) && !coolflag) {
		if (!attackflag) {
			attackflag = true;
		}
	}
	if (attackflag) {
		//Effect_Pos.x = enemy[target->GetNearIndex()]->GetPosition().x-10;
		//Effect_Pos.y = enemy[target->GetNearIndex()]->GetPosition().y;
		//Effect_Pos.z = enemy[target->GetNearIndex()]->GetPosition().z;
		//effect->Load_Effect();
		coolflag = true;
		float distance = sqrtf(((enemy[target->GetNearIndex()]->GetPosition().x - position.x) * (enemy[target->GetNearIndex()]->GetPosition().x - position.x))
			+ ((enemy[target->GetNearIndex()]->GetPosition().y - position.y) * (enemy[target->GetNearIndex()]->GetPosition().y - position.y))
			+ ((enemy[target->GetNearIndex()]->GetPosition().z - position.z) * (enemy[target->GetNearIndex()]->GetPosition().z - position.z)));

		if (distance <= 10) {
			enemy[target->GetNearIndex()]->SetHP(enemy[target->GetNearIndex()]->GetHP() - 1);
		}
		attackflag = false;
	}
	if (coolflag) {
		cooldowntime++;
		if (cooldowntime > CoolTime) {
			coolflag = false;
			cooldowntime = 0;
		}
	}
	//effect->SetPosition(Effect_Pos.x, Effect_Pos.y, Effect_Pos.z);

	//effect->EffekseerDraw(dxcomn->GetCmdList());

}

void Player::RotationStatus()
{

	//�������ւ̈ړ�
	if (rotate != RotationPrm::LEFT && input->TriggerKey(DIK_A)) {//�������Ă��������������Ȃ�A�L�[��������A
		if (rotate == RotationPrm::FRONT) {//�E�ȊO�������Ă�����
			rotation.y = rotation.y - 90;
		} 
		else if(rotate == RotationPrm::BACK){//�E�������Ă�����
			rotation.y = rotation.y +90;
		}
		else if (rotate == RotationPrm::RIGHT) {
			rotation.y = rotation.y - 180;
		}
		//�����̏�������
		rotate = RotationPrm::LEFT;
	}

	//�E�����ւ̈ړ�
	else if (rotate != RotationPrm::RIGHT && input->TriggerKey(DIK_D)) {//�������Ă���������E����Ȃ��c�L�[��������A
		if (rotate == RotationPrm::FRONT) {//�E�ȊO�������Ă�����
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {//�E�������Ă�����
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {
			rotation.y = rotation.y + 180;
		}
		//�����̏����E��
		rotate = RotationPrm::RIGHT;
	}

	//�O�����ւ̈ړ�
	if (rotate != RotationPrm::FRONT && input->TriggerKey(DIK_W)) {//�������Ă���������E����Ȃ��c�L�[��������A
		if (rotate == RotationPrm::RIGHT) {//�����E�������Ă���
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {//�������������Ă���
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {
			rotation.y -= 180;
		}
		//�����̏���O��
		rotate = RotationPrm::FRONT;
	}

	//�������ֈړ�
	if (rotate != RotationPrm::BACK && input->TriggerKey(DIK_S)) {//�������Ă���������E����Ȃ��c�L�[��������A
		if (rotate == RotationPrm::RIGHT) {//�����E�������Ă���
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::LEFT) {//�������������Ă���
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::FRONT) {
			rotation.y += 180;
		}
		//�����̏���O��
		rotate = RotationPrm::BACK;
	}
}
