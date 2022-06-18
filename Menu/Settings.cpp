#include "pch.h"
#include "Settings.h"

using json = nlohmann::json;

void Settings::LoadSettingsChar(const char* path)
{
	return Settings::LoadSettings(path);
}

void Settings::LoadSettings(std::string configName)
{
	size_t sz = 0;
	char* buf = nullptr;
	std::string lcDirectory;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr)
	{
		lcDirectory = std::string(buf) + "\\LCSSD\\RUST\\";
		free(buf);
	}
	std::string path = lcDirectory + configName + ".json";

	std::ifstream inputs(path);

	if (inputs.fail())
	{
		Ulog("File no exist.");
		return;
	}

	json loadedSettings;
	inputs >> loadedSettings;
	inputs.close();

	//Visuals
	for (ESPOption& option : ESPOptions)
	{
		if (loadedSettings.find(combineChar("%s:Draw", option.Prefab)) != loadedSettings.end())
			option.Draw = loadedSettings[combineChar("%s:Draw", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:DrawName", option.Prefab)) != loadedSettings.end())
			option.DrawName = loadedSettings[combineChar("%s:DrawName", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:DrawDistance", option.Prefab)) != loadedSettings.end())
			option.DrawDistance = loadedSettings[combineChar("%s:DrawDistance", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:MaxDistance", option.Prefab)) != loadedSettings.end())
			option.MaxDistance = loadedSettings[combineChar("%s:MaxDistance", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:checkMaxDistance", option.Prefab)) != loadedSettings.end())
			option.checkMaxDistance = loadedSettings[combineChar("%s:checkMaxDistance", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:Color0", option.Prefab)) != loadedSettings.end())
			option.Color[0] = loadedSettings[combineChar("%s:Color0", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:Color1", option.Prefab)) != loadedSettings.end())
			option.Color[1] = loadedSettings[combineChar("%s:Color1", option.Prefab)];

		if (loadedSettings.find(combineChar("%s:Color2", option.Prefab)) != loadedSettings.end())
			option.Color[2] = loadedSettings[combineChar("%s:Color2", option.Prefab)];

		if (loadedSettings.find("Visuals::Health") != loadedSettings.end())
			Settings::Visuals::Players::Health = loadedSettings["Visuals::Health"];

		if (loadedSettings.find("Visuals::Healthbar") != loadedSettings.end())
			Settings::Visuals::Players::HealthBar = loadedSettings["Visuals::Healthbar"];

		if (loadedSettings.find("Visuals::Snaplines") != loadedSettings.end())
			Settings::Visuals::Players::Snaplines = loadedSettings["Visuals::Snaplines"];

		if (loadedSettings.find("Visuals::OOFIndicator") != loadedSettings.end())
			Settings::Visuals::Players::OffscreenIndicators = loadedSettings["Visuals::OOFIndicator"];

		if (loadedSettings.find("Visuals::CornerBox") != loadedSettings.end())
			Settings::Visuals::Players::CornerBox = loadedSettings["Visuals::CornerBox"];

		if (loadedSettings.find("Visuals::Chams") != loadedSettings.end())
			Settings::Visuals::Players::Chams = loadedSettings["Visuals::Chams"];

		if (loadedSettings.find("Visuals::HealthChams") != loadedSettings.end())
			Settings::Visuals::Players::HealthChams = loadedSettings["Visuals::HealthChams"];

		if (loadedSettings.find("Visuals::Players") != loadedSettings.end())
			Settings::Visuals::Players::Players = loadedSettings["Visuals::Players"];

		if (loadedSettings.find("Visuals::Name") != loadedSettings.end())
			Settings::Visuals::Players::Name = loadedSettings["Visuals::Name"];

		if (loadedSettings.find("Visuals::Distance") != loadedSettings.end())
			Settings::Visuals::Players::Distance = loadedSettings["Visuals::Distance"];
	}

	//Aimbot
	if (loadedSettings.find("Aimbot:Aimbot") != loadedSettings.end())
		Settings::Combat::Aimbot::Aimbot = loadedSettings["Aimbot:Aimbot"];
	if (loadedSettings.find("AimKey") != loadedSettings.end())
		Globals::Hotkeys::hotkey_AimbotKey = loadedSettings["AimKey"];
	if (loadedSettings.find("Aimbot:Smoothing") != loadedSettings.end())
		Settings::Combat::Aimbot::Smoothing = loadedSettings["Aimbot:Smoothing"];
	if (loadedSettings.find("Aimbot:SmoothingAmount") != loadedSettings.end())
		Settings::Combat::Aimbot::SmoothingAmount = loadedSettings["Aimbot:SmoothingAmount"];
	if (loadedSettings.find("Aimbot:DrawFOV") != loadedSettings.end())
		Settings::Combat::Aimbot::DrawFOV = loadedSettings["Aimbot:DrawFOV"];
	if (loadedSettings.find("Aimbot:KeepTarget") != loadedSettings.end())
		Settings::Combat::Aimbot::KeepTarget = loadedSettings["Aimbot:KeepTarget"];
	if (loadedSettings.find("Aimbot:FOV") != loadedSettings.end())
		Settings::Combat::Aimbot::FOV = loadedSettings["Aimbot:FOV"];
	if (loadedSettings.find("Aimbot:IgnoreNPCs") != loadedSettings.end())
		Settings::Combat::Aimbot::IgnoreNPCs = loadedSettings["Aimbot:IgnoreNPCs"];
	if (loadedSettings.find("Aimbot:IgnorePlayers") != loadedSettings.end())
		Settings::Combat::Aimbot::IgnorePlayers = loadedSettings["Aimbot:IgnorePlayers"];
	if (loadedSettings.find("Aimbot:IgnoreSleepers") != loadedSettings.end())
		Settings::Combat::Aimbot::IgnoreSleepers = loadedSettings["Aimbot:IgnoreSleepers"];
	if (loadedSettings.find("Aimbot:IgnoreWounded") != loadedSettings.end())
		Settings::Combat::Aimbot::IgnoreWounded = loadedSettings["Aimbot:IgnoreWounded"];

	//Silent
	if (loadedSettings.find("Silent:Silent") != loadedSettings.end())
		Settings::Combat::Silent::Silent = loadedSettings["Silent:Silent"];
	if (loadedSettings.find("SilentKey") != loadedSettings.end())
		Globals::Hotkeys::hotkey_SilentKey = loadedSettings["SilentKey"];
	if (loadedSettings.find("Silent:AutoShoot") != loadedSettings.end())
		Settings::Combat::Silent::AutoShoot = loadedSettings["Silent:AutoShoot"];
	if (loadedSettings.find("Silent:DrawSilent") != loadedSettings.end())
		Settings::Combat::Silent::DrawSilent = loadedSettings["Silent:DrawSilent"];
	if (loadedSettings.find("Silent:SilentFOV") != loadedSettings.end())
		Settings::Combat::Silent::SilentFOV = loadedSettings["Silent:SilentFOV"];

	//Weapon Mods
	if (loadedSettings.find("WeaponMods:Recoil Percentage") != loadedSettings.end())
		Settings::Combat::WeaponMods::Recoil = loadedSettings["WeaponMods:Recoil Percentage"];

	if (loadedSettings.find("WeaponMods:Spread Percentage") != loadedSettings.end())
		Settings::Combat::WeaponMods::Spread = loadedSettings["WeaponMods:Spread Percentage"];

	if (loadedSettings.find("WeaponMods:Sway Percentage") != loadedSettings.end())
		Settings::Combat::WeaponMods::Sway = loadedSettings["WeaponMods:Sway Percentage"];

	if (loadedSettings.find("WeaponMods:FireRate Percentage") != loadedSettings.end())
		Settings::Combat::WeaponMods::FireRate = loadedSettings["WeaponMods:FireRate Percentage"];

	if (loadedSettings.find("WeaponMods:Bullet Thickness") != loadedSettings.end())
		Settings::Combat::WeaponMods::Thickness = loadedSettings["WeaponMods:Bullet Thickness"];

	if (loadedSettings.find("WeaponMods:Bullet Speed") != loadedSettings.end())
		Settings::Combat::WeaponMods::FastBulletSpeed = loadedSettings["WeaponMods:Bullet Speed"];

	if (loadedSettings.find("WeaponMods:InstantEoka") != loadedSettings.end())
		Settings::Combat::WeaponMods::InstantEoka = loadedSettings["WeaponMods:InstantEoka"];

	if (loadedSettings.find("WeaponMods:CanHoldItems") != loadedSettings.end())
		Settings::Combat::WeaponMods::CanHoldItems = loadedSettings["WeaponMods:CanHoldItems"];

	if (loadedSettings.find("WeaponMods:AutoReload") != loadedSettings.end())
		Settings::Combat::WeaponMods::AutoReload = loadedSettings["WeaponMods:AutoReload"];

	if (loadedSettings.find("WeaponMods:Automatic") != loadedSettings.end())
		Settings::Combat::WeaponMods::Automatic = loadedSettings["WeaponMods:Automatic"];

	if (loadedSettings.find("WeaponMods:Penetrate") != loadedSettings.end())
		Settings::Combat::WeaponMods::Penetrate = loadedSettings["WeaponMods:Penetrate"];

	if (loadedSettings.find("WeaponMods:Spam") != loadedSettings.end())
		Settings::Combat::WeaponMods::Spam = loadedSettings["WeaponMods:Spam"];

	if (loadedSettings.find("WeaponMods:AlwaysSpam") != loadedSettings.end())
		Settings::Combat::WeaponMods::AlwaysSpam = loadedSettings["WeaponMods:AlwaysSpam"];

	if (loadedSettings.find("WeaponMods:SpamRate") != loadedSettings.end())
		Settings::Combat::WeaponMods::SpamRate = loadedSettings["WeaponMods:SpamRate"];

	if (loadedSettings.find("WeaponMods:OVDist") != loadedSettings.end())
		Settings::Combat::WeaponMods::OVDist = loadedSettings["WeaponMods:OVDist"];

	if (loadedSettings.find("WeaponMods:OVDistance") != loadedSettings.end())
		Settings::Combat::WeaponMods::OVDistance = loadedSettings["WeaponMods:OVDistance"];

	if (loadedSettings.find("WeaponMods:OVHitbox") != loadedSettings.end())
		Settings::Combat::WeaponMods::OVHitbox = loadedSettings["WeaponMods:OVHitbox"];

	if (loadedSettings.find("WeaponMods:currentHitbox") != loadedSettings.end())
		Menu::currentHitbox = loadedSettings["WeaponMods:currentHitbox"];

	// Exploits

//f (loadedSettings.find("Exploits::Desync") != loadedSettings.end())
	//	Settings::Combat::Rage::Desync = loadedSettings["Exploits::Desync"];

	if (loadedSettings.find("Exploits::DesyncKey") != loadedSettings.end())
		Settings::Combat::Rage::DesyncKey = loadedSettings["Exploits::DesyncKey"];
	
	if (loadedSettings.find("Exploits::DesyncBar") != loadedSettings.end())
		Settings::Combat::Rage::ShowDesync = loadedSettings["Exploits::DesyncBar"];
	
	if (loadedSettings.find("Exploits::PowerShoot") != loadedSettings.end())
		Settings::Combat::Rage::PowerShot = loadedSettings["Exploits::PowerShoot"];
	
	if (loadedSettings.find("Exploits::InstantShoot") != loadedSettings.end())
		Settings::Combat::Rage::InstantShoot = loadedSettings["Exploits::InstantShoot"];
	 

	// Hot keys
}

void Settings::SaveSettings(std::string path)
{
	Ulog("Saving to path %s", path.data());

	json settings;

	// Visuals
	for (ESPOption& option : ESPOptions)
	{
		settings[combineChar("%s:Draw", option.Prefab)] = option.Draw;

		settings[combineChar("%s:DrawName", option.Prefab)] = option.DrawName;

		settings[combineChar("%s:DrawDistance", option.Prefab)] = option.DrawDistance;

		settings[combineChar("%s:MaxDistance", option.Prefab)] = option.MaxDistance;

		settings[combineChar("%s:checkMaxDistance", option.Prefab)] = option.checkMaxDistance;

		settings[combineChar("%s:Color0", option.Prefab)] = option.Color[0];

		settings[combineChar("%s:Color1", option.Prefab)] = option.Color[1];

		settings[combineChar("%s:Color2", option.Prefab)] = option.Color[2];

		settings["Visuals::Name"] = Settings::Visuals::Players::Name;
		settings["Visuals::Distance"] = Settings::Visuals::Players::Distance;
		settings["Visuals::Chams"] = Settings::Visuals::Players::Chams;
		settings["Visuals::CornerBox"] = Settings::Visuals::Players::CornerBox;
		settings["Visuals::Healthbar"] = Settings::Visuals::Players::HealthBar;
		settings["Visuals::Health"] = Settings::Visuals::Players::Health;
		settings["Visuals::OOFIndicator"] = Settings::Visuals::Players::OffscreenIndicators;
		settings["Visuals::Players"] = Settings::Visuals::Players::Players;
		settings["Visuals::Snaplines"] = Settings::Visuals::Players::Snaplines;
		settings["Visuals::HealthChams"] = Settings::Visuals::Players::HealthChams;
	}

	// Exploits
	//settings["Exploits::Desync"] = Settings::Combat::Rage::Desync;
	settings["Exploits::DesyncKey"] = Settings::Combat::Rage::DesyncKey;
	settings["Exploits::DesyncBar"] = Settings::Combat::Rage::ShowDesync;
	settings["Exploits::InstantShoot"] = Settings::Combat::Rage::InstantShoot;
	settings["Exploits::PowerShoot"] = Settings::Combat::Rage::PowerShot;

	// Misc

	// ¨Combat
	settings["Aimbot:Aimbot"] = Settings::Combat::Aimbot::Aimbot;
	settings["AimKey"] = Globals::Hotkeys::hotkey_AimbotKey;
	settings["Aimbot:Smoothing"] = Settings::Combat::Aimbot::Smoothing;
	settings["Aimbot:SmoothingAmount"] = Settings::Combat::Aimbot::SmoothingAmount;
	settings["Aimbot:DrawFOV"] = Settings::Combat::Aimbot::DrawFOV;
	settings["Aimbot:KeepTarget"] = Settings::Combat::Aimbot::KeepTarget;
	settings["Aimbot:FOV"] = Settings::Combat::Aimbot::FOV;
	settings["Aimbot:IgnorePlayers"] = Settings::Combat::Aimbot::IgnorePlayers;
	settings["Aimbot:IgnoreSleepers"] = Settings::Combat::Aimbot::IgnoreSleepers;
	settings["Aimbot:IgnoreWounded"] = Settings::Combat::Aimbot::IgnoreWounded;
	settings["Aimbot:IgnoreNPCs"] = Settings::Combat::Aimbot::IgnoreNPCs;

	//Silent
	settings["Silent:Silent"] = Settings::Combat::Silent::Silent;
	settings["SilentKey"] = Globals::Hotkeys::hotkey_SilentKey;
	settings["Silent:AutoShoot"] = Settings::Combat::Silent::AutoShoot;
	settings["Silent:DrawSilent"] = Settings::Combat::Silent::DrawSilent;
	settings["Silent:SilentFOV"] = Settings::Combat::Silent::SilentFOV;

	//Weapon Mods
	settings["WeaponMods:Recoil Percentage"] = Settings::Combat::WeaponMods::Recoil;
	settings["WeaponMods:Spread Percentage"] = Settings::Combat::WeaponMods::Spread;
	settings["WeaponMods:Sway Percentage"] = Settings::Combat::WeaponMods::Sway;
	settings["WeaponMods:FireRate Percentage"] = Settings::Combat::WeaponMods::FireRate;
	settings["WeaponMods:Bullet Thickness"] = Settings::Combat::WeaponMods::Thickness;
	settings["WeaponMods:Bullet Speed"] = Settings::Combat::WeaponMods::FastBulletSpeed;

	settings["WeaponMods:InstantEoka"] = Settings::Combat::WeaponMods::InstantEoka;
	settings["WeaponMods:CanHoldItems"] = Settings::Combat::WeaponMods::CanHoldItems;
	settings["WeaponMods:AutoReload"] = Settings::Combat::WeaponMods::AutoReload;
	settings["WeaponMods:Automatic"] = Settings::Combat::WeaponMods::Automatic;
	settings["WeaponMods:Penetrate"] = Settings::Combat::WeaponMods::Penetrate;
	settings["WeaponMods:Spam"] = Settings::Combat::WeaponMods::Spam;
	settings["WeaponMods:AlwaysSpam"] = Settings::Combat::WeaponMods::AlwaysSpam;
	settings["WeaponMods:SpamRate"] = Settings::Combat::WeaponMods::SpamRate;
	settings["WeaponMods:OVDist"] = Settings::Combat::WeaponMods::OVDist;
	settings["WeaponMods:OVDistance"] = Settings::Combat::WeaponMods::OVDistance;
	settings["WeaponMods:OVHitbox"] = Settings::Combat::WeaponMods::OVHitbox;
	settings["WeaponMods:currentHitbox"] = Menu::currentHitbox;

	// Hot keys

	std::ofstream output(path);
	output << std::setw(4) << settings << std::endl;
	output.close();
}