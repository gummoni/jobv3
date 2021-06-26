#pragma once

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

#define fork_last(self, item) {										\
	for (job* __chk = self; ; __chk = __chk->fork_next) {			\
		if (self == __chk->fork_next) {								\
			__chk->fork_next = item;								\
			break;													\
		}															\
	}																\
}

#define fork(self, item) {	fork_last(self, item);	fork_last(item, self);	}

#define action(self, item) {										\
	for (job* __chk = self; ; __chk = __chk->action_next) {			\
		if (NULL == __chk->action_next) {							\
			__chk->action_next = item;								\
			break;													\
		}															\
	}																\
}

#define wait(self, cur) {											\
	for (; JOB_STATE_FINISH <= self->errno; cur = dispatch(cur));	\
}

extern job* dispatch(job* self);
