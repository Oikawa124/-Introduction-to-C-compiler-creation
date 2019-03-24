# 整数1個をコンパイルする言語の作成

## コンパイラ本体の作成

```
gaku@DESKTOP-IB1OCGR:~/9cc$ ./tmp
gaku@DESKTOP-IB1OCGR:~/9cc$ echo $?
123
```
実行できた。
>シェルでは直前のコードの終了コードが$?という変数でアクセスできる

## ユニットテストの作成

```
gaku@DESKTOP-IB1OCGR:~/9cc$ ./test.sh
0 => 0
42 => 42
OK
```
失敗する場合
```
0 => 0
42 expected, but got 4
```

デバッグ
```
gaku@DESKTOP-IB1OCGR:~/9cc$ bash -x test.sh
+ try 0 0
+ expected=0
+ input=0
+ ./9cc 0
+ gcc -o tmp tmp.s
+ ./tmp
+ actual=0
+ '[' 0 = 0 ']'
+ echo '0 => 0'
0 => 0
+ try 42 4
+ expected=42
+ input=4
+ ./9cc 4
+ gcc -o tmp tmp.s
+ ./tmp
+ actual=4
+ '[' 4 = 42 ']'
+ echo '42 expected, but got 4'
42 expected, but got 4
+ exit 1
```

>ユニットテストというものは、要は自分の書いたコードを一発で動かして結果を機械的に比較できればよいだけなので、難しく考えすぎず、まずはテストを行うことが大切なのです。

## makeによるビルド

```
gaku@DESKTOP-IB1OCGR:~/9cc$ nano Makefile
gaku@DESKTOP-IB1OCGR:~/9cc$ make
make: '9cc' is up to date.
gaku@DESKTOP-IB1OCGR:~/9cc$ nano Makefile
gaku@DESKTOP-IB1OCGR:~/9cc$ make
make: '9cc' is up to date.
gaku@DESKTOP-IB1OCGR:~/9cc$ make test
./test.sh
0 => 0
42 expected, but got 4
Makefile:4: recipe for target 'test' failed
make: *** [test] Error 1
```

## gitによるバージョン管理

読了










