//#include "Effects.h"
//
//void Effects::Initialize(DirectXCommon* dxcomn, DebugCamera* camera)
//{
//	//�G�t�F�N�g�̃C���X�^���X����
//	efk = new mEffekseer();
//	efk1 = new mEffekseer();
//
//	//�G�t�F�N�g�̃Z�b�g(3��������)
//	efk->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/thunder.efk", (const EFK_CHAR*)L"effect/10");
//	efk1->EffekseerSetting(dxcomn, camera, (const EFK_CHAR*)L"Effect/10/SimpleLaser.efk", (const EFK_CHAR*)L"effect/10");
//}
//
//void Effects::Update(DirectXCommon* dxcomn, DebugCamera* camera)
//{
//	//�G�t�F�N�g�̃p�����[�^�Z�b�g
//	efk->SetPosition(Effect_Pos.x, Effect_Pos.y, Effect_Pos.z);
//	efk->SetRotation(0, 0, 0);
//	efk->SetScale(1, 1, 1);
//	efk1->SetPosition(-10, 0, 190);
//
//	//�G�t�F�N�g�̍Đ�
//	//if (Input::GetInstance()->Pushkey(DIK_SPACE)) {
//	efk->Load_Effect();
//	//}
//	efk1->Load_Effect();
//
//	//�G�t�F�N�g�̃A�j���[�V�����~�߂�
//	if (Input::GetInstance()->Pushkey(DIK_C)) {
//		efk->Stop_Effect();
//	}
//
//	//view,projection�s����G�t�F�N�g�̃e�N�X�`���ɂ�����
//	efk->EffekseerUpdate(dxcomn, camera);
//	efk1->EffekseerUpdate(dxcomn, camera);
//
//}
//
//void Effects::Draw(DirectXCommon* dxcomn)
//{
//	//�G�t�F�N�g�̉摜
//	efk->EffekseerDraw(dxcomn->GetCmdList());
//	efk1->EffekseerDraw(dxcomn->GetCmdList());
//}