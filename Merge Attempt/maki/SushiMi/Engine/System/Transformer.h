#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <vector>
#include "SystemFrame.h"
#include "../Headers/Math_Header.h"
#include "../Game Object/GameObject.h"

#include "../Headers/STL_Header.h"
#include "Graphics/glslshader.h"
#include "../Engine/Mesh/model.h"


#define DEFAULTFORWARD gfxVector2(1.f, 0.f)

namespace Core
{
	//Forward Declaration
	class Transform;
	
	class Transformer : public SystemFrame
	{
		friend class Transform;

	public:
		Transformer();
		virtual ~Transformer();

		void Init(Object::GameObject* obj);
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		void Serialise(const std::string name);
		void UpdateTransformation(Transform* Transform);

		gfxVector2 orientation{};	// orientation.x is angle_disp and
		// orientation.y is angle_speed both in degrees

		gfxVector2 scaling{};		// scaling parameters
		gfxVector2 position{};		// translation vector coordinates
		gfxVector2 velocity{};
		float dirCurr{};

		// compute object's model transform matrix using scaling,
		// rotation, and translation attributes
		gfxMatrix3 mdl_to_ndc_xform{};
		gfxMatrix3 mdl_xform{}; // model transformation

		GLboolean rot_right{ GL_FALSE };
		GLboolean rot_left{ GL_FALSE };
		GLboolean scale_up{ GL_FALSE };
		GLboolean scale_down{ GL_FALSE };

	private:
		std::unordered_map<std::string, Object::GameObject*> Transforms;

		
	};
}

#endif