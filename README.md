# RPI-Vocoder
An implementation of vocoder using baremetal Raspberry Pi  
Raspberry PiをBaremetal(OSなし)環境で使って作るチャネル・ヴォコーダ

## 使い方
このプロジェクトはオーディオ入力を必要とするので，Raspberry Piに対してコーデックを接続する必要があります．
このプロジェクトではTLV320AIC23BをI2S経由で接続しています．接続方法についてはSchematics.pdfに簡単な回路図が書いてあります．実際にはマイクアンプ等を適宜追加する必要があります．

通常のRaspberry Pi用のディスクイメージが書き込まれたSDカードに対して，"rpi-micom.img"を書き込み，  
BOOTボリュームにある"config.txt"の最後に"kernel=rpi-micom.img"と書き足せば利用できるようになるはずです．  
(詳細は[「BareMetalで遊ぶ Raspberry Pi」](http://tatsu-zine.com/books/raspi-bm)をご参照ください．)

なお，本プログラムはRaspberry Pi A/B向けになっています．
Raspberry Pi A+/B+/Zeroにも対応できるようにI2Sライブラリは書いてある(ただしまだテストしていません…一応テスト済みの別プロジェクトからソースを持ってきたので動くはずですが)ので，rpi_lib内のi2s.cを変更するだけでA+等にも対応できるはずです．また，今回は使っていませんが，PCM510xのようなDACを使う場合にも対応できるように書いてあるので，興味のある方はi2s.cをご覧ください．

搭載されているSoCが異なるRaspberry Pi 2については，ペリフェラルの仕様変更等があるため
現状では動かないことを確認しています．データシートも公開されていないため，当面対応の予定はありません．

## ソースおよびライセンスについて
[「BareMetalで遊ぶ Raspberry Pi」](http://tatsu-zine.com/books/raspi-bm)
のサンプルコードをベースに，ヴォコーダを作成する上で必要なI2Sペリフェラル向けライブラリ等を追加してあります．
私が改変した部分（および新規作成部分）と元から継承している部分の詳細についてはLICENSEをお読みください．
元ライセンス，私の部分ともにMITライセンスとなっています．

元のサンプルコードはこちら：[jitomesky/RPi_Micon_C85book](https://github.com/jitomesky/RPi_Micon_C85book)

## 作者情報
RPI-Vocoder作者:[@JA1TYE](https://twitter.com/JA1TYE) / [TYE's Tech. Lab.](http://t-techlab.net/)  
元ソース及び「BareMetalで遊ぶ Raspberry Pi」作者：[@tnishinaga](https://twitter.com/tnishinaga)様
