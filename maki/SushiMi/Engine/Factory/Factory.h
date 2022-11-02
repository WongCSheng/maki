//******************************************************************************/
/*!
\file		Factory.h
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Header for factory for managing GameObjects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#pragma once

#include <set>
#include "../Engine/System/SystemFrame.h"

namespace Core
{
	//forward declaration
	namespace Object
	{
		class GameObject;
	}

	class ObjectFactory : public SystemFrame
	{
	private:
		unsigned int LastObjectID;

		std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer;

		std::set<Object::GameObject*> DeleteList;

	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		Object::GameObject* Create();

		void AddtoDestroyList(Object::GameObject* Obj);

		void DestroyEverything();

		virtual void Update(const double dt);

		void AddObjects(Object::GameObject* added, unsigned int i);

		virtual void Init();

		Object::GameObject* BuildSerialise(const std::string filename);
	};
}