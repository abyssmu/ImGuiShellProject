#pragma once

#ifndef _DEBUGMANAGER_
#define _DEBUGMANAGER_

#include <string>
#include <vector>

namespace
{
	static std::vector<std::string> DEBUG_MSG;

	void DebugMessage(const std::string& msg, const char* func)
	{
		DEBUG_MSG.push_back(msg + " " + std::string(func));
	}
}

#endif