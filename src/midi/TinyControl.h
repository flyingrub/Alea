#pragma once
#include "ofMain.h"
#define NUMBER_OF_BUTTON 9

class TinyControl {

	public:
		TinyControl();
        void update(int control, int value);
        bool getButton(int i);
        int getFader(int i);
        int getPotentiometer(int i);
	private:
		bool button[NUMBER_OF_BUTTON];
		int fader[NUMBER_OF_BUTTON];
		int potentiometer[NUMBER_OF_BUTTON];

};