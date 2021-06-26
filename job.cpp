//#include <stdio.h>
//#include "job.hpp"
//
//
///// <summary>
///// ���݂̃W���u���x�~
///// </summary>
//void job::suspend() {
//	error_code = JOB_STATE_BUSY;		//���s��
//}
//
//void job::cancel() {
//	error_code = JOB_STATE_CANCEL;		//�L�����Z��
//}
//
//void job::error(int errno) {
//	error_code = errno;
//}
//
///// <summary>
///// ���񏈗��ǉ�
///// </summary>
///// <param name="self"></param>
//void job::action(job* self) {
//	for (job* last = this; ; last = last->action_next) {
//		if (NULL == last->action_next) {
//			last->action_next = self;
//			return;
//		}
//	}
//}
//
///// <summary>
///// ���񏈗��ǉ�
///// </summary>
///// <param name="jobs"></param>
//void job::action(job** jobs) {
//	while (NULL != *jobs)
//		action(*(jobs++));
//}
//
///// <summary>
///// �z���X�g�̍Ō�擾
///// </summary>
///// <param name="self"></param>
///// <returns></returns>
//job* job::fork_last(job* self) {
//	for (job* last = self; ; last = last->fork_next)
//		if (self == last->fork_next)
//			return last;
//}
//
///// <summary>
///// ���񏈗��ǉ�(�Q�̏z���X�g���q�����킹��)
///// </summary>
///// <param name="self"></param>
//void job::fork(job* self) {
//	fork_last(this)->fork_next = self;
//	fork_last(self)->fork_next = this;
//}
//
///// <summary>
///// ���񏈗��ǉ�
///// </summary>
///// <param name="jobs"></param>
//void job::fork(job** jobs) {
//	while (NULL != *jobs)
//		fork(*(jobs++));
//}
//
///// <summary>
///// �����҂�
///// </summary>
//void job::wait() {
//	wait(this);
//}
//
///// <summary>
///// �����҂�
///// </summary>
///// <param name="cur"></param>
//void job::wait(job* cur) {
//	while (2 > this->error_code)
//		cur = cur->dispatch();
//}
//
///// <summary>
///// ���s
///// </summary>
///// <param name="self"></param>
//job* job::dispatch() {
//	//�������s
//	if (error_code < JOB_STATE_FINISH) {
//		error_code = JOB_STATE_FINISH;
//		func();
//
//		//���������璼��V�[�P���X�����V�[�P���X�ɓo�^
//		if (JOB_STATE_FINISH == error_code)
//			if (NULL != action_next)
//				fork(action_next);
//	}
//
//
//	//���Ɏ��s�������V�[�P���X��Ԃ�
//	for (; JOB_STATE_FINISH <= fork_next->error_code; fork_next = fork_next->fork_next)
//		if (this == fork_next)
//			return NULL;
//
//	return fork_next;
//}
