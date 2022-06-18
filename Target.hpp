#pragma once
namespace Target {
	BasePlayer FindTarget(float fov, bool vischeck = true);
	BasePlayer LightFindTarget(float fov);
}