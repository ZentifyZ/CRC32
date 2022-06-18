#pragma once

inline void DrawSwastikaCrosshair(int size, int Drehungswinkel)
{
	auto MiddleX = Vars::Global::ScreenWidth / 2;
	auto MiddleY = Vars::Global::ScreenHigh / 2;
	int a = (int)(Vars::Global::ScreenHigh / 2 / (61 - size));
	float gamma = atan(a / a);

	int i = 0;
	while (i < 4)
	{
		std::vector <int> p;
		p.push_back(a * sin(GRD_TO_BOG(Drehungswinkel + (i * 90))));
		p.push_back(a * cos(GRD_TO_BOG(Drehungswinkel + (i * 90))));
		p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));
		p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));

		ImGui::GetBackgroundDrawList()->AddLine({ MiddleX, MiddleY }, { MiddleX + p[0], MiddleY - p[1] }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
		ImGui::GetBackgroundDrawList()->AddLine({ MiddleX + p[0], MiddleY - p[1] }, { MiddleX + p[2], MiddleY - p[3] }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));

		i++;
	}
}

inline void DrawCrossCrosshair(int size)
{
	auto MiddleX = Vars::Global::ScreenWidth / 2;
	auto MiddleY = Vars::Global::ScreenHigh / 2;

	ImGui::GetBackgroundDrawList()->AddLine({ MiddleX - size, MiddleY }, { MiddleX + size + 1, MiddleY }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
	ImGui::GetBackgroundDrawList()->AddLine({ MiddleX, MiddleY - size }, { MiddleX, MiddleY + size + 1 }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
}

inline void DrawXCrosshair(int size)
{
	auto MiddleX = Vars::Global::ScreenWidth / 2;
	auto MiddleY = Vars::Global::ScreenHigh / 2;

	ImGui::GetBackgroundDrawList()->AddLine({ MiddleX - size, MiddleY - size }, { MiddleX + size, MiddleY + size + 1 }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
	ImGui::GetBackgroundDrawList()->AddLine({ MiddleX + size, MiddleY - size - 1 }, { MiddleX - size, MiddleY + size }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
}

inline void DrawCircleCrosshair(int size)
{
	auto MiddleX = Vars::Global::ScreenWidth / 2;
	auto MiddleY = Vars::Global::ScreenHigh / 2;

	ImGui::GetBackgroundDrawList()->AddCircle({ MiddleX, MiddleY }, size, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]), 48);
}

inline void DrawCustomCrosshair(int size, int thickness, int gap)
{
	auto MiddleX = Vars::Global::ScreenWidth / 2;
	auto MiddleY = Vars::Global::ScreenHigh / 2;

	ImGui::GetBackgroundDrawList()->AddRectFilled({ MiddleX - gap - size,  MiddleY + thickness }, { MiddleX - gap,  MiddleY - thickness }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ MiddleX + gap + size,  MiddleY + thickness }, { MiddleX + gap,  MiddleY - thickness }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));

	ImGui::GetBackgroundDrawList()->AddRectFilled({ MiddleX - thickness,  MiddleY - gap - size }, { MiddleX + thickness,  MiddleY - gap }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ MiddleX - thickness,  MiddleY + gap + size }, { MiddleX + thickness,  MiddleY + gap }, ImColor(Vars::Color::CrosshairColor[0], Vars::Color::CrosshairColor[1], Vars::Color::CrosshairColor[2]));
}

inline Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float mainAngle = flAngle;
	mainAngle += 45.f;

	float flYaw = (mainAngle) * (M_PI / 180.0);

	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));

	return Vector2(posonscreenX, posonscreenY);
}

inline void CreateLine(Vector3 p0, Vector3 p1, ImColor color)
{
	TempILines.push_front(ILine(p0, p1, color));
}

inline void CreateBoneLine(int b0, int b1, ImColor color, BasePlayer basePlayer)
{
	if (b0 == BoneList(head))
	{
		auto bb = basePlayer.model.GetTransform(BoneList(b0)).GetPosition();
		CreateLine(bb, basePlayer.model.GetTransform(BoneList(b1)).GetPosition(), color);
	}
	else CreateLine(basePlayer.model.GetTransform(BoneList(b0)).GetPosition(), basePlayer.model.GetTransform(BoneList(b1)).GetPosition(), color);
}

inline void InvisiblePlayerIndicator(Vector3 position, Vector3 local, Quaternion localRotation, ImColor color)
{
	float num = atan2(local.x - position.x, local.z - position.z) * 57.29578f - 180.f - EulerAngles(localRotation).y;

	Vector2 tp0 = CosTanSinLineH(num, 5.f, Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2, 150.f);
	Vector2 tp1 = CosTanSinLineH(num + 2.f, 5.f, Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2, 140.f);
	Vector2 tp2 = CosTanSinLineH(num - 2.f, 5.f, Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2, 140.f);
	ImGui::GetBackgroundDrawList()->AddTriangleFilled({ tp0.x,tp0.y }, { tp1.x,tp1.y }, { tp2.x,tp2.y }, color);
}
inline void DrawFilledBox(const Vector2& vecStart, const Vector2& vecEnd, ImU32 col)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(vecStart.x, vecStart.y), ImVec2(vecStart.x + vecEnd.x, vecStart.y + vecEnd.y), col);
}
inline void DrawOutlineBox(const Vector2& pos, const Vector2& size, ImU32 col) {

	float thickness = 1.0f;

	DrawFilledBox(Vector2(pos.x, pos.y - thickness), Vector2(size.x + 1, thickness), col);
	DrawFilledBox(Vector2(pos.x, pos.y + size.y), Vector2(size.x + 1, thickness), col);

	DrawFilledBox(Vector2(pos.x - thickness, pos.y - thickness), Vector2(thickness, size.y + thickness * 2), col);
	DrawFilledBox(Vector2(pos.x + size.x, pos.y - thickness), Vector2(thickness, size.y + thickness * 2), col);
}
inline void DrawHealthBar(const Vector2& vecStart, const Vector2& vecEnd, float distance, int health, int maxhealth) {
	// i literally tried to do dynamic color like green to red but this shit aint working i dont fucking know why and this is so embarassing but i dont really care at this point anymore im just frustrated... i really hate to do uncompleted stuff but i dont really care anymore im really fucking shitt right now and i just did nigger stuff and idk i dont care
	auto x = vecStart.x;
	auto y = vecStart.y;

	auto w = vecEnd.x - vecStart.x;
	auto h = vecEnd.y - vecStart.y;

	auto Percentage = health * (h / maxhealth);
	float HeightOffset = max(w / 8.f, 8.f);

	DrawOutlineBox(Vector2(x - HeightOffset - 1, y), Vector2(2, h), ImColor(0, 0, 0, 170));
	DrawFilledBox(Vector2(x - HeightOffset - 1, y), Vector2(2, h), ImColor(0, 0, 0, 170));
	DrawFilledBox(Vector2(x - HeightOffset - 1, y + h - Percentage), Vector2(2, Percentage), ImColor(0, 200, 0, 255));
}


inline void DrawBox(const Vector2& vecStart, const Vector2& vecEnd, ImU32 col, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(vecStart.x, vecStart.y), ImVec2(vecStart.x + vecEnd.x, vecStart.y + vecEnd.y), col, 0, 0, thickness);
}

inline void DrawCornerBox(const Vector2& vecStart, const Vector2& vecEnd, ImU32& color, float thickness)
{
	auto x = vecStart.x;
	auto y = vecStart.y;

	auto w = vecEnd.x - vecStart.x;
	auto h = vecEnd.y - vecStart.y;

	float ratio = 3.0f;

	auto MiddleY = Vars::Global::ScreenHigh / 2;

	if (vecStart.x < 1.f || vecStart.x > Vars::Global::ScreenWidth)
	{
		//return;
	}
	if (vecStart.y < 1.f || vecStart.y > Vars::Global::ScreenHigh)
	{
		//return;
	}

	auto corner = [&](const int32_t _x, const int32_t _y, const int32_t width, const int32_t height, const bool right_side, const bool down, ImU32& color_) -> void
	{
		const auto corner_x = right_side ? _x - width : _x;
		const auto corner_y = down ? _y - height : _y;
		const auto corner_w = down && right_side ? width + 1 : width;

		DrawBox(Vector2(corner_x + 1, _y + 1), Vector2(corner_w + 1, 1), color_, thickness);
		DrawBox(Vector2(_x + 1, corner_y + 1), Vector2(1, height + 1), color_, thickness);
	};

	corner(x, y, w / ratio, w / ratio, false, false, color);
	corner(x, y + h, w / ratio, w / ratio, false, true, color);
	corner(x + w, y, w / ratio, w / ratio, true, false, color);
	corner(x + w, y + h, w / ratio, w / ratio, true, true, color);
}
