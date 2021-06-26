#include <stdio.h>
#include "job.h"


inline job* dispatch(job* self) {
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
