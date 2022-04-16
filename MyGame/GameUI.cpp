#include "GameUI.h"

void GameUI::Initialize()
{
	Sprite::LoadTexture(12, L"Resources/bosshp.png");
	EnemyHPGauge = Sprite::Create(12, { 0.0f,-200.0f });

	Sprite::LoadTexture(13, L"Resources/lifegauge.png");
	EnemyHPGauge2 = Sprite::Create(13, { 0.0f,-200.0f });

	Sprite::LoadTexture(14, L"Resources/eggreport.png");
	Eggreport = Sprite::Create(14, { 0.0f,-200.0f });

	Sprite::LoadTexture(15, L"Resources/debugfont2.png");
	debugText = new DebugTxt();
	debugText->Initialize(15);
	Sprite::LoadTexture(16, L"Resources/hint1.png");
	hint1 = Sprite::Create(16, { 0.0f,-200.0f });
	
	Sprite::LoadTexture(17, L"Resources/life.png");
	EnemyHPGauge = Sprite::Create(17, { 0.0f,-200.0f });

	Sprite::LoadTexture(18, L"Resources/lifegauge.png");
	EnemyHPGauge2 = Sprite::Create(18, { 0.0f,-200.0f });
	
	Sprite::LoadTexture(23, L"Resources/life.png");
	PlayerHPGauge = Sprite::Create(23, { 0.0f,-200.0f });

	Sprite::LoadTexture(24, L"Resources/lifegauge.png");
	PlayerHPGauge2 = Sprite::Create(24, { 0.0f,-200.0f });

	Sprite::LoadTexture(19, L"Resources/egggetcount.png");
	GetEggCount[0] = Sprite::Create(19, { 0.0f,-200.0f });

	Sprite::LoadTexture(20, L"Resources/egggetcount2.png");
	GetEggCount[1] = Sprite::Create(20, { 0.0f,-200.0f });

	Sprite::LoadTexture(21, L"Resources/egggetcountcount3.png");
	GetEggCount[2] = Sprite::Create(21, { 0.0f,-200.0f });

	Sprite::LoadTexture(22, L"Resources/egggetcount4.png");
	GetEggCount[3] = Sprite::Create(22, { 0.0f,-200.0f });
}
void GameUI::Update(Enemy* enemy[], TargetMarker* target)
{
	debugText->Print("", 950, 20, 3.0f);
	//�p�����[�^�̐ݒ�
	EnemyHPGaugePosition = { 100,870 };
	EnemyHPGauge2Position = { 80,860 };

	PlayerHPGaugePosition = { 100,60 };
	PlayerHPGauge2Position = { 80,40 };
	//�v���C���[�����ԋ߂��G�̗̑͂�\��
	/*����Draw()������enemys[target->GetNearIndex()]->Draw()�ɂ��Ă��������ǂ��ꂾ��scale�ϐ���
	�G�̐����p�ӂ��Ȃ��Ⴂ���Ȃ��̂ł߂�ǂ�����.*/
	
	EnemyHPGaugeScale = { enemy[target->GetNearIndex()]->GetHP() * 100,20 };
		
	EnemyHPGauge2Scale = { 1700,40 };

	PlayerHPGaugeScale = { 600,50 };

	PlayerHPGauge2Scale = { 800,90 };
	//
	Eggreport->SetPosition({ 1300,100 });
	Eggreport->SetSize({ 400,400 });
	for (int i = 0; i < 4; i++) {
		GetEggCount[i]->SetPosition({ 1670,240 });
		GetEggCount[i]->SetSize({ 100,100 });
	}
	EnemyHPGauge2->SetPosition(EnemyHPGauge2Position);
	EnemyHPGauge2->SetSize(EnemyHPGauge2Scale);
	EnemyHPGauge->SetPosition(EnemyHPGaugePosition);
	EnemyHPGauge->SetSize(EnemyHPGaugeScale);

	PlayerHPGauge2->SetPosition(PlayerHPGauge2Position);
	PlayerHPGauge2->SetSize(PlayerHPGauge2Scale);
	PlayerHPGauge->SetPosition(PlayerHPGaugePosition);
	PlayerHPGauge->SetSize(PlayerHPGaugeScale);
	hint1->SetPosition({ WinApp::window_width / 2,WinApp::window_height / 2 });
	
}

void GameUI::Draw(DirectXCommon*dxcomn,Enemy*enemy[],TargetMarker*target,Player*player)
{
	float distance = sqrtf(((hintspot1.x - player->GetPosition().x) * (hintspot1.x - player->GetPosition().x)) +
		((hintspot1.y - player->GetPosition().y) * (hintspot1.y - player->GetPosition().y)) +
		((hintspot1.z - player->GetPosition().z) * (hintspot1.z - player->GetPosition().z)));
	if (distance <= 10 && (hintscale.x <= 0 || hintscale.y <= 0)) {
		hintf = true;
	}
	if (hintf) {
		player->SetPosition({hintspot1.x,hintspot1.y,hintspot1.z - 15 });
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			hintf = false;
		}
		if (hintscale.x <= 500 && hintscale.y <= 500) {
			hintscale.x += 10.0f;
			hintscale.y += 10.0f;
		}
		
	}
	if (!hintf) {
		if (hintscale.x > 0 || hintscale.y >0) {
			hintscale.x -= 10.0f;
			hintscale.y -= 10.0f;
		}
	}
	hint1->SetSize({ hintscale });

	Sprite::PreDraw(dxcomn->GetCmdList());
	if (enemy[target->GetNearIndex()]->Distance(player) <= 30) {
		EnemyHPGauge2->Draw();
		EnemyHPGauge->Draw();
	}
	PlayerHPGauge2->Draw();
	PlayerHPGauge->Draw();
	hint1->SetAnchorPoint({ 0.5,0.5});
	hint1->Draw();
	for (int i = 0; i < 4; i++) {
		GetEggCount[i]->SetAnchorPoint({ 0.5,0.5 });
		//GetEggCount[i]->Draw();
	}
	GetEggCount[0]->Draw();
	Eggreport->Draw();

	Sprite::PostDraw(dxcomn->GetCmdList());

	
}