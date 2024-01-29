/**
  ******************************************************************************
  * @file           : app_freertos.h
  * @brief          : tasks common definitions
  ******************************************************************************
  */

#ifndef INC_APP_FREERTOS_H_
#define INC_APP_FREERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief KERNEL FUNCTION DO NOT USE
 * @attention DO NOT USE
 */
void MX_FREERTOS_Init(void);

/*
 * @brief main control loop, handles mission selction
 * and other
 * @param not used
 */
void mainTaskEntry(void *argument);

//void dspTaskEntry(void *argument);

/*
 * @brief dspTimer Callback, main loop for time sensitive
 * calculations
 * @param not used
 */
void dspTimerCallback(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* INC_APP_FREERTOS_H_ */
