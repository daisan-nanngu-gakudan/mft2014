//
// serialListner.ino
//    - クライアントと接続確立するまでは、何もしない。
//    - 1秒間に1回シリアルポートをチェックする。
//    - クライアントと接続すると、高頻度で回路の電圧をチェックし、その状態に応じて
//      クライアントに'P'(高電圧), 'T'(低電圧)を送信する。
// 
int P_IN  = 7;   // pushbutton connected to digital pin 7; センシング
int P_OUT = 13; // LED connected to digital pin 13; デバッグ用

void setup()
{
  Serial.begin(9600);
  
  // digitalピンの利用は、analogピンと異なりピンモードを宣言する必要がある
  pinMode(P_OUT, OUTPUT);
  pinMode(P_IN, INPUT);
  
  // 接続されるまで主処理に入らない
  establishContact();  
}

// 主処理
void loop()
{
  // 電圧のチェック
  // 1なら回路が閉じている: 'P'(80);  peek
  // 0なら回路は開いている: 'T'(84);  trough
  int value = digitalRead(P_IN);
  if ( value == HIGH) {
    digitalWrite(P_OUT, HIGH);
    Serial.print('P');
  } else {
    digitalWrite(P_OUT, LOW);    
    Serial.print('T');
  }
  delay(30); // クライアントの読み出しペースより遅くする
    // しかしあんまり遅いと、ホイールの回転をサンプリングできない
}

// クライアントから何か文字が送られてくるのを待つ
// 何かしら asciiを受信すると抜ける
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("waiting for connection.");
    delay(1000);
  }
  Serial.println("new client connected.");
}
