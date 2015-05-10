## 自転車で行くデスクトップの旅2 

普通の自転車をつかってPCのデスクトップ内を動きまわる
エンターテイメントなデモ

初出: 2014.11.23

[MakerFaireTokyo 2014 / 自転車で行くデスクトップの旅2](http://makezine.jp/event/maker2014/taniguchikouheitodaisannnanngugakudann/)


#### 1. リポジトリ構成
***

- 00_Sensor : *センサー統合部*
	- デバイスからセンサー値を取得するMaxパッチ
	- センサー値を整形して、下位アプリにOSC形式で配信する

- 10_Controller : *主コントローラ*
	- 自転車情報をデスクトップ空間にマップするアプリケーション
	- 下位アプリに座標と方角を一定間隔ごとに送信する(OSC)
	- デバッグ用シミュレータを同梱しており、キーボードによるデバッグが可能

- 30_3dView : *三次元デスクトップビュー*
	- openGLを使ってデスクトップとデスクトップアイテム、自転車、を表現したアプリケーション
	- OculusLift DK2に最適化されたビュー、およびGUI
	- サウンドファイルの再生も行う(暫定処置)
	- 自転車とオブジェクトの接触判定はここ
	
- 41_2dView : *二次元デスクトップビュー(代替)*
	- 40_2dViewの代替
	- 主コントローラのメッセージによりカーソルを制御

- 80_Camera : *天窓プラグイン*
	- 30_3dView のプラグイン的に動作するアプリケーション
	- カメラからの入力映像を、30_3dView から参照できる領域にメモリ展開します

- 90_Batch : *事前バッチ処理*
	- ローカルマシンのデスクトップ上に存在するファイルのFinder座標を取得します
	- 作成したファイルは、30_3dView のインプットとして利用します



###### *** 以下は未実装/未テスト ***

- 20_SoundPlayer : *音声部*
	- デスクトップに配置されたサウンドファイルをミックスして再生
	- ポインタからファイルへの距離を考慮

- 40_2dView : *二次元デスクトップビュー*
	- OSのマウスイベントをハックしてスクリプトからマウスポインタを操作するアプリケーション


#### 2.実行時の構成
***

###### PC1 (tgck/MacBookPro 15/OSX 10.9)
	In:  USB-Serial
	Out: Video (Projector)

	Application:
		90_Batch/_doIt.sh
		00_Sensor/analyzerSender.maxpat
		10_Controller/mySketch.xcodeproj	(Video Out)
		41_2dView

###### PC2 (TatsuyaOGth/MacBookPro 15)
	Out: Audio
	Out: Video (OculusLift DK2)

	Application:

		30_3dView/OculusRenderingBasic.xcodeproj	(Audio Out/Video Out)
		80_Camera/GrabSender.xcodeproj



#### 3.既知の問題
******

以下のアプリケーションは稼動実績なし

	20_SoundPlayer
	40_2dView
	41_2dView


#### 4.TODO
******

※未記入

#### 5. Releases

- v1.0.0 (2014.11.24) MFT2014版

- v1.1.0 (2015.5.10)  41_2dView, 90_Batch アップデート後のリハーサル版


