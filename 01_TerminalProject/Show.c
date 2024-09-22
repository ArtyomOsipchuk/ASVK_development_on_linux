#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1024


int main(int argc, char *argv[]) {
	WINDOW *win;
	FILE *file = fopen(argv[1], "r");
	if (!file) {
		return 1;
	}
	
	int c = 0;
	int max_lines = 0, max_len = 0;
	while (EOF != (c = getc(file))) {
		if (c == '\n') {
			max_lines++;
		}
	}	
	fseek(file, 0, SEEK_SET );

	char *buf[max_lines];
    	for (int i = 0; i < max_lines; i++) {
        	buf[i] = malloc(MAX_LEN);
    	}
	
	initscr();
	noecho();
	cbreak();
	printw("File: %s; size:%d", argv[1], max_lines);
	refresh();
	
	win = newwin(LINES - 15, COLS - 15, 3, 3);
	keypad(win, TRUE);
	scrollok(win, TRUE);
	box(win, 0, 0);
	wmove(win, 0, 1);
	int index = 0;
	while (index < max_lines && fgets(buf[index], MAX_LEN, file) != NULL) {
		if (strlen(buf[index]) > max_len) {
			max_len = strlen(buf[index]);
		}
		index++;
	}
	fclose(file);
	
	int start = 0, shift = 0;
	while (c != 27) {
		werase(win);
		int end = start + LINES;
		for (int i = start; i < end; i++) {
			mvwprintw(win, i - start + 3, 1, "  %d:  %s", i + 1, buf[i] + shift);
		}
		box(win, 0, 0);
		wrefresh(win);
		c = wgetch(win);
		switch (c) {
		case KEY_DOWN:
			if (start + LINES - 17 <= max_lines) {
				start++;
			}
			break;
		case KEY_UP:
			if (start > 0) {
				start--;
			}
			break;
		case KEY_LEFT:
			if (shift > 0) {
				shift--;
			}
			break;
		case KEY_RIGHT:
			if (shift <= max_len) {
				shift++;
			}
			break;
		}
	}
	endwin();
	return 0;
}
