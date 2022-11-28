#pragma once
/*!
@file    Physics.cpp
@author	 Aurelia Chong
\par	 email: fei.x@digipen.edu
		 Manages game physics such as acceleration and decelleration


 /*		Copyright(C) 2022 DigiPen Institute of Technology.
		Reproduction or disclosure of this file or its contents without the
		prior written consent of DigiPen Institute of Technology is prohibited.
*//*__________________________________________________________________________*/


/***********************************************************************************/
	/*!
															    Function declarations
	 */
	 /******************************************************************************/
float applyAccel(float mass);
float applyDecel(float mass);
void updatePosition(Object& objectData);