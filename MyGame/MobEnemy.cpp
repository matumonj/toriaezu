#include "MobEnemy.h"
/// <summary>
/// コンストラクタ
/// </summary>
MobEnemy::MobEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MobEnemy::~MobEnemy()
{
	delete MobObject, MobModel;
}

DirectX::XMMATRIX MobEnemy::Getmatrot()
{
	return MobObject->GetMatrot();
}

//初期化処理
bool MobEnemy::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
{
	EnemyHP = 15.0f;
	//モデルの読込
	MobModel = Model::CreateFromOBJ("subenemy");
	//モデル割り当て
	//MobObject = new Object3d();
	MobObject = Object3d::Create(dxcomn, camera);
	MobObject->SetModel(MobModel);

	//
	Texture::LoadTexture(11, L"Resources/Sertch.png");
	SearchPlayerTexture = Texture::Create(11, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	SearchPlayerTexture->CreateTexture();
	//パラメータのセット
	Scale = { 2,2,2 };
	Rotation = { 0,180,0 };
	Position = { -12,-2,0 };
	return true;
}

//更新処理
void MobEnemy::Update(DirectXCommon* dxcomn, DebugCamera* camera, Player* player)
{

	if (player->GetAttackFlag() == true) {
		//EnemyHP -= 3;
	}
	if (EnemyHP <= 0) {
		Position={900,900,900};
		Alive = false;
	}
	//パラメータのセット
	//モブ
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

//描画処理
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

//解放処理
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
	//プレイヤーと敵の距離を計算
	float distance;
	distance = sqrtf(((Position.x - player->GetPosition().x) * (Position.x - player->GetPosition().x)) +
		((Position.y - player->GetPosition().y) * (Position.y - player->GetPosition().y)) +
		((Position.z - player->GetPosition().z) * (Position.z - player->GetPosition().z)));

	if (distance <= 30) {//距離が一定数なったらプレイヤーを検知
		SearchPlayerFlag = TRUE;
	} else {
		SearchPlayerFlag = FALSE;
	}

	XMVECTOR positionA = { player->GetPosition().x, player->GetPosition().y, player->GetPosition().z };
	XMVECTOR positionB = { Position.x,Position.y,Position.z };
	//プレイヤーと敵のベクトルの長さ(差)を求める
	XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;
	if (SearchPlayerFlag == TRUE) {
		//追跡
		Follow(player);
		//角度の取得 プレイヤーが敵の索敵位置に入ったら向きをプレイヤーの方に
		rotx = atan2f(SubVector.m128_f32[0], SubVector.m128_f32[2]);

		Rotation.y = rotx * 60 + 180;//60=角度調整用 180=反転
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