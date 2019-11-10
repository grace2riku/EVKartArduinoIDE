#include "stdafx.h"
#include "EvKartPin.h"
#include "LedController.h"
#include <MsTimer2.h>

const unsigned short VOL_0PCT_POINT = 51;               /* スロットル電圧 1.0V 205/4 */
const unsigned short VOL_100PCT_POINT = 204;            /* スロットル電圧 4.0V 819/4 */
const unsigned short VOL_RANGE = 153;                   /* Duty(0% - 100%)設定範囲 */

static byte pwmDuty = 0;
static boolean f_MotorDrive = false;

void setFETDrivePattern();
void setFETStopPattern();
void expireTimer();

/* ホールセンサー位置(ホールセンサーの入力ポートから読み込んだ値) */
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

	/* ホールセンサーは入力ポートに設定 */
	pinMode(HALL_U_PORT, INPUT);
	pinMode(HALL_V_PORT, INPUT);
	pinMode(HALL_W_PORT, INPUT);

	/* FETは出力ポートに設定 */
	pinMode(FET_UH_PORT, OUTPUT);
	pinMode(FET_UL_PORT, OUTPUT);
	pinMode(FET_VH_PORT, OUTPUT);
	pinMode(FET_VL_PORT, OUTPUT);
	pinMode(FET_WH_PORT, OUTPUT);
	pinMode(FET_WL_PORT, OUTPUT);
		
  /* パイロットLED */
  pinMode(PILOT_LED, OUTPUT);
	
	/* ホールセンサーの外部割り込み設定。両エッジ割り込み */
	attachInterrupt(U_HALL_SENSOR_INTERRPT, setFETDrivePattern, CHANGE);
	attachInterrupt(V_HALL_SENSOR_INTERRPT, setFETDrivePattern, CHANGE);
	attachInterrupt(W_HALL_SENSOR_INTERRPT, setFETDrivePattern, CHANGE);

	/* タイマー設定 */
	MsTimer2::set(10, expireTimer);
	MsTimer2::start();
}


void loop() {
  // put your main code here, to run repeatedly:

}


void setFETDrivePattern()
{
	byte hallSensorPosition;	// ホールセンサー位置
	
	hallSensorPosition = digitalRead(HALL_W_PORT) << 2 | 
						digitalRead(HALL_V_PORT) << 1 | 
						digitalRead(HALL_U_PORT);
	
	switch(hallSensorPosition) {
		/* ホールセンサ入力位置:W=1, V=0, U=1 */
		case HALL_SENSOR_POSITION_5: /* FET通電ステージ1:UH=PWM, VH=0, WH=0, UL=0, VL=1, WL=0 */
      analogWrite(FET_UH_PORT, pwmDuty);
      analogWrite(FET_VH_PORT, 0);
      analogWrite(FET_WH_PORT, 0);
      digitalWrite(FET_UL_PORT, LOW);
      digitalWrite(FET_VL_PORT, HIGH);
      digitalWrite(FET_WL_PORT, LOW);      
			break;

		/* ホールセンサ入力位置:W=0, V=0, U=1 */
		case HALL_SENSOR_POSITION_1: /* FET通電ステージ2:UH=PWM, VH=0, WH=0, UL=0, VL=0, WL=1 */
      analogWrite(FET_UH_PORT, pwmDuty);
      analogWrite(FET_VH_PORT, 0);
      analogWrite(FET_WH_PORT, 0);
      digitalWrite(FET_UL_PORT, LOW);
      digitalWrite(FET_VL_PORT, LOW);
      digitalWrite(FET_WL_PORT, HIGH);      
			break;

		/* ホールセンサ入力位置:W=0, V=1, U=1 */
		case HALL_SENSOR_POSITION_3: /* FET通電ステージ3:UH=0, VH=PWM, WH=0, UL=0, VL=0, WL=1 */
      analogWrite(FET_UH_PORT, 0);
      analogWrite(FET_VH_PORT, pwmDuty);
      analogWrite(FET_WH_PORT, 0);
      digitalWrite(FET_UL_PORT, LOW);
      digitalWrite(FET_VL_PORT, LOW);
      digitalWrite(FET_WL_PORT, HIGH);      
			break;

		/* ホールセンサ入力位置:W=0, V=1, U=0 */
		case HALL_SENSOR_POSITION_2: /* FET通電ステージ4:UH=0, VH=PWM, WH=0, UL=1, VL=0, WL=0 */
      analogWrite(FET_UH_PORT, 0);
      analogWrite(FET_VH_PORT, pwmDuty);
      analogWrite(FET_WH_PORT, 0);
      digitalWrite(FET_UL_PORT, HIGH);
      digitalWrite(FET_VL_PORT, LOW);
      digitalWrite(FET_WL_PORT, LOW);      
			break;
			
		/* ホールセンサ入力位置:W=1, V=1, U=0 */
		case HALL_SENSOR_POSITION_6: /* FET通電ステージ5:UH=0, VH=0, WH=PWM, UL=1, VL=0, WL=0 */
      analogWrite(FET_UH_PORT, 0);
      analogWrite(FET_VH_PORT, 0);
      analogWrite(FET_WH_PORT, pwmDuty);
      digitalWrite(FET_UL_PORT, HIGH);
      digitalWrite(FET_VL_PORT, LOW);
      digitalWrite(FET_WL_PORT, LOW);      
			break;

		/* ホールセンサ入力位置:W=1, V=0, U=0 */
		case HALL_SENSOR_POSITION_4: /* FET通電ステージ6:UH=0, VH=0, WH=PWM, UL=0, VL=1, WL=0 */
      analogWrite(FET_UH_PORT, 0);
      analogWrite(FET_VH_PORT, 0);
      analogWrite(FET_WH_PORT, pwmDuty);
      digitalWrite(FET_UL_PORT, LOW);
      digitalWrite(FET_VL_PORT, HIGH);
      digitalWrite(FET_WL_PORT, LOW);      
			break;

		default:
      analogWrite(FET_UH_PORT, 0);
      analogWrite(FET_VH_PORT, 0);
      analogWrite(FET_WH_PORT, 0);
      digitalWrite(FET_UL_PORT, LOW);
      digitalWrite(FET_VL_PORT, LOW);
      digitalWrite(FET_WL_PORT, LOW);      
			break;
	}
  
	/* ホールセンサーLEDの点灯・消灯 */
	digitalWrite(U_HALL_SENSOR_LED, hallSensorPosition & 0x01);
	digitalWrite(V_HALL_SENSOR_LED, (hallSensorPosition >> 1) & 0x01);
	digitalWrite(W_HALL_SENSOR_LED, (hallSensorPosition >> 2) & 0x01);
	
}


void setFETStopPattern()
{
  analogWrite(FET_UH_PORT, 0);
  analogWrite(FET_VH_PORT, 0);
  analogWrite(FET_WH_PORT, 0);
  digitalWrite(FET_UL_PORT, LOW);
  digitalWrite(FET_VL_PORT, LOW);
  digitalWrite(FET_WL_PORT, LOW);      
}

void expireTimer() {
	static int counter1sec = 0;
	static boolean pilotLedStatus = LOW;

  /* AD値(0〜1023, PWM duty 0〜255) */
  pwmDuty = analogRead(THROTTLE_PORT) / 4;
  
  if (pwmDuty > VOL_0PCT_POINT) {
    if(f_MotorDrive == false){
      f_MotorDrive = true;
      setFETDrivePattern();
    }
  } else {
    f_MotorDrive = false;
    pwmDuty = 0;
    setFETStopPattern();
  }

	++counter1sec;
	if (counter1sec >= COUNTER_1SEC) {
		counter1sec = 0;

    /* パイロットLEDの点滅 */
		digitalWrite(PILOT_LED, pilotLedStatus);
		pilotLedStatus = !pilotLedStatus;    
	}	

}
