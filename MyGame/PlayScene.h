#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"mEffekseer.h"
#include "FbxLoader.h"
#include "f_Object3d.h"
#include"Texture.h"
#include"PostEffect.h"
#include"Enemy.h"
#include"Effects.h"
#include"TargetMarker.h"
#include"GameUI.h"
#include"OBBCollision.h"

#pragma comment(lib,"winmm.lib")
class TouchableObject;
class CollisionManager;
class Player;
class PlayScene :public BaseScene
{
public:
	//�V�[���̃R���X�g���N�^
	PlayScene(SceneManager* sceneManager);
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	const float window_width = 1900;
	const float window_height = 1020;
	static const int debugTextTexNumber = 0;

private:
	int obbf = 0;
	unsigned long prev_time = timeGetTime();
	int count_frame = 0;
	TargetMarker* targetm = nullptr;
	GameUI* gameui = nullptr;
	float ty;
	float cameraAngle = -90;
	float charaAngle = 0;
	XMFLOAT3 CameraPosition;

	DirectXCommon* dxcomn;
	Sprite* background = nullptr;
	Texture* mech = nullptr;
	Texture* zukki = nullptr;
	DebugTxt* debugText;
	OBB pobb;// = nullptr;
	OBB eobb;// = nullptr;
	OBBCollision* pobbcol = nullptr;
	Collision* collision = nullptr;

	Player* player = nullptr;
	Object3d* Boss = nullptr;
	TouchableObject* Field = nullptr;
	Object3d* yugudo3d = nullptr;


	Model* playermodel = nullptr;
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* model5;
	Model* yugudo = nullptr;
	
	PostEffect* postEffect = nullptr;
	DebugCamera* camera;

	Enemy* enemys[3];
	//Effects* effects;
private:
	XMFLOAT3 Player_Pos;// = player->GetPosition();
	XMFLOAT3 Player_Rot;// = player->GetRotation();

	XMFLOAT3 Boss_Pos;// = Boss->GetPosition();
	XMFLOAT3 Boss_Scl;// = Boss->GetScale();
	XMFLOAT3 Boss_Rot;// = { 0,180,0 };

	float distance = 30;

	float dy;
	float dx;
	float dz;

private://�_����
	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,-50 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.05f,0.05f,0.05f };

	int SpotLightflag = false;
private://�X�|�b�g���C�g
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightpos[3] = { 0,5,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f,30.0f };

public:
	void SpriteCreate();
	void ModelCreate(DirectXCommon* dxcomn, DebugCamera* camera);
	void MyGameDraw(DirectXCommon* dxcomn);
	void SetPrm();
	void objUpdate(DirectXCommon* dxcomn, DebugCamera* camera);

public:
	XMFLOAT3 texpo = { 0,0,0 };
	void Initialize(DirectXCommon* dxCommon)override;
	void Update(DirectXCommon* dxCommon)override;
	void Draw(DirectXCommon* dxcomn)override;
	void PreBackGround(ID3D12GraphicsCommandList* cmdList);
	void BackGround(ID3D12GraphicsCommandList* cmdList);

	void PostBackGround(ID3D12GraphicsCommandList* cmdList);
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList);
	void ImGuiDraw();
	void Finalize()override;

public:
	XMFLOAT3 efkposition = { -50,-10,90 };
	//�G�t�F�N�g�p(�����v���O�����ł������̂̓v���O�����ō����������@���p�͂����Ȃ�)

	f_Model* fbxmodel = nullptr;
	f_Object3d* object1 = nullptr;

	int c_postEffect;
private:
	enum {
		Blur,
		Default,
	};
	CollisionManager* collisionManager = nullptr;
};

