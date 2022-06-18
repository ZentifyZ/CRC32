#pragma once
/*
class Temp
{
public:
	UINT_PTR Base_ = 0;

	Temp(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Temp() {};

	//CreateUnSafeField("Assembly-CSharp", "", "class", "field", field, float);
};
*/
inline char PatrolID[255] = "patrolhelicopter.prefab";
inline Item heldEntity;

class Sprite
{
public:
	UINT_PTR Base_ = 0;

	Sprite(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Sprite() {};

	Rect get_rect()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Sprite", "get_rect");
			}

			typedef Rect Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Rect();
	}

	UINT_PTR get_texture()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Sprite", "get_texture");
			}

			typedef UINT_PTR Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
};

class Transform
{
public:
	UINT_PTR Base_ = 0;

	Transform(UINT_PTR Base)
	{
		this->Base_ = Base;
	}

	Transform() {};

	inline Vector3 InverseTransformDirection(Vector3 p0)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Transform", "InverseTransformDirection");
			}

			typedef Vector3 Method(UINT_PTR, Vector3);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, p0);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	inline Vector3 up() {
		__try {
			UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_up");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	inline Vector3 InverseTransformPoint(Vector3 p0)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Transform", "InverseTransformPoint");
			}

			typedef Vector3 Method(UINT_PTR, Vector3);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, p0);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}

	void SetPosition(Vector3 set)
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Transform", "set_position");
			}

			typedef void set_Position(UINT_PTR, Vector3);
			((set_Position*)(Globals::g_GameAssemblyBase + var))(this->Base_, set);
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers)
			{
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
	}

	Vector3 GetPosition()
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position");
			}

			if (this->Base_ == 0)
				return Vector3();

			typedef Vector3 Get_Position(UINT_PTR);
			return ((Get_Position*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers)
			{
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
		return Vector3();
	}

private:
};
class Component
{
public:
	UINT_PTR Base_ = 0;

	Component(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Component() {};

	Transform get_transform()
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Component", "get_transform");
			}

			if (!this) return 0;

			typedef UINT_PTR Method(UINT_PTR);
			Transform transform(((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_));
			return transform;
			//return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers)
			{
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
		//return 0.f;
		return Transform();
	}
};

class PickupRequest
{
public:
	UINT_PTR entity;
};

inline std::list<PickupRequest> PickupQueue;
inline float lastRequestWipe = 0.f;

class BaseEntity : public Component
{
public:
	BaseEntity(UINT_PTR base)
	{
		this->Base_ = base;
	}

	BaseEntity() {};

	char* className = "BasePlayer";

	Vector3 ClosestPoint(Vector3 position)
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "ClosestPoint", 1);
			}

			typedef Vector3 Method(UINT_PTR, Vector3);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, position);
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers)
			{
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
		return Vector3();
	}
	void ServerRPC(Str funcName)
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "ServerRPC", 1);
			}

			if (UnityEngine::get_realtimeSinceStartup() > lastRequestWipe)
			{
				lastRequestWipe = UnityEngine::get_realtimeSinceStartup() + 1.f;
				PickupQueue.clear();
			}

			bool alreadyUpgraded = false;

			for (PickupRequest& request : PickupQueue)
			{
				if (request.entity == this->Base_)
				{
					alreadyUpgraded = true;
					return;
				}
			}

			if (!alreadyUpgraded)
			{
				PickupRequest pickupRequest;
				pickupRequest.entity = this->Base_;
				typedef void Method(UINT_PTR, Str);
				((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, funcName);
				PickupQueue.push_front(pickupRequest);
			}
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers)
			{
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
		return;
	}

	float MaxHealth()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", className, "MaxHealth");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	CreateUnSafeField("Assembly-CSharp", "", "BaseEntity", "flags", flags, int);
};

class HitTest
{
public:
	UINT_PTR Base_ = 0;

	HitTest(UINT_PTR base)
	{
		this->Base_ = base;
	}

	HitTest()
	{
		this->Base_ = Dumper::GetNewObject("Assembly-CSharp", "", "HitTest");
	}

	Vector3 HitNormalWorld() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "HitTest", "HitNormalWorld");
			}

			if (!this) return Vector3(0, 0, 0);

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	bool DoHit() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "DoHit");
			}

			if (!this) return false;

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "AttackRay", AttackRay, Ray);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "MaxDistance", MaxDistance, float);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "HitTransform", HitTransform, Transform);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "DidHit", DidHit, bool);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "HitMaterial", HitMaterial, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "HitEntity", HitEntity, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "HitPoint", HitPoint, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "HitNormal", HitNormal, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "HitTest", "damageProperties", damageProperties, UINT_PTR);
};

class GatherPropertyEntry
{
public:
	UINT_PTR Base_ = 0;

	GatherPropertyEntry(UINT_PTR base)
	{
		this->Base_ = base;
	}

	GatherPropertyEntry() {};

	float gatherDamage()
	{
		__try
		{
			return *(UINT_PTR*)(this->Base_ + 0x10);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

class GatherProperties
{
public:
	UINT_PTR Base_ = 0;
	GatherPropertyEntry Tree;
	GatherPropertyEntry Ore;

	GatherProperties(UINT_PTR base)
	{
		this->Base_ = base;
		Tree = GatherPropertyEntry(gTree());
		Ore = GatherPropertyEntry(gOre());
	}

	GatherProperties() {};

private:
	UINT_PTR gTree()
	{
		__try
		{
			return *(UINT_PTR*)(this->Base_ + 0x10);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	UINT_PTR gOre()
	{
		__try
		{
			return *(UINT_PTR*)(this->Base_ + 0x18);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

class ViewModel
{
public:
	UINT_PTR Base_ = 0;

	ViewModel(UINT_PTR base)
	{
		this->Base_ = base;
	}

	ViewModel() {};

	void Play(Str string)
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "ViewModel", "Play");
			}

			typedef void Method(UINT_PTR, Str);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, string);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
	//CreateUnSafeField("Assembly-CSharp", "", "class", "field", field, float);
};

class BaseMelee
{
public:
	UINT_PTR Base_ = 0;
	GatherProperties gatherProperties;
	ViewModel viewModel;

	BaseMelee(UINT_PTR base)
	{
		this->Base_ = base;
		viewModel = ViewModel(gviewModel());
		gatherProperties = GatherProperties(gathering());
	}

	BaseMelee() {};

	float get_NextAttackTime()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "AttackEntity", "get_NextAttackTime");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
	void ServerRPC(Str funcName) {
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try {
			UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "ServerRPC", 1);
			}

			typedef void Method(UINT_PTR, Str);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, funcName);
		}
		__except (
			ExceptionCode = GetExceptionCode(),
			ExceptionPointers = GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER
			) {
			if (ExceptionPointers) {
				Ulog("Exception (%lx) caught in %s @ (%p) (%llx)",
					ExceptionCode, __FUNCTION__,
					ExceptionPointers->ExceptionRecord->ExceptionAddress,
					Globals::g_GameAssemblyBase
				);
			}
		}
		return;
	}

	bool IsFullyDeployed()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "AttackEntity", "IsFullyDeployed");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	void ProcessInputTime()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "AttackEntity", "ProcessInputTime");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void DoViewmodelImpact()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMelee", "DoViewmodelImpact");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	bool HasAttackCooldown()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "AttackEntity", "HasAttackCooldown");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	float StartAttackCooldown(float cooldown)
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "AttackEntity", "StartAttackCooldown");
			}

			typedef float Method(UINT_PTR, float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, cooldown);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	CreateUnSafeField("Assembly-CSharp", "", "BaseMelee", "damageProperties", damageProperties, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "timeSinceDeploy", timeSinceDeploy, float);
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "deployDelay", deployDelay, float);
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "repeatDelay", repeatDelay, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseMelee", "maxDistance", maxDistance, float);

	bool CanHit(HitTest hit)
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMelee", "CanHit");
			}

			typedef bool Method(UINT_PTR, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, hit.Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	float ProcessAttack(HitTest hit)
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMelee", "ProcessAttack");
			}

			typedef float Method(UINT_PTR, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, hit.Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
private:
	CreateUnSafeField("Assembly-CSharp", "", "BaseMelee", "viewModel", gviewModel, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseMelee", "gathering", gathering, UINT_PTR);
};

class Chainsaw : public BaseMelee
{
public:
	Chainsaw(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Chainsaw() {};

	bool IsAttacking()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Chainsaw", "IsAttacking");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	CreateUnSafeField("Assembly-CSharp", "", "Chainsaw", "ammo", ammo, int);
};

class GrowableEntity : public BaseEntity
{
public:
	GrowableEntity(UINT_PTR base)
	{
		this->Base_ = base;
	}

	GrowableEntity() {};

	bool CanPick()
	{
		__try
		{
			UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "GrowableEntity", "CanPick");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}
};

class WorldItem : public BaseEntity
{
public:
	WorldItem(UINT_PTR base)
	{
		this->Base_ = base;
	}

	WorldItem() {};

	CreateUnSafeField("Assembly-CSharp", "", "WorldItem", "item", item, UINT_PTR);
};

class Upgrade
{
public:
	int Grade;
	UINT_PTR basePlayer;
	UINT_PTR entity;
};

inline std::list<Upgrade> UpgradeQueue;
inline float lastWipe = 0.f;

class BuildingBlock : public BaseEntity
{
public:
	BuildingBlock(UINT_PTR base)
	{
		this->Base_ = base;
	}

	BuildingBlock() {};

	bool CanChangeToGrade(int iGrade, UINT_PTR player)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BuildingBlock", "CanChangeToGrade");
			}

			typedef bool Method(UINT_PTR, int, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, iGrade, player);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	bool CanAffordUpgrade(int iGrade, UINT_PTR player)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BuildingBlock", "CanAffordUpgrade");
			}

			typedef bool Method(UINT_PTR, int, UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, iGrade, player);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	void UpgradeToGrade(int iGrade, UINT_PTR player)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BuildingBlock", "UpgradeToGrade");
			}

			if (UnityEngine::get_realtimeSinceStartup() > lastWipe)
			{
				lastWipe = UnityEngine::get_realtimeSinceStartup() + 1.f;
				UpgradeQueue.clear();
			}

			bool alreadyUpgraded = false;

			for (Upgrade& upgrade : UpgradeQueue)
			{
				if (upgrade.basePlayer == player && upgrade.Grade == iGrade && upgrade.entity == this->Base_)
				{
					alreadyUpgraded = true;
					return;
				}
			}

			if (!alreadyUpgraded)
			{
				Upgrade upgrade;
				upgrade.basePlayer = player;
				upgrade.Grade = iGrade;
				upgrade.entity = this->Base_;
				typedef bool Method(UINT_PTR, int, UINT_PTR);
				((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, iGrade, player);
				UpgradeQueue.push_front(upgrade);
			}
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	CreateUnSafeField("Assembly-CSharp", "", "BuildingBlock", "grade", grade, int);
};

class BaseCombatEntity : public BaseEntity
{
public:
	BaseCombatEntity(UINT_PTR base)
	{
		this->Base_ = base;
	}

	BaseCombatEntity() {};

	CreateUnSafeField("Assembly-CSharp", "", "BaseCombatEntity", "lifestate", lifestate, int);
	CreateUnSafeField("Assembly-CSharp", "", "BaseCombatEntity", "_health", health, float);
};

class StorageContainer : public BaseEntity
{
public:
	StorageContainer(UINT_PTR base)
	{
		this->Base_ = base;
	}

	StorageContainer() {};

	CreateUnSafeField("Assembly-CSharp", "", "StorageContainer", "inventorySlots", inventorySlots, int);
};

class PlayerNameID
{
public:
	UINT_PTR Base_ = 0;

	PlayerNameID(UINT_PTR base)
	{
		this->Base_ = base;
	}

	PlayerNameID() {};

	CreateUnSafeField("Rust.Data", "ProtoBuf", "PlayerNameID", "username", username, pUncStr);
};

class AutoTurret : public BaseCombatEntity
{
public:
	AutoTurret(UINT_PTR base)
	{
		this->Base_ = base;
	}

	AutoTurret() {};

	CreateUnSafeField("Assembly-CSharp", "", "AutoTurret", "authorizedPlayers", authorizedPlayers, List<UINT_PTR>*);
};

class BuildingPrivlidge : public StorageContainer
{
public:
	BuildingPrivlidge(UINT_PTR base)
	{
		this->Base_ = base;
	}

	BuildingPrivlidge() {};

	CreateUnSafeField("Assembly-CSharp", "", "BuildingPrivlidge", "authorizedPlayers", authorizedPlayers, List<UINT_PTR>*);
};

class LootContainer : public StorageContainer
{
public:
	LootContainer(UINT_PTR base)
	{
		this->Base_ = base;
	}

	LootContainer() {};
};

class SleepingBag : public BaseEntity
{
public:
	SleepingBag(UINT_PTR base)
	{
		this->Base_ = base;
	}

	SleepingBag() {};

	CreateUnSafeField("Assembly-CSharp", "", "SleepingBag", "deployerUserID", deployerUserID, ULONG);
};

class HackableLockedCrate : public LootContainer
{
public:
	HackableLockedCrate(UINT_PTR base)
	{
		this->Base_ = base;
	}

	HackableLockedCrate() {};

	CreateUnSafeField("Assembly-CSharp", "", "HackableLockedCrate", "hackSeconds", hackSeconds, float);
};

class Projectile : public Component
{
public:
	UINT_PTR Base_ = 0;

	Projectile(UINT_PTR Base)
	{
		this->Base_ = Base;
	}

	Projectile() {};


	bool DoHit(HitTest test, Vector3 point, Vector3 normal) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "DoHit");
			}

			if (!this) return false;

			typedef bool Method(UINT_PTR, HitTest, Vector3, Vector3);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, test, point, normal);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}

	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "hitTest", hitTest, HitTest);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "previousVelocity", previousVelocity, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "currentVelocity", currentVelocity, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "initialVelocity", initialVelocity, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "traveledTime", traveledTime, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "swimRandom", swimRandom, float);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "thickness", thickness, float);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "currentPosition", currentPosition, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "Projectile", "drag", drag, float);
};

class PlayerEyes {
public:
	UINT_PTR Base_ = 0;

	PlayerEyes(UINT_PTR Base) {
		this->Base_ = Base;
	}

	PlayerEyes() { };

	 static inline Vector3 EyeOffset() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "", "PlayerEyes");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			return *reinterpret_cast<Vector3*> (static_fields + 0x0);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	Quaternion GetRotation() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "get_rotation");
			}

			typedef Quaternion Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Quaternion();
	}

	Vector3 GetPosition() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "get_position");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	Vector3 MovementRight() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "MovementRight");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	//Vector3 get_center()
	//{
	//	__try
	//	{
	//		static UINT_PTR var = 0x402402;

	//		if (var == 0x402402)
	//		{
	//			var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "get_center");
	//		}

	//		typedef Vector3 Method(UINT_PTR);
	//		return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
	//	}
	//	__except (true)
	//	{
	//		Ulog("%s - Exception Occurred.", __FUNCTION__);
	//	}
	//	return Vector3();
	//}
	Vector3 MovementForward() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "MovementForward");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	Vector3 HeadForward() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerEyes", "HeadForward");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	CreateUnSafeField("Assembly-CSharp", "", "PlayerEyes", "viewOffset", viewOffset, Vector3);
	//CreateUnSafeField("Assembly-CSharp", "", "PlayerEyes", "EyeOffset", EyeOffset, Vector3);
	//CreateField("Assembly-CSharp", "", "PlayerEyes", "viewOffset", SetViewOffset, void*);
};

class ItemContainer
{
public:
	UINT_PTR Base_ = 0;
	//Item Items[6];

	ItemContainer(UINT_PTR Base)
	{
		this->Base_ = Base;
	}

	ItemContainer() {};

	UINT_PTR GetSize()
	{
		__try
		{
			return *(UINT_PTR*)(GetItemList() + 0x14);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	UINT_PTR GetItems()
	{
		__try
		{
			return *(UINT_PTR*)(GetItemList() + 0x10);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	Item FindActiveItem(int clActiveItem)
	{
		__try
		{
			for (int i = 0; i < 6; i++)
			{
				auto invitem = *(UINT_PTR*)(GetItems() + 0x20 + (i * 0x8));

				if (invitem)
				{
					Item item(invitem);
					if (item.itemDefinition.Base_ != 0 && item.Base_ != 0)
					{
						if (item.uid() == clActiveItem) return item;
					}
				}
			}
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Item();
	}

	Item GetItem(int i)
	{
		__try
		{
			auto invitem = *(UINT_PTR*)(GetItems() + 0x20 + (i * 0x8));

			if (invitem)
			{
				Item item(invitem);
				if (item.itemDefinition.Base_ != 0 && item.Base_ != 0)
				{
					return item;
				}
			}
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Item();
	}

	UINT_PTR GetItemList()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "ItemContainer", "itemList");
			}

			return *(UINT_PTR*)(this->Base_ + var);;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

class PlayerInventory
{
public:
	UINT_PTR Base_ = 0;
	ItemContainer ContainerBelt;
	ItemContainer ContainerWear;

	PlayerInventory(UINT_PTR Base)
	{
		this->Base_ = Base;
		ContainerBelt = ItemContainer(GetContainerBelt());
		ContainerWear = ItemContainer(GetContainerWear());
	}

	PlayerInventory() {};

private:
	CreateUnSafeField("Assembly-CSharp", "", "PlayerInventory", "containerWear", GetContainerWear, UINT_PTR);

	CreateUnSafeField("Assembly-CSharp", "", "PlayerInventory", "containerBelt", GetContainerBelt, UINT_PTR);
};

class Model
{
public:
	UINT_PTR Base_ = 0;

	Model(UINT_PTR Base)
	{
		this->Base_ = Base;
	}

	Model() {};

	Transform GetTransform(int bone)
	{
		__try
		{
			if (this->Base_ == 0)
				return Transform();
			return Transform(*(UINT_PTR*)((GetBoneTransforms() + (0x20 + (bone * 0x8)))));
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Transform();
	}

private:
	UINT_PTR GetBoneTransforms()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "Model", "boneTransforms");
			}

			if (this->Base_ == 0)
				return 0;

			return *(UINT_PTR*)(this->Base_ + var);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

inline UINT_PTR FindShader(Str shader)
{
	__try
	{
		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find");
		}

		typedef UINT_PTR Method(Str);
		return ((Method*)(Globals::g_GameAssemblyBase + var))(shader);
	}
	__except (true)
	{
		Ulog("%s - Exception Occurred.", __FUNCTION__);
	}
	return 0;
}
class Shader {
public:
	UINT_PTR Base_ = 0;

	Shader(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Shader() {};

	static UINT_PTR Find(Str name) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find");
			}

			typedef UINT_PTR Method(Str);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(name);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};
class Material
{
public:
	UINT_PTR Base_ = 0;

	Material(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Material() {};

	UINT_PTR get_shader()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "get_shader");
			}

			typedef UINT_PTR Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
	Shader shader() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "get_shader");
			}

			typedef Shader Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
	void SetInt(Str name, int value)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "SetInt");
			}

			typedef void Method(UINT_PTR, Str, int);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, name, value);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void set_shader(UINT_PTR shader)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "set_shader");
			}

			typedef void Method(UINT_PTR, UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, shader);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void SetColor(Str prop, Color color)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{//REPLACEME
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "SetColor");
				//var = 0x187CAC0;//var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Material", "SetColor");
			}

			typedef void Method(UINT_PTR, Str, Color);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, prop, color);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
};

class Renderer
{
public:
	UINT_PTR Base_ = 0;

	Renderer(UINT_PTR base)
	{
		this->Base_ = base;
	}

	Renderer() {};

	UINT_PTR get_material()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Renderer", "get_material");
			}

			typedef UINT_PTR Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

class SkinnedMultiMesh
{
public:
	UINT_PTR Base_ = 0;

	SkinnedMultiMesh(UINT_PTR base)
	{
		this->Base_ = base;
	}

	SkinnedMultiMesh() {};

	List<UINT_PTR>* get_Renderers()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "SkinnedMultiMesh", "get_Renderers");
			}

			typedef List<UINT_PTR>* Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}

		return 0;
	}
};

inline int PropertyToID(Str name)
{
	__try
	{
		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Shader", "PropertyToID");
		}

		typedef int Method(Str);
		return ((Method*)(Globals::g_GameAssemblyBase + var))(name);
	}
	__except (true)
	{
		Ulog("%s - Exception Occurred.", __FUNCTION__);
	}
	return 0;
}

class ModelState
{
public:
	UINT_PTR Base_ = 0;

	ModelState(UINT_PTR base)
	{
		this->Base_ = base;
	}

	ModelState() {};

	bool HasFlag(Flags F) {
		__try {
			UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Rust.Data", "", "ModelState", "HasFlag");
			}

			typedef bool Method(UINT_PTR, Flags);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, F);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return false;
	}
	CreateUnSafeField("Rust.Data", "", "ModelState", "flags", flags, int);
	CreateUnSafeField("Rust.Data", "", "ModelState", "inheritedVelocity", inheritedVelocity, Vector3);
};

class PlayerModel
{
public:
	UINT_PTR Base_ = 0;
	ModelState modelState;

	PlayerModel(UINT_PTR base)
	{
		this->Base_ = base;
		modelState = ModelState(modelState_ptr());
	}

	PlayerModel() {};
	


	CreateUnSafeField("Assembly-CSharp", "", "PlayerModel", "modelState", modelState_ptr, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerModel", "<IsNpc>k__BackingField", GetNPC, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerModel", "newVelocity", newVelocity, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerModel", "velocity", velocity, Vector3);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerModel", "_multiMesh", _multiMesh, UINT_PTR);

};

class PlayerInput
{
public:
	UINT_PTR Base_ = 0;

	PlayerInput(UINT_PTR base)
	{
		this->Base_ = base;
	}

	PlayerInput() {};

	CreateUnSafeField("Assembly-CSharp", "", "PlayerInput", "bodyAngles", bodyAngles, Vector2);
};

class DamageTypeList {
public:
	UINT_PTR Base_ = 0;

	DamageTypeList(UINT_PTR base)
	{
		this->Base_ = base;
	}

	DamageTypeList() {};

	enum class DamageType {
		Generic,
		Hunger,
		Thirst,
		Cold,
		Drowned,
		Heat,
		Bleeding,
		Poison,
		Suicide,
		Bullet,
		Slash,
		Blunt,
		Fall,
		Radiation,
		Bite,
		Stab,
		Explosion,
		RadiationExposure,
		ColdExposure,
		Decay,
		ElectricShock,
		Arrow,
		AntiVehicle,
		Collision,
		Fun_Water,
		LAST
	};

	float Total()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "Rust", "DamageTypeList", "Total");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
};

class HitInfo
{
public:
	UINT_PTR Base_ = 0;

	HitInfo(UINT_PTR base)
	{
		this->Base_ = base;
	}

	HitInfo() {};

	pUncStr GetBoneName()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "HitInfo", "get_boneName");
			}

			typedef pUncStr Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	CreateUnSafeField("Assembly-CSharp", "", "HitInfo", "damageTypes", damageTypes, UINT_PTR);
};
class RigidBody {
public:
	UINT_PTR Base_ = 0;

	RigidBody(UINT_PTR base) {
		this->Base_ = base;
	}

	RigidBody() { };


	inline Vector3 velocity() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "get_velocity");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}

	void set_velocity(Vector3 p0) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("UnityEngine.PhysicsModule", "UnityEngine", "Rigidbody", "set_velocity");
			}

			typedef void Method(UINT_PTR, Vector3);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, p0);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}//
	}
};
class BaseMovement
{
public:
	UINT_PTR Base_ = 0;

	BaseMovement(UINT_PTR base)
	{
		this->Base_ = base;
	}

	BaseMovement() {};

	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "groundAngle", groundAngle, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "groundAngleNew", groundAngleNew, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "maxVelocity", maxVelocity, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleCenter", capsuleCenter, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleHeightDucked", capsuleHeightDucked, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleCenterDucked", capsuleCenterDucked, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleCenterCrawling", capsuleCenterCrawling, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleHeightCrawling", capsuleHeightCrawling, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "maxStepHeight", maxStepHeight, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "groundTime", groundTime, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "maxAngleWalking", maxAngleWalking, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "maxAngleClimbing", maxAngleClimbing, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "flying", flying, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "swimming", swimming, bool);
	CreateUnSafeField("Assembly-CSharp", "", "BaseMovement", "<Ducking>k__BackingField", Ducking, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseMovement", "<TargetMovement>k__BackingField", TargetMovement, Vector3);

	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "jumping", jumping, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "jumpTime", jumpTime, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "gravityMultiplierSwimming", gravityMultiplierSwimming, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "capsuleHeight", capsuleHeight, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "grounded", grounded, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "climbing", climbing, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "sliding", sliding, bool);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "ladder", ladder, void*);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "WaterLevelHead", WaterLevelHead, float);
	CreateUnSafeField("Assembly-CSharp", "", "PlayerWalkMovement", "body", body, RigidBody);


	void SetTargetMovement(Vector3 position) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMovement", "set_TargetMovement");
			}

			typedef void Method(UINT_PTR, Vector3);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, position);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void TeleportTo(Vector3 position, UINT_PTR player) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseMovement", "TeleportTo");
			}

			typedef void Method(UINT_PTR, Vector3, UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, position, player);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
};
class PlayerTick {
public:
	UINT_PTR Base_ = 0;

	PlayerTick(UINT_PTR Base) {
		this->Base_ = Base;
	}

	PlayerTick() { };

	CreateUnSafeField("Assembly-CSharp", "", "PlayerTick", "position", position, Vector3);
};
class BasePlayer : public BaseCombatEntity
{
public:
	Vector3 velocities[51];
	int currentVelocityRecords = { 0 };
	int currentVelocityIndex = { 0 };
	Vector3 avgVel = Vector3{ 0.f, 0.f, 0.f };

	BaseMovement movement;
	PlayerEyes Eyes;
	PlayerInventory Inventory;
	ModelState ModelStates;
	Model model;
	PlayerModel playerModel;
	PlayerInput input;
	char* HeldWeapon = "";

	int hits = 0;

	BasePlayer(UINT_PTR base)
	{
		__try
		{
			this->Base_ = base;
			auto n = nullptr;
			if (gmovement() != reinterpret_cast<UINT_PTR&>(n))movement = BaseMovement(gmovement());
			hits++;
			if (gplayerModel() != reinterpret_cast<UINT_PTR&>(n))playerModel = PlayerModel(gplayerModel());
			hits++;
			if (ginput() != reinterpret_cast<UINT_PTR&>(n)) input = PlayerInput(ginput());
			hits++;
			if (geyes() != reinterpret_cast<UINT_PTR&>(n))Eyes = PlayerEyes(geyes());
			hits++;
			if (gmodel() != reinterpret_cast<UINT_PTR&>(n))model = Model(gmodel());
			hits++;
			if (ginventory() != reinterpret_cast<UINT_PTR&>(n))Inventory = PlayerInventory(ginventory());
			hits++;
		}
		__except (true)
		{
			Ulog("%s - %i Hits - Exception Occurred.", __FUNCTION__, hits);
			this->Base_ = 0;
			this->playerModel.Base_ = 0;
			this->input.Base_ = 0;
			this->Eyes.Base_ = 0;
			this->model.Base_ = 0;
			this->Inventory.Base_ = 0;
		}
	}

	BasePlayer() {};

	wchar_t* GetDisplayName()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "BasePlayer", "_displayName");
			}

			return (*(pUncStr*)(this->Base_ + var))->str;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
	size_t class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
	bool HasPlayerFlag(PlayerFlags flag) {
		__try {
			if (!this) return false;

			return (playerFlags() & flag) == flag;
		}
		__except (true) {
			std::cout << "%s - Exception Occurred." << __FUNCTION__ << std::endl;
		}
	}
	Vector3 GetWorldVelocity() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "GetWorldVelocity");
			}

			typedef Vector3 Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	float BoundsPadding() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseEntity", "BoundsPadding");
			}

			typedef float Method(BaseEntity*);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
	Vector3 GetMountVelocity() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetMountVelocity");
			}

			typedef Vector3 Method(BaseEntity*);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	Vector3 GetParentVelocity() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetParentVelocity");
			}

			typedef Vector3 Method(BaseEntity*);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return Vector3();
	}
	pUncStr GetDisplayNamePtr()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "BasePlayer", "_displayName");
			}

			return *(pUncStr*)(this->Base_ + var);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	float GetHeight(bool ducked) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetHeight", 1);
			}

			typedef float Method(UINT_PTR, bool);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, ducked);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	float GetRadius()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetRadius");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	float GetJumpHeight()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetJumpHeight");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	float MaxVelocity()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "MaxVelocity");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	void OnLand(float fVelocity)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "OnLand");
			}

			typedef void Method(UINT_PTR, float);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_, fVelocity);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
	float GetMaxSpeed() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetMaxSpeed");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
	float EyeMaxVelocity() {
		if (!this) return 0.f;

		if (this->mounted())
			return this->GetMaxSpeed() * 4;

		return this->GetMaxSpeed();
	}
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "mounted", mounted, uintptr_t);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "Frozen", Frozen, bool);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "clActiveItem", clActiveItem, int);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "lastSentTickTime", lastSentTickTime, float);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "clientTickInterval", clientTickInterval, float);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "playerFlags", playerFlags, int);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "lastSentTick", lastSentTick, PlayerTick); 
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "userID", userID, ULONG);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "playerModel", gplayerModel, UINT_PTR);
private:
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "movement", gmovement, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "inventory", ginventory, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "eyes", geyes, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "model", gmodel, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "BasePlayer", "input", ginput, UINT_PTR);
};

namespace MathF
{
	static inline float Max(float a, float b)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "Max", 2);
			}

			typedef float Method(float, float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(a, b);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
	inline float Asin(float f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "Asin");
			}

			typedef float Method(float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(f);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}
	static inline float Abs(float f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "Abs");
			}

			typedef float Method(float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(f);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline float Sin(float f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "Sin");
			}

			typedef float Method(float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(f);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline float Cos(float f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "Cos");
			}

			typedef float Method(float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(f);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	inline int FloorToInt(float f)
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Mathf", "FloorToInt");
			}

			typedef float Method(float);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(f);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
}

class LocalPlayer {
public:
	UINT_PTR Base_ = 0;

	LocalPlayer(UINT_PTR base)
	{
		this->Base_ = base;
	}

	LocalPlayer() {};

	static inline BasePlayer Entitys() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "", "LocalPlayer");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			return *reinterpret_cast<BasePlayer*>(static_fields + 0x0);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}
};

class ItemModProjectile
{
public:
	UINT_PTR Base_;

	ItemModProjectile(UINT_PTR Base)
	{
		this->Base_ = Base;
	}

	ItemModProjectile() {};

	CreateField("Assembly-CSharp", "", "ItemModProjectile", "projectileVelocity", projectileVelocity, float);
	CreateField("Assembly-CSharp", "", "ItemModProjectile", "projectileVelocityScale", projectileVelocityScale, float);
	CreateField("Assembly-CSharp", "", "ItemModProjectile", "projectileSpread", projectileSpread, float);
	CreateField("Assembly-CSharp", "", "ItemModProjectile", "projectileVelocitySpread", projectileVelocitySpread, float);
	CreateField("Assembly-CSharp", "", "ItemModProjectile", "numProjectiles", numProjectiles, int);
	CreateField("Assembly-CSharp", "", "ItemModProjectile", "ammoType", ammoType, int);
	CreateField("Assembly-CSharp", "", "BaseEntity", "SendSignalBroadcast", SendSignalBroadcast, void*);
};
class AdminTime {
public:
	AdminTime() { };

	void SetAdminTime(float timeAmount) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "ConVar", "Admin");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			*reinterpret_cast<float*>(static_fields + 0x0) = timeAmount;
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	float GetAdminTime() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "ConVar", "Admin");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			return *reinterpret_cast<float*>(static_fields + 0x0);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}
};

class Graphics {
public:
	Graphics() { };

	void SetFov(float fovAmount) {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "ConVar", "Graphics");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			*reinterpret_cast<float*>(static_fields + 0x18) = fovAmount;
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	float GetFov() {
		__try {
			static UINT_PTR var = 0x402402;

			if (var == 0x402402) {
				var = Dumper::GetClassOffset("Assembly-CSharp", "ConVar", "Graphics");
			}

			static UINT_PTR static_fields = 0x402402;

			if (static_fields == 0x402402) {
				static_fields = *reinterpret_cast<uintptr_t*>(var + 0xB8);
			}

			return *reinterpret_cast<float*>(static_fields + 0x18);
		}
		__except (true) {
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.0f;
	}
};
