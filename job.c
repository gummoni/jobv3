#include <stdio.h>
#include "job.h"


job* fork_last(job* self) {
	job* last = self;
	while (self != last->fork_next)
		last = last->fork_next;
	return last;
}

void fork(job* self, job* item) {
	fork_last(self)->fork_next = item;
	fork_last(item)->fork_next = self;
}

void forks(job* self, job** items) {
	job* last = self;
	while (NULL != *items)
		fork_last(last)->fork_next = last = *(items++);
	fork_last(last)->fork_next = self;
}

job* action_last(job* self) {
	job* last = self;
	while (self != last->action_next)
		last = last->action_next;
	return last;
}

void action(job* self, job* item) {
	while (NULL != self->action_next)
		self = self->action_next;
	self->action_next = item;
}

void actions(job* self, job** items) {
	job* last = self;
	while (NULL != *items)
		action_last(last)->action_next = last = *(items++);
}

job* dispatch(job* self) {
	if (self->errno < JOB_STATE_FINISH) {
		self->errno = JOB_STATE_FINISH;
		self->execute(self);
		if (self->errno == JOB_STATE_FINISH)
			if (NULL != self->action_next)
				fork(self, self->action_next);
	}

	for (; JOB_STATE_FINISH <= self->fork_next->errno; self->fork_next = self->fork_next->fork_next)
		if (self == self->fork_next)
			return NULL;

	return self->fork_next;
}

void wait(job* self, job* cur) {
	while (JOB_STATE_FINISH <= self->errno)
		cur = dispatch(cur);
}
