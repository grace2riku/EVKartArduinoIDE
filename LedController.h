#ifndef LedController_h
#define LedController_h

class LedController {
	
public:
	LedController(int pin);
	void on();
	void off();
	
private:
	int m_ledPin;
	
};

#endif
