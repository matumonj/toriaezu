#include "SceneManager.h"

/// <summary>
/// �X�V
/// </summary>
void SceneManager::Update(DirectXCommon* dxCommon)
{
	if (nextScene) {
		if (Scene) {//�O�̃V�[����j��
			Scene->Finalize();
			delete Scene;
		}
		//���̃V�[���ֈڍs
		Scene = nextScene;
		nextScene = nullptr;

		Scene->Initialize(dxCommon);//�ڍs�����珉����
	}
	//�X�V
	Scene->Update(dxCommon);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void SceneManager::Draw(DirectXCommon* dxcomn)
{
	Scene->Draw(dxcomn);
}
