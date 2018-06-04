

/* グローバル変数の宣言 */
byte bb[32];  /* 文字パターンの配列 */
int kind;     /* 文字パターン配列bb の添え字*/
int km;       /* 添え字の最大値 = 文字パターンのコマ数 */
long kct;      /*ループカウンタ*/
int sn1;      /*センサの現在値*/
int sn2;      /*センサの1回前の値*/
int Tperiod;  /*1周期の時間 (ms単位)  振り始め(傾斜センサ動作)の間隔で計測する。
               T_Period   1周期ごとに更新する。  */
long times = 0;
int a1;
int a2;
int i;
int j;
int l;
int m;
int n;
byte k;

int zz;
int xx;
int nn;
int vv;
int mm;
int ss;

/* マイコンの入出力ピンの定義 */
int SensPin=0;
int LEDPin1=1;
int LEDPin2=2;
int LEDPin3=3;
int LEDPin4=4;
int LEDPin5=5;
int LEDPin6=6;
int LEDPin7=7;
int speaker=8;
int pinNo=9;

byte aa[5];
byte cc[5];
byte dd[5];
byte a[5];
byte b[5];
byte c[5];
byte d[5];
byte e[5];
byte f[5];
byte g[5];
byte h[5];
byte i2[5];
byte j2[5];

void setup()/*初期化関数*/
{
   /* 入出力ピンの設定 */
  pinMode(SensPin,INPUT_PULLUP);
  pinMode(LEDPin1,OUTPUT);
  pinMode(LEDPin2,OUTPUT);
  pinMode(LEDPin3,OUTPUT);
  pinMode(LEDPin4,OUTPUT);
  pinMode(LEDPin5,OUTPUT);
  pinMode(LEDPin6,OUTPUT);
  pinMode(LEDPin7,OUTPUT);
  pinMode(speaker,OUTPUT);
  pinMode(pinNo,OUTPUT);
  
  /* 初期値3:00に設定 */
  bb[0] =B00000000;     
  bb[1] =B00000000;
  bb[2] =B00000000;
  bb[3] =B00000000;
  bb[4] =B01001001; 
  bb[5] =B01001001;
  bb[6] =B01001001;
  bb[7] =B01001001;
  bb[8] =B01111111;
  bb[9] =B00000000;
  bb[10]=B00000000;
  bb[11]=B00000000;
  bb[12]=B01111111;
  bb[13]=B00000000;
  bb[14]=B00000000;
  bb[15]=B00000000;
  bb[16]=B01111111;
  bb[17]=B01000001;
  bb[18]=B01000001;
  bb[19]=B01000001;
  bb[20]=B01111111;
  bb[21]=B00000000;
  bb[22]=B00000000;
  bb[23]=B00000000;
  bb[24]=B01111111;
  bb[25]=B01000001;
  bb[26]=B01000001;
  bb[27]=B01000001;
  bb[28]=B01111111;
  bb[29]=B00000000;
  bb[30]=B00000000;
  bb[31]=B00000000;

  //0-9の数字を用意する
  //1
  a[0] =B01111111;
  a[1] =B00000000;
  a[2] =B00000000;
  a[3] =B00000000;
  a[4] =B00000000;

  //2
  b[0] =B01111001;
  b[1] =B01001001;
  b[2] =B01001001;
  b[3] =B01001001;
  b[4] =B01001111;
  
  //3
  c[0] =B01001001;
  c[1] =B01001001;
  c[2] =B01001001;
  c[3] =B01001001;
  c[4] =B01111111;
  
  //4
  d[0] =B00001111;
  d[1] =B00001000;
  d[2] =B00001000;
  d[3] =B00001000;
  d[4] =B01111111;
  
  //5
  e[0] =B01001111;
  e[1] =B01001001;
  e[2] =B01001001;
  e[3] =B01001001;
  e[4] =B01111001;

  //6
  f[0] =B01111111;
  f[1] =B01001000;
  f[2] =B01001000;
  f[3] =B01001000;
  f[4] =B01111000;

  //7
  g[0] =B00000001;
  g[1] =B00000001;
  g[2] =B00000001;
  g[3] =B00000001;
  g[4] =B01111111;
  
  //8
  h[0] =B01111111;
  h[1] =B01001001;
  h[2] =B01001001;
  h[3] =B01001001;
  h[4] =B01111111;

  //9
  i2[0] =B00001111;
  i2[1] =B00001001;
  i2[2] =B00001001;
  i2[3] =B00001001;
  i2[4] =B01111111;

  //0
  j2[0] =B01111111;
  j2[1] =B01000001;
  j2[2] =B01000001;
  j2[3] =B01000001;
  j2[4] =B01111111;
  km=31;  /*パターンの総コマ数 */

kct=0;
Tperiod=300;
k=0.0;

}



void loop()   /*メイン ループ*/
{
  byte v;/*文字パターン作業変数*/

/*文字パターンの添え字kindを決める*/
if (kct < Tperiod/2) 
{ /* 行き(右から左)のときのみ表示*/
  kind=km - km*kct/(Tperiod/2);
  } else {
  kind=km+99; }

/*文字パターンの表示*/
if (kind>0 && kind<=km) 
  { /* 添え字が範囲内であることを確認した */
     v=bb[kind];  /* 文字パターンを読み出して，*/
     Hyoji(v);    /*  LEDに表示する  */
  }
/*1ms遅らせる*/
delay(1);
kct=kct+1; /*ループ回数をカウント*/

/*傾斜センサ*/
sn2=sn1;  /*ひとつ古い値を退避する*/
sn1=digitalRead(SensPin); /*センサ入力*/
if(sn1 ==LOW  && sn2 ==HIGH  &&  kct>30 )
  {  /*センサがHIGHからLOWに変わった。
       kct>30の条件は，チャタリングによって
      頻繁にLOW/HIGHが変化する現象を捨てるため  */
   /* 周期Tperiodを測定*/
      Tperiod=kct;
      
      times=times+Tperiod;
  /* ループカウンタkctを初期化*/
     kct=0;
  }

a1=times/10000;
a2=times/1000-a1*10;

//0-60000msのとき(2分台
if(times<=60000){
  //分を2に
  bb[4]=b[0];
  bb[5]=b[1];
  bb[6]=b[2];
  bb[7]=b[3];
  bb[8]=b[4];
  
  //10の位
  //5を表示
  if(times>=0 && times<10000){
    for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;
      bb[i]=e[j];
    }
  }//ifa1=0

  //4を表示
  if(times>=10000 && times<20000){
    for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;
      bb[i]=d[j];     
    }
  }//ifa1=1

  //3を表示
  if(times>=20000 && times<30000){
    for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;
    bb[i]=c[j];
    }
  }//ifa1=2

    //2を表示
  if(times>=30000 && times<40000){
    for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;
    bb[i]=b[j];     
    }
  }//ifa1=3

    //1を表示
  if(times>=40000 && times<50000){
    for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;  
    bb[i]=a[j];
    }
  }//ifa1=4

    //0を表示
  if(times>=50000 && times<60000){
   for(zz=0; zz<5; zz++){
    i=16+zz;
    j=0+zz;
    bb[i]=j2[j];
    }
  }//ifa1=5

    //1の位
    //9を表示
   if(a2==0){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=i2[l];
    }
   }//ifa2=0

    //8を表示
   if(a2==1){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=h[l];
    }
   }//ifa2=1
   
    //7を表示
   if(a2==2){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
     bb[k]=g[l];
    }
   }//ifa2=2

    //6を表示
   if(a2==3){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=f[l];
    }
   }//ifa2=3

    //5を表示
   if(a2==4){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=e[l];
    }
   }//ifa2=4

    //4を表示
   if(a2==5){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=d[l];
    }
   }//ifa2=5

    //3を表示
   if(a2==6){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=c[l];
    }
   }//ifa2=6

    //2を表示
   if(a2==7){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=b[l];
    }
   }//ifa2=7

    //1を表示
   if(a2==8){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=a[l];
    }
   }//ifa2=8

    //0を表示
   if(a2==9){
    for(xx=0; xx<5; xx++){
     k=24+xx;
     l=0+xx;
      bb[k]=j2[l];
    }
   }//ifa2=9

}//2分台


//60000-120000msのとき(1分台
else if(times<=120000){
  bb[4]=a[0];
  bb[5]=a[1];
  bb[6]=a[2];
  bb[7]=a[3];
  bb[8]=a[4];
  
  //10の位
  //5を表示
  if(times>=60000 && times<70000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=e[j];
    }
  }//ifa1=0

  //4を表示
  if(times>=70000 && times<80000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=d[j];
    }
  }//ifa1=1

  //3を表示
  if(times>=80000 && times<90000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=c[j];
    }
  }//ifa1=2

    //2を表示
  if(times>=90000 && times<100000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=b[j];
    }
  }//ifa1=3

    //1を表示
  if(times>=100000 && times<110000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=a[j];
    }
  }//ifa1=4

    //0を表示
  if(times>=110000 && times<120000){
    for(nn=0; nn<5; nn++){
      i=16+nn;
      j=0+nn;
      bb[i]=j2[j];  
    }
  }//ifa1=5

    //1の位
    //9を表示
   if(a2==0){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=i2[l];
    }
   }//ifa2=0

    //8を表示
   if(a2==1){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=h[l];
    }
   }//ifa2=1
   
    //7を表示
   if(a2==2){
    for(k=24; k<29; k++){
    for(l=0; l<5; l++){
      bb[k]=g[l];
    }
    }
   }//ifa2=2

    //6を表示
   if(a2==3){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=f[l];
    }
   }//ifa2=3

    //5を表示
   if(a2==4){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=e[l];
    }
   }//ifa2=4

    //4を表示
   if(a2==5){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=d[l];
    }
   }//ifa2=5

    //3を表示
   if(a2==6){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=c[l];
    }
   }//ifa2=6

    //2を表示
   if(a2==7){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=b[l];
    }
   }//ifa2=7

    //1を表示
   if(a2==8){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=a[l];
    }
   }//ifa2=8

    //0を表示
   if(a2==9){
     for(vv=0; vv<5; vv++){
     k=24+vv;
     l=0+vv;
      bb[k]=j2[l];
    }
   }//ifa2=9

}//1分台


//120000-180000msのとき(0分台
else if(times<=180000){
  bb[4]=j2[0];
  bb[5]=j2[1];
  bb[6]=j2[2];
  bb[7]=j2[3];
  bb[8]=j2[4];
  
  //10の位
  //5を表示
  if(times>=120000 && times<130000){
     for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
     bb[i]=e[j]; 
    }
  }//ifa1=0

  //4を表示
  if(times>=130000 && times<140000){
     for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
      bb[i]=d[j];
    }
  }//ifa1=1

  //3を表示
  if(times>=140000 && times<150000){
     for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
      bb[i]=c[j];
    }
  }//ifa1=2

    //2を表示
  if(times>=150000 && times<160000){
     for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
      bb[i]=b[j];
    }
  }//ifa1=3

    //1を表示
  if(times>=160000 && times<170000){
     for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
      bb[i]=a[j];
    }
  }//ifa1=4

    //0を表示
  if(times>=170000 && times<180000){
      for(mm=0; mm<5; mm++){
     k=16+mm;
     l=0+mm;
      bb[i]=j2[j];
    }
  }//ifa1=5

    //1の位
    //9を表示
   if(a2==0){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=i2[l];
    }
   }//ifa2=0

    //8を表示
   if(a2==1){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=h[l];
    }
   }//ifa2=1
   
    //7を表示
   if(a2==2){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=g[l];
    }
   }//ifa2=2

    //6を表示
   if(a2==3){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=f[l];
    }
   }//ifa2=3

    //5を表示
   if(a2==4){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=e[l];
    }
   }//ifa2=4

    //4を表示
   if(a2==5){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=d[l];
    }
   }//ifa2=5

    //3を表示
   if(a2==6){
     for(ss=0; ss<5; ss++){
      k=24+ss;
      l=0+ss;
      bb[k]=c[l];
    }
   }//ifa2=6

    //2を表示
   if(a2==7){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=b[l];
    }
   }//ifa2=7

    //1を表示
   if(a2==8){
     for(ss=0; ss<5; ss++){
      k=24+ss;
     l=0+ss;
      bb[k]=a[l];
    }
   }//ifa2=8

    //0を表示
   if(a2==9){
     for(ss=0; ss<5; ss++){
     k=24+ss;
     l=0+ss;
      bb[k]=j2[l];
    }
   }//ifa2=9

}//0分台

/*0:00になったら*/ 
    if(times==180000){
    tone(8, 523);
    delay(200);
    noTone(8);
    tone(8, 587);
    delay(200);
    noTone(8);
    tone(8, 659);
    delay(400);
    noTone(8);
    tone(8, 587);
    delay(200);
    noTone(8);
    tone(8, 523);
    delay(200);
    noTone(8);
  }
}

void Hyoji(byte v)  /*文字パターンを8個のLEDに表示する*/
{
if((v &B00000001)==0)digitalWrite(LEDPin1,LOW);else digitalWrite(LEDPin1,HIGH);
if((v &B00000010)==0)digitalWrite(LEDPin2,LOW);else digitalWrite(LEDPin2,HIGH);
if((v &B00000100)==0)digitalWrite(LEDPin3,LOW);else digitalWrite(LEDPin3,HIGH);
if((v &B00001000)==0)digitalWrite(LEDPin4,LOW);else digitalWrite(LEDPin4,HIGH);
if((v &B00010000)==0)digitalWrite(LEDPin5,LOW);else digitalWrite(LEDPin5,HIGH);
if((v &B00100000)==0)digitalWrite(LEDPin6,LOW);else digitalWrite(LEDPin6,HIGH);
if((v &B01000000)==0)digitalWrite(LEDPin7,LOW);else digitalWrite(LEDPin7,HIGH);
}








