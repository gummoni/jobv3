#include <stdio.h>


class job {

private:
	job* action_next = NULL;				//�P�������X�g
	job* fork_next = this;					//�z���X�g
	bool is_finished = false;				//�������

	virtual void func() = 0;

protected:

	/// <summary>
	/// ���݂̃W���u���x�~
	/// </summary>
	void suspend() {
		is_finished = false;
	}

public:

	/// <summary>
	/// ���񏈗��ǉ�
	/// </summary>
	/// <param name="self"></param>
	void action(job* self) {
		for (job* last = this; ; last = last->action_next) {
			if (NULL == last->action_next) {
				last->action_next = self;
				self->action_next = this;
				return;
			}
		}
	}

	/// <summary>
	/// ���񏈗��ǉ�
	/// </summary>
	/// <param name="jobs"></param>
	void action(job** jobs) {
		while (NULL != *jobs)
			action(*(jobs++));
	}

	/// <summary>
	/// ���񏈗��ǉ�
	/// </summary>
	/// <param name="self"></param>
	void fork(job* self) {
		for (job* last = this; ; last = last->fork_next) {
			if (this == last->fork_next) {
				last->fork_next = self;
				self->fork_next = this;
				return;
			}
		}
	}

	/// <summary>
	/// ���񏈗��ǉ�
	/// </summary>
	/// <param name="jobs"></param>
	void fork(job** jobs) {
		while (NULL != *jobs)
			fork(*(jobs++));
	}

	/// <summary>
	/// �����҂�
	/// </summary>
	void wait() {
		wait(this);
	}

	/// <summary>
	/// �����҂�
	/// </summary>
	/// <param name="cur"></param>
	void wait(job* cur) {
		while (!this->is_finished)
			cur = cur->dispatch();
	}

	/// <summary>
	/// ���s
	/// </summary>
	/// <param name="self"></param>
	job* dispatch() {
		//�������s
		is_finished = true;
		func();

		//���������璼��V�[�P���X���s
		if (is_finished)
			if (NULL != action_next)
				fork(action_next);

		//���̕���V�[�P���X���s
		for (; fork_next->is_finished; fork_next = fork_next->fork_next)
			if (this == fork_next)
				return NULL;

		return fork_next;
	}
};


class job1 : public job {
	int count = 0;
	const char* header;
public:

	job1(int count, const char* header) {
		this->count = count;
		this->header = header;
	}

	virtual void func() override
	{
		if (0 == count)
		{
			count++;
			printf("--start%s--\n", header);
			suspend();
		}
		else if (count < 10) {
			printf("busy%s:%d\n", header, count++);
			suspend();
		}
		else {
			printf("--end%s--\n", header);
		}
	}
};

int main(void) {

	auto j = new job1(-10, "A");
	auto l = new job1(0, "C");
	job* k = new job1(0, "B");
	j->fork(k);
	j->action(l);

	//k->wait(c);

	//while (NULL != c)
	//	c = c->dispatch();

	//j->wait();
	l->wait(j);

	return 1;
}
