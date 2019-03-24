# 加減算のできるコンパイラの作成

```
gaku@DESKTOP-IB1OCGR:~/9cc$ ./9cc '5+20-4'
.intel_syntax noprefix
.global main
main:
  mov rax, 5
  add rax, 20
  sub rax, 4
  ret
gaku@DESKTOP-IB1OCGR:~/9cc$ nano test.sh
gaku@DESKTOP-IB1OCGR:~/9cc$ make test
./test.sh
0 => 0
42 => 42
5+20-4 => 21
OK
gaku@DESKTOP-IB1OCGR:~/9cc$
```

