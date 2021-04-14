#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include "FIeld.h"


using namespace sf;


int main()
{ 
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    Field comp;
    comp.fillField();
    comp.createShip();
    comp.Play();
	return 0;
}