dscan 
---

デスクトップ上のファイルおよびフォルダの座標を取得します。

##定数
- WORK_DIR : デスクトップの絶対パス (例: "/User/me/Desktop")
- EXTS     : 抽出するファイル拡張子 (例: "\*.aiff", "\*.wav")

##使用方法
**用途に応じて定数は変更すること**

```bash
./dscan.py    # OSXシステム標準のpythonに依存します
```

###過去のバージョン
---

####v1.0
https://github.com/tgck/desktopScanner

- 同じ目的だが、常駐して変更監視する & 出力をOSC通信する点が大きな違い
- Cocoa製なので無駄なウィンドウが表示される

####v1.1
https://gist.github.com/tgck/f89384515261afd7a140

- DesktopScanner.m
- OSC通信省いて標準出力するようにしたもの

####v1.2
https://github.com/daisan-nanngu-gakudan/mft2014/tree/8cc91639dcc395ab0adf4c9379804b3fdd8332fd/90_Batch

- 当リポジトリの改訂前バージョン
- 常駐しない、一回きりのスキャンをおこなう