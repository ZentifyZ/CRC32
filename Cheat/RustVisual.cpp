#pragma once
#include "pch.h"
float timeBefore;
Vector3 LocalPosition;
Quaternion LocalRotation;
Vector3 beforeInvalid = Vector3().Zero();
void Visuals::AddObject(char* Prefab, char* Name, bool Draw, bool Alive)
{
	bool Exists = false;

	for (const ESPOption& option : ESPOptions)
	{
		if (option.Prefab == Prefab)
			Exists = true;
	}

	if (!Exists)
	{
		ESPOption Op;
		Op.Draw = Draw;
		Op.Prefab = Prefab;
		Op.Name = Name;
		Op.Alive = Alive;
		ESPOptions.push_back(Op);
	}

	for (ESPOption& option : ESPOptions)
	{
		if (option.Prefab == Prefab)
		{
			ImGui::Checkbox(option.Name, &option.Draw);

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
				ImGui::OpenPopup(option.Name);

			if (ImGui::BeginPopup(option.Name))
			{
				ImGui::Checkbox("Name", &option.DrawName);
				ImGui::Checkbox("Distance", &option.DrawDistance);
				ImGui::ColorEdit4("Color", (float*)&option.Color, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Max Distance", &option.checkMaxDistance);
				if (option.checkMaxDistance) ImGui::SliderFloat("Max Draw Distance", &option.MaxDistance, 0.f, 400.f);
				ImGui::EndPopup();
			}
		}
	}
}


bool AreAllDataInitialized()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;

	__try
	{
		// Making sure GlobalObjectManager is ready
		if (Globals::g_GlobalObjectManager &&
			Globals::g_GlobalObjectManager->pGlobalObjectManager->pListStart &&

			// Making sure the BaseNetworkable is ready
			Globals::g_BaseNetworkable &&
			Globals::g_BaseNetworkable->pBaseNetworkable &&
			Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm &&
			Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->BufferListCount)
		{
			return true;
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
	return false;
}

class Text
{
public:
	Text(Vector3 pos, ImU32 col, std::string string)
	{
		this->Position = pos;
		this->Color = col;
		this->Input = string;
	}
	Vector3 Position;
	ImU32 Color;
	std::string Input;
};

std::list<Text> textList;
std::list<Text> temp_textList;
std::list<Text> g_textList;

class TextGroup
{
public:
	TextGroup(Vector3 pos)
	{
		this->textList = g_textList;
		this->Position = pos;
	}

	std::list<Text> textList;
	Vector3 Position;
};

std::list<TextGroup> textGroupList;
std::list<TextGroup> temp_textGroupList;

bool RefreshShaders = false;

void DrawBasePlayer(BasePlayer basePlayer)
{
	if (!((basePlayer.lifestate() == LifeState::Alive || basePlayer.health() >= 0.1f))) return;
	Vector3 position = basePlayer.get_transform().GetPosition();


	ImU32 Skeleton = ImColor(Settings::Visuals::Players::Colors::Skeleton[0], Settings::Visuals::Players::Colors::Skeleton[1], Settings::Visuals::Players::Colors::Skeleton[2]);
	bool Visible = false;

	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

	BoneList Bones[15] = {
		l_foot, l_knee, l_hip,
		r_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
	};

	CornerBox cornerBox;

	for (int j = 0; j < 15; j++)
	{
		auto currentBoneV3 = basePlayer.model.GetTransform(BoneList(Bones[j])).GetPosition(); Vector2 bone_screen;
		if (Bones[j] == BoneList(head))
		{
			currentBoneV3.y += 0.2f;
		}
		else if (Bones[j] == BoneList(r_foot) || Bones[j] == BoneList(l_foot))
		{
			currentBoneV3.y -= 0.2f;
		}
		WorldToScreen(currentBoneV3, bone_screen);
		if (bone_screen.x < ret.left)
		{
			ret.left = bone_screen.x;
			cornerBox.left = currentBoneV3;
		}
		if (bone_screen.x > ret.right)
		{
			ret.right = bone_screen.x;
			cornerBox.right = currentBoneV3;
		}
		if (bone_screen.y < ret.top)
		{
			ret.top = bone_screen.y;
			cornerBox.top = currentBoneV3;
		}
		if (bone_screen.y > ret.bottom)
		{
			ret.bottom = bone_screen.y;
			cornerBox.bottom = currentBoneV3;
		}
	}

	if (ret.empty()) cornerBox.Valid = false;

	cornerBox.Color = Skeleton;


	temp_basePlayerVectorList.push_back(BasePlayerVectors(basePlayer, position, cornerBox, Visible));
	if (Settings::Visuals::Players::Skeleton)
	{
		CreateBoneLine(BoneList(head), BoneList(neck), Skeleton, basePlayer);

		{
			CreateBoneLine(BoneList(neck), BoneList(l_clavicle), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_clavicle), BoneList(l_upperarm), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_upperarm), BoneList(l_forearm), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_forearm), BoneList(l_ulna), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_ulna), BoneList(l_hand), Skeleton, basePlayer);
		}

		{
			CreateBoneLine(BoneList(neck), BoneList(r_clavicle), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_clavicle), BoneList(r_upperarm), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_upperarm), BoneList(r_forearm), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_forearm), BoneList(r_ulna), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_ulna), BoneList(r_hand), Skeleton, basePlayer);
		}

		CreateBoneLine(BoneList(neck), BoneList(spine4), Skeleton, basePlayer);
		CreateBoneLine(BoneList(spine4), BoneList(spine3), Skeleton, basePlayer);
		CreateBoneLine(BoneList(spine3), BoneList(spine2), Skeleton, basePlayer);
		CreateBoneLine(BoneList(spine2), BoneList(spine1), Skeleton, basePlayer);
		{
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), Skeleton, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(l_hip), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_hip), BoneList(l_knee), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_knee), BoneList(l_ankle_scale), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_ankle_scale), BoneList(l_foot), Skeleton, basePlayer);
			CreateBoneLine(BoneList(l_foot), BoneList(l_toe), Skeleton, basePlayer);
		}

		{
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), Skeleton, basePlayer);
			CreateBoneLine(BoneList(spine1), BoneList(r_hip), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_hip), BoneList(r_knee), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_knee), BoneList(r_ankle_scale), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_ankle_scale), BoneList(r_foot), Skeleton, basePlayer);
			CreateBoneLine(BoneList(r_foot), BoneList(r_toe), Skeleton, basePlayer);
		}
	}

	if (Settings::Visuals::Players::Chams)
	{
		static UINT_PTR asset_bundle = 0x402402;

		static UINT_PTR shader = 0;
		static int setShader = 420;

		auto multimesh = basePlayer.playerModel._multiMesh();
		if (multimesh)
		{
			SkinnedMultiMesh mesh(multimesh);
			auto mainRendList = mesh.get_Renderers();
			for (int idx = 0; idx < mainRendList->get_size(); idx++)
			{
				Renderer renderer(mainRendList->get_value(idx));
				if (renderer.Base_ != 0)
				{
					Material material(renderer.get_material());
					if (material.Base_ != 0)
					{
						if (shader != material.get_shader())
						{
							material.set_shader(shader);
						}
						if (!shader)
							shader = material.shader().Find(Str(L"Hidden/Internal-Colored"));
						material.SetInt(Str(L"_ZTest"), 8);
						material.SetColor(Str(L"_Color"), Color(Settings::Visuals::Players::Colors::Chams[0], Settings::Visuals::Players::Colors::Chams[1], Settings::Visuals::Players::Colors::Chams[2], Settings::Visuals::Players::Colors::Chams[3]));

					}
				}
			}
		}
	}
}

void HandleBasePlayer(UINT_PTR player_ptr, char* entityClass)
{
	__try
	{
		BasePlayer basePlayer = BasePlayer(player_ptr);
		basePlayer.className = entityClass;

		if (basePlayer.Base_ == 0)
		{
			Ulog("%s - Exception Occurred.", entityClass);
			return;
		}

		if (basePlayer.playerModel.Base_ == 0) return;
		if (basePlayer.model.Base_ == 0) return;
		if (basePlayer.Inventory.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerBelt.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerWear.Base_ == 0) return;
		if (basePlayer.Inventory.ContainerBelt.GetItemList() == 0) return;
		if (basePlayer.Inventory.ContainerBelt.GetItems() == 0) return;

		TempBasePlayers.push_back(basePlayer);
		if (strstr(entityClass, "BasePlayer"))
		{
			if (!Settings::Visuals::Players::Players) return;
			if ((basePlayer.lifestate() != LifeState::Alive || basePlayer.health() < 0.1f)) return;
			if (basePlayer.playerFlags() & PlayerFlags(Sleeping) && !Settings::Visuals::Players::Sleepers) return;
			if (basePlayer.playerFlags() & PlayerFlags(Wounded) && !Settings::Visuals::Players::Wounded) return;
		}
		else
		{
			if (!Settings::Visuals::Players::NPC) return;
		}

		DrawBasePlayer(basePlayer);
	}
	__except (true)
	{
		Ulog("%s - Exception Occurred.", __FUNCTION__);
	}
}

void HandleObject(EntityClass* curEntity)
{
	for (ESPOption& option : ESPOptions)
	{
		if (option.Draw && strstr(curEntity->m_CachedPtr->pObjectClass->pPrefabNameString, option.Prefab))
		{
			auto mainclass = curEntity->m_CachedPtr->pBaseClass;
			BaseEntity baseEntity(mainclass);
			auto transform = baseEntity.get_transform();
			auto position = transform.GetPosition();
			std::string string;

			if (option.checkMaxDistance && option.MaxDistance < position.distance(LocalPlayer.get_transform().GetPosition())) break;

			if (option.DrawDistance)
			{
				char buf[256] = { 0 }; sprintf_s(buf, "[%.f m] ", position.distance(LocalPlayer.get_transform().GetPosition()));
				string += buf;
			}
			if (option.DrawName)
			{
				char buf[256] = { 0 }; sprintf_s(buf, "%s", option.Name);
				string += buf;
			}

			temp_textList.push_back(Text(position, ImColor(option.Color[0], option.Color[1], option.Color[2]), string));
			break;
		}
	}


}

BasePlayer lastTarget;


BasePlayer LightFindTarget(float fovDistance, bool meleeCheck = false) {
	BasePlayer target;
	if (Settings::Combat::Aimbot::KeepTarget && lastTarget.Base_ != 0) {
		if ((strstr(lastTarget.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnorePlayers) || (!strstr(lastTarget.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnoreNPCs)) {
			if (strstr(lastTarget.className, "BasePlayer")) {
				if ((target.lifestate() == LifeState::Alive || target.health() > 0.1f)) {
					if (!(target.playerFlags() & PlayerFlags(Sleeping)) || !Settings::Combat::Aimbot::IgnoreSleepers) {
						if (!(target.playerFlags() & PlayerFlags(Wounded)) || !Settings::Combat::Aimbot::IgnoreWounded) {
							if (UnityEngine::LineOfSight(lastTarget.model.GetTransform(head).GetPosition(), LocalPlayer.Eyes.GetPosition())) {
								Vector2 position;
								if (!meleeCheck) {
									if (WorldToScreen(lastTarget.model.GetTransform(neck).GetPosition(), position)) {
										if (fovDistance > position.Distance(GetScreenCenter())) {
											return lastTarget;
										}
									}
								}
								else {
									if (lastTarget.model.GetTransform(neck).GetPosition().distance(LocalPosition) > 3.3f)
										return target;

									return lastTarget;
								}
							}
						}
					}
				}
			}
		}
	}

	for (BasePlayer& basePlayer : BasePlayers) {
		if ((strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnorePlayers) || (!strstr(basePlayer.className, "BasePlayer") && !Settings::Combat::Aimbot::IgnoreNPCs)) {
			if (strstr(basePlayer.className, "BasePlayer")) {
				if ((basePlayer.lifestate() != LifeState::Alive || basePlayer.health() < 0.1f)) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Sleeping) && Settings::Combat::Aimbot::IgnoreSleepers) continue;
				if (basePlayer.playerFlags() & PlayerFlags(Wounded) && Settings::Combat::Aimbot::IgnoreWounded) continue;
			}

			if (UnityEngine::LineOfSight(basePlayer.model.GetTransform(head).GetPosition(), LocalPlayer.Eyes.GetPosition())) {
				Vector2 position;
				Vector3 transformPosition = basePlayer.model.GetTransform(neck).GetPosition();

				if (!meleeCheck) {
					if (WorldToScreen(transformPosition, position)) {
						if (fovDistance > position.Distance(GetScreenCenter())) {
							fovDistance = position.Distance(GetScreenCenter());
							target = basePlayer;
						}
					}
				}
				else {
					if (transformPosition.distance(LocalPosition) > 3.3f)
						continue;

					target = basePlayer;
				}
			}
		}
	}

	lastTarget = target;
	return target;
}

inline void StepConstant(Vector2& angles)
{
	bool smooth = Settings::Combat::Aimbot::Smoothing;
	int smooth_factor = Settings::Combat::Aimbot::SmoothingAmount;
	Vector2 angles_step = angles - LocalPlayer.input.bodyAngles();
	Normalize(angles_step.x, angles_step.y);

	if (smooth) {
		float factor_pitch = (smooth_factor / 10.f);
		if (angles_step.x < 0.f) {
			if (factor_pitch > std::abs(angles_step.x)) {
				factor_pitch = std::abs(angles_step.x);
			}
			angles.x = LocalPlayer.input.bodyAngles().x - factor_pitch;
		}
		else {
			if (factor_pitch > angles_step.x) {
				factor_pitch = angles_step.x;
			}
			angles.x = LocalPlayer.input.bodyAngles().x + factor_pitch;
		}
	}
	if (smooth) {
		float factor_yaw = (smooth_factor / 10.f);
		if (angles_step.y < 0.f) {
			if (factor_yaw > std::abs(angles_step.y)) {
				factor_yaw = std::abs(angles_step.y);
			}
			angles.y = LocalPlayer.input.bodyAngles().y - factor_yaw;
		}
		else {
			if (factor_yaw > angles_step.y) {
				factor_yaw = angles_step.y;
			}
			angles.y = LocalPlayer.input.bodyAngles().y + factor_yaw;
		}
	}
}

void Aimbot()
{
	if (LocalPlayer.Base_ != 0)
	{
		if (Settings::Combat::Aimbot::Aimbot && (Globals::Hotkeys::hotkey_AimbotKey == 0 || Globals::PressedKeys[Globals::Hotkeys::hotkey_AimbotKey]))
		{
			Item item = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
			if (item.Base_)
			{
				BasePlayer target = LightFindTarget(Settings::Combat::Aimbot::FOV);

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
								auto projectileVelocity = *(float*)(ItemModProjectile + 0x34);
								auto projectileVelocityScale = item.baseProjectile.projectileVelocityScale();
								float drag = *(float*)(projectile + 0x24);
								float gravityModifier = *(float*)(projectile + 0x28);
								auto gravity = UnityEngine::get_gravity();
								auto get_fixedDeltaTime = UnityEngine::get_fixedDeltaTime();
								auto get_timeScale = UnityEngine::get_timeScale();
								float deltaTime = get_fixedDeltaTime * get_timeScale;
								Vector3 actualtargetposition = target.model.GetTransform(head).GetPosition();
								Vector3 localPosition = LocalPlayer.Eyes.GetPosition();
								Vector3 playerVelocity = Vector3(target.GetWorldVelocity().x, 0, target.GetWorldVelocity().z) * 0.75f;

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
											bulletTime = i * deltaTime;
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
												bulletTime = i * deltaTime;
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

									auto angle_offset = CalcAngle(localPosition, targetPosition) - LocalPlayer.input.bodyAngles();
									Normalize(angle_offset.y, angle_offset.x);
									Vector2 AimAngle = LocalPlayer.input.bodyAngles() + angle_offset;
									if (Settings::Combat::Aimbot::Smoothing && Settings::Combat::Aimbot::SmoothingAmount != 0)
										StepConstant(AimAngle);
									Normalize(AimAngle.y, AimAngle.x);
									LocalPlayer.input.bodyAngles() = AimAngle;
									return;

								}
							}
						}
					}
				}
			}
		}
	}
}

void DrawProjectilePath()
{
	if (LocalPlayer.Base_ != 0)
	{
		Item item = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
		if (item.Base_)
		{
			BasePlayer target = LightFindTarget(Settings::Combat::Silent::SilentFOV);

			if (target.Base_)
			{
				auto primaryMagazine = item.baseProjectile.primaryMagazine();
				auto ammoType = Magazine(primaryMagazine).ammoType();
				if (ammoType != 0)
				{
					auto m_CachedPtr = *(UINT_PTR*)(ammoType + 0x10);
					auto gameobj = *(UINT_PTR*)(m_CachedPtr + 0x30);
					auto ItemModProjectile = getComponent(gameobj, "ItemModProjectile");
					if (ItemModProjectile)
					{
						auto projectileObject = *(UINT_PTR*)(ItemModProjectile + 0x18);
						auto a2 = *(UINT_PTR*)(projectileObject + 0x18);
						auto a3 = *(UINT_PTR*)(a2 + 0x10);
						UINT_PTR projectile = getComponent(a3, "Projectile");
						if (projectile)
						{
							auto projectileVelocity = *(float*)(ItemModProjectile + 0x34);
							auto projectileVelocityScale = item.baseProjectile.projectileVelocityScale();
							float drag = *(float*)(projectile + 0x24);
							float gravityModifier = *(float*)(projectile + 0x28);
							auto gravity = UnityEngine::get_gravity();
							auto get_fixedDeltaTime = UnityEngine::get_fixedDeltaTime();
							auto get_timeScale = UnityEngine::get_timeScale();
							float deltaTime = get_fixedDeltaTime * get_timeScale;
							//float offset = 0.1f;
							int simulations = 0;
							Vector3 actualtargetposition = target.model.GetTransform(head).GetPosition();
							Vector3 localPosition = LocalPlayer.Eyes.GetPosition();

							Vector3 targetPosition = actualtargetposition;
							while (simulations < 30)
							{
								auto _aimdirection = Globals::Functions::Original_GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
								Vector3 velocity = _aimdirection * projectileVelocity * projectileVelocityScale;

								auto currentPosition = localPosition;
								auto previousPosition = currentPosition;

								//auto previousOffset = offset;

								Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
								Vector3 offset = Vector3().Zero();

								for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
								{
									previousPosition = currentPosition;
									currentPosition += velocity * deltaTime;
									velocity += gravity * gravityModifier * deltaTime;
									velocity -= velocity * drag * deltaTime;

									float distance = abs(currentPosition.distance(previousPosition));

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
										temp_textList.push_back(Text(nearestPoint, ImColor(0.f, 1.f, 0.f), "HIT"));
										return;
									}
									else
									{
										if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
										{
											closestPoint = nearestPoint;
											offset = actualtargetposition - nearestPoint;
										}
										//if (d != 0.f && d != len)
										{
											//if (actualtargetposition.y > nearestPoint.y)
											{
												//offset += 0.5f;
												//targetPosition
												//offset += abs(nearestPoint.distance(actualtargetposition));
												//break;
											}
											//else
											{
												//offset -= 0.5f;
												//offset -= abs(nearestPoint.distance(actualtargetposition));
												//break;
											}
										}
										//temp_textList.push_back(Text(nearestPoint, ImColor(1.f, 0.f, 0.f), "CLOSEST"));
									}

									TempILines.push_back(ILine(previousPosition, currentPosition, ImColor(1.f, 0.f, 0.f)));

									/*
									public static Vector3 NearestPointOnFiniteLine(Vector3 start, Vector3 end, Vector3 pnt)
									{
										var line = (end - start);
										var len = line.magnitude;
										line.Normalize();

										var v = pnt - start;
										var d = Vector3.Dot(v, line);
										d = Mathf.Clamp(d, 0f, len);
										return start + line * d;
									}
									*/
								}

								targetPosition += offset;

								//if (offset == previousOffset)
								//{
									//offset += 0.1f;
								//}

								simulations++;
							}
						}
					}
				}
			}
		}
	}
}
void AutoFarm() {
	if (!Settings::Misc::AntiFlyHack)
		return;

	if (LocalPlayer.Inventory.ContainerBelt.GetSize() > 0) {
		auto pInventory = (ContainerInventory*)LocalPlayer.Inventory.ContainerBelt.GetItems();

		for (int i = 0; i < 6; i++) {
			if (pInventory) {
				auto invitem = pInventory->Item[i];

				if (invitem) {
					Item item(invitem);
					if (item.itemDefinition.Base_ != 0 && item.Base_ != 0) {
						if (LocalPlayer.clActiveItem() == item.uid()) {
							std::string sbuffer;
							char sbuf[256] = { 0 }; sprintf_s(sbuf, "%ls", item.itemDefinition.GetShortName());
							sbuffer = sbuf;
							if (LocalPlayer.clActiveItem() == item.uid() && sbuffer.length() > 0) {
								if (LocalPlayer.clActiveItem() == item.uid() && (strstr(item.className(), "BaseMelee") || strstr(item.className(), "Chainsaw") || strstr(item.className(), "Jackhammer"))) {
									BaseMelee baseMelee(item.heldEntity());
									BaseEntity target = BaseEntity();
									auto distance = baseMelee.maxDistance() * 1.75f;
									Vector3 eyePosition = LocalPlayer.Eyes.GetPosition();
									bool isTree = false;
									bool isTreeMarker = false;
									BasePlayer playerTarget = LightFindTarget(Settings::Combat::Silent::SilentFOV, true);
									Vector3 treeMarker;

									if (playerTarget.Base_ == 0) {
										for (BasePlayer& basePlayer : basePlayers) {
											if (UnityEngine::LineOfSight(basePlayer.model.GetTransform(47).GetPosition(), eyePosition, 10551296)) {
												auto dist = basePlayer.model.GetTransform(head).GetPosition().Distance(eyePosition);
												if (distance > dist) {
													distance = dist;
													playerTarget = basePlayer;
												}
											}
										}
									}


									if (target.Base_ == 0 && playerTarget.Base_ == 0) {
										break;
									}

									if (baseMelee.HasAttackCooldown()) {
										break;
									}

									if (!baseMelee.IsFullyDeployed() && !(baseMelee.timeSinceDeploy() > (baseMelee.deployDelay() * 1.05f))) {
										break;
									}

									Vector3 position;
									if (playerTarget.Base_ != 0) {
										position = playerTarget.model.GetTransform(head).GetPosition();
									}
									else {
										position = target.get_transform().GetPosition();
									}
									auto localPosition = LocalPlayer.model.GetTransform(BoneList(neck)).GetPosition();

									HitTest hTest = HitTest();
									hTest.MaxDistance() = 1000.0f;
									Ray ray = Ray(localPosition, (position - localPosition).normalized());
									hTest.AttackRay() = ray;
									hTest.DidHit() = true;
									if (playerTarget.Base_ != 0) {
										hTest.HitTransform() = playerTarget.model.GetTransform(head).Base_;
										hTest.HitEntity() = playerTarget.Base_;
										hTest.HitPoint() = playerTarget.model.GetTransform(head).InverseTransformPoint(position);
										hTest.HitNormal() = playerTarget.model.GetTransform(head).InverseTransformPoint(position);
									}
									else {
										hTest.HitTransform() = target.get_transform().Base_;
										hTest.HitEntity() = target.Base_;
										hTest.HitPoint() = target.get_transform().InverseTransformPoint(position);
										hTest.HitNormal() = target.get_transform().InverseTransformPoint(position);
									}
									hTest.damageProperties() = baseMelee.damageProperties();

									baseMelee.StartAttackCooldown(baseMelee.repeatDelay());
									//if (!strstr(item.className(), "Jackhammer")) baseMelee.DoViewmodelImpact();
									baseMelee.ProcessInputTime();
				
									if (baseMelee.CanHit(hTest)) {
										baseMelee.ProcessAttack(hTest);
									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}
void Visuals::SyncedInput()
{
	if (!AreAllDataInitialized()) return;

	static float LastShaderRefresh = 0.f;
	static float LastUpdate = 0.f;
	static float LastRefresh = 0.f;

	if (Settings::Misc::GroundAngles)
	{
		LocalPlayer.movement.groundAngle() = 0.f;
		LocalPlayer.movement.groundAngleNew() = 0.f;
	}


	if (LocalPlayer.Base_ != 0)
	{
		LocalPosition = LocalPlayer.get_transform().GetPosition();
		LocalRotation = LocalPlayer.Eyes.GetRotation();
		heldEntity = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());//



		if (Settings::Misc::AntiFlyHack) {
			AutoFarm();
		}
		//DrawProjectilePath();

		if (Settings::Misc::TimeChanger) {
			AdminTime adminTime = AdminTime();
			adminTime.SetAdminTime(Settings::Misc::TimeChangerAmount);
		}

		Graphics graphicsInstance = Graphics();
		if (Settings::Misc::FOVChanger) {
			graphicsInstance.SetFov(Globals::PressedKeys[Globals::Hotkeys::hotkey_Zoom] ? 14.f : Settings::Misc::FOVChangerAmount);
		}
		else {
			graphicsInstance.SetFov(90.f);
		}

		Aimbot();

		static float lastFireTime = 0.f;

		if (Settings::Combat::WeaponMods::Spam)
		{
			if (UnityEngine::get_realtimeSinceStartup() > lastFireTime + 1.f / Settings::Combat::WeaponMods::SpamRate)
			{
				lastFireTime = UnityEngine::get_realtimeSinceStartup();
				if (LocalPlayer.clActiveItem() != 0)
				{
					Item activeItem = LocalPlayer.Inventory.ContainerBelt.FindActiveItem(LocalPlayer.clActiveItem());
					if (activeItem.heldEntity())
					{
						if (Settings::Combat::WeaponMods::AlwaysSpam)
						{
							UnityEngine::SendSignalBroadcast(activeItem.heldEntity(), Signal::Attack);
						}
						else if (Globals::PressedKeys[Globals::Hotkeys::hotkey_SpamKey])
						{
							UnityEngine::SendSignalBroadcast(activeItem.heldEntity(), Signal::Attack);
						}
					}
				}
			}
		}
		else
		{
			lastFireTime = 0.f;
		}

		static float lastFallTime = 0.f;

		if (Settings::Misc::Suicide)
		{
			if (UnityEngine::get_realtimeSinceStartup() > lastFallTime + 1.f / Settings::Misc::SuicideRate)
			{
				lastFallTime = UnityEngine::get_realtimeSinceStartup();

				if (Settings::Misc::AlwaysSuicide || Globals::PressedKeys[Globals::Hotkeys::hotkey_SuicideKey])
				{
					LocalPlayer.OnLand(-50.f);
					LocalPlayer.OnLand(-50.f);
				}
			}
		}
		else
		{
			lastFallTime = 0.f;
		}

		static bool alreadystartedReload = false;

		static bool alreadyReset = false;	

		if (Settings::Combat::Silent::Silent && (Globals::Hotkeys::hotkey_SilentKey == 0 || Globals::PressedKeys[Globals::Hotkeys::hotkey_SilentKey]) && Settings::Combat::Silent::AutoShoot && heldEntity.Base_  && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator] != 0) {
			if (heldEntity.baseProjectile.primaryMagazine().contents() != 0) {
				if (LightFindTarget(Settings::Combat::Silent::SilentFOV).Base_ != 0) {
					if (!heldEntity.baseProjectile.HasAttackCooldown()) {
						heldEntity.baseProjectile.LaunchProjectile();
						heldEntity.baseProjectile.primaryMagazine().contents()--;
						heldEntity.baseProjectile.UpdateAmmoDisplay();
						heldEntity.baseProjectile.ShotFired();
						heldEntity.baseProjectile.DidAttackClientside();
						heldEntity.baseProjectile.BeginCycle();
					}
				}
			}
		}
	}

}
void DrawEntity(UINT_PTR BasePlayers)
{
	if (LocalPlayer.Base_ != 0) {

		BasePlayer basePlayer = BasePlayers;

		if (Settings::Misc::KeepWoundedAlive) {
			if (LocalPlayer.get_transform().GetPosition().distance(basePlayer.get_transform().GetPosition()) < 5.0f) {
				if (basePlayer.HasPlayerFlag(PlayerFlags::Wounded)) {
					basePlayer.ServerRPC(Str(L"RPC_KeepAlive"));
				}
			}
		}
	}
}
void Visuals::SyncedThread()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (!AreAllDataInitialized()) return;

		for (int i = 0; i <= Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->BufferListCount; i++)
		{
			auto curEntity = Globals::g_BaseNetworkable->pBaseNetworkable->pEntityRealm->pClientEntities->pEntityList->pBufferListVals->pBufferListData->Items[i].pItemClass;

			if (!curEntity || !curEntity->m_CachedPtr || !curEntity->pClassPointer || !curEntity->pClassPointer->pEntityClassNameString)
				continue;




			if (strcmp(curEntity->m_CachedPtr->pObjectClass->pPrefabNameString, "LocalPlayer") == 0)
			{
				BasePlayer basePlayer = BasePlayer(curEntity->m_CachedPtr->pBaseClass);
				basePlayer.className = curEntity->pClassPointer->pEntityClassNameString;
				LocalPlayer = basePlayer;
			}
			else
			{
				if (curEntity->class_name_hash() == STATIC_CRC32("BasePlayer") ||
					curEntity->class_name_hash() == STATIC_CRC32("NPCPlayerApex") ||
					curEntity->class_name_hash() == STATIC_CRC32("NPCMurderer") ||
					curEntity->class_name_hash() == STATIC_CRC32("NPCPlayer") ||
					curEntity->class_name_hash() == STATIC_CRC32("HumanNPC") ||
					curEntity->class_name_hash() == STATIC_CRC32("Scientist") ||
					curEntity->class_name_hash() == STATIC_CRC32("HTNPlayer") ||
					curEntity->class_name_hash() == STATIC_CRC32("HumanNPCNew") ||
					curEntity->class_name_hash() == STATIC_CRC32("ScientistNPCNew") ||
					curEntity->class_name_hash() == STATIC_CRC32("ScientistNPC") ||
					curEntity->class_name_hash() == STATIC_CRC32("TunnelDweller") ||
					curEntity->class_name_hash() == STATIC_CRC32("BanditGuard")) {

					DrawEntity(curEntity->m_CachedPtr->pBaseClass);
					HandleBasePlayer(curEntity->m_CachedPtr->pBaseClass, curEntity->pClassPointer->pEntityClassNameString);

				}
				else
				{
					HandleObject(curEntity);
				}
			}
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

	textGroupList = temp_textGroupList;
	temp_textGroupList.clear();

	textList = temp_textList;
	temp_textList.clear();

	ILines = TempILines;
	TempILines.clear();

	BasePlayers = TempBasePlayers;
	TempBasePlayers.clear();

	basePlayerVectorList = temp_basePlayerVectorList;
	temp_basePlayerVectorList.clear();
}
void CTHookIndicators() {
	Vector2 FlyHackBarSize = Vector2(600, 8);
	int FlyHackYStart = 50; // 50 looks perfect Y
	float xs = Vars::Global::ScreenWidth, ys = Vars::Global::ScreenHigh;

	DrawList = ImGui::GetBackgroundDrawList();
	struct Indicator_t { ImColor color; std::string text; bool draw_bar = false; float percentage = 0.f; };
	std::vector< Indicator_t > indicators{ };

	// Menu::Vars::misc_desync
	//if (Menu::Vars::combat_autoreload && ent) {
	//	float reloadDuration = other::time_since_last_shot;
	//	float reloadDurationTotal = ent->CalculateCooldownTime(ent->nextReloadTime(), ent->reloadTime()) - GLOBAL_TIME;
	//	auto percentage = (((reloadDuration / reloadDurationTotal) * 100.0f) + 1.f) / 100.0f;
	//	auto clampedPercentage = std::clamp(percentage, 0.f, 100.f);

	//	Indicator_t ind{ };
	//	ind.color = ImColor(215, 230, 10);
	//	ind.text = xorstr_("AUTO RELOAD");
	//	ind.draw_bar = true;
	//	ind.percentage = clampedPercentage;

	//	indicators.push_back(ind);
	//}

	if (Settings::Combat::Rage::DesyncInd == 3 && Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator]) {
		float desyncTime = (UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime());
		auto percentage = (((desyncTime) * 100.0f)) / 100;
		Indicator_t ind{ };
		ind.color = ImColor(215, 230, 10);
		ind.text = xorstr_("DESYNC TIME");
		ind.draw_bar = true;
		ind.percentage = percentage;

		indicators.push_back(ind);
	}

	//if ( Menu::Vars::misc_automed ) {
	//	Indicator_t ind { };
	//	ind.color = ImColor( 215, 230, 10 );
	//	ind.text = xorstr_( "NIGGER" );

	//	indicators.push_back( ind );
	//}

	//if ( Menu::Vars::misc_automed ) {
	//	Indicator_t ind { };
	//	ind.color = ImColor( 215, 230, 10 );
	//	ind.text = xorstr_( "TESTING THIS BITCH" );

	//	indicators.push_back( ind );
	//}

	//if (Menu::Vars::visuals_reloadind && ent) {
	//	float reloadDuration = ent->nextReloadTime() - GLOBAL_TIME;
	//	float reloadDurationTotal = ent->CalculateCooldownTime(ent->nextReloadTime(), ent->reloadTime()) - GLOBAL_TIME;
	//	auto percentage = (((reloadDuration / reloadDurationTotal) * 100.0f) + 1.f) / 100;
	//	auto clampedPercentage = std::clamp(percentage, 0.f, 100.f);
	//	Indicator_t ind{ };
	//	ind.color = ImColor(215, 230, 10);
	//	ind.text = xorstr_("RELOAD TIME");
	//	ind.draw_bar = true;
	//	ind.percentage = clampedPercentage;

	//	indicators.push_back(ind);
	//}

	if (indicators.empty())
		return;

	// iterate and draw indicators.
	for (size_t i{ }; i < indicators.size(); ++i) {
		auto& indicator = indicators[i];

		float xs = 80, ys = Vars::Global::ScreenHigh - 67 - (32 * i);

		Vector2 BarSize = Vector2(110, 10);

		if (indicator.draw_bar) {
			DrawFilledBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x, BarSize.y), ImColor{ 0, 0, 0, 255 });
			DrawFilledBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x * (indicator.percentage), BarSize.y), indicator.color);
			DrawOutlineBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x, BarSize.y), ImColor{ 0, 0, 0 });

			DrawList->AddText({ 25 + BarSize.x / 2 - ImGui::CalcTextSize(indicator.text.c_str()).x / 2, Vars::Global::ScreenHigh - 80 - (32 * i) }, indicator.color, indicator.text.c_str());
		}
		else
			DrawList->AddText({ 25 + BarSize.x / 2 - ImGui::CalcTextSize(indicator.text.c_str()).x / 2, Vars::Global::ScreenHigh - 80 - (24 * i) }, indicator.color, indicator.text.c_str());
	}

	// replace with checkbox (2lazy rn im almost sleeping) owo
	//if (Menu::Vars::misc_AntiFlyhack) {
	//	DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0, 255 });
	//	DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x * (VFlyhack / VMaxFlyhack), FlyHackBarSize.y), ImColor(255, 0, 0));
	//	DrawOutlineBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0 });
	//}

	//if (Menu::Vars::misc_AntiFlyhack) {
	//	DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0, 255 });
	//	DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(FlyHackBarSize.x * (HFlyhack / HMaxFlyhack), FlyHackBarSize.y), ImColor(255, 0, 0));
	//	DrawOutlineBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(600, FlyHackBarSize.y), ImColor{ 0, 0, 0 });
	//}
}

void SafeDraw()
{
	DrawList = ImGui::GetBackgroundDrawList();

	if (!AreAllDataInitialized() || LocalPlayer.Base_ == 0)
	{
		StaticCamera = 0;
		return;
	}

	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	CTHookIndicators();

	if (Settings::Combat::Rage::DesyncInd == 2 && Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator]) {
		auto desynctime = UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;

		float red, green, blue;
		float Num = desyncpercentage;
		if (desyncpercentage < 0.1)
			Num = 0;

		if (Settings::Combat::Rage::ShowDesync && Num != 0) {
			if (Num < 0.5) {
				red = Num * 2.f * 255.f;
				green = 255.f;
				blue = 0.f;
			}
			else {
				red = 255.f;
				green = (2.f - 2.f * Num) * 255.f;
				blue = 0.f;
			}

			if (Num > 1.f)
				Num = 1.f;

			ImVec2 center(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2);

			std::string text = "TESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTTESTSTTESTS"; //cancer omg
			ImVec2 size = ImGui::CalcTextSize(text.c_str());
			DrawList->AddRectFilled({ xs - (size.x / 6.5f), ys - 130.f }, { xs + (size.x / 6.1f), ys - 125.f }, ImColor(40, 40, 40));

			float x = (desynctime * size.x / 1.5f) / 2.f;
			if (x > (size.x / 1.5f) * 2)
				x = (size.x / 1.5f) * 2; //s
			DrawList->AddRectFilled({ xs - (size.x / 6.5f), ys - 130.f }, { (xs - ((size.x / 6.1f))) + x, ys - 125.f }, ImColor((int)(red), (int)(green), (int)(blue)));
			//DrawList->AddLine(ImVec2(center.x, center.y), ImVec2(center.x + 200, center.y), ImColor((int)(red), (int)(green), (int)(blue)), 15);

		}
	}

	if (Settings::Combat::Rage::DesyncInd == 1 && Settings::Misc::Manipulator && Globals::PressedKeys[Globals::Hotkeys::hotkey_Manipulator])
	{
		auto desynctime = UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime();
		auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;

		float red, green, blue;
		float Num = desyncpercentage;
		if (desyncpercentage < 0.1)
			Num = 0;

		if (Settings::Combat::Rage::ShowDesync && Num != 0)
		{
			if (Num < 0.5)
			{
				red = Num * 2.f * 255.f;
				green = 255.f;
				blue = 0.f;
			}
			else
			{
				red = 255.f;
				green = (2.f - 2.f * Num) * 255.f;
				blue = 0.f;
			}

			if (Num > 1.f)
				Num = 1.f;

			ImVec2 center(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2);

			DrawList->PathArcTo({ center.x, center.y - 1 }, -42, PI, 0, 48);
			DrawList->PathStroke(ImColor(40, 40, 40, 230), false, 5);

			DrawList->PathArcTo({ center.x, center.y - 1 }, -42, PI * Num, 0, 48);
			DrawList->PathStroke(ImColor((int)(red), (int)(green), (int)(blue)), false, 5);
		}
	}

	if (Menu::currentCrosshair == 1)
		DrawCrossCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 2)
		DrawXCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 3)
		DrawCircleCrosshair(Settings::Misc::CrosshairSize);
	else if (Menu::currentCrosshair == 4)
		DrawCustomCrosshair(Settings::Misc::CrosshairSize, Settings::Misc::CrosshairThickness, Settings::Misc::CrosshairGap);




	for (const ILine& iLine : ILines)
	{
		Vector2 startPosition; Vector2 endPosition;

		auto p0w = WorldToScreen(iLine.Start, startPosition);
		auto p1w = WorldToScreen(iLine.End, endPosition);
		if ((p0w && p1w))
			DrawList->AddLine(ImVec2(startPosition.x, startPosition.y), ImVec2(endPosition.x, endPosition.y), iLine.Color);
	}
	for (const Text& text : textList)
	{
		Vector2 screenPosition;
		if (WorldToScreen(text.Position, screenPosition))
		{
			DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(text.Input.c_str()).x / 2), screenPosition.y }, text.Color, text.Input.c_str());
		}
	}

	for (const TextGroup& textGroup : textGroupList)
	{
		Vector2 screenPosition;
		if (WorldToScreen(textGroup.Position, screenPosition))
		{
			for (const Text& text : textGroup.textList)
			{
				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(text.Input.c_str()).x / 2), screenPosition.y }, text.Color, text.Input.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}
		}
	}
	for (BasePlayerVectors& basePlayerV3 : basePlayerVectorList)
	{
		Vector3 position = basePlayerV3.position;
		BasePlayer basePlayer = basePlayerV3.basePlayer;
		CornerBox cornerBox = basePlayerV3.cornerBox;
		Vector2 screenPosition;
		Vector3 textPosition = position;

		ImU32 Name = ImColor(Settings::Visuals::Players::Colors::Name[0], Settings::Visuals::Players::Colors::Name[1], Settings::Visuals::Players::Colors::Name[2]);
		ImU32 Health = ImColor(Settings::Visuals::Players::Colors::Health[0], Settings::Visuals::Players::Colors::Health[1], Settings::Visuals::Players::Colors::Health[2]);
		ImU32 Distance = ImColor(Settings::Visuals::Players::Colors::Distance[0], Settings::Visuals::Players::Colors::Distance[1], Settings::Visuals::Players::Colors::Distance[2]);
		ImU32 HeldItem = ImColor(Settings::Visuals::Players::Colors::HeldItem[0], Settings::Visuals::Players::Colors::HeldItem[1], Settings::Visuals::Players::Colors::HeldItem[2]);
		ImU32 OOF = ImColor(Settings::Visuals::Players::Colors::OOF[0], Settings::Visuals::Players::Colors::OOF[1], Settings::Visuals::Players::Colors::OOF[2]);
		ImU32 SnapLines = ImColor(Settings::Visuals::Players::Colors::Snaplines[0], Settings::Visuals::Players::Colors::Snaplines[1], Settings::Visuals::Players::Colors::Snaplines[2]);
		ImU32 Box = ImColor(Settings::Visuals::Players::Colors::Box[0], Settings::Visuals::Players::Colors::Box[1], Settings::Visuals::Players::Colors::Box[2]);



		if (Settings::Visuals::Players::CornerBox)
		{
			if (cornerBox.Valid)
			{
				Vector2 left;
				auto leftw2s = WorldToScreen(cornerBox.left, left);

				Vector2 right;
				auto rightw2s = WorldToScreen(cornerBox.right, right);

				Vector2 top;
				auto topw2s = WorldToScreen(cornerBox.top, top);

				Vector2 bottom;
				auto bottomw2s = WorldToScreen(cornerBox.bottom, bottom);

				if (cornerBox.Valid && leftw2s || rightw2s || topw2s || bottomw2s)
				{
					DrawCornerBox(Vector2(left.x, top.y), Vector2(right.x, bottom.y), Box, 1.5f);
				}
			}
		}
		textPosition.y -= 0.3f;

		auto vis = WorldToScreen(textPosition, screenPosition);

		if (vis)
		{
			if (Settings::Visuals::Players::Name)
			{
				std::string string;

				char buf[256] = { 0 }; sprintf_s(buf, "%ls", basePlayer.GetDisplayName());
				string += buf;

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, Name, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}


			if (Settings::Visuals::Players::Distance)
			{
				std::string string;

				char buf[256] = { 0 }; sprintf_s(buf, "%.f M", position.distance(LocalPosition));
				string = buf;

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, Distance, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}
			if (Settings::Visuals::Players::Health)
			{
				char buf[256] = { 0 }; sprintf_s(buf, " %.f HP", basePlayer.health());
				std::string string = buf;

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, Health, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}
		

			if (Settings::Visuals::Players::HeldItem)
			{
				std::string string;
				if (basePlayer.clActiveItem() != 0)
				{
					Item item = basePlayer.Inventory.ContainerBelt.FindActiveItem(basePlayer.clActiveItem());
					if (item.Base_)
					{
						char buf[256] = { 0 }; sprintf_s(buf, "%ls", item.itemDefinition.GetDisplayName());
						basePlayer.HeldWeapon = buf;
						string = buf;
					}
					else
					{
						string = "None";
					}
				}
				else
				{
					string = "None";
				}

				DrawList->AddText({ screenPosition.x - (ImGui::CalcTextSize(string.c_str()).x / 2), screenPosition.y }, HeldItem, string.c_str());
				screenPosition.y += ImGui::CalcTextSize("1").y;
			}


			if (Settings::Visuals::Players::Snaplines)
			{
				DrawList->AddLine(ImVec2(GetScreenSize().Width / 2, GetScreenSize().Height - 100.f), ImVec2(screenPosition.x, screenPosition.y), SnapLines);
			}

			if (Settings::Visuals::Players::HealthBar) {
				Vector2 left;
				auto leftw2s = WorldToScreen(cornerBox.left, left);

				Vector2 right;
				auto rightw2s = WorldToScreen(cornerBox.right, right);

				Vector2 top;
				auto topw2s = WorldToScreen(cornerBox.top, top);

				Vector2 bottom;
				auto bottomw2s = WorldToScreen(cornerBox.bottom, bottom);

				if (cornerBox.Valid && leftw2s || rightw2s || topw2s || bottomw2s) {
					DrawHealthBar(Vector2(left.x, top.y), Vector2(right.x, bottom.y), 100.f, basePlayer.health(), basePlayer.MaxHealth());
				}
			}
		}
		else
		{
			if (Settings::Visuals::Players::OffscreenIndicators)
			{
				InvisiblePlayerIndicator(position, LocalPosition, LocalRotation, OOF);
			}
		}
	}

	if (Settings::Combat::Aimbot::Aimbot && Settings::Combat::Aimbot::DrawFOV)
	{
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Aimbot::FOV, ImColor(255, 255, 255), 64);
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Aimbot::FOV + 0.5, ImColor(255, 255, 255, 255), 64, 0.5);
	}

	if (Settings::Combat::Silent::Silent && Settings::Combat::Silent::DrawSilent)
	{
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Silent::SilentFOV, ImColor(255, 255, 255), 64);
		DrawList->AddCircle({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2 }, Settings::Combat::Silent::SilentFOV + 0.5, ImColor(255, 255, 255, 255), 64, 0.5);
	}
}

void Visuals::DrawESP()
{
	__try
	{
		SafeDraw();
	}
	__except (true)
	{
		Ulog("%s - Exception occurred within SafeDraw Function.", __FUNCTION__);
	}
}