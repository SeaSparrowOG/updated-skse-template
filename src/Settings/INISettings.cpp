#include "INISettings.h"

#include <SimpleIni.h>

namespace
{
    static constexpr auto MakeINIPath() {
        constexpr std::string_view prefix = R"(.\Data\SKSE\Plugins\)";
        constexpr std::string_view suffix = ".ini";
        constexpr std::string_view pluginName = Plugin::NAME;

        constexpr size_t totalSize = prefix.size() + pluginName.size() + suffix.size();
        std::array<char, totalSize + 1> buffer{};

        std::copy(prefix.begin(), prefix.end(), buffer.begin());
        std::copy(pluginName.begin(), pluginName.end(), buffer.begin() + prefix.size());
        std::copy(suffix.begin(), suffix.end(), buffer.begin() + prefix.size() + pluginName.size());

        return buffer;
    }
}

namespace Settings::INI
{
	void Holder::Read() {
        static constexpr auto iniPathArray = MakeINIPath();
        static constexpr std::string_view IniPath{ iniPathArray.data(), iniPathArray.size() };

		CSimpleIniA ini{};
		ini.SetUnicode();
        ini.LoadFile(IniPath.data());
	}
}
