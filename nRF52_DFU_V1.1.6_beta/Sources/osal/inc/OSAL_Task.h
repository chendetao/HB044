
#ifndef __OSAL_TASK_H__
#define __OSAL_TASK_H__

typedef unsigned long (*pTaskEventHandlerFn)(unsigned char task_id,\
            unsigned long event);

extern const pTaskEventHandlerFn tasksArr[];
extern unsigned long taskEventsTable[];
extern const unsigned char tasksCnt;

extern void osal_init_tasks( void );
extern unsigned long osal_event_count( void );

#endif

