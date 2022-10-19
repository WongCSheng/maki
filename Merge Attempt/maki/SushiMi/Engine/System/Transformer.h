#pragma once

#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <vector>
#include "SystemFrame.h"

//Forward Declaration

namespace Core
{
	class Entity;
	class Transform;
	
	class Transformer : public ::SystemFrame
	{
	public:
		Transformer();
		virtual ~Transformer();
		virtual void RegisterComponents(const Core::Component comp);
		virtual void Update(const double dt);
		virtual void CheckForNewComponents(void);
		void UpdateTransformation(Transform* Transform);

	private:
		void RemoveFromTree(Transform* transform);
		std::vector<Transform*> transforms;
		Entity* root;
	};
}

#endif