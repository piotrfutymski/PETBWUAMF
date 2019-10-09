#include "Application.h"


int main()
{
	Application a;
	a.init("data/settings.json");
	return a.run();
}