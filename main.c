#include <stdio.h>
#include "job.h"


typedef struct {
	job token;
	int count;
	const char* header;
} count_job;

void countup(count_job* self) {
	if (0 == self->count) {
		printf("--start:%s--\n", self->header);
		self->count++;
		suspend(self);
	}
	else if (self->count < 10) {
		printf("--busy:%s%d--\n", self->header, self->count++);
		suspend(self);
	}
	else
	{
		printf("--end:%s--\n", self->header);
	}

}

void token_init(job* self, execute func) {
	self->execute = func;
	self->action_next = NULL;
	self->fork_next = self;
	self->errno = JOB_STATE_START;
}

void countup_init(count_job* self, const char* header, int count) {
	self->header = header;
	self->count = count;
	token_init(&self->token, (execute)countup);
}

/// <summary>
/// ƒƒCƒ“ˆ—
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(void) {

	count_job t1;
	count_job t2;
	count_job t3;
	count_job t4;
	countup_init(&t1, "A", -5);
	countup_init(&t2, "B", 0);
	countup_init(&t3, "C", 0);
	countup_init(&t4, "D", 0);
	fork(&t2.token, &t3.token);
	fork(&t1.token, &t2.token);
	action(&t1.token, &t4.token);
	
	for (job* exe = &t1.token; NULL != exe; exe = dispatch(exe));
		
	return 1;
}
