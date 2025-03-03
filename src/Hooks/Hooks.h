#pragma once

#include "utilities/utilities.h"

namespace Hooks {
	void Install();

	class ExampleHook : public Utilities::Singleton::ISingleton<ExampleHook>
	{
	public:
		static void Install();

	private:
		static void Hook();
		inline static REL::Relocation<decltype(&Hook)> _hook;
	};
}