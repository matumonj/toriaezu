#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class OBB
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	XMVECTOR m_Pos;              // �ʒu
	XMVECTOR m_NormaDirect[3];   // �����x�N�g�� ��]�x�N�g���ł�����
	float m_fLength[3];             // �e�������̒���

public:
	XMVECTOR GetDirect(int elem) { return m_NormaDirect[elem]; }   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem) { return m_fLength[elem]; }          // �w�莲�����̒������擾
	XMVECTOR GetPos_W() { return m_Pos; }
};