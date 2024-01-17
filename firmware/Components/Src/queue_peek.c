/*
 * tx_queue_peek.c
 *
 *  Created on: Jan 17, 2024
 *      Author: HP
 */

#include "tx_api.h"
#include "tx_trace.h"
#include "tx_thread.h"
#include "tx_queue.h"

UINT  _queue_peek(TX_QUEUE *queue_ptr, VOID *destination_ptr, ULONG wait_option)
{

TX_INTERRUPT_SAVE_AREA

TX_THREAD       *thread_ptr;
ULONG           *source;
ULONG           *destination;
UINT            size;
UINT            suspended_count;
TX_THREAD       *next_thread;
TX_THREAD       *previous_thread;
UINT            status;


    /* Default the status to TX_SUCCESS.  */
    status =  TX_SUCCESS;

    /* Disable interrupts to receive message from queue.  */
    TX_DISABLE

#ifdef TX_QUEUE_ENABLE_PERFORMANCE_INFO

    /* Increment the total messages received counter.  */
    _tx_queue_performance__messages_received_count++;

    /* Increment the number of messages received from this queue.  */
    queue_ptr -> tx_queue_performance_messages_received_count++;

#endif

    /* If trace is enabled, insert this event into the trace buffer.  */
    TX_TRACE_IN_LINE_INSERT(TX_TRACE_QUEUE_RECEIVE, queue_ptr, TX_POINTER_TO_ULONG_CONVERT(destination_ptr), wait_option, queue_ptr -> tx_queue_enqueued, TX_TRACE_QUEUE_EVENTS)

    /* Log this kernel call.  */
    TX_EL_QUEUE_RECEIVE_INSERT

    /* Pickup the thread suspension count.  */
    suspended_count =  queue_ptr -> tx_queue_suspended_count;

    /* Determine if there is anything in the queue.  */
    if (queue_ptr -> tx_queue_enqueued != TX_NO_MESSAGES)
    {
		/* There is a message waiting in the queue and there are no suspensi.  */

		/* Setup source and destination pointers.  */
		source =       queue_ptr -> tx_queue_read;
		destination =  TX_VOID_TO_ULONG_POINTER_CONVERT(destination_ptr);
		size =         queue_ptr -> tx_queue_message_size;

		/* Copy message. Note that the source and destination pointers are
		   incremented by the macro.  */
		TX_QUEUE_MESSAGE_COPY(source, destination, size)

		/* Restore interrupts.  */
		TX_RESTORE
    }
    else
    {
        /* Restore interrupts.  */
        TX_RESTORE

        /* Immediate return, return error completion.  */
        status =  TX_QUEUE_EMPTY;
    }

    /* Return completion status.  */
    return(status);
}
