/*
 * app_freertos.h
 *
 *  Created on: Jul 5, 2023
 *      Author: piotr
 */

#ifndef INC_APP_FREERTOS_H_
#define INC_APP_FREERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

void MX_FREERTOS_Init(void);

void mainTaskEntry(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* INC_APP_FREERTOS_H_ */
