#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

// トークンの型を表す値
enum {
    TK_NUM = 256, // 整数トークン
    TK_EOF,       // 入力の終わりを表すトークン EOF
};

// トークンの型
typedef struct {
    int ty;  // トークンの型
    int val; // tyがTK_NUMの場合、数値をいれる
    char *input; // トークン文字列（エラーメッセージ）
} Token;


// トークナイズした結果のトークン列はこの配列に保存する
// 100個以上のトークンは来ないものとする
Token tokens[100];


void tokenize(char *p){
    int i = 0;

    // 空白文字スキップ
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-') {
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++; // ポインタを進める
            continue;
        }

        if (isdigit(*p)) {
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p, &p, 10);
            i++;
            continue;
        }

        fprintf(stderr, "fail %s\n", p);
        exit(1);
    }

    tokens[i].ty = TK_EOF;
    tokens[i].input = p;
}

// エラーを報告する関数
void error(int i){
    fprintf(stderr, "unexpected token: %s\n", tokens[i].input);
    exit(1);
}



//static int streq(char *s1, char *s2) { return 0 == strcmp(s1, s2); }

static void test_tokenize_1(){

    // SetUp
    char *input = "1 + 1";

    // Exercise
    tokenize(input);

    // Verify
    assert(tokens[0].ty == TK_NUM);
    assert(tokens[0].val == 1);

    assert(tokens[1].ty == '+');

    assert(tokens[2].ty == TK_NUM);
    assert(tokens[2].val == 1);

    assert(tokens[3].ty == TK_EOF);
}

static void unit_tests(){
    test_tokenize_1();
}


int main(int argc, char **argv) {

    // ユニットテスト
    unit_tests();

    if (argc != 2) {
        fprintf(stderr, "invalid arg");
        return 1;
    }

    // トークナイズする
    tokenize(argv[1]);


    // アセンブリの前半部分
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 式の最初は数字である必要がある
    // 最初のmov命令を出力

    if (tokens[0].ty != TK_NUM) {
        error(0);
    }

    printf("  mov rax, %d\n", tokens[0].val);

    // アセンブリを出力
    int i = 1;
    while (tokens[i].ty != TK_EOF) {

        if (tokens[i].ty == '+') {

            i++; // "+"の次に移動。　+<数字>

            if (tokens[i].ty != TK_NUM) {
                error(i);
            }

            printf("  add rax, %d\n", tokens[i].val);

            i++; // 次のトークンに移動
            continue;
        }

        if (tokens[i].ty == '-') {

            i++; // "-"の次に移動。　+<数字>

            if (tokens[i].ty != TK_NUM) {
                error(i);
            }

            printf("  sub rax, %d\n", tokens[i].val);

            i++; // 次のトークンに移動
            continue;
        }

        error(i);
    }

    printf("  ret\n");
    return 0;
}
