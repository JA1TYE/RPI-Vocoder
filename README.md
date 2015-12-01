# RPI-Vocoder
An implementation of vocoder using baremetal Raspberry Pi  
Raspberry PiをBaremetal(OSなし)環境で使って作るチャネル・ヴォコーダ

##使い方
通常のRaspberry Pi用のディスクイメージが書き込まれたSDカードに対して，"rpi-micom.img"を書き込み，  
BOOTボリュームにある"config.txt"の最後に"kernel=rpi-micom.img"と書き足せば利用できるようになるはずです．  
(詳細は[「BareMetalで遊ぶ Raspberry Pi」](http://tatsu-zine.com/books/raspi-bm)をご参照ください．)

なお，本プログラムはRaspberry Pi A/B向けになっています．
A+/B+/Zero向けの改変は予定しています(実験済み，コード整理中)．

搭載されているSoCが異なるRaspberry Pi 2については，ペリフェラルの仕様変更等があるため
現状では動かないことを確認しています．データシートも公開されていないため，当面対応の予定はありません．

##ソースおよびライセンスについて
[「BareMetalで遊ぶ Raspberry Pi」](http://tatsu-zine.com/books/raspi-bm)
のサンプルコードをベースに，ヴォコーダを作成する上で必要なI2Sペリフェラル向けライブラリ等を追加してあります．
私が改変した部分（および新規作成部分）と元から継承している部分の詳細についてはLICENSEをお読みください．
元ライセンス，私の部分ともにMITライセンスとなっています．

元のサンプルコードはこちら：[jitomesky/RPi_Micon_C85book](https://github.com/jitomesky/RPi_Micon_C85book)

##作者情報
RPI-Vocoder作者:[@JA1TYE](https://twitter.com/JA1TYE) / [TYE's Tech. Lab.](http://t-techlab.net/)  
元ソース及び「BareMetalで遊ぶ Raspberry Pi」作者：[@tnishinaga](https://twitter.com/tnishinaga)様
