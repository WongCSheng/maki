#pragma once

#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <vector>
#include "SystemFrame.h"
#include "../Headers/Math_Header.h"
#include "../Game Object/GameObject.h"

#include "../Headers/STL_Header.h"
#include "../include/glslshader.h"
#include "../Engine/Mesh/model.h"

//Forward Declaration

namespace Core
{
	class Transform;
	
	class Transformer : public SystemFrame
	{
	public:
		Transformer();
		virtual ~Transformer();
		virtual void Init();
		virtual void Update(const double dt);
		virtual void Exit();
		void UpdateTransformation(Transform* Transform);


		glm::vec2 orientation{};	// orientation.x is angle_disp and
		// orientation.y is angle_speed both in degrees

		glm::vec2 scaling{};		// scaling parameters
		glm::vec2 position{};		// translation vector coordinates
		gfxVector2 velocity{};
		float dirCurr{};
		AABB aabb;

		// compute object's model transform matrix using scaling,
		// rotation, and translation attributes
		glm::mat3 mdl_to_ndc_xform{};

		// reference of the model to keep track of which model is it.
		std::map<std::string, Model>::iterator mdl_ref;

		// draw the specific model using the specific shader
		std::map<std::string, GLSLShader>::iterator shd_ref;

		static Object::GameObjectProperty* square;
		glm::vec3 color{};
		glm::mat3 mdl_xform{}; // model transformation

		static std::map<std::string, Object::GameObjectProperty*> objects; // singleton

		GLboolean rot_right{ GL_FALSE };
		GLboolean rot_left{ GL_FALSE };
		GLboolean scale_up{ GL_FALSE };
		GLboolean scale_down{ GL_FALSE };

	private:
		void RemoveFromTree(Transform* transform);
		std::vector<Transform*> transforms;
	};
}

#endif