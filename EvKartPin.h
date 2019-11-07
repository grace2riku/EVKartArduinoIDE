#ifndef __EVKARTPIN_H__
#define __EVKARTPIN_H__

/***** FET�쓮 *****/
#define FET_UH_PORT (5) /* U�� FET High �s���ԍ� �s��5 */
#define FET_UL_PORT (6) /* U�� FET Low �s���ԍ� �s��6 */
#define FET_VH_PORT (2) /* V�� FET High �s���ԍ� �s��2 */
#define FET_VL_PORT (7) /* V�� FET Low �s���ԍ� �s��7 */
#define FET_WH_PORT (3) /* W�� FET High �s���ԍ� �s��3 */
#define FET_WL_PORT (8) /* W�� FET Low �s���ԍ� �s��8 */


/***** �z�[���Z���T *****/
#define HALL_U_PORT (19) /* U�� �z�[���Z���T�s���ԍ� �s��19 */
#define HALL_V_PORT (20) /* U�� �z�[���Z���T�s���ԍ� �s��20 */
#define HALL_W_PORT (21) /* U�� �z�[���Z���T�s���ԍ� �s��21 */

#define U_HALL_SENSOR_INTERRPT (2) /* U�� �z�[���Z���T���荞�ݔԍ� INT2 �s��19 */
#define V_HALL_SENSOR_INTERRPT (1) /* V�� �z�[���Z���T���荞�ݔԍ� INT1 �s��20 */
#define W_HALL_SENSOR_INTERRPT (0) /* W�� �z�[���Z���T���荞�ݔԍ� INT0 �s��21 */

/***** �z�[���Z���TLED *****/
#define U_HALL_SENSOR_LED (23) /* U�� �z�[���Z���TLED */
#define V_HALL_SENSOR_LED (25) /* V�� �z�[���Z���TLED */
#define W_HALL_SENSOR_LED (27) /* W�� �z�[���Z���TLED */


/***** �X���b�g�� *****/
#define THROTTLE_PORT (0)	/* �X���b�g���s���ԍ� �A�i���OA0 */


/***** �^�C�}�[ *****/
#define COUNTER_1SEC	(100) /* 1000msec/10msec */


/***** �p�C���b�gLED *****/
#define PILOT_LED (13) /* Aruduino MEGA ����LED �p�C���b�gLED�Ŏg�p���� */


#endif
