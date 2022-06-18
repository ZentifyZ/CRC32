#pragma once
#include "Cheat\Header\RustMath.h"
#include "UnityEngineSDK.h"
#include "Cheat\Header\RustVisual.h"
#include <RustHooks.h>
#include <BasePlayer.h>
#include <Variables.h>
#include <array>


BasePlayer FindManipulateTarget(float fovDistance, bool vischeck = false)
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
void get_cyl(float radius, unsigned int sectors, std::vector<Vector3>& re, float max = 1.60f)
{

	for (float y = -1.60f; y < 1.60f; y += 0.1f) {
		int points = sectors;
		float step = (1.57079632679489661923) / points;
		float x, z, current = 0;
		for (size_t i = 0; i < points; i++)
		{
			x = MathF::Sin(current) * radius;
			z = MathF::Cos(current) * radius;

			re.push_back(Vector3(x, y, z));
			re.push_back(Vector3(-x, y, z));
			re.push_back(Vector3(x, y, -z));
			re.push_back(Vector3(-x, y, -z));

			current += step;
		}
	}
}
#define M_PI 3.14159265358979323846f

void get_cyl_points_z(std::vector<Vector3>& re, float radius = 2.2f, unsigned int sectors = 20, unsigned int rings = 20)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	for (r = 0; r < rings; r++)
		for (s = 0; s < sectors; s++)
		{
			float y = sin(-(M_PI / 2) + M_PI * r * R);
			float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			x *= radius;
			y *= radius;
			z *= radius;

			re.push_back(Vector3(x, y, z));
		}
}
namespace other {
	Vector3 m_manipulate = Vector3::Zero();

	void find_manipulate_angle() {
		m_manipulate = Vector3::Zero();
		BasePlayer target = FindManipulateTarget(Settings::Combat::Silent::SilentFOV, false);
		auto loco = LocalPlayer;
		int mask = Settings::Combat::WeaponMods::Penetrate ? 10551296 : 1503731969; // projectile los, flyhack mask

		// just remake this mess

		Vector3 re_p = LocalPlayer.get_transform( ).GetPosition( ) + LocalPlayer.get_transform( ).up( ) * ( PlayerEyes::EyeOffset().y + LocalPlayer.Eyes.viewOffset( ).y );
		//Vector3 re_p = LocalPlayer.Eyes.GetPosition();

		Vector3 target_pos = target.model.GetTransform(48).GetPosition();
		if (target_pos.empty()) return;
		// real eye pos
		//BasePlayer target = FindTarget(Settings::Combat::Silent::SilentFOV);
		Vector3 choice = Vector3::Zero();

		if (UnityEngine::IsVisible(re_p, target_pos, mask, 0.2f)) {
			m_manipulate = Vector3::Zero();
			return;
		}

		double desyncTime = (UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime()) - 0.033125 * 3;
		double mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.50f) * LocalPlayer.EyeMaxVelocity()) - 0.05f;

		//Ulog("Max Eye %f", mm_max_eye);
		if (mm_max_eye < 1.3f) mm_max_eye = 1.3f;
		Vector3 _right = LocalPlayer.Eyes.MovementRight();
		Vector3 forward = LocalPlayer.Eyes.MovementForward();
		std::vector<Vector3> arr = {};

		get_cyl(mm_max_eye, 10, arr);

		int z = 0;
		for (auto s : arr) {
			if (s.y > 1.3f || s.y < -1.3f) continue;
			//(s.z > 1.6 || s.x < -1.6);
			Vector3 point = re_p + s;


			z += 1;
			//UnityEngine::Line(re_p, point, Color(0.5, 0.5, 0.5, 0.5), 0.02f, false, false);
			//UnityEngine::Sphere(point, 0.05f, Color(0.5, 0.5, 0.5, 0.5), 0.02f, false);
			if (!UnityEngine::IsVisible(point, re_p, mask, 0.2f))
				continue;

			if (!UnityEngine::IsVisible(target_pos, point, mask, 0.2f))
				continue;

			if (!ValidateEyePos(point))
				continue;

		//	Ulog("LOS from position %i (%ff, %ff, %ff)\n", z, point.x, point.y, point.z);
			choice = s;
			break;
		}
		if (choice.empty()) {
			m_manipulate = Vector3::Zero();
			return;
		}

		m_manipulate = choice;
	}
}