#pragma once
#include"BaseScene.h"
class SceneManager
{
public:
	//�X�V
	void Update(DirectXCommon* dxCommon);
	//�`��
	void Draw(DirectXCommon* dxcomn);
	//���̃V�[���ֈڍs���邽�߂̃Z�b�^�[
	void SetnextScene(BaseScene* nextScene_) { nextScene = nextScene_; }

	void Finalize();
private:
	BaseScene* Scene;
	BaseScene* nextScene = nullptr;
};

