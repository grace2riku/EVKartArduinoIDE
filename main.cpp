#include "stdafx.h"
#include "EvKartPin.h"
#include "LedController.h"
#include <MsTimer2.h>

void pollDetect();
void expireTimer();

LedController uHallSensorLED = LedController(U_HALL_SENSOR_LED);
LedController vHallSensorLED = LedController(V_HALL_SENSOR_LED);
LedController wHallSensorLED = LedController(W_HALL_SENSOR_LED);

/* �z�[���Z���T�̃|�W�V���� �z�[���Z���T�̓��̓|�[�g����ǂݎ�����l */
enum hallSensorPositionValue {
    HALL_SENSOR_POSITION_1 = 1,
    HALL_SENSOR_POSITION_2,
    HALL_SENSOR_POSITION_3,
    HALL_SENSOR_POSITION_4,
    HALL_SENSOR_POSITION_5,
    HALL_SENSOR_POSITION_6
} HALLSENSORPOSITIONVALUE;


void setup() {
  // put your setup code here, to run once:

	/* �z�[���Z���T�̃s���ݒ� */
	pinMode(HALL_U_PORT, INPUT);
	pinMode(HALL_V_PORT, INPUT);
	pinMode(HALL_W_PORT, INPUT);

	/* FET�̃s���ݒ� */
	pinMode(FET_UH_PORT, OUTPUT);
	pinMode(FET_UL_PORT, OUTPUT);
	pinMode(FET_VH_PORT, OUTPUT);
	pinMode(FET_VL_PORT, OUTPUT);
	pinMode(FET_WH_PORT, OUTPUT);
	pinMode(FET_WL_PORT, OUTPUT);
		
	/* �z�[���Z���T�̊��荞�ݐݒ� */
	attachInterrupt(U_HALL_SENSOR_INTERRPT, pollDetect, CHANGE);
	attachInterrupt(V_HALL_SENSOR_INTERRPT, pollDetect, CHANGE);
	attachInterrupt(W_HALL_SENSOR_INTERRPT, pollDetect, CHANGE);

	/* �^�C�}���荞�ݐݒ� */
	MsTimer2::set(10, expireTimer);
	MsTimer2::start();
}


void loop() {
  // put your main code here, to run repeatedly:

#if 0	
	uHallSensorLED.on();
	vHallSensorLED.on();
	wHallSensorLED.on();
	
	delay(500);
	
	uHallSensorLED.off();
	vHallSensorLED.off();
	wHallSensorLED.off();

	delay(500);
#endif
}


void pollDetect()
{
	byte hallSensorPosition;	// ���݂̃z�[���Z���T�\�ʒu
	
	hallSensorPosition = digitalRead(HALL_W_PORT) << 2 | 
						digitalRead(HALL_V_PORT) << 1 | 
						digitalRead(HALL_U_PORT);
	
	switch(hallSensorPosition) {
		/* �z�[���Z���T�ʒu:W=1, V=0, U=1 */
		case HALL_SENSOR_POSITION_5: /* FET�ʓd�X�e�[�W1:UH=PWM, VH=0, WH=0, UL=0, VL=1, WL=0 */
			break;

		/* �z�[���Z���T�ʒu:W=0, V=0, U=1 */
		case HALL_SENSOR_POSITION_1: /* FET�ʓd�X�e�[�W2:UH=PWM, VH=0, WH=0, UL=0, VL=0, WL=1 */
			break;

		/* �z�[���Z���T�ʒu:W=0, V=1, U=1 */
		case HALL_SENSOR_POSITION_3: /* FET�ʓd�X�e�[�W3:UH=0, VH=PWM, WH=0, UL=0, VL=0, WL=1 */
			break;

		/* �z�[���Z���T�ʒu:W=0, V=1, U=0 */
		case HALL_SENSOR_POSITION_2: /* FET�ʓd�X�e�[�W4:UH=0, VH=PWM, WH=0, UL=1, VL=0, WL=0 */
			break;
			
		/* �z�[���Z���T�ʒu:W=1, V=1, U=0 */
		case HALL_SENSOR_POSITION_6: /* FET�ʓd�X�e�[�W5:UH=0, VH=0, WH=PWM, UL=1, VL=0, WL=0 */
			break;

		/* �z�[���Z���T�ʒu:W=1, V=0, U=0 */
		case HALL_SENSOR_POSITION_4: /* FET�ʓd�X�e�[�W6:UH=0, VH=0, WH=PWM, UL=0, VL=1, WL=0 */
			break;

		default:
			break;		
	}
	
	// �z�[���Z���TLED�̓_���E����
	digitalWrite(U_HALL_SENSOR_LED, digitalRead(HALL_U_PORT));
	digitalWrite(V_HALL_SENSOR_LED, digitalRead(HALL_V_PORT));
	digitalWrite(W_HALL_SENSOR_LED, digitalRead(HALL_W_PORT));
	
}


void expireTimer() {
	static int counter1sec = 0;
	static boolean pilotLedStatus = LOW;

	++counter1sec;
	if (counter1sec >= COUNTER_1SEC) {
		counter1sec = 0;
		digitalWrite(PILOT_LED, pilotLedStatus);
		pilotLedStatus = !pilotLedStatus;
	}
	
	
}
