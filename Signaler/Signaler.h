#ifndef SIGNALER_H
#define SIGNALER_H

#define MAX_STRIP_LEN 100

class Signaler {
public:
	enum SignalState {
		NONE,
		LEFT,
		RIGHT
	};
	enum LightState {
		OFF,
		LOW,
		HIGH
	};

	struct Strip {
		unsigned int pixels[MAX_STRIP_LEN];
		struct {
			unsigned int center;
			unsigned int side;
			unsigned int total;
		} len;
	};

	Strip fstrip;
	Strip rstrip;

	Signaler(unsigned int frontCenterLen_, unsigned int frontSideLen_,
			 unsigned int rearCenterLen_, unsigned int rearSideLen_);
	
	void activateLeftTurn();
	void activateRightTurn();
	void deactivateTurn();

	void activateHazard();
	void deactivateHazard();

	void activateReverse();
	void deactivateReverse();

	void activateVisibility();
	void deactivateVisibility();

	void activateLowLight();
	void activateHighLight();
	void deactivateLight();

	void activateBrake();
	void deactivateBrake();

	void activateHorn();
	void deactivateHorn();
	void update();

private:
	struct {
		SignalState signal;
		LightState light;
		bool hazard;
		bool visibility;
		bool reverse;
		bool brake;
		bool horn;
	} state;

	struct {
		unsigned long signal;
		unsigned long light;
		unsigned long horn;
		unsigned long brake;
	} timestamp;
};

#endif // SIGNALER_H
