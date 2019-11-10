#ifndef __EVKARTPIN_H__
#define __EVKARTPIN_H__

/***** FET駆動 *****/
#define FET_UH_PORT (5) /* U相 FET High */
#define FET_UL_PORT (6) /* U相 FET Low */
#define FET_VH_PORT (2) /* V相 FET High */
#define FET_VL_PORT (7) /* V相 FET Low */
#define FET_WH_PORT (3) /* W相 FET High */
#define FET_WL_PORT (8) /* W相 FET Low */


/***** ホールセンサー *****/
#define HALL_U_PORT (19) /* U相 */
#define HALL_V_PORT (20) /* V相 */
#define HALL_W_PORT (21) /* W相 */

#define U_HALL_SENSOR_INTERRPT (2) /* U相 INT2 ピン番号19 */
#define V_HALL_SENSOR_INTERRPT (1) /* V相 INT1 ピン番号20 */
#define W_HALL_SENSOR_INTERRPT (0) /* W相 INT0 ピン番号21 */

/***** ホールセンサーLED *****/
#define U_HALL_SENSOR_LED (23) /* U相 ホールセンサーLED */
#define V_HALL_SENSOR_LED (25) /* V相 ホールセンサーLED */
#define W_HALL_SENSOR_LED (27) /* W相 ホールセンサーLED */


/***** スロットル *****/
#define THROTTLE_PORT (0)	/* スロットル電圧 A0 */


/***** タイマー *****/
#define COUNTER_1SEC	(100) /* 1000msec/10msec */


/***** パイロットLED *****/
#define PILOT_LED (13) /* Arduino MEGAに実装されているLED */


#endif
