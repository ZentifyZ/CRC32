#pragma once


class Magazine
{
public:
	UINT_PTR Base_ = 0;

	Magazine(UINT_PTR base)
	{
		Base_ = base;
	}

	UINT_PTR ammoType()
	{
		__try
		{
			return *(UINT_PTR*)(this->Base_ + 0x20);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	int& contents()
	{
		__try
		{
			auto& ptr = *(int*)(this->Base_ + 0x1C);
			return ptr;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		auto n = nullptr;
		return reinterpret_cast<int&>(n);
	}

	//CreateUnSafeField("Assembly-CSharp", "", "Magazine", "ammoType", primaryMagazine, UINT_PTR);
};

class BaseProjectile
{
public:
	UINT_PTR Base_ = 0;

	BaseProjectile(UINT_PTR base)
	{
		Base_ = base;
	}
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
	int GetAvailableAmmo()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "GetAvailableAmmo");
			}

			typedef int Method(UINT_PTR);
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
	void LaunchProjectile()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "LaunchProjectile");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void UpdateAmmoDisplay()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "UpdateAmmoDisplay");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void ShotFired()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "ShotFired");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	bool HasReloadCooldown()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "HasReloadCooldown");
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

	bool HasAttackCooldown()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

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

	float GetReloadCooldown()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "GetReloadCooldown");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	float GetReloadDuration()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "GetReloadDuration");
			}

			typedef float Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0;
	}

	void DidAttackClientside()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "DidAttackClientside");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	void BeginCycle()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "BeginCycle");
			}

			typedef void Method(UINT_PTR);
			((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	float GetProjectileVelocityScale()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "CompoundBowWeapon", "GetProjectileVelocityScale");
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

	Magazine primaryMagazine()
	{
		return Magazine(primaryMagazine_ptr());
	}
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "timeSinceDeploy", timeSinceDeploy, float);
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "deployDelay", deployDelay, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseProjectile", "reloadPressTime", reloadPressTime, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseProjectile", "automatic", automatic, bool);
	CreateUnSafeField("Assembly-CSharp", "", "AttackEntity", "repeatDelay", repeatDelay, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseProjectile", "projectileVelocityScale", projectileVelocityScale, float);
	CreateUnSafeField("Assembly-CSharp", "", "BaseProjectile", "primaryMagazine", primaryMagazine_ptr, UINT_PTR);
};

class ItemDefinition
{
public:
	UINT_PTR Base_ = 0;

	ItemDefinition(UINT_PTR base)
	{
		this->Base_ = base;
	}

	wchar_t* GetDisplayName()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "ItemDefinition", "displayName");
			}
			auto translation = *(UINT_PTR*)(this->Base_ + var);
			auto stringPointer = *(pUncStr*)(translation + 0x18);
			if (!stringPointer)
			{
				return L"None";
			}
			else return stringPointer->str;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return L"None";
	}

	CreateUnSafeField("Assembly-CSharp", "", "ItemDefinition", "stackable", stackable, int);
	CreateUnSafeField("Assembly-CSharp", "", "ItemDefinition", "itemid", itemid, int);

	wchar_t* GetShortName()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "ItemDefinition", "shortname");
			}
			auto stringPointer = *(pUncStr*)(this->Base_ + var);
			if (!stringPointer)
			{
				return L"None";
			}
			else return stringPointer->str;
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return L"None";
	}
};

class Item
{
public:
	ItemDefinition itemDefinition = 0;
	BaseProjectile baseProjectile = 0;
	UINT_PTR Base_ = 0;

	Item(UINT_PTR base)
	{
		__try
		{
			if (base != 0)
			{
				this->Base_ = base;
				itemDefinition = ItemDefinition(this->GetInfo());
				if (itemDefinition.Base_ != 0)
				{
					if (this->CanBeHeld())
					{
						baseProjectile = BaseProjectile(this->GetHeldEntity());
					}
				}
			}
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
	}

	Item() {};

	char* className()
	{
		__try
		{
			auto klass = *(UINT_PTR*)(heldEntity());
			return *(char**)(klass + 0x10);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return "";
	}

	bool CanBeHeld()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Item", "CanBeHeld");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	bool HasCondition()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Item", "get_hasCondition");
			}

			typedef bool Method(UINT_PTR);
			return ((Method*)(Globals::g_GameAssemblyBase + var))(this->Base_);
		}
		__except (true)
		{
			Ulog("%s - Exception Occurred.", __FUNCTION__);
		}
		return 0.f;
	}

	float get_condition()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Item", "get_condition");
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

	float get_maxCondition()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Item", "get_maxCondition");
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

	UINT_PTR get_iconSprite()
	{
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Item", "get_iconSprite");
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

	CreateUnSafeField("Assembly-CSharp", "", "Item", "heldEntity", heldEntity, UINT_PTR);
	CreateUnSafeField("Assembly-CSharp", "", "Item", "uid", uid, int);
	CreateUnSafeField("Assembly-CSharp", "", "Item", "amount", amount, int);

private:
	UINT_PTR GetInfo()
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "Item", "info");
			}


			return *(UINT_PTR*)(this->Base_ + var);;
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
		return 0;
	}

	UINT_PTR GetHeldEntity()
	{
		ULONG ExceptionCode = 0;
		PEXCEPTION_POINTERS ExceptionPointers = 0;
		__try
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "Item", "heldEntity");
			}

			if (!this) return 0;

			return *(UINT_PTR*)(this->Base_ + var);;
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
		return 0;
	}
};