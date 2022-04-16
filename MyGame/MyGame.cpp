#include "MyGame.h"
#include"SceneManager.h"
void MyGame::Initialize(DirectXCommon* dxCommon)
{
	Framework::Initialize(dxCommon);
	Sprite::StaticInitialize(dxcomn->GetDev(), WinApp::window_width, WinApp::window_height);
	LightGroup::StaticInitialize(dxcomn->GetDev());
	FbxLoader::GetInstance()->Initialize(dxcomn->GetDev());
	Texture::StaticInitialize(dxcomn->GetDev(), WinApp::window_width, WinApp::window_height);
	//Scene = new TitleScene();
	//�����V�[��
	BaseScene* scene_ = new TitleScene(sceneManger);
	sceneManger->SetnextScene(scene_);

	//Scene->Initialize();
}

void MyGame::Update(DirectXCommon* dxCommon)
{
	Framework::Update(dxCommon);
}


void MyGame::Draw(DirectXCommon* dxcomn)
{
	Framework::Draw(dxcomn);
}


//�w�i�X�v���C�g�`��@�����߂�ǂ��������� clearDepthBuffer()��݂��ނ���
void MyGame::backGround()
{
	//->BackGround(dxcomn->GetCmdList());
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	//Scene->SpritePost(dxcomn->GetCmdList());
}
void MyGame::Finalize()
{
	Framework::Finalize();
}
