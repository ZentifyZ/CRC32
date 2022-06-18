#include "pch.h"
#include "Settings.h"

ImGuiContext* pImGuiContext;
ID3D11RenderTargetView* mainRenderTargetView;

char PrefabName[255] = "Custom Prefab";
char PrefabID[255] = "";

void Settings::AddESPObject(char* SubTab, char* Prefab, char* Name, bool Draw)
{
	bool Exists = false;

	for (const ESPOption& option : ESPOptions)
	{
		if (option.Prefab == Prefab) Exists = true;
	}

	if (!Exists)
	{
		ESPOption Op;
		Op.Draw = Draw;
		Op.Prefab = Prefab;
		Op.Name = Name;
		Op.SubTab = SubTab;
		ESPOptions.push_back(Op);
	}
}
void Menu::MainMenu() {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImGui::GetStyle().FrameRounding = 0.0f;
	ImGui::GetStyle().GrabRounding = 0.0f;
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().WindowTitleAlign = { 0.5f, 0.5f };
	ImGui::GetStyle().ScrollbarRounding = 0.f;
	ImGui::GetStyle().ScrollbarSize = 4.f;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.04f, 0.04f, 0.04f, 0.50f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_::ImGuiCond_FirstUseEver);
	if (ImGui::Begin("CRC32 Private", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)) {
		static int activeTab;


		//ImGui::BeginChild( "TabChild", ImVec2( ImGui::GetContentRegionAvail( ).x, 37 ), true, ImGuiWindowFlags_NoResize );
		//{
		if (ImGui::Button("COMBAT", { 115, 30 })) {
			activeTab = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("VISUALS", { 115, 30 })) {
			activeTab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("WEAPONS", { 115, 30 })) {
			activeTab = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button("MISC", { 115, 30 })) {
			activeTab = 3;
		}
		//}
		//ImGui::EndChild( );

		switch (activeTab) {
		case 0:
			ImGui::BeginChild("Combat", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Silent Aimbot", &Settings::Combat::Silent::Silent); ImGui::SameLine(); Menu::Hotkey(" ", &Globals::Hotkeys::hotkey_SilentKey, ImVec2{ 100, 20 });
				if (Settings::Combat::Silent::Silent) {
					ImGui::Checkbox("Draw Silent FOV", &Settings::Combat::Silent::DrawSilent);
					ImGui::SliderInt("Silent FOV", &Settings::Combat::Silent::SilentFOV, 0, 2500);
					ImGui::Checkbox("Automatic Shoot", &Settings::Combat::Silent::AutoShoot);
				}
			}
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("Combat2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Memory Aimbot", &Settings::Combat::Aimbot::Aimbot); ImGui::SameLine(); Menu::Hotkey("   ", &Globals::Hotkeys::hotkey_AimbotKey, ImVec2{ 100, 20 });
				if (Settings::Combat::Aimbot::Aimbot) {
					ImGui::Checkbox("Smoothness", &Settings::Combat::Aimbot::Smoothing);
					ImGui::SliderFloat("Silent FOV", &Settings::Combat::Aimbot::FOV, 0, 500);
					ImGui::SliderInt("Smoothness Amount", &Settings::Combat::Aimbot::SmoothingAmount, 0, 20);
				}
			}
			ImGui::EndChild();

			break;
		case 1:
			ImGui::BeginChild("Visuals", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Player ESP", &Settings::Visuals::Players::Players);
				ImGui::Checkbox("NPC ESP", &Settings::Visuals::Players::NPC);
				ImGui::Checkbox("Name", &Settings::Visuals::Players::Name); ImGui::SameLine(); ImGui::ColorEdit4("", (float*)&Settings::Visuals::Players::Colors::Name, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Health", &Settings::Visuals::Players::Health); ImGui::SameLine(); ImGui::ColorEdit4(" ", (float*)&Settings::Visuals::Players::Colors::Health, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Distance", &Settings::Visuals::Players::Distance); ImGui::SameLine(); ImGui::ColorEdit4("  ", (float*)&Settings::Visuals::Players::Colors::Distance, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Held Item", &Settings::Visuals::Players::HeldItem); ImGui::SameLine(); ImGui::ColorEdit4("   ", (float*)&Settings::Visuals::Players::Colors::HeldItem, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Chams", &Settings::Visuals::Players::Chams); ImGui::SameLine(); ImGui::ColorEdit4("          ", (float*)&Settings::Visuals::Players::Colors::Chams, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("Visuals2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("Boxes", &Settings::Visuals::Players::CornerBox); ImGui::SameLine(); ImGui::ColorEdit4("    ", (float*)&Settings::Visuals::Players::Colors::Box, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Skeleton", &Settings::Visuals::Players::Skeleton); ImGui::SameLine(); ImGui::ColorEdit4("     ", (float*)&Settings::Visuals::Players::Colors::Skeleton, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Health Bar", &Settings::Visuals::Players::HealthBar);
				ImGui::Checkbox("Snaplines", &Settings::Visuals::Players::Snaplines); ImGui::SameLine(); ImGui::ColorEdit4("       ", (float*)&Settings::Visuals::Players::Colors::Snaplines, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("OOF Indicator", &Settings::Visuals::Players::OffscreenIndicators); ImGui::SameLine(); ImGui::ColorEdit4("      ", (float*)&Settings::Visuals::Players::Colors::OOF, ImGuiColorEditFlags_NoInputs);


				
				Visuals::AddObject(PrefabID, PrefabName, false); ImGui::SameLine(); ImGui::InputText("", PrefabID, IM_ARRAYSIZE(PrefabID));
				if (ImGui::CollapsingHeader("Vehicles##1")) {
					Visuals::AddObject("bradley", "Bradley", false);
					Visuals::AddObject(PatrolID, "Patrol Helicopter", false, true);

					Visuals::AddObject("kayak.prefab", "Kayak", false);
					Visuals::AddObject("rhib.prefab", "Rhib", false);
					Visuals::AddObject("rowboat.prefab", "Rowboat", false);

					Visuals::AddObject("minicopter.entity.prefab", "Mini-Copter", false);
					Visuals::AddObject("scraptransporthelicopter.prefab", "Scrap Helicopter", false, true);
					Visuals::AddObject("ch47.entity.prefab", "Chinook Helicopter", false);
					Visuals::AddObject("submarineduo.entity.prefab", "Submarine Solo", false);
					Visuals::AddObject("submarinesolo.entity.prefab", "Submarine Duo", false);
				}
				if (ImGui::CollapsingHeader("Collectables##1")) {
					Visuals::AddObject("stone-collectable.prefab", "Stone Collectible Ore", false);
					Visuals::AddObject("metal-collectable.prefab", "Metal Collectable Ore", false);
					Visuals::AddObject("sulfur-collectable.prefab", "Sulfur Collectable Ore", false);
					Visuals::AddObject("collectable/berry", "Berries", false);
					Visuals::AddObject("/hemp/hemp", "Hemp", false);
				}
				if (ImGui::CollapsingHeader("Ores##1")) {
					Visuals::AddObject("stone-ore.prefab", "Stone Ore", false);
					Visuals::AddObject("metal-ore.prefab", "Metal Ore", false);
					Visuals::AddObject("sulfur-ore.prefab", "Sulfur Ore", false);
				}
				if (ImGui::CollapsingHeader("Animals##1")) {
					Visuals::AddObject("wolf.prefab", "Wolf", false, true);
					Visuals::AddObject("boar.prefab", "Boar", false, true);
					Visuals::AddObject("bear.prefab", "Bear", false, true);
					Visuals::AddObject("horse.prefab", "Horse", false, true);
				}
				if (ImGui::CollapsingHeader("Loot##1")) {
					Visuals::AddObject("(world)", "Dropped Item", false);
					Visuals::AddObject("loot-barrel-1.prefab", "Loot Barrel 1", false);
					Visuals::AddObject("loot-barrel-2.prefab", "Loot Barrel 2", false);
					Visuals::AddObject("crate_basic.prefab", "Basic Crate", false);
					Visuals::AddObject("crate_normal.prefab", "Normal Crate", false);
					Visuals::AddObject("crate_elite.prefab", "Elite Crate", false);

					Visuals::AddObject("bradley_crate.prefab", "Bradley Crate", false);
					Visuals::AddObject("codelockedhackablecrate.prefab", "Locked Crate", false);
					Visuals::AddObject("codelockedhackablecrate_oilrig.prefab", "Locked Oilrig Crate", false);
				}   
				if (ImGui::CollapsingHeader("Traps##1")) {
					Visuals::AddObject("flameturret.deployed.prefab", "Flame Turret", false);
					Visuals::AddObject("landmine.prefab", "Landmine", false);
					Visuals::AddObject("sam_site_turret_deployed.prefab", "Sam Site", false);
					Visuals::AddObject("guntrap.deployed.prefab", "Shotgun Trap", false);
					Visuals::AddObject("beartrap.prefab", "Snap Trap", false);
					Visuals::AddObject("spikes.floor.prefab", "Wooden Floor Spikes", false);

					Visuals::AddObject("autoturret_deployed.prefab", "Auto Turret", false);
				}
				if (ImGui::CollapsingHeader("Construction##1")) {
					Visuals::AddObject("sleepingbag_leather_deployed.prefab", "Sleeping Bag", false);
					Visuals::AddObject("cupboard.tool.deployed.prefab", "Tool Cupboard", false);
					Visuals::AddObject("small_stash_deployed.prefab", "Stash", false);
				}
			}
			ImGui::EndChild();

			break;
		case 2:
			ImGui::BeginChild("Weapons", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Combo("Indicators", &Settings::Combat::Rage::DesyncInd, "None\0Last Cheat\0Quantum Cheats\0CT Hook");
				ImGui::Checkbox("Manipulator", &Settings::Misc::Manipulator); ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_Manipulator, ImVec2{ 100, 20 });
				ImGui::Checkbox("Insta Kill", &Settings::Combat::Rage::PowerShot); ImGui::SameLine(); Menu::Hotkey(" ", &Globals::Hotkeys::hotkey_InstaKill, ImVec2{ 100, 20 });

				ImGui::Checkbox("Instant Eoka", &Settings::Combat::WeaponMods::InstantEoka);
				ImGui::Checkbox("Reload Indicator", &Settings::Misc::Reloadindicator);
				ImGui::Checkbox("Heli Weakspot", &Settings::Combat::WeaponMods::HeliWeakspot);
				ImGui::Checkbox("Full Automatic", &Settings::Combat::WeaponMods::Automatic);
				ImGui::Checkbox("Fast Bullet", &Settings::Combat::WeaponMods::FastBullet);
				ImGui::Checkbox("Penetrate", &Settings::Combat::WeaponMods::Penetrate);
				ImGui::Checkbox("Spoof Hit Distance", &Settings::Combat::WeaponMods::OVDist);
				if (Settings::Combat::WeaponMods::OVDist)
					ImGui::SliderFloat("Distance", &Settings::Combat::WeaponMods::OVDistance, 1337.f, 7777.f);

				ImGui::Checkbox("Override Hitbox", &Settings::Combat::WeaponMods::OVHitbox);//
				if (Settings::Combat::WeaponMods::OVHitbox) {
					ImGui::Combo("Hitbox", &Menu::currentHitbox, "Head\0Chest\0Stomach\0R_Leg\0L_Leg\0R_Arm\0L_Arm");
					switch (Menu::currentHitbox)
					{
					case 0:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::hhead;
						break;
					case 1:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::cchest;
						break;
					case 2:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::sstomach;
						break;
					case 3:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::rleg;
						break;
					case 4:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::lleg;
						break;
					case 5:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::rhand;
						break;
					case 6:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::lhand;
						break;
					case 7:
						Settings::Combat::WeaponMods::OVHit = BoneHitbox::lhand, BoneHitbox::rhand, BoneHitbox::lleg, BoneHitbox::rleg;
						break;
					}
				}

			}
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("Weapons2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::SliderInt("Recoil", &Settings::Combat::WeaponMods::Recoil, 0.f, 100.f);
				ImGui::SliderInt("Spread", &Settings::Combat::WeaponMods::Spread, 0.f, 100.f);
				ImGui::SliderInt("Weapon Spam", &Settings::Combat::WeaponMods::SpamRate, 0.f, 100.f);
				ImGui::SliderInt("Sway", &Settings::Combat::WeaponMods::Sway, 0.f, 100.f);
				ImGui::SliderInt("Fire Rate", &Settings::Combat::WeaponMods::FireRate, 100.f, 500.f);
				ImGui::SliderFloat("Thickness", &Settings::Combat::WeaponMods::Thickness, 0.1f, 1.f);
			}
			ImGui::EndChild();

			break;
		case 3:
			ImGui::BeginChild("Misc", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("No Jumping Restriction", &Settings::Misc::InfJump);
				ImGui::Checkbox("No Attack Restriction", &Settings::Misc::CanAttack);
				ImGui::Checkbox("No Sprinting Restriction", &Settings::Misc::OmniSprint);


				ImGui::Checkbox("Anti Flyhack", &Settings::Misc::AntiFlyHack);

				ImGui::Checkbox("Auto Med", &Settings::Misc::AutoMed);
				ImGui::Checkbox("Fake Admin", &Settings::Misc::FakeAdmin);
				ImGui::Checkbox("Anti Aim", &Settings::Misc::Spinbot);
				ImGui::Checkbox("No Fall Damage", &Settings::Misc::NoFallDamage);
				ImGui::Checkbox("Keep Wounded Alive", &Settings::Misc::KeepWoundedAlive);
				ImGui::Checkbox("Fake Lag", &Settings::Misc::FakeLag);
				ImGui::Checkbox("Silent Walk", &Settings::Misc::SilentWalk);
				ImGui::Checkbox("High Jump", &Settings::Misc::JumpHigh);
				ImGui::Checkbox("Suicide", &Settings::Misc::Suicide);
				if (Settings::Misc::Suicide)
				{
					if (!Settings::Misc::AlwaysSuicide)
					{
						ImGui::SameLine(); Menu::Hotkey("", &Globals::Hotkeys::hotkey_SuicideKey, ImVec2{ 200, 20 });
					}
					ImGui::Checkbox("Always On", &Settings::Misc::AlwaysSuicide);
					ImGui::SliderFloat("Suicide Rate", &Settings::Misc::SuicideRate, 1.f, 30.f);
				}

			//	ImGui::Checkbox("Suicide", &Menu::Vars::misc_suicide); ImGui::SameLine(); Hotkey("   ", Menu::Vars::misc_suicidekey, 105.f);
			}
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("Misc2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
			{
				ImGui::Checkbox("FOV Changer", &Settings::Misc::FOVChanger); ImGui::SameLine(); Menu::Hotkey("Zoom", &Globals::Hotkeys::hotkey_Zoom, ImVec2{ 100, 20 });
				ImGui::Checkbox("Time Changer", &Settings::Misc::TimeChanger);

				ImGui::Checkbox("Walk On Water", &Settings::Misc::WalkOnWater);
				ImGui::Checkbox("Walk Through Players", &Settings::Misc::WalkThroughPlayers);
				ImGui::Checkbox("Walk Through Trees", &Settings::Misc::WalkThroughTrees);

				ImGui::Checkbox("No Weapon Bobing", &Settings::Misc::NoBobbing);
				ImGui::Checkbox("No Weapon Lowering", &Settings::Misc::NoLowering);
				ImGui::Checkbox("No Weapon Lerping", &Settings::Misc::NoSwaying);
				ImGui::Checkbox("No Firing Animation", &Settings::Combat::WeaponMods::NoAttackAnimation);

				ImGui::Combo("Crosshair", &Menu::currentCrosshair, "None\0Cross\0X\0Circle\0Custom");
				if (Menu::currentCrosshair != 0)
					ImGui::SliderInt("Size", &Settings::Misc::CrosshairSize, 1, 60);

				if (Menu::currentCrosshair == 4) {
					ImGui::SliderInt("Gap", &Settings::Misc::CrosshairGap, 1, 60);
					ImGui::SliderInt("Thickness", &Settings::Misc::CrosshairThickness, 1, 60);
				}

				ImGui::SliderInt("FOV", &Settings::Misc::FOVChangerAmount, 70.f, 140.0f);
				ImGui::SliderInt("Time", &Settings::Misc::TimeChangerAmount, 0.f, 24.f);
			}
			ImGui::EndChild();

			break;
		}
	}
	ImGui::End();
}

void SaveDefaultConfig()
{
	size_t sz = 0;
	char* buf = nullptr;
	std::string lcDirectory;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		lcDirectory = std::string(buf) + "\\LCSSD\\";

		if (!std::filesystem::exists(lcDirectory))
		{
			std::filesystem::create_directory(lcDirectory);
		}

		lcDirectory += "RUST\\";

		free(buf);
	}
	else
	{
		Ulog("APPDATA does not exist in environment."); return;
	}

	if (std::filesystem::exists(lcDirectory))
	{
		if (!std::filesystem::exists(lcDirectory + std::string("Default.json")))
		{
			Settings::SaveSettings(lcDirectory + "Default.json");
		}
	}
	else
	{
		Ulog("Creating directory...");
		std::filesystem::create_directory(lcDirectory);
	}
}

ImFont* espFont;
ImFont* defaultFont;

void Menu::Wrapper(void* swapChain)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (!Globals::Window::pChain)
		{
			if (!InitializeMenu((IDXGISwapChain*)swapChain))
			{
				Ulog("%s - Failed to initialize Menu.", __FUNCTION__);
				return;
			}
		}

		ImGui::GetIO().IniFilename = "rust.temp";
		ImGui::GetIO().IniSavingRate = 99999999999999.f;
		ImGui::GetIO().WantSaveIniSettings = false;// = "my_config.ini"

		ImGui_ImplDX11_NewFrame(); ImGui_ImplWin32_NewFrame(); ImGui::NewFrame();

		SaveDefaultConfig();

		if (Globals::Ready)
		{
			if (Vars::Global::ScreenHigh != 0 && Vars::Global::ScreenWidth != 0)
			{
				ImGui::PushFont(espFont);
				__try
				{
					Visuals::DrawESP();
				}
				__except ([](unsigned int code, struct _EXCEPTION_POINTERS* ep) -> int
					{
						Ulog("ESP - Exception happened in (%s) with code %lx - at RIP %p | %p ", __FUNCTION__,
							code, ep->ExceptionRecord->ExceptionAddress, Globals::g_Module);

						return EXCEPTION_EXECUTE_HANDLER;
					}(GetExceptionCode(), GetExceptionInformation())) {
				}

				if (Globals::Settings::g_bMenu) Menu::MainMenu();
				ImGui::PopFont();
			}
		}

		ImGui::EndFrame();
		ImGui::Render();
		Globals::Window::pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		Vars::Global::ScreenHigh = ImGui::GetDrawData()->DisplaySize.y;
		Vars::Global::ScreenWidth = ImGui::GetDrawData()->DisplaySize.x;
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers)
		{
			Ulog("Exception (%lx) caught in %s @ (%p). Base (%p) - (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress, Globals::g_GameAssemblyBase, Globals::g_Module
			);
		}
	}
}

/**********************************************************************************************************************/
/***************************************************** [ INTERNALS ] **************************************************/
/**********************************************************************************************************************/

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext)
{
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

bool Menu::InitializeMenu(IDXGISwapChain* ptr_SwapChain) {
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try {
		Globals::Window::pChain = ptr_SwapChain;
		mainRenderTargetView = NULL;
		pImGuiContext = NULL;

		HRESULT result = GetDeviceAndCtxFromSwapchain(Globals::Window::pChain, &Globals::Window::pDevice, &Globals::Window::pContext);
		if (FAILED(result)) {
			Ulog("%s - GetDeviceAndCtxFromSwapchain failed with HRESULT (%x) pChain reset (%p)", __FUNCTION__, result, Globals::Window::pChain = 0);
			return false;
		}

		DXGI_SWAP_CHAIN_DESC sd;
		Globals::Window::pChain->GetDesc(&sd);
		pImGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDrawCursor = false;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

		Globals::Window::GameWindow = sd.OutputWindow;
		ImGui_ImplWin32_Init(Globals::Window::GameWindow);
		ImGui_ImplDX11_Init(Globals::Window::pDevice, Globals::Window::pContext);
		ImGui::GetIO().ImeWindowHandle = Globals::Window::GameWindow;

		ImFontConfig cfg;

		cfg.RasterizerFlags = 1 << 7 | 1 << 4; // semi-disable antialiasing

		defaultFont = io.Fonts->AddFontDefault();
		espFont = io.Fonts->AddFontFromMemoryCompressedTTF(MinecraftCHMC_compressed_data, MinecraftCHMC_compressed_size, 13.25f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

		ID3D11Texture2D* pBackBuffer = 0;

		Globals::Window::pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		if (pBackBuffer) {
			Globals::Window::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}

		return true;
	}
	__except (
		ExceptionCode = GetExceptionCode(),
		ExceptionPointers = GetExceptionInformation(),
		EXCEPTION_EXECUTE_HANDLER
		) {
		if (ExceptionPointers) {
			Ulog("Exception (%lx) caught in %s @ (%p). Base (%p) - (%p)",
				ExceptionCode, __FUNCTION__,
				ExceptionPointers->ExceptionRecord->ExceptionAddress, Globals::g_GameAssemblyBase, Globals::g_Module
			);
		}
	}
	return false;
}

ImVec2 ImVecAdd(ImVec2 vec1, ImVec2 vec2)
{
	return { vec1.x + vec2.x, vec1.y + vec2.y };
}

ImVec2 ImVecSubtract(ImVec2 vec1, ImVec2 vec2)
{
	return { vec1.x - vec2.x, vec1.y - vec2.y };
}

bool Menu::Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(ImVecAdd(window->DC.CursorPos, ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f)), ImVecAdd(window->DC.CursorPos, size));
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered)
	{
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked)
	{
		if (g.ActiveId != id)
		{
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0])
	{
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id)
	{
		for (auto i = 0; i < 5; i++)
		{
			if (io.MouseDown[i])
			{
				switch (i)
				{
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed)
		{
			for (auto i = VK_BACK; i <= VK_RMENU; i++)
			{
				if (io.KeysDown[i])
				{
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (ImGui::IsKeyPressedMap(ImGuiKey_Escape))
		{
			*k = 0;
			ImGui::ClearActiveID();
		}
		else
		{
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);

	if (*k != 0 && g.ActiveId != id)
	{
		if (*k > 210)
		{
			strcpy_s(buf_display, "Invalid Key");
		}
		else
		{
			strcpy_s(buf_display, Menu::KeyNames[*k]);
		}
	}
	else if (g.ActiveId == id)
	{
		strcpy_s(buf_display, "<Press a key>");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = ImVecAdd(frame_bb.Min, style.FramePadding);

	ImGui::RenderTextClipped(ImVecAdd(frame_bb.Min, style.FramePadding), ImVecSubtract(frame_bb.Max, style.FramePadding), buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}

char pendingSettingsName[0x100];
bool bPendingSettingsSave = false;
void Menu::RenderConfig()
{
	ImGui::Text("Settings Configuration");

	size_t sz = 0;
	char* buf = nullptr;
	std::string lcDirectory;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		lcDirectory = std::string(buf) + "\\LCSSD\\";

		if (!std::filesystem::exists(lcDirectory))
		{
			std::filesystem::create_directory(lcDirectory);
		}

		lcDirectory += "RUST\\";

		free(buf);
	}
	else
	{
		Ulog("APPDATA does not exist in environment."); return;
	}

	if (std::filesystem::exists(lcDirectory))
	{
		if (!std::filesystem::exists(lcDirectory + std::string("Default.json")))
		{
			Settings::SaveSettings(lcDirectory + "Default.json");
		}

		for (auto& p : std::filesystem::directory_iterator(lcDirectory))
		{
			auto path = p.path().generic_string();
			auto fileName = path.substr(path.find_last_of("/\\") + 1);
			std::string::size_type const p(fileName.find_last_of('.'));
			fileName = fileName.substr(0, p);

			bool hasNameBeenAdded = false;
			for (auto name : Globals::Settings::ConfigList)
			{
				if (strcmp(name.data(), fileName.c_str()) == 0)
				{
					hasNameBeenAdded = true;
				}
			}

			if (!hasNameBeenAdded)
			{
				Globals::Settings::ConfigList.push_back(fileName);
			}
		}

		ImGui::SetNextItemWidth(130);
		if (ImGui::BeginCombo("Setting Profiles", Globals::Settings::currentConfig.data()))
		{
			for (auto config : Globals::Settings::ConfigList)
			{
				bool is_selected = (config == Globals::Settings::currentConfig);
				if (ImGui::Selectable(config.data(), is_selected))
				{
					Globals::Settings::currentConfig = config;
					Settings::LoadSettings(config);
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
	}
	else
	{
		Ulog("Creating directory...");
		std::filesystem::create_directory(lcDirectory);
	}

	if (bPendingSettingsSave)
	{
		ImGui::SetNextItemWidth(130);
		ImGui::InputText("Config Name", pendingSettingsName, IM_ARRAYSIZE(pendingSettingsName));
	}

	if (bPendingSettingsSave)
	{
		if (ImGui::Button("Confirm Save Config"))
		{
			bPendingSettingsSave = false;
			Settings::SaveSettings(lcDirectory + std::string(pendingSettingsName) + ".json");
			memset(pendingSettingsName, 0, 16);
		}
	}
	else
	{
		if (ImGui::Button("Save Config"))
		{
			bPendingSettingsSave = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Config"))
		{
			Ulog("Deleting current Config = %s", Globals::Settings::currentConfig.data());

			if (DeleteFileA((lcDirectory + Globals::Settings::currentConfig + ".json").data()))
			{
				auto itr = std::find(Globals::Settings::ConfigList.begin(), Globals::Settings::ConfigList.end(), Globals::Settings::currentConfig);
				if (itr != Globals::Settings::ConfigList.end()) Globals::Settings::ConfigList.erase(itr);

				Globals::Settings::currentConfig = "DELETED";
			}
		}
	}
}