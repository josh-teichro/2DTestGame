#pragma once

#include <memory>

namespace GameEngine
{

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using WeakRef = std::weak_ptr<T>;


	template<typename T, typename...Args>
	constexpr Scope<T> MakeScope(Args&&...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename...Args>
	constexpr Ref<T> MakeRef(Args&&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
