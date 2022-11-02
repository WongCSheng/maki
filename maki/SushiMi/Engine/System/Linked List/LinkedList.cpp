
#include "LinkedList.h"

namespace Core
{
	template<typename T>
	LinkedList<T>::LinkedList()
	{
		left = right = data = nullptr;
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		delete data;
		delete left;
		delete right;
	}
}