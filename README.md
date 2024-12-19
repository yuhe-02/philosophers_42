# 概要
philosopher の課題を解く
いわゆる食事する哲学者問題

## 設計等(自分用)

[notion](https://www.notion.so/philosophers-157fd64b77948096b49ddb46567c9269?pvs=4)

## 関数リスト(external fucntions)

| 関数名               | 説明                                             | リンク                                                                 |
|-----------------------|--------------------------------------------------|----------------------------------------------------------------------|
| `memset`             | 指定したバイト分値を埋める                       | [devdocs.io](https://devdocs.io/c/string/byte/memset)               |
| `printf`             | コンソール上に出力するやつ、文字数が返却値        | [devdocs.io](https://devdocs.io/c/io/fprintf)                       |
| `malloc`             | head領域に指定したバイト分メモリを確保するやつ。 | [devdocs.io](https://devdocs.io/c/memory/malloc)                    |
| `free`               | head領域に確保したメモリを解放するやつ           | [devdocs.io](https://devdocs.io/c/memory/free)                      |
| `write`              | 指定したfdに、指定したバイト分書き込み行うやつ   | [cgengo.sakura.ne.jp](https://cgengo.sakura.ne.jp/write.html)       |
| `usleep`             | 指定した時間分実行待つやつ                       | [man7.org](https://man7.org/linux/man-pages/man3/usleep.3.html)     |
| `gettimeofday`       | 時刻取得するやつ                                 | [manpages.org](https://ja.manpages.org/gettimeofday/2)              |
| `pthread_create`     | 呼び出したプロセス内でスレッド作成するやつ        | [manpages.org](https://ja.manpages.org/pthread_create/3)            |
| `pthread_detach`     | スレッドを切り離すやつ                           | [manpages.org](https://ja.manpages.org/pthread_detach/3)            |
| `pthread_join`       | スレッドの終了を待つやつ                         | [manpages.org](https://ja.manpages.org/pthread_join/3)              |
| `pthread_mutex_init` | 新しいmutexを作成する        | [manpages.org](https://nxmnpg.lemoda.net/ja/3/pthread_mutex_init#google_vignette)              |
| `pthread_mutex_destory` | mutexに割り当てられたリソースを解放する| [manpages.org](https://nxmnpg.lemoda.net/ja/3/pthread_mutex_destroy#google_vignette) |
| `pthread_mutex_lock` | mutexをロックする                        | [manpages.org](https://nxmnpg.lemoda.net/ja/3/pthread_mutex_lock#google_vignette)  |
| `pthread_mutex_unlock` | mutexのロックを解除する           | [manpages.org](https://nxmnpg.lemoda.net/ja/3/pthread_mutex_unlock)            |

## タスク進捗状況 ✅

- [x] 課題の理解 (完了)
- [x] スレッドの基本知識・使い方 (完了)
- [x] ロジックの実装 (完了)
-	- 	各スレッドを動かす
-	-	食事までの流れの実装
-	-	usleepを正しく使うように各スレッドのsleep
-	-	ownerにdeath checkさせるようにする
-	-	exit処理
- [x] デッドロック等の回避 (完了)
- [in progress] バリデーション実装 (着手中: 60%)
- [in progress] norm  (着手中: 60%)
- [ ] レビュー  (未着手: 0%)

*目標：2024-12-21に完了(平日2h以上時間を取る)

