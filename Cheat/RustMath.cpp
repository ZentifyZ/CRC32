#include "pch.h"
#include "RustMath.h"

StaticCameraClass* Get_Camera()
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;

	__try
	{
		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_main");
		}

		typedef StaticCameraClass* Method();
		auto pCamera = ((Method*)(Globals::g_GameAssemblyBase + var))();

		return pCamera;
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

Vector3 WorldToScreenPoint(Vector3 Position)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = Dumper::GetMethodOffset("UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToScreenPoint", 1);
		}

		typedef Vector3 Method(StaticCameraClass*, Vector3);
		return ((Method*)(Globals::g_GameAssemblyBase + var))(Get_Camera(), Position);
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

Vector2 World2Screen(Vector3 entitiyPosition)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (StaticCamera == 0) StaticCamera = Get_Camera();
		GlobalCurrentViewMatrix = &StaticCamera->PointerOne_->PointerTwo_->PointerThree_->PointerFour->ViewMatrix;

		float w = Vector3(GlobalCurrentViewMatrix->_14, GlobalCurrentViewMatrix->_24, GlobalCurrentViewMatrix->_34).Dot(entitiyPosition) + GlobalCurrentViewMatrix->_44;
		if (w < 0.098f) return Vector2();

		float y = Vector3(GlobalCurrentViewMatrix->_12, GlobalCurrentViewMatrix->_22, GlobalCurrentViewMatrix->_32).Dot(entitiyPosition) + GlobalCurrentViewMatrix->_42;
		float x = Vector3(GlobalCurrentViewMatrix->_11, GlobalCurrentViewMatrix->_21, GlobalCurrentViewMatrix->_31).Dot(entitiyPosition) + GlobalCurrentViewMatrix->_41;
		Vector2 screenPosition = Vector2((Vars::Global::ScreenWidth / 2) * (1.f + x / w), (Vars::Global::ScreenHigh / 2) * (1.f - y / w));

		if (screenPosition.x >= GetScreenWidth())
		{
			return Vector2();
		}
		else if (screenPosition.y >= GetScreenHeight())
		{
			return Vector2();
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
	return Vector2();
}

bool WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		if (StaticCamera == 0) StaticCamera = Get_Camera();

		GlobalCurrentViewMatrix = &StaticCamera->PointerOne_->PointerTwo_->PointerThree_->PointerFour->ViewMatrix;

		float w = Vector3(GlobalCurrentViewMatrix->_14, GlobalCurrentViewMatrix->_24, GlobalCurrentViewMatrix->_34).Dot(EntityPos) + GlobalCurrentViewMatrix->_44;
		if (w < 0.098f) return false;
		float y = Vector3(GlobalCurrentViewMatrix->_12, GlobalCurrentViewMatrix->_22, GlobalCurrentViewMatrix->_32).Dot(EntityPos) + GlobalCurrentViewMatrix->_42;
		float x = Vector3(GlobalCurrentViewMatrix->_11, GlobalCurrentViewMatrix->_21, GlobalCurrentViewMatrix->_31).Dot(EntityPos) + GlobalCurrentViewMatrix->_41;
		ScreenPos = Vector2((Vars::Global::ScreenWidth / 2) * (1.f + x / w), (Vars::Global::ScreenHigh / 2) * (1.f - y / w));
		if (ScreenPos.x <= 0.f)
			return false;
		if (ScreenPos.y <= 0.f)
			return false;

		if (ScreenPos.x >= Vars::Global::ScreenWidth)
			return false;
		if (ScreenPos.y >= Vars::Global::ScreenHigh)
			return false;

		/*
		if (ScreenPos.x <= -Vars::Global::ScreenWidth * 0.25f)
			return false;
		if (ScreenPos.y <= -Vars::Global::ScreenHigh * 0.25f)
			return false;

		if (ScreenPos.x >= Vars::Global::ScreenWidth * 1.25f)
			return false;
		if (ScreenPos.y >= Vars::Global::ScreenHigh * 1.25f)
			return false;
		*/

		return true;
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

	StaticCamera = 0;
	return false;
}

bool NewMethodWorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos)
{
	ULONG ExceptionCode = 0;
	PEXCEPTION_POINTERS ExceptionPointers = 0;
	__try
	{
		auto w2sp = WorldToScreenPoint(EntityPos);
		ScreenPos.x = w2sp.x;
		ScreenPos.y = Vars::Global::ScreenHigh - w2sp.y;
		if (w2sp.z < 0.f)
		{
			return false;
		}
		return true;
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