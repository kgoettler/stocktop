#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Setup the curses session
 */
void start_curses(void)
{
    /* Setup ncurses */
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    return;
}

/**
 * Clean up the curses session
 */
void end_curses(void)
{
    endwin();
    return;
}

void draw(void)
{
    char msg[] = "This is a test.";
    int row, col;
    attron(COLOR_PAIR(1));
    getmaxyx(stdscr, row, col);
    mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);
    mvprintw(row-2, 0, "This screen has %d rows and %d columns\n", row, col);
    printw("Try resizing your window(if possible) and then run this program again");
    attroff(COLOR_PAIR(1));
    return;
}

int main (void) 
{
    char key;
    start_curses();
    draw();
    while ((key = getch()) != 'q')
    {
        switch (key)
        {
            default:
                break;
        }
        clear();
        draw();
        /* Redraw */
    }
    end_curses();
    return 0;
}
