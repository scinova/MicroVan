#ifndef SIGNALERCONTROL_H
#define SIGNALERCONTROL_H

#include <Devices.h>

class SignalerControl {
private:
	Signaler& signaler;
	int leftTurnSwitchPin;
	int rightTurnSwitchPin;
	int hazardSwitchPin;
	int visibilitySwitchPin;
	int lowLightSwitchPin;
	int highLightSwitchPin;
	int hornSwitchPin;
	int brakeSwitchPin;
	int reverseSwitchPin;
	void hornOn() { signaler.activateHorn(); }
	void hornOff() { signaler.deactivateHorn(); }
	void visibilityOn() { signaler.activateVisibility(); }
	void visibilityOff() { signaler.deactivateVisibility(); }
	void brakeOn() { signaler.activateBrake(); }
	void brakeOff() { signaler.deactivateBrake(); }
	void hazardOn() { signaler.activateHazard(); }
	void hazardOff() { signaler.deactivateHazard(); }
	void reverseOn() { signaler.activateReverse(); }
	void reverseOff() { signaler.deactivateReverse(); }

	void lowLightOn() { signaler.activateLowLight(); }
	void lowLightOff() { if (signaler.state.light == OFF) signaler.deactivateLight(); }
	void highLightOn() { signaler.activateHighLight(); }
	void highLightOff() { if (signaler.state.light == HIGH) signaler.activateLowLight(); }

	void turnLeftOn() { signaler.activateLeftTurn(); }
	void turnLeftOff() { if (signaler.state.signal == LEFT) signaler.deactivateTurn(); }
	void turnRightOn() { signaler.activateRightTurn(); }
	void turnRightOff() { if (signaler.state.signal == RIGHT) signaler.deactivateTurn(); }

	Switch leftTurnSwitch(turnLeftOn, turnLeftOff);
	Switch rightTurnSwitch(turnRightOn, turnRightOff);
	Switch hazardSwitch(hazardOn, hazardOff);
	Switch visibilitySwitch(visibilityOn, visibilityOff);;
	Switch lowLightSwitch(lowLightOn, lowLightOff);
	Switch highLightSwitch(highLightOn, highLightOff);
	Switch hornSwitch(hornOn, hornOff);
	Switch brakeSwitch(brakeOn, brakeOff);
	Switch reverseSwitch(reverseOn, reverseOff);
public:
	SignalerControl(Signaler& signaler_,
			int leftTurnSwitchPin_, int rightTurnSwitchPin_, int hazardSwitchPin_, int visibilitySwitchPin_,
			int lowLightSwitchPin_, int highLightSwitchPin_, int hornSwitchPin_, int brakeSwitchPin_, int reverseSwitchPin_)
			: leftTurnSwitchPin(leftTurnSwitchPin_),
			rightTurnSwitchPin(rightTurnSwitchPin_),
			hazardSwitchPin(hazardSwitchPin_),
			visibilitySwitchPin(visibilitySwitchPin_),
			lowLightSwitchPin(lowLightSwitchPin_),
			highLightSwitchPin(highLightSwitchPin_),
			hornSwitchPin(hornSwitchPin_),
			brakeSwitchPin(brakeSwitchPin_),
			reverseSwitchPin(reverseSwitchPin_) {
	}

	void update() {
	}
};

#endif // SIGNALERCONTROL_H
