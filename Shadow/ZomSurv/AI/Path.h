#include "sdpch.h"
#pragma once

#include "Node.h"

class Path
{
public:
	inline void AddToPath(Node node) { m_path.push_back(node); }
	inline void PopPath() { m_path.pop_front(); }
private:
	std::list<Node> m_path;
};

