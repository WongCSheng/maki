#pragma once

#include "../Headers/STL_Header.h"

namespace Core
{
	enum MessageId
	{
		None = 0,
		Start,
		Quit,
		Collide,
		Key_Press,
		Mouse_Press,
		File_Loaded,
		File_Error,
		Lvl_Load_Success,
		Lvl_Load_Fail,
	};
	
	class Message
	{
	private:
		std::string msg;

	public:
		Message();
		~Message();
	};
}