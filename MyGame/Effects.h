//#pragma once
//#include <Windows.h>
//#include <wrl.h>
//#include <d3d12.h>
//#include <d3dx12.h>
//#include <DirectXMath.h>
//#include <string>
//#include"mEffekseer.h"
//#include"DirectXCommon.h"
//#include"DebugCamera.h"
//class Effects
//{
//private:
//	//Microosoft::WRL::���ȗ�
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	//DirectX::���ȗ�
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//
//private:
//	//�G�t�F�N�g�p(�����v���O�����ł������̂̓v���O�����ō����������@���p�͂����Ȃ�)
//	mEffekseer* efk = nullptr;
//	mEffekseer* efk1 = nullptr;
//
//public:
//	//XMFLOAT3 GetPosition
//	XMFLOAT3 Effect_Pos = { -50,-10,90 };
//	XMFLOAT3 Effect_Rot;
//	XMFLOAT3 Effect_SCl;
//
//public:
//	void Initialize(DirectXCommon* dxcomn, DebugCamera* camera);
//	void Update(DirectXCommon* dxcomn, DebugCamera* camera);
//	void Draw(DirectXCommon* dxcomn);
//	void Finalize();
//
//	XMFLOAT3 GetPos() { return Effect_Pos; }
//};
//
