#pragma once

#include "Utilities/Utilities.h"
#include "RE/Offset.h"

namespace Hooks {
	class HookClass : public Utilities::Singleton::ISingleton<HookClass>
	{
	public:
		void Install();

	private:
		struct Hook1
		{
			static void Install();
			static void Hook();

			inline static REL::ID addressID{ RE::Offset::Example::PleaseEditMe };
			inline static std::ptrdiff_t offset{ 0x0 };
			inline static REL::Relocation<decltype(&Hook)> _hook;
		};
	};

	void Install();
}