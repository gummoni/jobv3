#pragma once
#include <stdio.h>

#define JOB_STATE_START		(0)
#define JOB_STATE_BUSY		(1)
#define JOB_STATE_FINISH	(2)
#define JOB_STATE_CANCEL	(3)

typedef void (*execute)(void*);

typedef struct job {
	struct job* action_next;
	struct job* fork_next;
	execute execute;
	int errno;
} job;


#define suspend(self) { ((job*)self)->errno = JOB_STATE_BUSY; }

extern job* fork_last(job* self);
extern void fork(job* self, job* item);
extern void forks(job* self, job** items);
extern job* action_last(job* self);
extern void action(job* self, job* item);
extern void actions(job* self, job** items);
extern job* dispatch(job* self);
extern void wait(job* self, job* cur);
