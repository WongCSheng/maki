//******************************************************************************/
/*!
\file		Messaging.h
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Header for Messaging system the engine.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/


#pragma once

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