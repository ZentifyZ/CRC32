#pragma once

enum BoneHitbox : int
{
	hhead = 698017942,
	sstomach = -523945340,
	cchest = 827230707,
	lleg = 1286912989,
	rleg = -1963356626,
	rhand = -393310151,
	lhand = -1358607930
};

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};


enum Signal : int
{
	Attack,
	Alt_Attack,
	DryFire,
	Reload,
	Deploy,
	Flinch_Head,
	Flinch_Chest,
	Flinch_Stomach,
	Flinch_RearHead,
	Flinch_RearTorso,
	Throw,
	Relax,
	Gesture,
	PhysImpact,
	Eat,
	Startled,
	Admire
};

enum BaseEntityFlags : int
{
	Placeholder = 1,
	On = 2,
	OnFire = 4,
	Open = 8,
	Locked = 16,
	Debugging = 32,
	Disabled = 64,
	Reserved1 = 128,
	Reserved2 = 256,
	Reserved3 = 512,
	Reserved4 = 1024,
	Reserved5 = 2048,
	Broken = 4096,
	Busy = 8192,
	Reserved6 = 16384,
	Reserved7 = 32768,
	Reserved8 = 65536
};
enum class Flags : int {
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeping = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aiming = 128,
	Prone = 256,
	Mounted = 512,
	Relaxed = 1024,
	OnPhone = 2048,
};
enum PlayerFlags : int
{
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};

enum LifeState
{
	Alive,
	Dead
};

class Rect {
public:
	float x; // 0x10
	float y; // 0x14
	float wid; // 0x18
	float hei; // 0x1C
	Rect(float x, float y/*top left*/, float width, float height) {
		this->x = x;
		this->y = y;
		wid = width;
		hei = height;
	}
	Rect() {
		this->x = 0;
		this->y = 0;
		wid = 0;
		hei = 0;
	}
	bool Contains(Vector2 point)
	{
		return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei);
	}
};

enum class Layers
{
	Terrain = 8388608,
	World = 65536,
	Ragdolls = 512,
	Construction = 2097152,
	ConstructionSocket = 4194304,
	Craters = 1,
	GameTrace = 16384,
	Trigger = 262144,
	VehiclesDetailed = 8192,
	RainFall = 1101070337,
	Deploy = 1235288065,
	DefaultDeployVolumeCheck = 537001984,
	BuildLineOfSightCheck = 2097152,
	ProjectileLineOfSightCheck = 2162688,
	ProjectileLineOfSightCheckTerrain = 10551296,
	MeleeLineOfSightCheck = 2162688,
	EyeLineOfSightCheck = 2162688,
	EntityLineOfSightCheck = 1218519041,
	PlayerBuildings = 18874624,
	PlannerPlacement = 161546496,
	Solid = 1218652417,
	VisCulling = 10551297,
	AltitudeCheck = 1218511105,
	HABGroundEffect = 1218511105,
	AILineOfSight = 1218519297,
	DismountCheck = 1486946561,
	AIPlacement = 278986753,
	WheelRay = 1235321089,
};

enum BuildingGrade : int
{
	None = -1,
	Twigs,
	Wood,
	Stone,
	Metal,
	TopTier,
	Count
};

class ESPOption
{
public:
	char* Prefab = "";
	char* Name = "";
	char* SubTab = "";
	bool Alive = false;

	bool Draw = false;
	bool DrawName = true;
	bool DrawDistance = true;
	bool DrawHealth = true;
	bool checkMaxDistance = false;
	float MaxDistance = 400;
	float Color[3] = { 255.f, 255.f, 255.f };
};

struct box_bounds {
	float left, right, top, bottom;

	bool empty() {
		if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
			return true;

		if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
			return true;

		return false;
	}
	static box_bounds null() {
		return { 0, 0, 0, 0 };
	}
};

template<typename T>
class List {
public:
	T get(uint32_t idx)
	{
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T get_value(uint32_t idx) {
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T operator[](uint32_t idx) { return get(idx); }
	const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }
	template<typename F>
	void for_each(const F callback) {
		for (auto i = 0; i < get_size(); i++) {
			auto object = this->get(i);
			if (!object)
				continue;
			callback(object, i);
		}
	}
};

template<typename T = void*>

class Array {
public:
	uint32_t size() {
		if (!this) return 0;
		return *reinterpret_cast<uint32_t*>(this + 0x18);
	}
	T get(int idx) {
		if (!this) return T{};
		return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
	}
	void add(int idx, T value) {
		if (!this) return;
		*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
	}
};

class Str {
	char zpad[0x10];
public:
	int size;
	wchar_t str[64 + 1];
	Str(const wchar_t* st) {
		size = min(wcslen((wchar_t*)st), 64);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
};

class CachedBone
{
public:
	int BoneID;
	DWORD64 BoneTransform;
};

//
//
// Rust Structs
//
//

class BaseNetworkableClass
{
public:
	class BaseNetworkable_* pBaseNetworkable; //0x0000
	char pad_0008[16]; //0x0008
}; //Size: 0x0018

class BaseNetworkable_
{
public:
	char pad_0000[184]; //0x0000
	class EntityRealm* pEntityRealm; //0x00B8
}; //Size: 0x00C0

class EntityRealm
{
public:
	class ClientEntitiesClass* pClientEntities; //0x0000
	char pad_0008[16]; //0x0008
}; //Size: 0x0018

class ClientEntitiesClass
{
public:
	char pad_0000[16]; //0x0000
	class EntityListClass* pEntityList; //0x0010
}; //Size: 0x0018

class EntityListClass
{
public:
	char pad_0000[40]; //0x0000
	class BufferListVals* pBufferListVals; //0x0028
}; //Size: 0x0030

class BufferListVals
{
public:
	char pad_0000[16]; //0x0000
	uint64_t BufferListCount; //0x0010
	class BufferListData* pBufferListData; //0x0018
}; //Size: 0x0020

class ItemData
{
public:
	class EntityClass* pItemClass; //0x0000
}; //Size: 0x0008

class BufferListData
{
public:
	char pad_0000[32]; //0x0000
	class ItemData Items[1]; //0x0020
}; //Size: 0x0028

class GlobalObjectManagerClass
{
public:
	class GlobalObjectManager* pGlobalObjectManager; //0x0000
	char pad_0008[8]; //0x0008
}; //Size: 0x0010

class GlobalObjectManager
{
public:
	uint64_t pListEnd; //0x0000
	class GameObjectListClass* pListStart; //0x0008
}; //Size: 0x0010

class GameObjectListClass
{
public:
	char pad_0000[16]; //0x0000
	class GameObjectClass* pGameObject; //0x0010
}; //Size: 0x0018

class GameObjectClass
{
public:
	char pad_0000[48]; //0x0000
	class ObjectEntityClass* pObjectEntity; //0x0030
	char pad_0038[28]; //0x0038
	uint16_t Tag; //0x0054
	char pad_0056[10]; //0x0056
	char* ObjectName; //0x0060
	char pad_0068[32]; //0x0068
}; //Size: 0x0088

class ObjectEntityClass
{
public:
	char pad_0000[24]; //0x0000
	class ObjectDataClass* pObjectData; //0x0018
}; //Size: 0x0020

class ObjectDataClass
{
public:
	char pad_0000[16]; //0x0000
}; //Size: 0x0010

class EntityClass
{
public:
	uint32_t class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
	class ClassPointer* pClassPointer; //0x0000
	char pad_0008[8]; //0x0008
	class CachedPtrClass* m_CachedPtr; //0x0010
}; //Size: 0x0018

class ObjectClass
{
public:
	char pad_0000[48]; //0x0000
	class ComponentListClass* pComponentList; //0x0030
	char pad_0038[40]; //0x0038
	char* pPrefabNameString; //0x0060
	char pad_0068[8]; //0x0068
}; //Size: 0x0070

class CachedPtrClass
{
public:
	char pad_0000[40]; //0x0000
	uint64_t pBaseClass; //0x0028
	class ObjectClass* pObjectClass; //0x0030
	char pad_0038[16]; //0x0038
}; //Size: 0x0048

class ClassPointer
{
public:
	char pad_0000[16]; //0x0000
	char* pEntityClassNameString; //0x0010
}; //Size: 0x0018

class ComponentListClass
{
public:
	char pad_0000[8]; //0x0000
	class ObjectTransformClass* pObjectTransforms; //0x0008
}; //Size: 0x0010

class ObjectTransformClass
{
public:
	char pad_0000[56]; //0x0000
	class ObjectTransformData* pObjectTransformData; //0x0038
	char pad_0040[8]; //0x0040
}; //Size: 0x0048

class ObjectTransformData
{
public:
	char pad_0000[144]; //0x0000
	Vector3 Position; //0x0090
}; //Size: 0x009C

class ContainerInventory
{
public:
	char pad_0000[32]; //0x0000
	uint64_t Item[6]; //0x0020
}; //Size: 0x0050

class StaticCameraClass
{
public:
	char pad_0000[16]; //0x0000
	class StaticCameraPointerOne* PointerOne_; //0x0010
}; //Size: 0x0018

class StaticCameraPointerOne
{
public:
	char pad_0000[48]; //0x0000
	class StaticCameraPointerTwo* PointerTwo_; //0x0030
}; //Size: 0x0038

class StaticCameraPointerTwo
{
public:
	char pad_0000[48]; //0x0000
	class StaticCameraPointerThree* PointerThree_; //0x0030
}; //Size: 0x0038

class StaticCameraPointerThree
{
public:
	char pad_0000[24]; //0x0000
	class StaticCameraPointerFour* PointerFour; //0x0018
}; //Size: 0x0020

class StaticCameraPointerFour
{
public:
	char pad_0000[740]; //0x0000
	Matrix4x4 ViewMatrix; //0x02E4
}; //Size: 0x0324