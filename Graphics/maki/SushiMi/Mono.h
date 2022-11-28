#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

class SushiMi
{
	public:
		SushiMi();
		~SushiMi();

		//interface
		void keyEvent(char key);
		bool tick();

	private:
		MonoDomain* m_ptrMonoDomain = nullptr;
		MonoAssembly* m_ptrGameAssembly = nullptr;
		MonoImage* m_ptrGameAssemblyImage = nullptr;
};