#pragma once

#include "../Core/Array.h"
#include "../Core/Log.h"

#include <glm/glm.hpp>
#include <ThreadPool.h>

struct DRay
{
	glm::vec3 Origin;
	glm::vec3 Direction;
	glm::vec3 Color;
};

void BuildFrustumProjection(
	DArray<DRay>& RayBundle,
	const glm::ivec2& Resolution,
	const glm::vec2& FieldOfView)
{
	const int32_t RayCount = Resolution.x * Resolution.y;
	RayBundle.Resize(RayCount);

	const float ImagePlaneDepth = 1.0f;
	const float ImagePlaneWidth = 2.0f * glm::tan(FieldOfView.x / 2.0f);
	const float ImagePlaneHeight = 2.0f * glm::tan(FieldOfView.y / 2.0f);

	int32_t RayIndex = 0;
	for (int32_t Row = 0; Row < Resolution.y; Row++)
	{
		const float Green = static_cast<float>(Row) / static_cast<float>(Resolution.y);
		for (int32_t Column = 0; Column < Resolution.x; Column++)
		{
			DRay& Ray = RayBundle[RayIndex];

			Ray.Color.r = static_cast<float>(Column) / static_cast<float>(Resolution.x);
			Ray.Color.g = Green;
			Ray.Color.b = 0.0f;

			Ray.Direction.x = (static_cast<float>(Column) - static_cast<float>(Resolution.x) / 2.0f) * ImagePlaneWidth;
			Ray.Direction.y = (static_cast<float>(Row) - static_cast<float>(Resolution.y) / 2.0f) * ImagePlaneHeight;
			Ray.Direction.z = ImagePlaneDepth;

			Ray.Origin = {0.0f, 0.0f, 0.0f};
			
			RayIndex++;
		}
	}
	LogInfo("Built {} Rays", RayCount);
}

struct DRayBundle
{
	DArray<DRay> Rays;

	void Project(float Distance)
	{
		for (DRay& Ray : Rays)
		{
			Ray.Origin += Ray.Direction * Distance;
		}
	}
};
