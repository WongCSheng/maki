#pragma once

namespace Core
{
	template<typename T>
	class LinkedList
	{
	private:
		T* left, * right;
		T* data;

	public:
		LinkedList();
		~LinkedList();

		/*T* AddLeft(T* child);
		T* AddRight(T* child);*/
	};
}