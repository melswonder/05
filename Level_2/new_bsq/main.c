#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *f = argc > 1 ? fopen(argv[1], "r") : stdin;
	char *line = NULL, e, o, p, **map;
	size_t cap = 0;
	int h, w = -1, i, x, y, best = 0, by = 0, bx = 0, **dp;

	if (!f)
		return (1);
	if (fscanf(f, "%d %c %c %c\n", &h, &e, &o, &p) != 4 || h < 1)
		return (fprintf(stderr, "map error\n"), 1);

	map = malloc(sizeof(char *) * h);
	for (i = 0; i < h; i++)
	{
		/* 1行読む。読めなかった(行数不足)ら break して後でエラー判定 */
		ssize_t len = getline(&line, &cap, f);
		if (len < 1)
			break;
		/* 末尾の改行 '\n' を消して文字列を終端しておく */
		if (line[len - 1] == '\n')
			line[--len] = 0;
		/* 最初の行の長さを基準幅 w として覚える */
		if (w == -1)
			w = len;
		/* 行頭から「空白文字 or 障害物文字」が続く間だけ進める。
		   途中で知らない文字に当たると x が w まで届かない */
		for (x = 0; x < w && (line[x] == e || line[x] == o); x++)
			;
		/* 幅が他の行と違う、または知らない文字があった → 不正マップ */
		if (len != w || x != w)
			break;
		/* この行をコピーして保存('\0'込みで w+1 文字ぶん) */
		map[i] = malloc(len + 1);
		for (x = 0; x <= w; x++)
			map[i][x] = line[x];
	}
	/* h 行ぶん最後まで読めなかった = どこかで break した = 不正マップ */
	if (i != h)
		return (fprintf(stderr, "map error\n"), 1);

	/* ---- DP で最大の正方形を探す ----
	   dp[y][x] = 「(y,x) を右下の角にできる正方形の最大サイズ」 */
	dp = malloc(sizeof(int *) * h);
	for (y = 0; y < h; y++)
		for (dp[y] = malloc(sizeof(int) * w), x = 0; x < w; x++)
		{
			if (map[y][x] != e)
				dp[y][x] = 0;          /* 空白以外(障害物)は正方形を置けない */
			else if (!y || !x)
				dp[y][x] = 1;          /* 一番上の行/左の列は最大でもサイズ1 */
			else
			{
				/* 上・左・左上 の3つの最小値 + 1 が自分の正方形サイズ */
				int m = dp[y - 1][x];
				if (m > dp[y][x - 1]) m = dp[y][x - 1];
				if (m > dp[y - 1][x - 1]) m = dp[y - 1][x - 1];
				dp[y][x] = m + 1;
			}
			if (dp[y][x] > best)
				best = dp[y][x], by = y, bx = x;
		}

	for (y = by - best + 1; y <= by; y++)
		for (x = bx - best + 1; x <= bx; x++)
			map[y][x] = p;


	for (y = 0; y < h; y++)
		fprintf(stdout, "%s\n", map[y]);
	return (0);
}