//#include "mEffekseer.h"
//
////�J�����ݒ�
//void mEffekseer::SyncronizeEffekseerCamera(DirectXCommon* dxCommon, DebugCamera* camera)
//{
//	Effekseer::Matrix44 fkViewMat;
//	Effekseer::Matrix44 fkProjMat;
//	auto view = camera->GetViewMatrix();//�J�����̃Z�b�g
//	auto proj = camera->GetProjectionMatrix();//�ˉe�A�������e����
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			fkViewMat.Values[i][j] = view.r[i].m128_f32[j];
//			fkProjMat.Values[i][j] = proj.r[i].m128_f32[j];
//		}
//	}
//	_efkRenderer->SetCameraMatrix(fkViewMat);
//	_efkRenderer->SetProjectionMatrix(fkProjMat);
//}
//
//void mEffekseer::EffekseerSetting(DirectXCommon* dxCommon, DebugCamera* camera, const EFK_CHAR* name1, const EFK_CHAR* name2)
//{
//	//�Ƃ肠�����͂��̂܂�
//	DXGI_FORMAT bbFormats[] = { DXGI_FORMAT_R8G8B8A8_UNORM };
//	_efkRenderer = EffekseerRendererDX12::Create(
//		dxCommon->GetDev(),//�f�o�C�X
//		dxCommon->GetcmdQue(), //�R�}���h�L���[
//		2, //�o�b�N�o�b�t�@�̐�
//		bbFormats, //�����_�[�^�[�Q�b�g�t�H�[�}�b�g
//		1, //�����_�[�^�[�Q�b�g��
//		DXGI_FORMAT_UNKNOWN, //�f�v�X�t�H�[�}�b�g
//		false, //���΃f�v�X���肩
//		1000);//�ő�p�[�e�B�N���̐� �ł���΂T�O�O���炢�����������@�P�O�O�O�O���ƕ����̎��d���Ȃ肻��
//
//	_efkManager = Effekseer::Manager::Create(1000);//�ő�C���X�^���X��
//
//	//����n��
//	_efkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
//
//	// �`��p�C���X�^���X����`��@�\��ݒ�
//	_efkManager->SetSpriteRenderer(_efkRenderer->CreateSpriteRenderer());
//	_efkManager->SetRibbonRenderer(_efkRenderer->CreateRibbonRenderer());
//	_efkManager->SetRingRenderer(_efkRenderer->CreateRingRenderer());
//	_efkManager->SetTrackRenderer(_efkRenderer->CreateTrackRenderer());
//	_efkManager->SetModelRenderer(_efkRenderer->CreateModelRenderer());
//
//	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ�
//	_efkManager->SetTextureLoader(_efkRenderer->CreateTextureLoader());
//	_efkManager->SetModelLoader(_efkRenderer->CreateModelLoader());
//
//	//DX12���L�̏���
//	_efkMemoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(_efkRenderer->GetGraphicsDevice());
//	_efkCmdList = EffekseerRenderer::CreateCommandList(_efkRenderer->GetGraphicsDevice(), _efkMemoryPool);
//	_efkRenderer->SetCommandList(_efkCmdList);
//
//
//	SyncronizeEffekseerCamera(dxCommon, camera);
//	// �G�t�F�N�g�̓Ǎ�
//	//_effect = Effekseer::Effect::Create(_efkManager, (const EFK_CHAR*)L"Effect/10/SimpleLaser.efk", 1.0f, (const EFK_CHAR*)L"effect/10");
//	_effect = Effekseer::Effect::Create(_efkManager, name1, 1.0f, name2);
//
//	// �G�t�F�N�g�̍Đ�
//	//_efkHandle = _efkManager->Play(_effect, 10, 5, 0);
//
//}
//
//void mEffekseer::Load_Effect()//playscene�Ƃ��Ŏg����悤��
//{
//	_efkManager->SetSpeed(_efkHandle, 0.5f);
//	_efkManager->SetScale(_efkHandle, 5,5,5 );
//	_efkHandle = _efkManager->Play(_effect,{ positionx, positiony, positionz
//}, 1);
//}
//
//void mEffekseer::Stop_Effect()
//{
//_efkManager->Release();
//	//_efkManager->Exists(_efkHandle);
//	//_efkManager->StopEffect(_efkHandle);
//	//}
//
//	// _efkManager = nullptr;
//}
//
//
//void mEffekseer::EffekseerUpdate(DirectXCommon* dxCommon, DebugCamera* camera)
//{
//	//if (Input::GetInstance()->Pushkey(DIK_SPACE)) {
//		// �G�t�F�N�g�̍Đ�
//
//	//_efkHandle = _efkManager->Play(_effect, positionx, positiony, positionz);
//	_efkManager->SetScale(_efkHandle, scalex, scaley, scalez);
//	_efkManager->SetRotation(_efkHandle, rotationx, rotationy, rotationz);
//	SyncronizeEffekseerCamera(dxCommon, camera);
//	
//	auto efkpos = _efkManager->GetLocation(_efkHandle);
//	efkpos.X +=0.1f;
//	
//		_efkManager->SetLocation(_efkHandle, efkpos);
//
//}
//
//void mEffekseer::EffekseerDraw(ID3D12GraphicsCommandList* cmdList)
//{
//	//�G�t�F�N�g�`��
//	_efkManager->Update();//�}�l�[�W���̍X�V
//	_efkMemoryPool->NewFrame();//�K�؂ȃo�b�N�o�b�t�@��I��
//	EffekseerRendererDX12::BeginCommandList(_efkCmdList, cmdList);//
//	_efkRenderer->BeginRendering();//�`��O����
//	_efkManager->Draw();//�G�t�F�N�g�`��
//	_efkRenderer->EndRendering();//�`��㏈��
//	EffekseerRendererDX12::EndCommandList(_efkCmdList);
//}
