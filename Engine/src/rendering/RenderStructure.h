#ifndef RENDER_STRUCTURE_H
#define RENDER_STRUCTURE_H

#include "core/utils.h"
#include "FrameBuffer.h"
#include "assets/Material.h"

namespace overflow
{
	struct Render_Camera
	{
		mat4 View;
		mat4 Projection;
	};
	
	struct Render_Object
	{
		mat4 Transformation;
		ref<Material> Material;
		bool CastShadows;
	};
	
	struct Render_Data
	{
		Render_Camera Camera;
		ref<FrameBuffer> Buffer;
		std::vector<Render_Object> Objects;
		bool SubmissionFinished;
	};
}

#endif //RENDER_STRUCTURE_H