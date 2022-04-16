#include "Framework.h"

void Framework::Run()
{
	Initialize(dxcomn);

	while (true) {
		//�E�B���h�E���b�Z�[�W����
		Update(dxcomn);

		//�I�����N�G�X�g�������甲����
		if (IsEndRequst()) {
			break;
		}

		Draw(dxcomn);
	}
	//Finalize();
}
/// <summary>
/// ������
/// </summary>
void Framework::Initialize(DirectXCommon* dxCommon)
{
	//���ʕ����̃C���X�^���X�����Ə�����
	winapp = new WinApp();
	winapp->Createwindow();
	dxcomn = new DirectXCommon();
	dxcomn->Initialize(winapp);
	input = Input::GetInstance();
	input->Initialize(winapp);
	audio = new Audio();

	// ���C�g�ÓI������
	Object3d::StaticInitialize(dxcomn->GetDev(), dxcomn->GetCmdList(), WinApp::window_width, WinApp::window_height);
	//MyGame* MyGame = new MyGame();
	sceneManger = new SceneManager();
}

/// <summary>
/// �X�V
/// </summary>
void Framework::Update(DirectXCommon* dxCommon)
{
	if (winapp->Processmassage()) {
		winRequest = true;
		return;
	}
	input->update();
	sceneManger->Update(dxCommon);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void Framework::Draw(DirectXCommon* dxcomn)
{
	sceneManger->Draw(dxcomn);
}

void Framework::Finalize()
{
	FbxLoader::GetInstance()->Finalize();
	delete sceneManger;
	delete audio;
	delete dxcomn;
	delete input;
	delete winapp;
}