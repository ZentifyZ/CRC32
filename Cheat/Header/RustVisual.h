#pragma once

class SafeExecution {
private:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};

inline std::list<BasePlayer> basePlayers;
inline auto gameAssembly = GetModuleHandleA(xorstr_("GameAssembly.dll"));

#define ProcAddr(func) GetProcAddress(gameAssembly, func)

template<typename T, typename... Args>
inline T Call(const char* func, Args... args) {
	return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
}
class String {
public:
	char pad_0000[0x10];
	int len;
	wchar_t buffer[0];

	static String* New(const char* str) {
		return Call<String*, const char*>(xorstr_("il2cpp_string_new"), str);
	}
};


inline static UINT_PTR GetType(const char* qualified_name)
{
	static auto off = Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("mscorlib", "System", "Type", "GetType", 1);
	return reinterpret_cast<UINT_PTR(__cdecl*)(String*)>(off)(String::New(qualified_name));
}

inline UINT_PTR GetComponent(UINT_PTR type, UINT_PTR pointer) {
	typedef UINT_PTR getComp(UINT_PTR, UINT_PTR);
	return ((getComp*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Component", "GetComponent", 1)))(pointer, type);
}

inline UINT_PTR GetGameObjectComponent(UINT_PTR type, UINT_PTR pointer) {
	typedef UINT_PTR getComp(UINT_PTR, UINT_PTR);
	return ((getComp*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1)))(pointer, type);
}

inline static UINT_PTR GUIDToObject(String* guid) {
	typedef UINT_PTR GUIDToObject(String*);
	return ((GUIDToObject*)(Globals::g_GameAssemblyBase + Dumper::GetMethodOffset("Assembly-CSharp", "", "GameManifest", "GUIDToObject", 1)))(guid);
}

inline UINT_PTR GetClassObject(UINT_PTR pointer) {
	String* guid = *reinterpret_cast<String**>(pointer + 0x10);
	UINT_PTR _cachedObject = GUIDToObject(guid);
	return _cachedObject;
}

inline std::list<ESPOption> ESPOptions;
inline BasePlayer LocalPlayer;
inline ImDrawList* DrawList;
inline StaticCameraClass* StaticCamera = 0;

// Storing values
inline float lastY = 0;
inline float MVelocity = 0.f;
inline float Cap = 0.f;
inline float CapCrouch = 0.f;
inline float GroundAngle = -1.f;
inline float GroundAngleNew = -1.f;

class ILine
{
public:
	ILine(Vector3 position1, Vector3 position2, ImColor lineColor)
	{
		this->Start = position1;
		this->End = position2;
		this->Color = lineColor;
	};

	Vector3 Start;
	Vector3 End;
	ImColor Color;
};

class CornerBox
{
public:
	Vector3 left;
	Vector3 right;
	Vector3 top;
	Vector3 bottom;
	bool Valid = true;
	ImColor Color;
};

class BasePlayerVectors
{
public:
	BasePlayerVectors(BasePlayer player, Vector3 pos, CornerBox cBox, bool VisCheck)
	{
		this->basePlayer = player;
		this->position = pos;
		this->cornerBox = cBox;
		this->visible = VisCheck;
	}

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

	BasePlayer basePlayer;
	Vector3 position;
	CornerBox cornerBox;
	bool visible;
};

inline std::list<BasePlayer> BasePlayers;
inline std::list<BasePlayer> TempBasePlayers;

inline std::list<BasePlayerVectors> basePlayerVectorList;
inline std::list<BasePlayerVectors> temp_basePlayerVectorList;

inline std::list<ILine> ILines; inline std::list<ILine> TempILines;

namespace Visuals
{
	void DrawESP();
	void SyncedThread();
	void SyncedInput();
	void AddObject(char* Prefab, char* Name, bool Draw, bool Alive = false);
};

namespace Entity
{
	bool isPlayer(char* EntityClassName);
};