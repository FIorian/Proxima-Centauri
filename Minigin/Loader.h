#pragma once
#include "Singleton.h"

namespace dae
{
	class Loader final : public dae::Singleton<Loader>
	{
	public:
		void LoadLevel(const std::string& fileName);
	};
}

