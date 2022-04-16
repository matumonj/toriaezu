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
//シーンのコンストラクタ
PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}

#pragma region スプライトの生成
//スプライト生成
void PlayScene::SpriteCreate()
{
	gameui = new GameUI();
	gameui->Initialize();
	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont2.png");
	Sprite::LoadTexture(1, L"Resources/0057b6fa9ec85ae.jpg");
	Sprite::LoadTexture(2, L"Resources/tyuta_C.png");

	//普通のテクスチャ(スプライトじゃないよ)
	Texture::LoadTexture(6, L"Resources/DQVDS_-_Mechanowyrm.png");
	Texture::LoadTexture(1, L"Resources/ball.png");
	background = Sprite::Create(1, { 0.0f,-200.0f });
	// デバッグテキスト初期化
	dxcomn = new DirectXCommon();
	debugText = new DebugTxt();
	debugText->Initialize(debugTextTexNumber);
	mech = Texture::Create(6, { 0,-2,20 }, { 2,2,2 }, { 1,1,1,1 });
	zukki = Texture::Create(1, { 0,-2,20 }, { 2,2,2 }, { 1,1,1,1 });
	mech->CreateTexture();
	zukki->CreateTexture();
}
#pragma endregion

#pragma region モデルとエフェクトとライトのインスタンス生成
void PlayScene::ModelCreate(DirectXCommon* dxcomn, DebugCamera* camera)
{
	model2 = Model::CreateFromOBJ("ground");
	yugudo = Model::CreateFromOBJ("skydome");
	playermodel = Model::CreateFromOBJ("chr_sword");

	//フィールドにモデル割り当て
	Field = TouchableObject::Create(model2,dxcomn,camera);
	//Field = Object3d::Create(dxcomn, camera);
	//Field->SetModel(model2);
	//天球
	yugudo3d = Object3d::Create(dxcomn, camera);
	yugudo3d->SetModel(yugudo);
	//プレイヤー
	player = Player::Create(playermodel, dxcomn, camera);
	
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);
	//パラメータの設定
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
	//FBX周り
	//モデル名を指定してファイル読み込み
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("Motti_idol");

	//デバイスをセット
	f_Object3d::SetDevice(dxcomn->GetDev());
	//カメラをセット
	f_Object3d::SetCamera(camera);
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();
	//FBXモデルの生成
	object1 = new f_Object3d();
	object1->Initialize(dxcomn,camera);
	object1->SetModel(fbxmodel);
	collisionManager = CollisionManager::GetInstance();
}
#pragma endregion

#pragma region 各パラメータのセット
void PlayScene::SetPrm()
{
	yugudo3d->SetPosition({ 0,30,0 });
	yugudo3d->SetScale({ 10,10,10 });

	//フィールド
	Field->SetPosition({ 0,-2,0 });
	Field->SetRotation({ 0,0,0 });
	//Field->SetScale({35,5,25 });
	
	//敵の体力と位置
	for (int i = 0; i < 3; i++) {
		enemys[i]->SetHP(10);
	}
	enemys[2]->SetPosition({ 0,-2,25 });
	enemys[1]->SetPosition({ 200,-2,25 });
	enemys[0]->SetPosition({ 200,-2,25 });
	//ライト
	spotLightpos[0] = 10;
	spotLightpos[2] = 0;
	spotLightpos[1] = 1000;
}
#pragma endregion

#pragma region オブジェクト+ライトの更新処理
void PlayScene::objUpdate(DirectXCommon* dxcomn, DebugCamera* camera)
{

	
	mech->SetPosition(texpo);
	mech->SetColor({ 1,0,0,1 });
	mech->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());
	zukki->Update(camera->GetViewMatrix(), camera->GetViewProjectionMatrix());

	{//ライトのパラメータを反映 	
		lightGroup->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		lightGroup->SetSpotLightPos(0, XMFLOAT3(spotLightpos));
		lightGroup->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		lightGroup->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		lightGroup->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	lightGroup->Update();
	//フィールド
	Field->Update({ 1,1,1,1 }, dxcomn, camera);
	//天球
	yugudo3d->Update({ 1,1,1,1 }, dxcomn, camera);
	//プレイヤー
	player->Update({ 1,1,1,1 }, dxcomn, camera);
	//ターゲットマーカー
	targetm->Update(enemys, this->camera, player);
	//UI系
	gameui->Update(enemys, targetm);
	//敵
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->Update(dxcomn, camera, player);
		}
	}
	
	// 全ての衝突をチェック
	
}
#pragma endregion

#pragma region 初期化
void PlayScene::Initialize(DirectXCommon* dxCommon)
{
	//敵へのターゲットマーカー
	targetm = new TargetMarker();
	targetm->Initialize();
	//ポストエフェクト
	c_postEffect = Default;
	//コライダー
	collision = new Collision();
	pobbcol = new OBBCollision();
	//ポストエフェクト
	postEffect = new PostEffect();
	postEffect->Initialize();

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height/*input*/);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	camera->SetEye({ Player_Pos.x,Player_Pos.y + 5,Player_Pos.z - 15 });
	
	SpriteCreate();//スプライトの生成呼び出し
	ModelCreate(dxCommon, camera);//モデル割当とかの呼び出し
	//プレイヤー
	player->Initialize(dxCommon, camera);
	SetPrm();//パラメータのセット	
}
#pragma endregion

#pragma region 更新処理
void PlayScene::Update(DirectXCommon* dxCommon)
{
	for (int i = 0; i < 3; i++) {
		enemys[i]->Distance(player);
	}
	Input::MouseMove mouseMove = Input::GetInstance()->GetMouseMove();
	//マウスの入力状態取得
	if (Input::GetInstance()->Pushkey(DIK_F)) {
		
	}
	//FBXのアニメーション再生
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
	
	//FBXモデルの更新
	object1->Updata({1,1,1,1},dxcomn,camera,TRUE);
	//カメラの移動(プレイヤーを中心に回る感じ)
	CameraPosition.x = player->GetPosition().x + cosf((float)(cameraAngle) * 3.14f / 180.0f) * 25;
	CameraPosition.z = player->GetPosition().z + sinf((float)(cameraAngle) * 3.14f / 180.0f) * 25;
	CameraPosition.y = player->GetPosition().y + 9;

	//カメラ関係の処理
	camera->SetDistance(distance);//距離
	camera->SetEye(CameraPosition);//位置
	camera->SetTarget({player->GetPosition().x,player->GetPosition().y,player->GetPosition().z});//注視点
	camera->Update();

	objUpdate(dxcomn, camera);//オブジェクトの更新処理
	
	//当たり判定の処理(OBB)後で分けたほうがいい
	//プレイヤーのOBB 回転ベクトル
	pobb.m_NormaDirect[0] = {player->GetMatrot().r[0].m128_f32[0],player->GetMatrot().r[0].m128_f32[1],player->GetMatrot().r[0].m128_f32[2] };
	pobb.m_NormaDirect[1] = { player->GetMatrot().r[1].m128_f32[0],player->GetMatrot().r[1].m128_f32[1],player->GetMatrot().r[1].m128_f32[2] };
	pobb.m_NormaDirect[2] = { player->GetMatrot().r[2].m128_f32[0],player->GetMatrot().r[2].m128_f32[1],player->GetMatrot().r[2].m128_f32[2] };
	pobb.m_fLength[0] = 1;//x方向の長さ
	pobb.m_fLength[1] = 1;//y方向の長さ
	pobb.m_fLength[2] = 1;//z方向の長さ
	//敵のOBB 回転ベクトル
	eobb.m_NormaDirect[0] = { enemys[2]->Getmatrot().r[0].m128_f32[0],enemys[2]->Getmatrot().r[0].m128_f32[1],enemys[2]->Getmatrot().r[0].m128_f32[2] };
	eobb.m_NormaDirect[1] = { enemys[2]->Getmatrot().r[1].m128_f32[0],enemys[2]->Getmatrot().r[1].m128_f32[1],enemys[2]->Getmatrot().r[1].m128_f32[2] };
	eobb.m_NormaDirect[2] = { enemys[2]->Getmatrot().r[2].m128_f32[0],enemys[2]->Getmatrot().r[2].m128_f32[1],enemys[2]->Getmatrot().r[2].m128_f32[2] };
	eobb.m_fLength[0] = 100;//x方向の長さ
	eobb.m_fLength[1] = 5;//y方向の長さ
	eobb.m_fLength[2] = 5;//z方向の長さ
	//OBBの設定位置
	pobb.m_Pos = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	eobb.m_Pos = { enemys[2]->GetPosition().x, enemys[2]->GetPosition().y, enemys[2]->GetPosition().z };
	
	if (pobbcol->ColOBBs(pobb,eobb)){
		obbf = 1;
	} else {
		obbf = 0;
	}
	//敵によるプレイヤーの検知
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->EnemySearchPlayer(player);
		}
	}
	//collisionManager->CheckAllCollisions();
	//シーンチェンジ
	if (Input::GetInstance()->TriggerKey(DIK_R)) {//押されたら
		BaseScene* scene = new TitleScene(sceneManager_);//次のシーンのインスタンス生成
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
}
#pragma endregion 

#pragma region モデルの描画
void PlayScene::SpriteDraw(ID3D12GraphicsCommandList* cmdList)
{
	//フィールド
	Field->PreDraw();
	Field->Draw();
	Field->PostDraw();
	
	//デバッグテキスト
	Sprite::PreDraw(cmdList);
	debugText->DrawAll(DirectXCommon::GetInstance()->GetCmdList());
	Sprite::PostDraw(cmdList);
}
//sプライと以外の描画
void PlayScene::MyGameDraw(DirectXCommon* dxcomn)
{
	SpriteDraw(dxcomn->GetCmdList());
	//プレイヤー
	player->PreDraw();
	player->Draw();
	player->PostDraw();
	//天球
	yugudo3d->PreDraw();
	yugudo3d->Draw();
	yugudo3d->PostDraw();
	//ターゲットマーカー
	Texture::PreDraw(dxcomn->GetCmdList());
	targetm->Draw(dxcomn);

	zukki->Draw();//ズッキーニャの画像
	mech->Draw();//メカバーンの画像
	
	Texture::PostDraw();
	//敵(プレイヤーとの距離が一定以下になったら描画)
	for (int i = 0; i < 3; i++) {
		if (enemys[i]->Distance(player) <= 70) {
			enemys[i]->Draw(dxcomn);
		}
	}
	//UI
	gameui->Draw(dxcomn,enemys,targetm,player);
	//普通のテクスチャの描画
	player->normalAttack(dxcomn,targetm,enemys,camera);
	//FBXの描画
	object1->Draw(dxcomn->GetCmdList());
}
#pragma endregion
//↓に入る
#pragma region 描画(imguiとスプライトとモデルまとめたもの)
void PlayScene::Draw(DirectXCommon* dxcomn)
{
	//ポストエフェクトの場合わけ(Bでぼかし Dがデフォルト)
	switch (c_postEffect)
	{
	case Blur://ぼかし　描画準違うだけ
		postEffect->PreDrawScene(dxcomn->GetCmdList());
		MyGameDraw(dxcomn);
		postEffect->PostDrawScene(dxcomn->GetCmdList());

		dxcomn->BeginDraw();
		postEffect->Draw(dxcomn->GetCmdList());
		ImGuiDraw();//imguiは最後の方入れとく
		dxcomn->EndDraw();
		break;

	case Default://普通のやつ特に何もかかっていない
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
#pragma region 解放部分
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