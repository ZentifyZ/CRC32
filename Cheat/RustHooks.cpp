#pragma once
#include "pch.h"
#include "RustHooks.h"
#include "other.hpp"


BasePlayer FindTarget(float fovDistance, bool vischeck = true)
{
	__try {
		BasePlayer target;
		auto desynctime = UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime();
		auto desyncpercentage = ((desynctime / 0.80f) * 100.0f) + 1.f;

		for (BasePlayerVectors& basePlayerV3 : basePlayerVectorList)
		{
			auto basePlayer = basePlayerV3.basePlayer;
			Vector2 position;
			if (WorldToScreen(basePlayer.model.GetTransform(neck).GetPosition(), position))
			{
				if (fovDistance > position.Distance(GetScreenCenter()))
				{
					if ((basePlayer.model.GetTransform(47).GetPosition(), LocalPlayer.Eyes.GetPosition(), 10551296)
						&& vischeck)
					{
						fovDistance = position.Distance(GetScreenCenter());
						target = basePlayer;
					}
					else if (!vischeck)
					{
						fovDistance = position.Distance(GetScreenCenter());
						target = basePlayer;
					}
				}
			}
		}

		return target;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
}

BasePlayer FindClosestTarget(Vector3 from)
{
	BasePlayer target;
	float Closest = FLT_MAX;

	for (BasePlayerVectors& basePlayerV3 : basePlayerVectorList)
	{
		if (UnityEngine::IsVisible(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition(), from, 10551296, 0.2f))
		{
			if (from.Distance(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition()) < Closest)
			{
				target = basePlayerV3.basePlayer;
				Closest = from.Distance(basePlayerV3.basePlayer.model.GetTransform(head).GetPosition());
			}
		}
	}

	return target;
}

uintptr_t Hooks::hk_FakeCreateProjectile(void* baseProjectile, void* prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity)
{
	__try
	{
		//Ulog("%s - hk_FakeCreateProjectile called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_CreateProjectile(baseProjectile, prefabPath, pos, forward, velocity);
}
float Hooks::hk_GetRandomVelocity(UINT_PTR self)
{
	__try {

		float modifier = 1.0f;

		if (Settings::Combat::WeaponMods::FastBullet)
			modifier += .499f;


		return Globals::Functions::Original_GetRandomVelocity(self) * modifier;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
}
void Hooks::hk_UpdateVelocity(UINT_PTR self)
{
	__try {

		//BaseMovement self1 = self;
		//if (!self1.flying()) {
		//	Vector3 vel = self1.TargetMovement();
		//	if (Settings::Misc::OmniSprint) {
		//		float max_speed = (self1.swimming() || self1.Ducking() > 0.5) ? 1.7f : 5.5f;
		//		Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
		//		self1.TargetMovement() = target_vel;
		//	}
		//}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
	return Globals::Functions::Original_UpdateVelocity(self);
}
Vector3 Hooks::hk_FakeGetModifiedAimConeDirection(float aimcone, Vector3 inputVec, bool anywhereInside)
{

	if (Settings::Combat::Silent::Silent && (Globals::Hotkeys::hotkey_SilentKey == 0 || Globals::PressedKeys[Globals::Hotkeys::hotkey_SilentKey]))
	{
		//Ulog("%s - hk_FakeGetModifiedAimConeDirection called", __FUNCTION__);


		Item item = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
		if (item.Base_)
		{
			BasePlayer target = FindTarget(Settings::Combat::Silent::SilentFOV);

			if (target.Base_)
			{
				auto primaryMagazine = item.baseProjectile.primaryMagazine();
				auto ammoType = Magazine(primaryMagazine).ammoType();
				if (ammoType != 0)
				{
					auto itemmodproj = GetComponent(GetType("ItemModProjectile, Assembly-CSharp"), ammoType);
					auto m_CachedPtr = *(UINT_PTR*)(ammoType + 0x10);
					auto gameobj = *(UINT_PTR*)(m_CachedPtr + 0x30);
					auto ItemModProjectile = itemmodproj;
					if (ItemModProjectile)
					{
						auto projectileObject = *(UINT_PTR*)(ItemModProjectile + 0x18);
						auto projectileType = GetType("Projectile, Assembly-CSharp");
						auto projectileClass = GetClassObject(projectileObject);
						UINT_PTR projectile = GetGameObjectComponent(projectileType, projectileClass);
						if (projectile)
						{
							float& integrity = *(float*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "integrity"));
							float& initialDistance = *(float*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "initialDistance"));
							Vector3& previousVelocity = *(Vector3*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "previousVelocity"));
							auto projectileVelocity = *(float*)(ItemModProjectile + 0x34);
							//auto projectileVelocityScale = item.baseProjectile.projectileVelocityScale() 
							auto projectileVelocityScale = (Settings::Combat::WeaponMods::FastBullet ? 1.499f : 1.f) * item.baseProjectile.projectileVelocityScale();//


							float drag = *(float*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "drag"));
							float gravityModifier = *(float*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "gravityModifier"));
							//float projectileDistance = *(float*)(projectile + Dumper::GetFieldOffet("Assembly-CSharp", "", "Projectile", "traveledDistance"));
							auto gravity = UnityEngine::get_gravity();
							auto get_fixedDeltaTime = UnityEngine::get_fixedDeltaTime();
							auto get_timeScale = UnityEngine::get_timeScale();
							float deltaTime = get_fixedDeltaTime * get_timeScale;
							Vector3 actualtargetposition = target.model.GetTransform(head).GetPosition();
							Vector3 localPosition = LocalPlayer.Eyes.GetPosition();
							//Vector3 playerVelocity = Vector3(target.GetWorldVelocity().x, 0, target.GetWorldVelocity().z);
							Vector3 playerVelocity = Vector3(target.GetWorldVelocity().x, 0, target.GetWorldVelocity().z) * 0.75f;

							Vector3 targetPosition = actualtargetposition;
							auto _aimdirection = Globals::Functions::Original_GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
							//float bulletTime = 1337.f;
							float bulletTime = std::sqrt((actualtargetposition.x) * (actualtargetposition.x) + (actualtargetposition.z) * (actualtargetposition.z));
							int sims = 1;
							while (sims < 30)
							{
								sims++;
								bool hitPlayer = false;

								_aimdirection = Globals::Functions::Original_GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
								Vector3 velocity = _aimdirection * projectileVelocity * projectileVelocityScale;

								auto currentPosition = localPosition;
								auto previousPosition = currentPosition;

								Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
								Vector3 offset = Vector3().Zero();

								for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
								{
									previousPosition = currentPosition;
									currentPosition += velocity * deltaTime;
									velocity += gravity * gravityModifier * deltaTime;
									velocity -= velocity * drag * deltaTime;

									//previousPosition = currentPosition;
									//previousVelocity = velocity;
									//currentPosition += velocity * deltaTime;
									//velocity += gravity * gravityModifier * deltaTime;
									//velocity -= velocity * drag * deltaTime;

									auto line = (currentPosition - previousPosition);
									auto len = line.UnityMagnitude();
									line.UnityNormalize();
									auto v = actualtargetposition - previousPosition;
									auto d = Vector3().UnityDot(v, line);

									if (d < 0.f)
									{
										d = 0.f;
									}
									else if (d > len)
									{
										d = len;
									}

									Vector3 nearestPoint = previousPosition + line * d;

									if (nearestPoint.distance(actualtargetposition) < 0.01f)
									{
										Ulog("Prediction Summary");
										Ulog("Total Simulations: %i", sims);
										Ulog("Player Velocity: {%f,%f,%f}", playerVelocity.x, playerVelocity.y, playerVelocity.z);
										Ulog("Bullet: Time To Target: %f", i * deltaTime);
										bulletTime = i * deltaTime;
										Ulog("Hit: Distance To Target Player Head: %f", nearestPoint.distance(actualtargetposition));
										Ulog("Hit: Distance To LocalPlayer Eyes: %f", nearestPoint.distance(localPosition));
										//return _aimdirection;
										hitPlayer = true;
									}
									else if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
									{
										closestPoint = nearestPoint;
										offset = actualtargetposition - nearestPoint;
									}
								}

								if (hitPlayer) break;
								targetPosition += offset;
							}


							if (bulletTime != 1337.f)
							{



								Vector3 finalVelocity = playerVelocity * bulletTime;

								actualtargetposition += finalVelocity;


								Vector3 targetPosition = actualtargetposition;
								auto _aimdirection = Globals::Functions::Original_GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
								float bulletTime = 1337.f;
								int sims = 0;
								while (sims < 30)
								{

									sims++;
									bool hitPlayer = false;

									_aimdirection = Globals::Functions::Original_GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
									Vector3 velocity = _aimdirection * projectileVelocity * projectileVelocityScale;

									auto currentPosition = localPosition;
									auto previousPosition = currentPosition;

									Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
									Vector3 offset = Vector3().Zero();

									for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
									{
										previousPosition = currentPosition;
										currentPosition += velocity * deltaTime;
										velocity += gravity * gravityModifier * deltaTime;
										velocity -= velocity * drag * deltaTime;

										auto line = (currentPosition - previousPosition);
										auto len = line.UnityMagnitude();
										line.UnityNormalize();
										auto v = actualtargetposition - previousPosition;
										auto d = Vector3().UnityDot(v, line);

										if (d < 0.f)
										{
											d = 0.f;
										}
										else if (d > len)
										{
											d = len;
										}

										Vector3 nearestPoint = previousPosition + line * d;

										if (nearestPoint.distance(actualtargetposition) < 0.1f)
										{
											Ulog("Prediction Summary");
											Ulog("Total Simulations: %i", sims);
											Ulog("Player Velocity: {%f,%f,%f}", playerVelocity.x, playerVelocity.y, playerVelocity.z);
											Ulog("AVG Vel: {%f,%f,%f}", target.avgVel.x, target.avgVel.y, target.avgVel.z);
											Ulog("Bullet: Time To Target: %f", i * deltaTime);
											bulletTime = i * deltaTime;
											Ulog("Hit: Distance To Target Player Head: %f", nearestPoint.distance(actualtargetposition));
											Ulog("Hit: Distance To LocalPlayer Eyes: %f", nearestPoint.distance(localPosition));
											//return _aimdirection;
											hitPlayer = true;
										}
										else if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
										{
											closestPoint = nearestPoint;
											offset = actualtargetposition - nearestPoint;
										}
									}

									if (hitPlayer) break;
									targetPosition += offset;
								}

								Ulog("8");
								return _aimdirection;
							}
						}
					}

				}
			}
		}

	}
	aimcone *= Settings::Combat::WeaponMods::Spread / 100.0f;


	return Globals::Functions::Original_GetModifiedAimConeDirection(aimcone, inputVec, anywhereInside);
}

void Hooks::hk_FrameUpdate(UINT_PTR PlayerModel, bool wounded)
{
	__try
	{
		if (Settings::Misc::SilentWalk)
		{
			static UINT_PTR model = 0x402402;
			static UINT_PTR flag = 0x402402;
			static UINT_PTR LCP = 0x402402;

			if (LCP == 0x402402)
			{
				LCP = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "isLocalPlayer");
			}

			auto& localplayer = *(bool*)(PlayerModel + LCP);

			if (!localplayer) {
				Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
				return;
			}

			if (model == 0x402402)
			{
				model = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "modelState");
			}

			if (flag == 0x402402)
			{
				flag = Dumper::GetFieldOffet("Rust.Data", "", "ModelState", "flags");
			}

			auto& modelState = *(UINT_PTR*)(PlayerModel + model);
			auto& modelflags = *(int*)(modelState + flag);

			int original = modelflags;
			modelflags |= (int)32;
			Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
			modelflags = original;
			return;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_FrameUpdate(PlayerModel, wounded);
}

Vector3 Hooks::hk_BodyLeanOffset(UINT_PTR a1)
{
	__try {
		if (Settings::Misc::Manipulator && !other::m_manipulate.empty()) {

			return other::m_manipulate;
		}

		return Globals::Functions::Original_BodyLeanOffset(a1);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
}
Vector3 Hooks::hk_EyePositionForPlayer(UINT_PTR arg1, UINT_PTR arg2, UINT_PTR arg3)
{
	BasePlayer player = arg2;
	__try
	{
		if (player.userID()) {
			if (Settings::Misc::Manipulator && Globals::Hotkeys::hotkey_Manipulator) {
				return Globals::Functions::Original_EyePositionForPlayer(arg1, arg2, arg3) + other::m_manipulate;
			}
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_EyePositionForPlayer(arg1, arg2, arg3);
}
void Hooks::hk_SendClientTick(UINT_PTR self)
{
	__try {
		BasePlayer plly = self;

		if (Settings::Misc::Spinbot)
		{
			if (LocalPlayer.Base_)
			{
				auto input = LocalPlayer.input.Base_;
				if (input)
				{
					auto state = *reinterpret_cast<UINT_PTR*>(input + 0x20);
					if (state)
					{
						auto current = *reinterpret_cast<UINT_PTR*>(state + 0x10);
						if (current)
						{
							*reinterpret_cast<Vector3*>(current + 0x18) = Vector3(rand() % 999 + -200, rand() % 600 + -200, rand() % 200 + -200);
						}
					}
				}
			}
		}



		//if (Settings::Misc::AntiFlyHack && LocalPlayer.Base_ != 0) {
		//	Vector3 current = LocalPlayer.get_transform().GetPosition();
		//	Vector3 old = LocalPlayer.lastSentTick().position();
		//	Vector3 vector4 = (LocalPlayer.get_transform().GetPosition() - LocalPlayer.lastSentTick().position());
		//	Vector3 overrided = Vector3(current.x, current.y, current.z);
		//	if (Settings::Misc::AntiFlyHack && Globals::FlyHack::VFlyhack >= (Globals::FlyHack::VMaxFlyhack - 1.5f))
		//	{
		//		overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
		//	}
		//	if (Settings::Misc::AntiFlyHack && Globals::FlyHack::HFlyhack >= (Globals::FlyHack::HMaxFlyhack - 1.5f))
		//	{
		//		overrided = Vector3(old.x, overrided.y, old.z);
		//	}
		//	if (Settings::Misc::AntiFlyHack && Globals::FlyHack::HFlyhack >= (Globals::FlyHack::HMaxFlyhack - 1.5f) ||
		//		Settings::Misc::AntiFlyHack && Globals::FlyHack::VFlyhack >= (Globals::FlyHack::VMaxFlyhack - 1.5f))
		//	{
		//		if (overrided != current)
		//			LocalPlayer.movement.TeleportTo(overrided, self);

		//	}
		//}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}


	return Globals::Functions::Original_SendClientTick(self);

}
void Hooks::hk_DoFirstPersonCamera(UINT_PTR a1, UINT_PTR cam) {
	__try {
		Component cam1 = cam;

		Globals::Functions::Original_DoFirstPersonCamera_hk(a1, cam);


		if (Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator] && !other::m_manipulate.empty()) {
			Vector3 re_p = LocalPlayer.get_transform().GetPosition() + LocalPlayer.get_transform().up() * (LocalPlayer.Eyes.EyeOffset().y + LocalPlayer.Eyes.viewOffset().y);

			cam1.get_transform().SetPosition(re_p);
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
	//return Globals::Functions::Original_DoFirstPersonCamera_hk(cam, a1);
}
void Hooks::hk_FakeVisUpdateUsingCulling(void* basePlayer, float dist, bool visibility)
{
	__try
	{
		//Ulog("%s - hk_FakeVisUpdateUsingCulling called", __FUNCTION__);
		if (Settings::Visuals::Players::Chams && !Settings::Visuals::Players::VisibleOnly)
			return Globals::Functions::Original_VisUpdateUsingCulling(basePlayer, 2.f, true);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_VisUpdateUsingCulling(basePlayer, dist, visibility);
}

Vector3 Hooks::hk_MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake MoveTowards called", __FUNCTION__);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "SimulateAimcone");
		}

		UINT_PTR returnAddress = (UINT_PTR)_ReturnAddress();

		if (returnAddress > var && returnAddress < var + 0x800)
		{
			target *= (Settings::Combat::WeaponMods::Recoil / 100.f);
			maxDistanceDelta *= Settings::Combat::WeaponMods::Recoil / 100.f;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_MoveTowards(current, target, maxDistanceDelta);
}

void Hooks::hk_AddPunch(UINT_PTR heldEntity, Vector3 amount, float duration)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake AddPunch called", __FUNCTION__);

		amount *= Settings::Combat::WeaponMods::Recoil / 100.0f;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_AddPunch(heldEntity, amount, duration);
}

void Hooks::hk_EokaDoAttack(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Eoka DoAttack called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::InstantEoka)
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Assembly-CSharp", "", "FlintStrikeWeapon", "_didSparkThisFrame");
			}

			auto& _didSparkThisFrame = *(bool*)(baseProjectile + var);
			_didSparkThisFrame = true;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_EokaDoAttack(baseProjectile);
}

void Hooks::hk_UpdateGravity(UINT_PTR PlayerWalkMovement, UINT_PTR state)
{
	__try
	{
		//Ulog("%s - hk_UpdateGravity called", __FUNCTION__);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerWalkMovement", "gravityMultiplier");
		}

		auto& gravityMultiplier = *(float*)(PlayerWalkMovement + var);
		auto origianlGravity = gravityMultiplier;
		if (Settings::Misc::JumpHigh) {
			gravityMultiplier = 1.25f;
		}


		Globals::Functions::Original_UpdateGravity(PlayerWalkMovement, state);

		gravityMultiplier = origianlGravity;

		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
	return Globals::Functions::Original_UpdateGravity(PlayerWalkMovement, state);
}

void Hooks::hk_SetFlying(UINT_PTR ModelState)
{
	// always use SEH in any hook cus its a god given right

	__try
	{
		if (Settings::Misc::FakeAdmin) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_SetFlying(ModelState);
}

void Hooks::hk_DoAttack(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake DoAttack called", __FUNCTION__);

		static UINT_PTR automatic_var = 0x402402;

		if (automatic_var == 0x402402)
		{
			automatic_var = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "automatic");
		}

		auto& automatic = *(bool*)(baseProjectile + automatic_var);
		auto defaultAutomaticValue = automatic;

		if (Settings::Combat::WeaponMods::Automatic) automatic = true;

		static UINT_PTR repeatDelay_var = 0x402402;

		if (repeatDelay_var == 0x402402)
		{
			repeatDelay_var = Dumper::GetFieldOffet("Assembly-CSharp", "", "AttackEntity", "repeatDelay");
		}

		auto& repeatDelay = *(float*)(baseProjectile + repeatDelay_var);
		auto defaultrepeatDelay = repeatDelay;

		repeatDelay /= Settings::Combat::WeaponMods::FireRate / 100.f;

		auto& projectileVelocityScale = BaseProjectile(baseProjectile).projectileVelocityScale();
		auto defaultprojectileVelocityScale = projectileVelocityScale;

		projectileVelocityScale *= Settings::Combat::WeaponMods::FastBulletSpeed;
		//projectileVelocityScale *= wcscmp(LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem()).itemDefinition.GetDisplayName(), L"L96 Rifle") ? 1.3f : Settings::Combat::WeaponMods::FastBulletSpeed;;

		Globals::Functions::Original_DoAttack(baseProjectile);

		projectileVelocityScale = defaultprojectileVelocityScale;
		automatic = defaultAutomaticValue;
		repeatDelay = defaultrepeatDelay;

		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoAttack(baseProjectile);
}

void Hooks::hk_OnCameraPositionChanged(UINT_PTR baseViewModel, UINT_PTR camera, UINT_PTR basePlayer)
{
	__try {
		//Ulog("%s - hk_OnCameraPositionChanged called", __FUNCTION__);
		static UINT_PTR bobVar = 0x402402;
		static UINT_PTR lowerVar = 0x402402;
		static UINT_PTR swayVar = 0x402402;

		if (bobVar == 0x402402)
			bobVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "bob");

		if (lowerVar == 0x402402)
			lowerVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "lower");

		if (swayVar == 0x402402)
			swayVar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseViewModel", "sway");

		auto& bob = *(UINT_PTR*)(baseViewModel + bobVar);
		auto defaultBobValue = bob;

		auto& lower = *(UINT_PTR*)(baseViewModel + lowerVar);
		auto defaultLowerValue = lower;

		auto& sway = *(UINT_PTR*)(baseViewModel + swayVar);
		auto defaultSwayValue = sway;

		if (Settings::Misc::NoBobbing)
			bob = 0;
		if (Settings::Misc::NoLowering)
			lower = 0;
		if (Settings::Misc::NoSwaying)
			sway = 0;

		Globals::Functions::Original_OnCameraPositionChanged(baseViewModel, camera, basePlayer);

		bob = defaultBobValue;
		lower = defaultLowerValue;
		sway = defaultSwayValue;

		return;
	}
	__except (true) {
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnCameraPositionChanged(baseViewModel, camera, basePlayer);
}

void Hooks::hk_EditViewAngles(UINT_PTR baseProjectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake DoAttack called", __FUNCTION__);

		static UINT_PTR aimswayvar = 0x402402;
		static UINT_PTR aimSwaySpeedvar = 0x402402;

		if (aimswayvar == 0x402402)
		{
			aimswayvar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "aimSway");
		}

		if (aimSwaySpeedvar == 0x402402)
		{
			aimSwaySpeedvar = Dumper::GetFieldOffet("Assembly-CSharp", "", "BaseProjectile", "aimSwaySpeed");
		}

		auto& aimsway = *(float*)(baseProjectile + aimswayvar);
		auto& aimSwaySpeed = *(float*)(baseProjectile + aimSwaySpeedvar);
		auto defaultAimSwayValue = aimsway;

		aimsway *= Settings::Combat::WeaponMods::Sway / 100.f;
		aimSwaySpeed *= Settings::Combat::WeaponMods::Sway / 100.f;

		Globals::Functions::Original_EditViewAngles(baseProjectile);

		aimsway = defaultAimSwayValue;
		aimSwaySpeed = defaultAimSwayValue;
		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_EditViewAngles(baseProjectile);
}

void Hooks::hk_ViewModelPlay(UINT_PTR viewModel, pUncStr name, int layer)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Play called", __FUNCTION__);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BaseProjectile", "DoAttack");
		}

		UINT_PTR returnAddress = (UINT_PTR)_ReturnAddress();

		if (returnAddress > var && returnAddress < var + 0x296)
		{
			if (Settings::Combat::WeaponMods::NoAttackAnimation) return;
			//target *= (Settings::Combat::WeaponMods::Recoil / 100.f);
			//maxDistanceDelta *= Settings::Combat::WeaponMods::Recoil / 100.f;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ViewModelPlay(viewModel, name, layer);
}

bool Hooks::hk_CanHoldItems(UINT_PTR baseMountable)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_CanHoldItems called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	if (Settings::Misc::CanAttack)
	{
		return true;
	}

	return Globals::Functions::Original_CanHoldItems(baseMountable);
}

bool Hooks::hk_DoHit(UINT_PTR projectile, UINT_PTR test, Vector3 point, Vector3 normal)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		HitTest hitTest(test);

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("Assembly-CSharp", "", "Projectile", "get_isAuthoritative");
		}

		typedef bool Method(UINT_PTR);
		bool auth = ((Method*)(Globals::g_GameAssemblyBase + var))(projectile);
		if (Settings::Combat::WeaponMods::Penetrate) {
			if (auth)
			{
				if (hitTest.HitEntity() != 0)
				{
					auto zzz = *(UINT_PTR*)(hitTest.HitEntity());
					auto className = *(char**)(zzz + 0x10);

					bool validPlayer = false;
					if (strstr(className, "Corpse"))
						validPlayer = false;
					else if (strstr(className, "BasePlayer"))
						validPlayer = true;
					else if (strstr(className, "BanditGuard"))
						validPlayer = true;
					else if (strstr(className, "UnderwaterDweller"))
						validPlayer = true;
					else if (strstr(className, "TunnelDweller"))
						validPlayer = true;
					else if (strstr(className, "ScientistNPCNew"))
						validPlayer = true;
					else if (strstr(className, "HumanNPCNew"))
						validPlayer = true;
					else if (strstr(className, "HTNPlayer"))
						validPlayer = true;
					else if (strstr(className, "Scientist"))
						validPlayer = true;
					else if (strstr(className, "NPCPlayer"))
						validPlayer = true;
					else if (strstr(className, "HumanNPC"))
						validPlayer = true;
					else if (strstr(className, "NPCMurderer"))
						validPlayer = true;
					else if (strstr(className, "NPCPlayerApex"))
						validPlayer = true;
					else if (strstr(className, "HeavyScientist"))
						validPlayer = true;

					if (validPlayer)
					{
					}

					if (strstr(className, "CargoShip"))
						return false;
					else if (strstr(className, "RHIB"))
						return false;
					else if (strstr(className, "WaterCatcher"))
						return false;
					else if (strstr(className, "JunkPile"))
						return false;
					else if (strstr(className, "MotorRowboat"))
						return false;
					else if (strstr(className, "RidableHorse"))
						return false;
					else if (strstr(className, "ResourceEntity"))
						return false;
					else if (strstr(className, "BuildingPrivlidge"))
						return false;
					else if (strstr(className, "HackableLockedCrate"))
						return false;
					else if (strstr(className, "TreeEntity"))
						return false;
					else if (strstr(className, "ScrapTransportHelicopter"))
						return false;
					else if (strstr(className, "BoxStorage"))
						return false;
					else if (strstr(className, "VendingMachine"))
						return false;
					else if (strstr(className, "CH47HelicopterAIController"))
						return false;
					else if (strstr(className, "MiniCopter"))
						return false;
					else if (strstr(className, "SupplyDrop"))
						return false;
					else if (strstr(className, "SimplebuildingBlock"))
						return false;
					else if (strstr(className, "MiningQuarry"))
						return false;
					else if (strstr(className, "RepairBench"))
						return false;
					else if (strstr(className, "ResearchTable"))
						return false;
					else if (strstr(className, "IceFence"))
						return false;
					else if (strstr(className, "LootContainer"))
						return false;
					else if (strstr(className, "OreResourceEntity"))
						return false;
					else if (strstr(className, "ElevatorLift"))
						return false;
					else if (strstr(className, "Elevator"))
						return false;
					//else if (strstr(className, "Barricade"))
						//return false;
					else if (strstr(className, "BaseOven"))
						return false;
					else if (strstr(className, "Workbench"))
						return false;
				}
			}
		}

		//Ulog("%s - Fake Launch called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoHit(projectile, test, point, normal);
}

void Hooks::hk_HandleRunDuckCrawl(UINT_PTR PlayerWalkMovement, UINT_PTR state, bool wantsRun, bool wantsDuck, bool wantsCrawl)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		if (Settings::Misc::OmniSprint) wantsRun = true;
		//Ulog("%s - hk_HandleRunDuckCrawl called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_HandleRunDuckCrawl(PlayerWalkMovement, state, wantsRun, wantsDuck, wantsCrawl);
}
bool Hooks::hk_ConsoleRun(UINT_PTR args, UINT_PTR str, UINT_PTR args2)
{

	if (*reinterpret_cast<bool*>(args + 0x6)) {
		auto str2 = reinterpret_cast<String*>(str);
		if (str2->buffer) {
			auto string = std::wstring(str2->buffer);
			if (string.find(xorstr_(L"noclip")) != std::wstring::npos ||
				string.find(xorstr_(L"debugcamera")) != std::wstring::npos ||
				string.find(xorstr_(L"admintime")) != std::wstring::npos ||
				string.find(xorstr_(L"camlerp")) != std::wstring::npos ||
				string.find(xorstr_(L"culling.debug")) != std::wstring::npos ||
				string.find(xorstr_(L"client.camlookspeed")) != std::wstring::npos ||
				string.find(xorstr_(L"camspeed")) != std::wstring::npos) {

				str2 = String::New(xorstr_(""));
				str = NULL;
			}
		}
	}
	return Globals::Functions::Original_ConsoleRun(args, str, args2);
}
bool Hooks::hk_CanAttack(UINT_PTR basePlayer)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake CanAttack called", __FUNCTION__);
		if (Settings::Misc::CanAttack) return true;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_CanAttack(basePlayer);
}

void Hooks::hk_OnLand(UINT_PTR basePlayer, float velocity)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake On Land called", __FUNCTION__);

		if (Settings::Misc::NoFallDamage) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnLand(basePlayer, velocity);
}

void Hooks::hk_ProjectileMovement(UINT_PTR projectile, float deltaTime)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		Projectile pr = projectile;
		float& thickness = *(float*)(projectile + 0x2C);
		auto defaultThickness = thickness;
		thickness = Settings::Combat::WeaponMods::Thickness;
		Globals::Functions::Original_ProjectileMovement(projectile, deltaTime);
		thickness = defaultThickness;
		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ProjectileMovement(projectile, deltaTime);
}

void Hooks::hk_OnAttacked(UINT_PTR basePlayer, UINT_PTR info)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_OnAttacked called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::CustomHitSound)
		{
			static float lastPlay = 0.f;

			if (UnityEngine::get_realtimeSinceStartup() > lastPlay + 0.1f)
			{
				lastPlay = UnityEngine::get_realtimeSinceStartup();
				PlaySoundA(Settings::Combat::WeaponMods::HitSound, NULL, SND_ASYNC);
			}
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnAttacked(basePlayer, info);
}

void Hooks::hk_DoHitNotify(UINT_PTR Entity, UINT_PTR info)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_DoHitNotify called", __FUNCTION__);

		BasePlayer basePlayer(Entity);

		HitInfo hitInfo(info);
		DamageTypeList damageTypeList(hitInfo.damageTypes());

		//Ulog("Hit %ls in %ls for %.2f damage", basePlayer.GetDisplayName(), hitInfo.GetBoneName()->str, damageTypeList.Total());

		if (Settings::Combat::WeaponMods::CustomHitSound) return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_DoHitNotify(Entity, info);
}

bool Hooks::hk_GetIsHeadshot(UINT_PTR hitInfo)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_GetIsHeadshot called", __FUNCTION__);

		if (Settings::Combat::WeaponMods::CustomHitSound) return false;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_GetIsHeadshot(hitInfo);
}

void Hooks::hk_SendProjectileAttack(UINT_PTR basePlayer, UINT_PTR playerProjectileAttack)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{//
		//Ulog("%s - hk_SendProjectileAttack called", __FUNCTION__);

		auto playerAttack = *(UINT_PTR*)(playerProjectileAttack + 0x18);
		auto& distance = *(float*)(playerProjectileAttack + 0x2C);
		auto attack = *(UINT_PTR*)(playerAttack + 0x18);
		auto& hitBone = *(UINT_PTR*)(attack + 0x30);
		//auto hitid = *(UINT_PTR*)(attack + 0x2C);
		//auto& hitBone = *(UINT_PTR*)(attack + 0x30);



		if (Settings::Combat::WeaponMods::OVDist) {
			distance = Settings::Combat::WeaponMods::OVDistance;
		}
		if (Settings::Combat::WeaponMods::OVHitbox) {
			hitBone = Settings::Combat::WeaponMods::OVHit;
		}
		if (Settings::Combat::WeaponMods::HeliWeakspot && FindTarget) {
			hitBone = 224139191;
		}
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_SendProjectileAttack(basePlayer, playerProjectileAttack);
}

bool Hooks::hk_IsWaterMaterial(UINT_PTR projectile, UINT_PTR materialName)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_IsWaterMaterial called", __FUNCTION__);
		//return false;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_IsWaterMaterial(projectile, materialName);
}

bool Hooks::hk_HasPermission(UINT_PTR args, UINT_PTR second)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_HandleJumping called", __FUNCTION__);
		if (Settings::Misc::FakeAdmin)
		{
			static UINT_PTR var = 0x402402;
			static UINT_PTR var2 = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetFieldOffet("Facepunch.Console", "", "ConsoleSystem.Arg", "cmd");
			}

			if (var2 == 0x402402)
			{
				var2 = Dumper::GetFieldOffet("Facepunch.Console", "", "ConsoleSystem.Command", "AllowRunFromServer");
			}

			UINT_PTR cmd = *(UINT_PTR*)(args + var);
			auto& AllowRun = *(bool*)(cmd + var2);

			AllowRun = false;
			bool retstate = Globals::Functions::Original_HasPermission(args, second);
			AllowRun = true;
			return retstate;
		}
		else
			return Globals::Functions::Original_HasPermission(args, second);
		

	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_HasPermission(args, second);
}

void Hooks::hk_HandleJumping(UINT_PTR playerWalkMovement, UINT_PTR modelState, bool wantsJump, bool jumpInDirection)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - hk_HandleJumping called", __FUNCTION__);

		if (!Settings::Misc::InfJump)
			return Globals::Functions::Original_HandleJumping(playerWalkMovement, modelState, wantsJump, jumpInDirection);

		if (wantsJump)
		{
			static UINT_PTR var = 0x402402;

			if (var == 0x402402)
			{
				var = Dumper::GetMethodOffset("Assembly-CSharp", "", "PlayerWalkMovement", "Jump");
			}

			typedef pUncStr Method(UINT_PTR, UINT_PTR, bool);
			((Method*)(Globals::g_GameAssemblyBase + var))(playerWalkMovement, modelState, jumpInDirection);
		}

		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_HandleJumping(playerWalkMovement, modelState, wantsJump, jumpInDirection);
}

void Hooks::hk_Launch(UINT_PTR projectile)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		//Ulog("%s - Fake Launch called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_Launch(projectile);
}


void Hooks::hk_OnGUI(UINT_PTR rcx)
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{

		//Ulog("%s - Fake OnGUI called", __FUNCTION__);

	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_OnGUI(rcx);
}

/*
float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;
void TestFlying() {
	flyhackPauseTime = Max(0.f, flyhackPauseTime - UnityEngine::get_fixedDeltaTime());
	bool inAir = false;

	typedef float Method(UINT_PTR);
	float radius = LocalPlayer.GetRadius();//((Method*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetRadius")))(LocalPlayer.Base_);
	//float radius = reinterpret_cast<float(*)(BasePlayer*)>(vars::stor::gBase + CO::GetRadius)(LocalPlayer::Entity());
	float height = LocalPlayer.GetHeight();//((Method*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "BasePlayer", "GetHeight")))(LocalPlayer.Base_);
	//float height = reinterpret_cast<float(*)(BasePlayer*, bool)>(vars::stor::gBase + CO::GetHeight)(LocalPlayer::Entity(), false);
	UINT_PTR lastSentTick = *(UINT_PTR*)(LocalPlayer.Base_ + Dumper::GetFieldOffet("Assembly-CSharp", "", "BasePlayer", "lastSentTick"));
	Vector3 lastSentPosition = *(Vector3*)(lastSentTick + Dumper::GetFieldOffet("Rust.Data", "", "PlayerTick", "position"));
	Vector3 position = *(Vector3*)(LocalPlayer.playerModel.Base_ + Dumper::GetFieldOffet("Assembly-CSharp", "", "PlayerModel", "position"));
	Vector3 vector = (lastSentPosition + position) * 0.5f;
	//Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + read(read(LocalPlayer::Entity() + (playermodel)0x4B0, uintptr_t) + (velocity or position)0x1D8, Vector3)) * 0.5f;
	Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
	Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	float radius2 = radius - 0.05f;
	bool a = UnityEngine::CheckCapsule(vector2, vector3, radius2, 1503731969);
	inAir = !a;

	if (inAir) {
		bool flag = false;
		Vector3 vector4 = position - lastSentPosition;
		//Vector3 vector4 = read(read(LocalPlayer::Entity() + 0x4B0, uintptr_t) + 0x1D8, Vector3) - LocalPlayer::Entity()->lastSentTick()->position();
		float num3 = abs(vector4.y);
		float num4 = vector4.magnitude2d();
		//float num4 = reinterpret_cast<float(*)(Vector3)>(vars::stor::gBase + CO::Magnitude2D)(vector4);
		if (vector4.y >= 0.f) {
			flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num3 < num4) {
			flyhackDistanceHorizontal += num4;
			flag = true;
		}
		if (flag) {
			float num5 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num6 = LocalPlayer.GetJumpHeight() + num5;
			//float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
			if (flyhackDistanceVertical > num6) {
				//return true;
			}
			float num7 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num8 = 5.f + num7;
			if (flyhackDistanceHorizontal > num8) {
				//return true;
			}
		}
	}
	else {
		flyhackDistanceHorizontal = 0.f;
		flyhackDistanceVertical = 0.f;
	}
}

void CheckFlyhack() {
	TestFlying();
	float num5 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer.GetJumpHeight() + num5;
	Vars::Global::max_flyhack = num6;
	//vars::stuff::max_flyhack = num6;
	//if (flyhackDistanceVertical <= num6)
	{
		Vars::Global::flyhack = flyhackDistanceVertical;
	}

	float num7 = Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	Vars::Global::max_hor_flyhack = num8;
	//vars::stuff::max_hor_flyhack = num8;
	//if (flyhackDistanceHorizontal <= num8)
	{
		Vars::Global::hor_flyhack = flyhackDistanceHorizontal;
	}
}*/
void Hooks::hk_LaunchProjectile(UINT_PTR P)
{

	if (Settings::Combat::Rage::PowerShot && Globals::PressedKeys[Globals::Hotkeys::hotkey_InstaKill])
	{

		heldEntity = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());


		float r = ((UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime())) / heldEntity.baseProjectile.repeatDelay();

		if (r <= 0)
			Globals::Functions::Original_LaunchProjectile(P);
		else
			for (size_t i = 0; i < r; i++)
			{
				Globals::Functions::Original_LaunchProjectile(P);

				auto mag = *reinterpret_cast<uintptr_t*>((uintptr_t)heldEntity.baseProjectile.primaryMagazine_ptr());
				auto c = *reinterpret_cast<int*>((uintptr_t)mag + 0x1C); //0x1C = public int contents;
				*reinterpret_cast<int*>((uintptr_t)mag + 0x1C) = (c - 1);


				//			heldEntity.baseProjectile.ricochetChance() = 100;
				heldEntity.baseProjectile.UpdateAmmoDisplay();
				heldEntity.baseProjectile.ShotFired();
				heldEntity.baseProjectile.DidAttackClientside();
			}
		//return;
	}
	return Globals::Functions::Original_LaunchProjectile(P);
}

void AutoMed() {
	if (!Settings::Misc::AutoMed)
		return;

	if (LocalPlayer.clActiveItem() != 0) {
		Item activeItem = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
		if (activeItem.heldEntity()) {
			if (std::wstring(activeItem.itemDefinition.GetShortName()).find(L"syringe") != std::string::npos ||
				std::wstring(activeItem.itemDefinition.GetShortName()).find(L"bandage") != std::string::npos &&
				activeItem.baseProjectile.timeSinceDeploy() > activeItem.baseProjectile.deployDelay() && activeItem.baseProjectile.get_NextAttackTime() > UnityEngine::get_fixedTime()) {
				if (LocalPlayer.health() < 95.0f)
				activeItem.baseProjectile.ServerRPC(Str(L"UseSelf"));
			}
		}
	}
}


void FlyHack() {
	__try {

		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.5f;
		float flyhack_extrusion = 2.0f;

		bool flag = false;

		bool isInAir = false;
		Vector3 vector = (LocalPlayer.lastSentTick().position() + LocalPlayer.get_transform().GetPosition()) * 0.5f;
		Globals::FlyHack::flyhackPauseTime = max(0.f, Globals::FlyHack::flyhackPauseTime - UnityEngine::get_deltaTime());

		if (!LocalPlayer.movement.ladder() && !UnityEngine::WaterLevelTest(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, LocalPlayer.Base_)) {
			float radius = LocalPlayer.GetRadius();
			float height = LocalPlayer.GetHeight(false);

			Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
			Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
			float radius2 = radius - 0.05f;

			isInAir = !UnityEngine::CheckCapsule(vector2, vector3, radius2, 1503731969, UnityEngine::QueryTriggerInteraction::Ignore);

			if (isInAir) {
				Vector3 vector4 = (LocalPlayer.get_transform().GetPosition() - LocalPlayer.lastSentTick().position());
				float num2 = std::abs(vector4.y);
				float num3 = vector4.magnitude2d();
				if (vector4.y >= 0.0f) {
					Globals::FlyHack::flyhackDistanceVertical += vector4.y;
					flag = true;
				}
				if (num2 < num3) {
					Globals::FlyHack::flyhackDistanceHorizontal += num3;
					flag = true;
				}
				if (flag) {
					float num5 = ((Globals::FlyHack::flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
					float num6 = (LocalPlayer.GetJumpHeight() + num5) * 3;
					if (Globals::FlyHack::flyhackDistanceVertical > num6) {
						//std::cout << OBFUSCATE_STR("Got Flyhacked") << std::endl;
					}
					float num7 = max((Globals::FlyHack::flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
					float num8 = (5.f + num7) * 3;
					if (Globals::FlyHack::flyhackDistanceHorizontal > num8) {
						//std::cout << OBFUSCATE_STR("Got Flyhacked") << std::endl;
					}
				}

			}
			else {
				Globals::FlyHack::flyhackDistanceHorizontal = 0.f;
				Globals::FlyHack::flyhackDistanceVertical = 0.f;
			}
			float num5 = max((Globals::FlyHack::flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
			float num6 = ((LocalPlayer.GetJumpHeight() + num5) * 3);
			//num6 = 13.0f;
			Globals::FlyHack::VMaxFlyhack = num6;//(num6 * 2) - 2;
			if (Globals::FlyHack::flyhackDistanceVertical <= (num6)) {
				Globals::FlyHack::VFlyhack = Globals::FlyHack::flyhackDistanceVertical;
			}
			if (Globals::FlyHack::VFlyhack >= Globals::FlyHack::VMaxFlyhack)
				Globals::FlyHack::VFlyhack = Globals::FlyHack::VMaxFlyhack;
			float num7 = max((Globals::FlyHack::flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
			float num8 = 5.f + num7;
			//num8 = 26.0f;
			Globals::FlyHack::HMaxFlyhack = num8;//(num8 * 2) - 2; //- (VFlyhack * 2);//(num6 * 2);
			if (Globals::FlyHack::flyhackDistanceHorizontal <= (num8)) {
				Globals::FlyHack::HFlyhack = Globals::FlyHack::flyhackDistanceHorizontal;// +(VFlyhack * 2);
			}
			if (Globals::FlyHack::HFlyhack >= Globals::FlyHack::HMaxFlyhack)
				Globals::FlyHack::HFlyhack = Globals::FlyHack::HMaxFlyhack;

		}
		else {
			Globals::FlyHack::flyhackDistanceHorizontal = 0.f;
			Globals::FlyHack::flyhackDistanceVertical = 0.f;
		}
		if (!isInAir) {
			Globals::FlyHack::flyhackDistanceHorizontal = 0.f;
			Globals::FlyHack::flyhackDistanceVertical = 0.f;
		}
		if (UnityEngine::WaterLevelTest(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, LocalPlayer.Base_)) {
			Globals::FlyHack::flyhackDistanceHorizontal = 0.f;
			Globals::FlyHack::flyhackDistanceVertical = 0.f;
		}
	}
	__except (true) {
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}
}


void Hooks::hk_ClientInput(UINT_PTR basePlayer, UINT_PTR state)
{
	// always use SEH in any hook cus its a god given right
	//
	BasePlayer pBasePlayer = basePlayer;
	__try
	{


		if (Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator])
			pBasePlayer.clientTickInterval() = 0.99f;
		else {
			pBasePlayer.clientTickInterval() = 0.05f;
		}
		if (Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator]) {
			other::find_manipulate_angle();
		}
		else if (!other::m_manipulate.empty()) {
			other::m_manipulate = Vector3::Zero();
		}

		if (Settings::Misc::FakeLag) {
			pBasePlayer.clientTickInterval() = 0.4f;
		}
		else if (Settings::Misc::FakeLag) {
			LocalPlayer.clientTickInterval() = 0.04f;
		}

		UnityEngine::DDrawGet();

		if (Settings::Misc::FakeAdmin)
		{
			pBasePlayer.playerFlags() |= PlayerFlags::IsAdmin;
		}
		if (Settings::Misc::AutoMed)
		{
			AutoMed();
		}


		Visuals::SyncedInput();

		UnityEngine::IgnoreLayerCollision(12, 4, !Settings::Misc::WalkOnWater);
		UnityEngine::IgnoreLayerCollision(12, 30, Settings::Misc::WalkThroughTrees);
		UnityEngine::IgnoreLayerCollision(12, 11, Settings::Misc::WalkThroughPlayers);

		//FlyHack();

		Globals::Functions::Original_ClientInput(basePlayer, state);


		return;
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ClientInput(basePlayer, state);
}

bool Hooks::hk_FakeShouldShowHud()
{
	// always use SEH in any hook cus its a god given right
	//

	__try
	{
		// Ulog("%s - Fake should show hud called", __FUNCTION__);
	}
	__except (true)
	{
		Ulog("%s - Exception occurred.", __FUNCTION__);
	}

	return Globals::Functions::Original_ShouldShowHud();
}