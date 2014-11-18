// キャリブレーション
// in:   list  --- "calibration $1"  : raw_Compassの値を入れる(0.-360.)
// out1: float --- calibrationDegree : 補正値。raw_Compassに穿かせる下駄。{-90., 0., 90.})
// out2: float --- rangeStart        : 写像された範囲の下限角度. [scale]への引数
// out3: float --- rangeEnd          : 写像された範囲の上限角度. [scale]への引数

inlets = 1;
outlets = 3;

var myval=0;
var calibrationDegree = 0;
var rangeStart = 0;
var rangeEnd = 0;

function bang(){
	outlet(0, myval);
}

// raw_Compass を元に、写像された角度を出力する
function msg_float(v) {
	outlet (0, v + calibrationDegree);
}

// 現在値を使ってキャリブレーションする
function calibrate(v){
	
    post ("[caribtate/caribrate] gyrOsc heading degree at:" + v + "\n");
    post ("[caribtate/caribrate] accceptable range is:" + (v -90) + ".." +  (v+90) + "\n");
    
	// 角度により3つのエリアに分割。
	if (v >= 90 && v < 180) {
        // 補正なし
		calibrationDegree = 0;
	} else if ( v >= 0 && v < 90 ) {
        // コンパス 0度を跨ぐので補正
		calibrationDegree = 180;
	} else if ( v >= 180 && v <= 360) {
        // コンパス 360度を跨ぐので補正
		calibrationDegree = -180;
	}
	
	// 下駄を穿かせた入力値
	post("---------------- steerNormalizer/calibrateAt (", v, ")" );
	post("----------------\n");
	post("inputValue: ", v, "\n");
	post("calibrationDegree: ", calibrationDegree, "\n");
	post("calibedValue: ", v + calibrationDegree, "\n");
	
	// [scale]の再設定用の出力
//	rangeStart = ( v + calibrationDegree ) - 90.;
	rangeStart = ( v + calibrationDegree ) - 45.;
//	rangeEnd   = ( v + calibrationDegree ) + 90.;
	rangeEnd   = ( v + calibrationDegree ) + 45.;
	post("rangeStarts: " , rangeStart, "\n");
	post("rangeEnds  : " , rangeEnd,   "\n");
	
	outlet(2, rangeEnd);
	outlet(1, rangeStart);
	outlet(0, calibrationDegree);
}