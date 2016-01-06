#include "TinyControl.h"

TinyControl::TinyControl() {

	for (int i = 0; i < NUMBER_OF_BUTTON; ++i) {
		button[i] = true;
		fader[i] = 0;
		potentiometer[i] = 0;
	}
}

void TinyControl::update(int control, int value) {
	if (23 <= control && control <= 31) {
		if (value == 0) {
			int i = control - 23;
			button[i] = !button[i];
		}
	} else if (3 <= control && control <= 11) {
		int i = control - 3;
		fader[i] = value;
	} else if (14 <= control && control <= 22) {
		int i = control - 14;
		potentiometer[i] = value;
	}
}

bool TinyControl::getButton(int i) {
	return button[i];
}

int TinyControl::getFader(int i) {
	return fader[i];
}

int TinyControl::getPotentiometer(int i) {
	return potentiometer[i];
}
