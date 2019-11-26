#pragma once
#include <utility>
#include "Asset.h"

class Buff;

class BuffPrototype :public Asset
{
public:
	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset

	virtual void loadAsset(const nlohmann::json & assetFile) override; /* Loads data from asset file*/

public:

	std::pair<std::string, std::string >_begin;
	std::pair<std::string, std::string >_turnEnd;
	std::pair<std::string, std::string >_end;
	bool beginFlag{ false };
	bool turnFlag{ false };
	bool endFlag{ false };
	std::function<void(size_t, Buff *)> _onBegin;
	std::function<void(size_t, Buff *)> _onTurnEnd;
	std::function<void(size_t, Buff *)> _onEnd;
	int toUParameter(const std::string & name);
	int _time;				// -1 = always

};