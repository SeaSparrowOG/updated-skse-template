#include "Hooks.h"

#include "RE/Offset.h"

namespace Hooks {
	void Install()
	{
		ExampleHook::Install();
	}

	void ExampleHook::Install()
	{
		auto& trampoline = SKSE::GetTrampoline();
		REL::Relocation<std::uintptr_t> target{ RE::Offset::Example::PleaseEditMe, 0x0 };
		_hook = trampoline.write_call<5>(target.address(), Hook);
	}

	void ExampleHook::Hook()
	{
		_hook();
	}
}