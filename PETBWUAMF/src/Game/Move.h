#pragma once


struct Move
{
	size_t orderID;

	std::vector<size_t> units;
	std::vector<sf::Vector2i> positions;

};


struct Target
{
	size_t unit;
	sf::Vector2i position;
};

struct MoveRes
{

	enum class EventType {
		Moved, Attacking, BeingAttacked, DMGTaken, Buff, Debuff, UnitCreated, UnitDestroyed
	};

	struct MoveEvent
	{
		EventType type;
		size_t unit;
		std::string buffName;
		sf::Vector2i position;
		int dmg;
		int time;
	};

	std::vector < MoveEvent> events;

	MoveEvent getEventOfType(EventType t)
	{
		if (auto e = std::find_if(events.begin(), events.end(), [t](const MoveEvent & ev) {ev.type == t; }); e != events.end())
			return *e;
		return {};
	}

	MoveRes operator+ (const MoveRes & r)
	{
		MoveRes res;
		res.events = this->events;
		res.events.insert(res.events.end(), r.events.begin(), r.events.end());
		return res;
	}
};


enum class UParameter
{
	Morale, Health, Attack, Armor, Defence, RangedAttack, ChargeDeffence, ChargeAttack, Range, Move
};

enum class UFlag : unsigned long long
{
	None = 0,
	Ranged = 1,
	UnableToAttack = 2,
	UnableToMove = 4,
	Bleeding = 8,
	Fleeing = 16,
	Overheald = 32
};