/*
 * tx_queue_peek.h
 *
 *  Created on: Jan 17, 2024
 *      Author: HP
 */

#ifndef INC_QUEUE_PEEK_H_
#define INC_QUEUE_PEEK_H_

#include "tx_api.h"

#ifdef __cplusplus
extern   "C" {
#endif

#ifdef TX_DISABLE_ERROR_CHECKING

#define 	queue_peek 		_queue_peek

UINT        _queue_peek(TX_QUEUE *queue_ptr, VOID *destination_ptr, ULONG wait_option);

#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_QUEUE_PEEK_H_ */
