#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_


/*!
@file		Sprite.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#include "../Engine/Components/Texture/Texture.h"
#include "../Engine/System/Renderer.h"
#include "../Engine/Components/Transform/Transform.h" //important as it is the only function that has a get()
//#include "../Engine/Components/Transform/Transform.h"
//#include "../Engine/System/Transformer.h"
#include "../Engine/Animation/Animation2D.h"

namespace Core
{
	class Sprite :public Component
	{
	public:

		Sprite(const char* filename);

		~Sprite();

		void draw();
		void drawTest();

		void draw(double deltatime, AnimationType type);

		void Add_animation(const char* filename);

		void Init();
		void Serialize(const std::string name);
		void Deserialize(const rapidjson::Value& jsonObj);

		void restart();

		bool IsActive();
		void Activate();
		void Deactivate();
		void Remove();
		bool isSpriteSheet;
		float SpriteSize[2];

		std::string levelname;
		std::vector<std::string> CorrectIngredients;
		static std::map<std::string, std::vector<std::string>> levelCorrectIngredients;
		Transform transformation;

		AnimationType curr_anim;

		static inline Sprite* menu;

		static inline struct ingr1GridPos
		{
			int x;
			int y;
		} ingredient1_Grid_pos;

		static inline struct ingr2GridPos
		{
			int x;
			int y;
		} ingredient2_Grid_pos;

		static inline struct ingr1_init_GridPos
		{
			int x;
			int y;
		} ingredient1_initial_pos;
			
		static inline struct ingr2_init_GridPos
		{
			int x;
			int y;
		}ingredient2_initial_pos;

		static inline struct trapGridPos
		{
			int x;
			int y;
		} trap_Grid_pos;

		static inline struct goal1GridPos
		{
			int x;
			int y;
		} goal1_Grid_pos;

		static inline struct goal2GridPos
		{
			int x;
			int y;
		} goal2_Grid_pos;

		float timer;
		int count;
		float alpha;
		bool animeMe;

		/*for salmon to toggle between the sprites
		status 0 = normal
		status 1 = soya
		status 2 = wasabi
		status 3 = both
		status 4 = soya clense
		status 5 = wasabi clense
		status 6 = soya clense go to wasabi
		status 7 = wasabi clense go to soya
		status 8 = cleanse all
		*/
		int status;

	private:

		Texture texture;
		vtx rectangle;
	
		std::vector<Animation2D*> anims;
	};

	

}
#endif
