#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int n = 6 * 2 + 1;
	char *wall = "#", *space = ".";
	char *maze[n][n];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if ((i % 2 == 1) && (j % 2 == 1)) {
				maze[i][j] = space;
			} else {
				maze[i][j] = wall;
			}
		}
	}

	int v[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	srand(42);
	
	int x = rand() % (n - 1) + 1;
	int y = rand() % (n - 1) + 1;
	for (int i = 1; i < n; i += 2) {
		for (int j = 1; j < n; j += 2) {
			int x = i, y = j;
			int vi = rand() % 4;
			int x_ = x + v[vi][0];
			int y_ = y + v[vi][1];
			while (maze[x_][y_] != wall) {
				int vi = rand() % 4;
				x_ = x + v[vi][0];
				y_ = y + v[vi][1];
			}
			int c = 1;
			maze[x_][y_] = space;
			if (x_ == (n - 1) || y_ == (n - 1) || x_ == 0 || y_ == 0) {
				maze[x_][y_] = wall;
				c = -1;
				x_ += c * v[vi][0];
				y_ += c * v[vi][1];
			}
			x_ += c * v[vi][0];
			y_ += c * v[vi][1];
			maze[x_][y_] = space;
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%s", maze[i][j]);
		}
		printf("\n");
	}

	return 0;
}
