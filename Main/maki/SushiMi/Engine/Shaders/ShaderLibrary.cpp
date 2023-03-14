#include "ShaderLibrary.h"
/*!
@file		ShaderLibrary.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Shader Library contains the vert and frag shaders for texture and colour shaders respectively.
			When shader programs are created, they will use the respective shader library
*//*__________________________________________________________________________*/

std::unique_ptr<ShaderLibrary> Shaders = nullptr;

namespace FS = std::filesystem;

const std::string shaders = "../shaders";
std::string Tvs, Tfs, Fvs,Ffs;

ShaderLibrary::ShaderLibrary()
{
	for (auto const& f : FS::directory_iterator(shaders))
	{
		if (f.path() == shaders + "\\Texture.vert" || f.path() == shaders + "\\Texture.frag")
		{
			std::ifstream fin(f);
			std::string line;
			while (!fin.eof())
			{
				std::getline(fin, line);
				if (f.path() == shaders + "\\Texture.vert")
				{
					Tvs += line;
					Tvs += "\n";
				}
				else
				{
					Tfs += line;
					Tfs += "\n";
				}
			}
		}
		else if (f.path() == shaders + "\\Font.vert" || f.path() == shaders + "\\Font.frag")
		{
			std::ifstream fin(f);
			std::string line;
			while (!fin.eof())
			{
				std::getline(fin,line);
					if (f.path() == shaders + "\\Font.vert")
					{
						Fvs += line;
						Fvs += "\n";
					}
					else
					{
						Ffs += line;
						Ffs += "\n";
					}
			}
		}
	}
	programs.insert(std::pair<std::string, ShaderProgram*>("Textured", new ShaderProgram(Tvs, Tfs)));
	programs.insert(std::pair<std::string, ShaderProgram*>("Font", new ShaderProgram(Fvs, Ffs)));

}

ShaderLibrary::~ShaderLibrary()
{
	for (auto& x : programs)
	{
		delete x.second; //memory leak 3
	}
}

ShaderProgram* ShaderLibrary::Textured_Shader()
{
	return programs["Textured"];
}

ShaderProgram* ShaderLibrary::Font_Shader()
{
	return programs["Font"];
}

ShaderProgram* ShaderLibrary::Colored_Shader()
{
	return programs["Colored"];
}
