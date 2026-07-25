#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char **argv) {

	(void)argc;
    int w = atoi(argv[1]), h = atoi(argv[2]), iter = atoi(argv[3]); // 幅・高さ・世代数
    int board[h][w], next[h][w], x = 0, y = 0, pen = 0;
    char c;
    
    // Initialize
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            board[i][j] = 0;
    
    // Draw
    while (read(0, &c, 1) == 1) {
        if (c == 'w' && y > 0) y--;            // 上へ（y=0 が上端なのでそれ以上は行かない）
        else if (c == 's' && y < h-1) y++;     // 下へ（y=h-1 が下端。h-1 を超えると盤外）
        else if (c == 'a' && x > 0) x--;       // 左へ（x=0 が左端）
        else if (c == 'd' && x < w-1) x++;     // 右へ（x=w-1 が右端）
        else if (c == 'x') pen = !pen;         // ペンの上げ下げを切り替え
        if (pen) board[y][x] = 1;              // ペンが下りていれば今のマスを生きたセルに
    }
    
    // Simulate
    for (int t = 0; t < iter; t++) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int n = 0; // 周囲8マスの生きているセル数
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++)
                    if ((di || dj) && i+di >= 0 && i+di < h && j+dj >= 0 && j+dj < w) // 自分自身は除外し、盤外もカウントしない
                            n += board[i+di][j+dj];
                        // 生存: 生きていて隣人2or3 / 誕生: 死んでいて隣人ちょうど3
                        next[i][j] = (board[i][j] && (n == 2 || n == 3)) || (!board[i][j] && n == 3);
            }
        }
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                board[i][j] = next[i][j]; // 次世代を現在の盤面にコピー
    }
    
    // Print
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            putchar(board[i][j] ? '0' : ' ');
        putchar('\n');
    }
    return 0;
}