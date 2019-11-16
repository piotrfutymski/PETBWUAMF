#include "Reporter.h"

Reporter::Reporter()
{

}
void Reporter::SaveTurn(MoveRes data)
{
	this->_turnReport.push_back(data);
}
MoveRes Reporter::getLastTurn() const
{
	if (!this->_turnReport.empty())
		return this->_turnReport.back();
	return { {},{},{},{} };
}
MoveRes Reporter::getTurn(int number) const
{
	return this->_turnReport.at(number);
}
std::vector<MoveRes> Reporter::getAllTurns() const
{
	return this->_turnReport;
}