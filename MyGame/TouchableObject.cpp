#include "TouchableObject.h"
#include "MeshCollider.h"
#include"CollisionAttribute.h"
TouchableObject* TouchableObject::Create(Model* model, DirectXCommon* dxcomn, DebugCamera* camera)
{
	// �I�u�W�F�N�g�̃C���X�^���X�𐶐�
	TouchableObject* instance = new TouchableObject();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
	if (!instance->Initialize(model, dxcomn, camera)) {
		delete instance;
		assert(0);
	}

	return instance;
}

bool TouchableObject::Initialize(Model* model, DirectXCommon* dxcomn, DebugCamera* camera)
{
	if (!Object3d::Initialize(dxcomn, camera))
	{
		return false;
	}

	SetModel(model);

	// �R���C�_�[�̒ǉ�
	MeshCollider* collider = new MeshCollider;
	SetCollider(collider);
	collider->ConstructTriangles(model);
	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
	return true;
}
