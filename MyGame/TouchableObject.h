#pragma once
#include "Object3d.h"
class TouchableObject :
	public Object3d
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static TouchableObject* Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera);

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize(Model* model, DirectXCommon* dxcomn, DebugCamera* camera);

	/// <summary>
	/// �X�P�[���̐ݒ�
	/// </summary>
	/// <param name="position">�X�P�[��</param>
	inline void SetScale(float scale) { this->scale = { scale,scale,scale }; }
	void SetScale(XMFLOAT3 scale) = delete;
};

