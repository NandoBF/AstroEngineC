#include <cmath>
#include <string>
#include <iostream>
using namespace std;


class CelestialBody {
	public:
		string name;
		unsigned int mass_m;
		unsigned int mass_e;
		unsigned int radius_m;
		unsigned int radius_e;
	
		CelestialBody(string name) {
			name = name;
		}
};
