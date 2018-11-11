#include "Core/Log.h"
#include "Ray/Ray.h"

#include <glm/gtc/constants.hpp>

int main(int argc, char *argv[])
{
	InitLog();
	LogInfo("Light Box");

	glm::ivec2 CameraResolution;

	DRayBundle CameraRayBundle;

	BuildFrustumProjection(
		CameraRayBundle.Rays,
		{ 4096, 4096 },
		{ glm::half_pi<float>(), glm::half_pi<float>() });

	CameraRayBundle.Project(5.0f);
}

