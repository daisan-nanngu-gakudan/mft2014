dscan
=====

デスクトップに配置されたファイルのFinder座標を取得します。
ひとまず ".aiff" 拡張子縛り。

常駐せず、一覧取得して終了します。


過去のバージョン:

https://github.com/tgck/desktopScanner
-同じ目的だが、常駐して変更監視する & 出力をOSC通信する点が大きな違い
-Cocoa製なので無駄なウィンドウが表示される

https://gist.github.com/tgck/f89384515261afd7a140
-DesktopScanner.m
-OSC通信省いて標準出力するようにしたもの
