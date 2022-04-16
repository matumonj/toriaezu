#include "PlayScene.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"TitleScene.h"
#include"SceneManager.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"MeshCollider.h"
#include"TouchableObject.h"
#include"CollisionManager.h"
#include"SphereCollider.h"
#include"Player.h"
//�V�[���̃R���X�g���N�^
PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region �X�v���C�g�̐���
//�X�v���C�g����
void PlayScene::SpriteCreate()
{
	gameui = new GameUI();
	gameui->Initialize();
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	Sprite::LoadTexture(1, L"Resources/0057b6fa9ec85ae.jpg");
	Sprite::LoadTexture(2, L"Resources/tyuta_C.png");

	//���ʂ̃e�N�X�`��(�X�v���C�g����Ȃ���)
	Texture::LoadTexture(6, L"Resources/DQVDS_-_Mechanowyrm.png");
	Texture::LoadTexture(1, L"Resources/ball.png");
	background = Sprite::Create(1, { 0.0f,-200.0f });
	// �f�o�b�O�e�L�X�g������
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
	mech = Texture::Create(6, { 0,-2,20 }, { 2,2,2 }, { 1,1,1,1 });
	zukki = Texture::Create(1, { 0,-2,20 }, { 2,2,2 }, { 1,1,1,1 });
	mech->CreateTexture();
	zukki->CreateTexture();
}
#pragma endregion

#pragma region ���f���ƃG�t�F�N�g�ƃ��C�g�̃C���X�^���X����
void PlayScene::ModelCreate(DirectXCommon* dxcomn, DebugCamera* camera)
{
	model2 = Model::CreateFromOBJ("ground");
	yugudo = Model::CreateFromOBJ("skydome");
	playermodel = Model::CreateFromOBJ("chr_sword");

	//�t�B�[���h�Ƀ��f�����蓖��
	Field = TouchableObject::Create(model2,dxcomn,camera);
	//Field = Object3d::Create(dxcomn, camera);
	//Field->SetModel(model2);
	//�V��
	yugudo3d = Object3d::Create(dxcomn, camera);
	yugudo3d->SetModel(yugudo);
	//�v���C���[
	player = Player::Create(playermodel, dxcomn, camera);
	
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);
	//�p�����[�^�̐ݒ�
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);
	//pointLightPos[0] = 0.0f;
	//pointLightPos[1] = 1.0f;
	//pointLightPos[2] = 0.0f;
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	lightGroup->SetPointLightActive(2, false);
	lightGroup->SetSpotLightActive(0, true);

	enemys[0] = new MobEnemy();
	enemys[1] = new MobEnemy();
	enemys[2] = new MobEnemy();
	for (int i = 0; i < 3; i++) {
		enemys[i]->Initialize(dxcomn, camera);
	}
	//FBX����
	//���f�������w�肵�ăt�@�C���ǂݍ���
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("Motti_idol");

	//�f�o�C�X���Z�b�g
	f_Object3d::SetDevice(dxcomn->GetDev());
	//�J�������Z�b�g
	f_Object3d::SetCamera(camera);
	//�O���t�B�b�N�p�C�v���C������
	f_Object3d::CreateGraphicsPipeline();
	//FBX���f���̐���
	object1 = new f_Object3d();
	object1->Initialize(dxcomn,camera);
	object1->SetModel(fbxmodel);
	collisionManager = CollisionManager::GetInstance();
}
#pragma endregion

#pragma region �e�p�����[�^�̃Z�b�g
void PlayScene::SetPrm()
{
	yugudo3d->SetPosition({ 0,30,0 });
	yugudo3d->SetScale({ 10,10,10 });

	//�t�B�[���h
	Field->SetPosition({ 0,-2,0 });
	Field->SetRotation({ 0,0,0 });
	//Field->SetScale({35,5,25 });
	
	//�G�̗̑͂ƈʒu
	for (int i = 0; i < 3; i++) {
		enemys[i]->SetHP(10);
	}
	enemys[2]->SetPosition({ 0,-2,25 });
	enemys[1]->SetPosition({ 200,-2,25 });
	enemys[0]->SetPosition({ 200,-2,25 });
	//���C�g
	spotLightpos[0] = 10;
	spotLightpos[2] = 0;
	spotLightpos[1] = 1000;
}
#pragma endregion

#pragma region �I�u�W�F�N�g+���C�g�̍X�V����
void PlayScene::objUpdate(DirectXCommon* dxcomn, DebugCamera* camera)
{

	
	mech->SetPosition(texpo);
	mech->SetColor({ 1,0,0,1 });
	mech->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());
	zukki->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());

	{//���C�g�̃p�����[�^�𔽉f 	
		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	lightGroup->Update();
	//�t�B�[���h
	Field->Update({ 1,1,1,1 }, dxcomn, camera);
	//�V��
	yugudo3d->Update({ 1,1,1,1 }, dxcomn, camera);
	//�v���C���[
	player->Update({ 1,1,1,1 }, dxcomn, camera);
	//�^�[�Q�b�g�}�[�J�[
	targetm->Update(enemys, this->camera, player);
	//UI�n
	gameui->Update(enemys, targetm);
	//�G
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->Update(dxcomn, camera, player);
		}
	}
	
	// �S�Ă̏Փ˂��`�F�b�N
	
}
#pragma endregion

#pragma region ������
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//�G�ւ̃^�[�Q�b�g�}�[�J�[
	targetm = new TargetMarker();
	targetm->Initialize();
	//�|�X�g�G�t�F�N�g
	c_postEffect = Default;
	//�R���C�_�[
	collision = new Collision();
	pobbcol = new OBBCollision();
	//�|�X�g�G�t�F�N�g
	postEffect = new PostEffect();
	postEffect->Initialize();

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	camera->SetEye({ Player_Pos.x,Player_Pos.y + 5,Player_Pos.z - 15 });
	
	SpriteCreate();//�X�v���C�g�̐����Ăяo��
	ModelCreate(dxCommon, camera);//���f�������Ƃ��̌Ăяo��
	//�v���C���[
	player->Initialize(dxCommon, camera);
	SetPrm();//�p�����[�^�̃Z�b�g	
}
#pragma endregion

#pragma region �X�V����
void PlayScene::Update(DirectXCommon* dxCommon)
{
	for (int i = 0; i < 3; i++) {
		enemys[i]->Distance(player);
	}
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//�}�E�X�̓��͏�Ԏ擾
	if (Input::GetInstance()->Pushkey(DIK_F)) {
		
	}
	//FBX�̃A�j���[�V�����Đ�
	if (Input::GetInstance()->Pushkey(DIK_0)) {
		object1->PlayAnimation();
	}
	if (Input::GetInstance()->Pushkey(DIK_RIGHT)) {
		charaAngle += 0.5f;
		cameraAngle -= 0.5f;
		player->SetCharaRotation(charaAngle);
	} else if (Input::GetInstance()->Pushkey(DIK_LEFT)) {
		cameraAngle += 0.5f;
		charaAngle -= 0.5f;
		player->SetCharaRotation(charaAngle);
	}
	
	//FBX���f���̍X�V
	object1->Updata({1,1,1,1},dxcomn,camera,TRUE);
	//�J�����̈ړ�(�v���C���[�𒆐S�ɉ�銴��)
	CameraPosition.x = player->GetPosition().x + cosf((float)(cameraAngle) * 3.14f / 180.0f) * 25;
	CameraPosition.z = player->GetPosition().z + sinf((float)(cameraAngle) * 3.14f / 180.0f) * 25;
	CameraPosition.y = player->GetPosition().y + 9;

	//�J�����֌W�̏���
	camera->SetDistance(distance);//����
	camera->SetEye(CameraPosition);//�ʒu
	camera->SetTarget({player->GetPosition().x,player->GetPosition().y,player->GetPosition().z});//�����_
	camera->Update();

	objUpdate(dxcomn, camera);//�I�u�W�F�N�g�̍X�V����
	
	//�����蔻��̏���(OBB)��ŕ������ق�������
	//�v���C���[��OBB ��]�x�N�g��
	pobb.m_NormaDirect[0] = {player->GetMatrot().r[0].m128_f32[0],player->GetMatrot().r[0].m128_f32[1],player->GetMatrot().r[0].m128_f32[2] };
	pobb.m_NormaDirect[1] = { player->GetMatrot().r[1].m128_f32[0],player->GetMatrot().r[1].m128_f32[1],player->GetMatrot().r[1].m128_f32[2] };
	pobb.m_NormaDirect[2] = { player->GetMatrot().r[2].m128_f32[0],player->GetMatrot().r[2].m128_f32[1],player->GetMatrot().r[2].m128_f32[2] };
	pobb.m_fLength[0] = 1;//x�����̒���
	pobb.m_fLength[1] = 1;//y�����̒���
	pobb.m_fLength[2] = 1;//z�����̒���
	//�G��OBB ��]�x�N�g��
	eobb.m_NormaDirect[0] = { enemys[2]->Getmatrot().r[0].m128_f32[0],enemys[2]->Getmatrot().r[0].m128_f32[1],enemys[2]->Getmatrot().r[0].m128_f32[2] };
	eobb.m_NormaDirect[1] = { enemys[2]->Getmatrot().r[1].m128_f32[0],enemys[2]->Getmatrot().r[1].m128_f32[1],enemys[2]->Getmatrot().r[1].m128_f32[2] };
	eobb.m_NormaDirect[2] = { enemys[2]->Getmatrot().r[2].m128_f32[0],enemys[2]->Getmatrot().r[2].m128_f32[1],enemys[2]->Getmatrot().r[2].m128_f32[2] };
	eobb.m_fLength[0] = 100;//x�����̒���
	eobb.m_fLength[1] = 5;//y�����̒���
	eobb.m_fLength[2] = 5;//z�����̒���
	//OBB�̐ݒ�ʒu
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	eobb.m_Pos = { enemys[2]->GetPosition().x, enemys[2]->GetPosition().y, enemys[2]->GetPosition().z };
	
	if (pobbcol->ColOBBs(pobb,eobb)){
		obbf = 1;
	} else {
		obbf = 0;
	}
	//�G�ɂ��v���C���[�̌��m
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->EnemySearchPlayer(player);
		}
	}
	//collisionManager->CheckAllCollisions();
	//�V�[���`�F���W
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//�����ꂽ��
		BaseScene* scene = new TitleScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
}
#pragma endregion 

#pragma region ���f���̕`��
void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	//�t�B�[���h
	Field->PreDraw();
	Field->Draw();
	Field->PostDraw();
	
	//�f�o�b�O�e�L�X�g
	Sprite::PreDraw(cmdList);
	debugText->DrawAll(DirectXCommon::GetInstance()->GetCmdList());
	Sprite::PostDraw(cmdList);
}
//s�v���C�ƈȊO�̕`��
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	SpriteDraw(dxcomn->GetCmdList());
	//�v���C���[
	player->PreDraw();
	player->Draw();
	player->PostDraw();
	//�V��
	yugudo3d->PreDraw();
	yugudo3d->Draw();
	yugudo3d->PostDraw();
	//�^�[�Q�b�g�}�[�J�[
	Texture::PreDraw(dxcomn->GetCmdList());
	targetm->Draw(dxcomn);

	zukki->Draw();//�Y�b�L�[�j���̉摜
	mech->Draw();//���J�o�[���̉摜
	
	Texture::PostDraw();
	//�G(�v���C���[�Ƃ̋��������ȉ��ɂȂ�����`��)
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->Draw(dxcomn);
		}
	}
	//UI
	gameui->Draw(dxcomn,enemys,targetm,player);
	//���ʂ̃e�N�X�`���̕`��
	player->normalAttack(dxcomn,targetm,enemys,camera);
	//FBX�̕`��
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//���ɓ���
#pragma region �`��(imgui�ƃX�v���C�g�ƃ��f���܂Ƃ߂�����)
void PlayScene::Draw(DirectXCommon* dxcomn)
{
	//�|�X�g�G�t�F�N�g�̏ꍇ�킯(B�łڂ��� D���f�t�H���g)
	switch (c_postEffect)
	{
	case Blur://�ڂ����@�`�揀�Ⴄ����
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		MyGameDraw(dxcomn);
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		postEffect->Draw(dxcomn->GetCmdList());
		ImGuiDraw();//imgui�͍Ō�̕�����Ƃ�
		dxcomn->EndDraw();
		break;

	case Default://���ʂ̂���ɉ����������Ă��Ȃ�
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		postEffect->Draw(dxcomn->GetCmdList());
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		MyGameDraw(dxcomn);
		ImGuiDraw();
		dxcomn->EndDraw();
		break;
	}
}
#pragma endregion

void PlayScene::ImGuiDraw()
{
	{
		ImGui::Begin("Obj1");
		ImGui::SetWindowPos(ImVec2(0, 500));
		ImGui::SetWindowSize(ImVec2(500, 300));
		if (ImGui::TreeNode("light_position")) {
			ImGui::SliderFloat("positionX", &spotLightpos[0], -100, 100);
			ImGui::SliderFloat("positionY", &spotLightpos[1], -100, 100);
			ImGui::SliderFloat("positionZ", &spotLightpos[2], -100, 100);
			if (ImGui::Button("spotlight ON")) {
				lightGroup->SetSpotLightActive(0, true);
			}
			if (ImGui::Button("spotlight OFF")) {
				lightGroup->SetSpotLightActive(0, false);
			}
			ImGui::ColorPicker3("light_color", spotLightColor);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Boss_position")) {
			ImGui::SliderFloat("positionX", &Boss_Pos.x, -100, 100);
			ImGui::SliderFloat("positionY", &Boss_Pos.y, -100, 100);
			ImGui::SliderFloat("positionZ", &Boss_Pos.z, -100, 100);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Effect_position")) {
			ImGui::SliderFloat("positionX", &efkposition.x, -100, 100);
			ImGui::SliderFloat("positionY", &efkposition.y, -100, 100);
			ImGui::SliderFloat("positionZ", &efkposition.z, -100, 100);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Texture_position")) {
			ImGui::SliderFloat("positionX", &texpo.x, -100, 100);
			ImGui::SliderFloat("positionY", &texpo.y, -100, 100);
			ImGui::SliderFloat("positionZ", &texpo.z, -100, 100);
			ImGui::TreePop();
		}
		ImGui::End();
	}
	//
	{
		ImGui::Begin("postEffect");
		if (ImGui::RadioButton("Blur", &c_postEffect)) {
			c_postEffect = Blur;
		}
		if (ImGui::RadioButton("Default", &c_postEffect)) {
			c_postEffect = Default;
		}
		ImGui::End();
	}
	//
	{
		ImGui::Begin("Target");
		float j = player->GetPosition().x;
		float o = player->GetPosition().y;
		float p = player->GetPosition().z;
		int nowTargetindex = targetm->GetNearIndex();
		float angle = cameraAngle;

		if (ImGui::TreeNode("Distance")) {
			ImGui::SliderFloat("MobDistance", &j, 0, 90);
			ImGui::SliderFloat("BossDistance", &o, -10, 50);
			ImGui::SliderFloat("Mob2Distance", &p, -10, 50);
			ImGui::TreePop();
		}

		ImGui::SliderInt("HitFlag", &obbf, -10, 50);
		ImGui::SliderInt("noeTargetEnemy", &nowTargetindex, -10, 50);
		ImGui::End();
	}
	//
	{
		unsigned long current_time = timeGetTime();
		float fps = float(count_frame) / (current_time - prev_time) * 1000;
		ImGui::SliderFloat("FPS", &fps, -10, 50);
		count_frame++;
		ImGui::End();
	}
}
#pragma region �������
void PlayScene::Finalize()
{
	//delete efk,efk1;
	delete mech, zukki;
	delete model, model5, model2;
	delete player;
	delete Boss;
	delete Field;
	delete debugText;
	delete collision;
	delete lightGroup;
	delete camera;
	delete background;
	delete enemys[0], enemys[1];
	delete yugudo3d;
	delete targetm;
	delete object1, fbxmodel;
	delete gameui;
}
#pragma endregion