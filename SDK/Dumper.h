#pragma once

#define CREATE_TYPE( type, name, args ) typedef type( __cdecl* name) args; name _##name;
#define ASSIGN_TYPE( name ) _##name = (name)Internal::GetProcAddressA((HINSTANCE)Globals::g_GameAssemblyBase, #name);

typedef void* (*il2cpp_method_pointer_t)(void* target, void* methodinfo);

typedef struct method_info_t
{
	il2cpp_method_pointer_t* method_ptr;
	void* invoker_method;
	const char* name;
	void* klass;
} method_info_t;

typedef class Assembly {
public:
	const char* name;
	void* base_image;
};

typedef class Method {
public:
	const char* _namespace;
	const char* class_name;
	const char* method_name;
	UINT_PTR Pointer;
};

typedef class Field {
public:
	const char* _namespace;
	const char* class_name;
	const char* field_name;
	UINT_PTR Pointer;
};
typedef class Class {
public:
	const char* _namespace;
	const char* class_name;
	UINT_PTR Pointer;
};
inline std::list<Assembly> Assemblies;
inline std::list<Method> Methods;
inline std::list<Field> Fields;
inline std::list<Class> Classes;

namespace Dumper
{
	//inline bool Loaded = false;

	inline const char* current_assembly_name;
	inline void* root_domain;
	inline void* base_image;
	inline void* thread_domain;

	bool think(const char* assembly_name);

	UINT_PTR GetObjectType(const char* assembly_name, const char* _namespace, const char* class_name);

	UINT_PTR GetNewObject(const char* assembly_name, const char* _namespace, const char* class_name);

	UINT_PTR GetClassOffset(const char* assembly_name, const char* _namespace, const char* class_name);

	UINT_PTR GetMethodOffset(const char* assembly_name, const char* _namespace, const char* class_name, const char* method_name, int args = -1);

	UINT_PTR GetFieldOffet(const char* assembly_name, const char* _namespace, const char* class_name, const char* field_name);
}