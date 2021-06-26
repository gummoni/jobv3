#pragma once
#include <stdio.h>

#define JOB_STATE_START		(0)
#define JOB_STATE_BUSY		(1)
#define JOB_STATE_FINISH	(2)
#define JOB_STATE_CANCEL	(3)

///// <summary>
///// ジョブ（処理単位）
///// </summary>
//struct job {
//protected:
//	virtual void func() = 0;
//	job* action_next = NULL;				//単方向リスト
//	job* fork_next = this;					//循環リスト
//	int error_code = 0;						//エラーコード		0=開始, 1=実行中, 2=完了, 3=キャンセル, 4=中断
//
//	/// <summary>
//	/// 現在のジョブを休止
//	/// </summary>
//	void suspend();
//
//public:
//
//	/// <summary>
//	/// キャンセル
//	/// </summary>
//	void cancel();
//
//	/// <summary>
//	/// エラー
//	/// </summary>
//	void error(int errno);
//
//	/// <summary>
//	/// 直列処理追加
//	/// </summary>
//	/// <param name="self"></param>
//	void action(job* self);
//
//	/// <summary>
//	/// 直列処理追加
//	/// </summary>
//	/// <param name="jobs"></param>
//	void action(job** jobs);
//
//	/// <summary>
//	/// 循環リストの最後取得
//	/// </summary>
//	/// <param name="self"></param>
//	/// <returns></returns>
//	static job* fork_last(job* self);
//
//	/// <summary>
//	/// 並列処理追加(２つの循環リストを繋げ合わせる)
//	/// </summary>
//	/// <param name="self"></param>
//	void fork(job* self);
//
//	/// <summary>
//	/// 並列処理追加
//	/// </summary>
//	/// <param name="jobs"></param>
//	void fork(job** jobs);
//
//	/// <summary>
//	/// 完了待ち
//	/// </summary>
//	void wait();
//
//	/// <summary>
//	/// 完了待ち
//	/// </summary>
//	/// <param name="cur"></param>
//	void wait(job* cur);
//
//	/// <summary>
//	/// 実行
//	/// </summary>
//	/// <param name="self"></param>
//	job* dispatch();
//};
