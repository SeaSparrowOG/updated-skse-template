#include "JSONSettings.h"

namespace
{
	constexpr auto MakeDirectory() {
		constexpr std::string_view prefix = R"(Data/SKSE/Plugins/)";
		constexpr std::string_view pluginName = Plugin::NAME;
		constexpr std::string_view suffix = R"(/)";

		constexpr size_t totalSize = prefix.size() + pluginName.size() + suffix.size();
		std::array<char, totalSize> buffer{}; //No +1 here, null terminator is wrong in this case.

		std::copy(prefix.begin(), prefix.end(), buffer.begin());
		std::copy(pluginName.begin(), pluginName.end(), buffer.begin() + prefix.size());
		std::copy(suffix.begin(), suffix.end(), buffer.begin() + prefix.size() + pluginName.size());

		return buffer;
	}

	static std::vector<std::string> GetAllJSONSettings()
	{
		static constexpr auto directoryArray = MakeDirectory();
		static constexpr std::string_view directory{ directoryArray.data(), directoryArray.size() };
		std::vector<std::string> jsonFilePaths;
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (entry.is_regular_file() && entry.path().extension() == ".json") {
				jsonFilePaths.push_back(entry.path().string());
			}
		}

		std::sort(jsonFilePaths.begin(), jsonFilePaths.end());
		return jsonFilePaths;
	}
}

namespace Settings::JSON
{
	void Holder::Read()
	{
		std::vector<std::string> paths{};
		try {
			paths = GetAllJSONSettings();
		}
		catch (const std::exception& e) {
			logger::warn("Caught {} while reading files.", e.what());
			return;
		}
		if (paths.empty()) {
			logger::info("No settings found");
			return;
		}

		for (const auto& path : paths) {
			Json::Reader JSONReader;
			Json::Value JSONFile;
			try {
				std::ifstream rawJSON(path);
				JSONReader.parse(rawJSON, JSONFile);
			}
			catch (const Json::Exception& e) {
				logger::warn("Caught {} while reading files.", e.what());
				continue;
			}
			catch (const std::exception& e) {
				logger::error("Caught unhandled exception {} while reading files.", e.what());
				continue;
			}
		}
	}
}
