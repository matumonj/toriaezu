#pragma once

#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "Object3d.h"

/// <summary>
/// �R���C�_�[���N���X
/// </summary>
class BaseCollider
{
public:
	friend class CollisionManager;

	inline void SetAttribute(unsigned short attribute) {
		this->attribute = attribute;
	}
	inline void AddAttribute(unsigned short attribute) {
		this->attribute |= attribute;
	}
	inline void RemoveAttribute(unsigned short attribute) {
		this->attribute &= !attribute;
	}

protected:
	//�����蔻�葮��
	unsigned short attribute = 0b1111111111111111;

public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d* object) {
		this->object3d = object;
	}

	inline Object3d* GetObject3d() {
		return object3d;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	inline void OnCollision(const CollisionInfo& info) {
		object3d->OnCollision(info);
	}

protected:
	Object3d* object3d = nullptr;
	// �`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

