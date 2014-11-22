2d view app
========

上位からOSC形式でメッセージを受け取り、
Finderのポインタを制御します。

制御可能な値は以下のとおり。
- 速度
- 座標

本アプリが受け取るメッセージの形式
- 速度:  /dsng2/speed float float
- 座標:  /dsng2/position int int

テスト用のコマンド
$ oscsend localhost 12022 /dsng2/speed ff 3.12 3.14
$ oscsend localhost 12022 /dsng2/position ff 324 661

TODO:
- Finder 項目との接触判定
- Finder 項目のイベント発火
