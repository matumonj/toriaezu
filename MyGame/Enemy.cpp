#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
Enemy* Enemy::Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera)
{
	
}



float Enemy::Distance(Player* player)
{

		distance = sqrtf(((player->GetPosition().x - Position.x) * (player->GetPosition().x - Position.x))
			+ ((player->GetPosition().y - Position.y) * (player->GetPosition().y - Position.y))
			+ ((player->GetPosition().z - Position.z) * (player->GetPosition().z - Position.z)));
		return distance;
	
}
