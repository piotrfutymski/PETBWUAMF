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
		Moved, Attacking, BeingAttacked, DMGTaken, Buff, Debuff, UnitCreated
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


	MoveRes operator+ (const MoveRes & r)
	{
		MoveRes res;
		res.events = this->events;
		res.events.insert(res.events.end(), r.events.begin(), r.events.end());
		return res;
	}
};