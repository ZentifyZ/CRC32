#pragma once

namespace Arrays {
}



static inline bool TestNoClipping(BasePlayer ply, Vector3 oldPos, Vector3 newPos, float radius, bool sphereCast) {
	int num = 429990145;
	//Ulog("6");
	//if ( ply.vehiclePauseTime > 0f ) {
	//	num &= -8193;
	//}
	Vector3 normalized = (newPos - oldPos).normalized();
	Vector3 vector = oldPos - normalized;
	float magnitude = (newPos - vector).magnitude();
	bool flag{};
	if (sphereCast) {
		flag = UnityEngine::SphereCast(Ray(vector, normalized), radius, magnitude, num);
	}
	return flag;
}
static float NoClipRadius(float margin)
{
	return  0.5f - margin;
}
static float Max(float f1, float f2, float f3)
{
	return MathF::Max(MathF::Max(f1, f2), f3);
}
static bool ValidateEyePos(Vector3 eyePos)
{
	bool flag = true;


	float desyncTime = (UnityEngine::get_realtimeSinceStartup() - LocalPlayer.lastSentTickTime());

	float num = 1.5f;
	float eye_clientframes = 2.0f;
	float eye_serverframes = 2.0f;
	float num2 = eye_clientframes / 60.0f;
	float num3 = eye_serverframes * Max(UnityEngine::get_deltaTime(), UnityEngine::get_smoothDeltaTime(), UnityEngine::get_fixedDeltaTime());
	float num4 = (desyncTime + num2 + num3) * num;
	int layerMask = Settings::Combat::WeaponMods::Penetrate ? 10551296 : 2162688;
	Vector3 position2 = LocalPlayer.Eyes.GetPosition();


	//float num8 = MathF::Abs(LocalPlayer.GetMountVelocity().y + LocalPlayer.GetParentVelocity().y);
	float num9 = LocalPlayer.BoundsPadding() + num4 + LocalPlayer.GetJumpHeight();
	float num10 = MathF::Abs(LocalPlayer.Eyes.GetPosition().y - eyePos.y);
	if (num10 > num9)
	{
		//eye alt
		printf("Valid 2 \n");
		flag = false;
	}

	//Vector3 center = LocalPlayer.Eyes.get_center();
	//Vector3 position = LocalPlayer.Eyes.GetPosition();

	if (eyePos.distance(position2) > 0.01f && TestNoClipping(LocalPlayer, position2, eyePos, NoClipRadius(0.21f), 0.01f))
	{
		Ulog("Valid");
		flag = false;
	}
	return flag;
}