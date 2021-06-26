#pragma once
#include <stdio.h>

#define JOB_STATE_START		(0)
#define JOB_STATE_BUSY		(1)
#define JOB_STATE_FINISH	(2)
#define JOB_STATE_CANCEL	(3)

///// <summary>
///// �W���u�i�����P�ʁj
///// </summary>
//struct job {
//protected:
//	virtual void func() = 0;
//	job* action_next = NULL;				//�P�������X�g
//	job* fork_next = this;					//�z���X�g
//	int error_code = 0;						//�G���[�R�[�h		0=�J�n, 1=���s��, 2=����, 3=�L�����Z��, 4=���f
//
//	/// <summary>
//	/// ���݂̃W���u���x�~
//	/// </summary>
//	void suspend();
//
//public:
//
//	/// <summary>
//	/// �L�����Z��
//	/// </summary>
//	void cancel();
//
//	/// <summary>
//	/// �G���[
//	/// </summary>
//	void error(int errno);
//
//	/// <summary>
//	/// ���񏈗��ǉ�
//	/// </summary>
//	/// <param name="self"></param>
//	void action(job* self);
//
//	/// <summary>
//	/// ���񏈗��ǉ�
//	/// </summary>
//	/// <param name="jobs"></param>
//	void action(job** jobs);
//
//	/// <summary>
//	/// �z���X�g�̍Ō�擾
//	/// </summary>
//	/// <param name="self"></param>
//	/// <returns></returns>
//	static job* fork_last(job* self);
//
//	/// <summary>
//	/// ���񏈗��ǉ�(�Q�̏z���X�g���q�����킹��)
//	/// </summary>
//	/// <param name="self"></param>
//	void fork(job* self);
//
//	/// <summary>
//	/// ���񏈗��ǉ�
//	/// </summary>
//	/// <param name="jobs"></param>
//	void fork(job** jobs);
//
//	/// <summary>
//	/// �����҂�
//	/// </summary>
//	void wait();
//
//	/// <summary>
//	/// �����҂�
//	/// </summary>
//	/// <param name="cur"></param>
//	void wait(job* cur);
//
//	/// <summary>
//	/// ���s
//	/// </summary>
//	/// <param name="self"></param>
//	job* dispatch();
//};
