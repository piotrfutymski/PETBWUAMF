#pragma once
#include "Asset.h"

class Buff;

class BuffPrototype :public Asset
{
public:
	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset

	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	std::function<void(size_t, Buff *)> _onBegin;
	std::function<void(size_t, Buff *)> _onTurnEnd;
	std::function<void(size_t, Buff *)> _onEnd;

	int _time;				// -1 = always
	int _Fvalue;
	float _Svalue;
	std::string _buffingParameter;
	std::string _buffedParameter;

};