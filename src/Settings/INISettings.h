#pragma once

namespace Settings
{
	namespace INI
	{
		class Holder : public Utilities::Singleton::ISingleton<Holder>
		{
		public:
			void Read();
		};
	}
}
