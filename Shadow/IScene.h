#pragma once

class IScene
{
public:
	virtual void OnCreate() = 0;

	virtual void OnDestroy() = 0;
};