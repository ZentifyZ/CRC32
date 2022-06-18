#pragma once
inline char* combineChar(char* a1, char* a2)
{
	char buf[256] = { 0 }; sprintf_s(buf, a1, a2);
	return buf;
}

namespace Settings
{
	void LoadSettingsChar(const char* path);
	void LoadSettings(std::string path);
	void SaveSettings(std::string path);
	void AddESPObject(char* SubTab, char* Prefab, char* Name, bool Draw);
}