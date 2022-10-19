#pragma once

#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#include <vector>
#include "SystemFrame.h"

//Forward Declaration

namespace Core
{
	class Transform;
	
	class Transformer : public ::SystemFrame
	{
	public:
		Transformer();
		virtual ~Transformer();
		virtual void Init();
		virtual void Update(const double dt);
		virtual void Exit();
		void UpdateTransformation(Transform* Transform);

	private:
		void RemoveFromTree(Transform* transform);
		std::vector<Transform*> transforms;
	};
}

#endif