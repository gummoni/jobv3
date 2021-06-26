#include <stdio.h>
#include "job.hpp"

typedef void (*execute)(void*);

typedef struct token {
	struct token* action_next;
	struct token* fork_next;
	execute execute;
	int errno;
} token;


#define suspend(self) { ((token*)self)->errno = JOB_STATE_BUSY; }

token* fork_last(token* self) {
	token* last = self;
	while (self != last->fork_next)
		last = last->fork_next;
	return last;
}

void fork(token* self, token* item) {
	fork_last(self)->fork_next = item;
	fork_last(item)->fork_next = self;
}

void action(token* self, token* item) {
	while (NULL != self->action_next)
		self = self->action_next;
	self->action_next = item;
}

token* dispatch(token* self) {
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

void wait(token* self, token* cur) {
	while (JOB_STATE_FINISH <= self->errno)
		cur = dispatch(cur);
}

typedef struct count_token {
	token token;
	int count;
	const char* header;
};

void countup(count_token* self) {
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

//10までカウントアップして終えるジョブ
//struct job1 : job {
//private:
//	int count = 0;
//	const char* header;
//public:
//
//	job1(int count, const char* header) {
//		this->count = count;
//		this->header = header;
//	}
//
//	virtual void func() override {
//		if (0 == count)
//		{
//			count++;
//			printf("--start%s--\n", header);
//			suspend();
//		}
//		else if (count < 10) {
//			printf("busy%s:%d\n", header, count++);
//			suspend();
//		}
//		else {
//			printf("--end%s--\n", header);
//		}
//	}
//};

void token_init(token* self, execute func) {
	self->execute = func;
	self->action_next = NULL;
	self->fork_next = self;
	self->errno = JOB_STATE_START;
}

void countup_init(count_token* self, const char* header, int count) {
	self->header = header;
	self->count = count;
	token_init(&self->token, (execute)countup);
}

/// <summary>
/// メイン処理
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(void) {

	count_token t1;
	count_token t2;
	count_token t3;
	count_token t4;
	countup_init(&t1, "A", -5);
	countup_init(&t2, "B", 0);
	countup_init(&t3, "C", 0);
	countup_init(&t4, "D", 0);
	fork((token*)&t2, (token*)&t3);
	fork((token*)&t1, (token*)&t2);
	//action((token*)&t2, (token*)&t3);
	//fork((token*)&t3, (token*)&t4);

	token* exe = &t1.token;
	while (NULL != exe)
		exe = dispatch(exe);

	//auto j = new job1(-10, "A");
	//auto l = new job1(0, "C");
	//job* k = new job1(0, "B");
	//auto m = new job1(0, "M");
	//k->fork(m);
	//j->fork(k);
	//j->action(l);

	////全て完了するまで待つ場合
	//job* x = j;
	//while (NULL != x)
	//	x = x->dispatch();

	////特定のジョブ完了するまで待つ場合
	////j->wait();
	//l->wait(j);

	return 1;
}
