#pragma once

#include "fbxsdk.h"
#include "f_Model.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxLoader
{
private:
	using string = std::string;


public:
	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static FbxLoader* GetInstance();
	/// <summary>
	///������
	/// </summary>
	/// <param name="device">D3D12�f�o�C�X</param>
	void Initialize(ID3D12Device* device);
	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();
	/// <summary>
	/// �t�@�C������FBX���f���ǂݍ���
	/// </summary>
	/// <param name="modelName"></param>
	f_Model* LoadModelFromFile(const string modelName);

	/// <summary>
	/// �ċA�I�Ƀm�[�h�\�������
	/// </summary>
	/// <param name="modle"></param>
	/// <param name="fbxNode">��͑Ώۂ̃m�[�h</param>
	void ParseNodeRecursive(f_Model* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// ���b�V���ǂݎ��
	/// </summary>
	/// <param name="model">�ǂݍ��ݐ惂�f���I�u�W�F�N�g</param>
	/// <param name="fbxNode">��͑Ώۂ̃m�[�h</param>
	void ParseMesh(f_Model* model, FbxNode* fbxNode);

	/// <summary>
	/// FBX�̍s���XMMatrix�ɕϊ�
	/// </summary>
	/// <param name="dst">�������ݐ�</param>
	/// <param name="src">���ƂȂ�FBX�s��</param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);

	//���_���W�ǂݎ��
	void ParseMeshVertices(f_Model* model, FbxMesh* fbxMesh);
	//�ʐϏ��ǂݎ��
	void ParseMeshFaces(f_Model* model, FbxMesh* fbxMesh);
	//�}�e���A���ǂݎ��
	void ParseMaterial(f_Model* model, FbxNode* fbxNode);
	//�e�N�X�`���ǂݍ���
	void LoadTexture(f_Model* model, const std::string& fullpath);
	//�X�L�j���O���̓ǂݎ��
	void ParseSkin(f_Model* model, FbxMesh* fbxMesh);

	//�f�B���N�g�����܂񂾃t�@�C���p�X����t�@�C�����𒊏o����
	std::string ExtractFileName(const std::string& path);

private:
	// private�ȃR���X�g���N�^�i�V���O���g���p�^�[���j
	FbxLoader() = default;
	// private�ȃf�X�g���N�^�i�V���O���g���p�^�[���j
	~FbxLoader() = default;
	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	FbxLoader(const FbxLoader& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const FbxLoader& obj) = delete;

	//D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	//FBX�}�l�[�W��
	FbxManager* fbxManager = nullptr;
	//FBX�C���|�[�^
	FbxImporter* fbxImporter = nullptr;


public:
	static const string baseDirectory;
	//�e�N�X�`�����Ȃ��ꍇ�̕W���e�N�X�`���t�@�C����
	static const string defaultTextureFileName;
};