//#include <stdio.h>
//#include "job.hpp"
//
//
///// <summary>
///// 現在のジョブを休止
///// </summary>
//void job::suspend() {
//	error_code = JOB_STATE_BUSY;		//実行中
//}
//
//void job::cancel() {
//	error_code = JOB_STATE_CANCEL;		//キャンセル
//}
//
//void job::error(int errno) {
//	error_code = errno;
//}
//
///// <summary>
///// 直列処理追加
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
///// 直列処理追加
///// </summary>
///// <param name="jobs"></param>
//void job::action(job** jobs) {
//	while (NULL != *jobs)
//		action(*(jobs++));
//}
//
///// <summary>
///// 循環リストの最後取得
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
///// 並列処理追加(２つの循環リストを繋げ合わせる)
///// </summary>
///// <param name="self"></param>
//void job::fork(job* self) {
//	fork_last(this)->fork_next = self;
//	fork_last(self)->fork_next = this;
//}
//
///// <summary>
///// 並列処理追加
///// </summary>
///// <param name="jobs"></param>
//void job::fork(job** jobs) {
//	while (NULL != *jobs)
//		fork(*(jobs++));
//}
//
///// <summary>
///// 完了待ち
///// </summary>
//void job::wait() {
//	wait(this);
//}
//
///// <summary>
///// 完了待ち
///// </summary>
///// <param name="cur"></param>
//void job::wait(job* cur) {
//	while (2 > this->error_code)
//		cur = cur->dispatch();
//}
//
///// <summary>
///// 実行
///// </summary>
///// <param name="self"></param>
//job* job::dispatch() {
//	//処理実行
//	if (error_code < JOB_STATE_FINISH) {
//		error_code = JOB_STATE_FINISH;
//		func();
//
//		//完了したら直列シーケンスを並列シーケンスに登録
//		if (JOB_STATE_FINISH == error_code)
//			if (NULL != action_next)
//				fork(action_next);
//	}
//
//
//	//次に実行する並列シーケンスを返す
//	for (; JOB_STATE_FINISH <= fork_next->error_code; fork_next = fork_next->fork_next)
//		if (this == fork_next)
//			return NULL;
//
//	return fork_next;
//}
