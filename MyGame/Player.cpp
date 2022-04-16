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
	Player* instance = new Player();	//インスタンスを生成

	if (instance == nullptr) {
		return nullptr;
	}

	//初期化
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

	//エフェクトのセット(3引き数に)
	//effect->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/attack.efk", (const EFK_CHAR*)L"effect/10");

	if (!Object3d::Initialize(dxcomn, camera))
	{
		return false;
	}
	position = { -20,10,20 };
	//aaaaaaa
	// コライダーの追加
	//character
	CollisionFieldSet();
	return true;
}
void Player::Update(XMFLOAT4 color, DirectXCommon* dxcomn, DebugCamera* camera)
{

	//エフェクトのパラメータセット
	//effect->SetRotation(0, 0, 0);
	//effect->SetScale(0.5, 0.5, 0.5);

	RotationStatus();

	
	//エフェクトの再生
	//effect->Load_Effect();
	//エフェクトのアニメーション止める
	if (Input::GetInstance()->Pushkey(DIK_C)) {
	//	effect->Stop_Effect();
	}
	scale = { 1,1,1 };
	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	//向いてる方向に移動
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

	//左方向への移動
	if (rotate != RotationPrm::LEFT && input->TriggerKey(DIK_A)) {//今向いている方向が左じゃなくAキーが押され、
		if (rotate == RotationPrm::FRONT) {//右以外を向いていたら
			rotation.y = rotation.y - 90;
		} 
		else if(rotate == RotationPrm::BACK){//右を向いていたら
			rotation.y = rotation.y +90;
		}
		else if (rotate == RotationPrm::RIGHT) {
			rotation.y = rotation.y - 180;
		}
		//向きの情報を左に
		rotate = RotationPrm::LEFT;
	}

	//右方向への移動
	else if (rotate != RotationPrm::RIGHT && input->TriggerKey(DIK_D)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::FRONT) {//右以外を向いていたら
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {//右を向いていたら
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {
			rotation.y = rotation.y + 180;
		}
		//向きの情報を右に
		rotate = RotationPrm::RIGHT;
	}

	//前方向への移動
	if (rotate != RotationPrm::FRONT && input->TriggerKey(DIK_W)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::RIGHT) {//もし右を向いてたら
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {//もし左を向いてたら
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {
			rotation.y -= 180;
		}
		//向きの情報を前に
		rotate = RotationPrm::FRONT;
	}

	//後ろ方向へ移動
	if (rotate != RotationPrm::BACK && input->TriggerKey(DIK_S)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::RIGHT) {//もし右を向いてたら
			rotation.y = rotation.y + 90;
		} else if (rotate == RotationPrm::LEFT) {//もし左を向いてたら
			rotation.y = rotation.y - 90;
		} else if (rotate == RotationPrm::FRONT) {
			rotation.y += 180;
		}
		//向きの情報を前に
		rotate = RotationPrm::BACK;
	}
}
