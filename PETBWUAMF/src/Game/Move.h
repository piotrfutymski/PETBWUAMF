#pragma once

struct Move
{

	size_t unitID;
	size_t orderID;


	std::vector<size_t> units;
	std::vector<sf::Vector2i> positions;

};