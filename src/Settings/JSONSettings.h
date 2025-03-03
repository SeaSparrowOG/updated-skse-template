#pragma once

#include "Utilities/Utilities.h"

namespace Settings
{
	namespace JSON
	{
		class Holder : public Utilities::Singleton::ISingleton<Holder>
		{
		public:
			void Read();
		};
	}
}
