#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Atlas
{
	class ATLAS_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

#define LOG_INFO(...) ::Atlas::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...) ::Atlas::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Atlas::Log::GetCoreLogger()->error(__VA_ARGS__)
}