#include "TitleScene.h"
#include"Input.h"
#include"PlayScene.h"
#include"SceneManager.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize(DirectXCommon* dxCommon)
{
	Sprite::LoadTexture(3, L"Resources/background.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });
}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update(DirectXCommon* dxCommon)
{
	//ENTER�Ŏ��̃V�[����
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {//�����ꂽ��
		BaseScene* scene = new PlayScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
	titlesprite->SetSize({ WinApp::window_width,WinApp::window_height });
}

/// <summary>
/// �X�v���C�g�`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	Sprite::PreDraw(cmdList);
	titlesprite->Draw();
	Sprite::PostDraw(cmdList);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw(DirectXCommon* dxcomn)
{
	//�|�X�g�G�t�F�N�g�̕`��
	dxcomn->BeginDraw();//�`��R�}���h�̏��ւ��
	SpriteDraw(dxcomn->GetCmdList());
	dxcomn->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}