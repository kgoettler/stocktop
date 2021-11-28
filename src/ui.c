#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "api.h"
#include "str.h"
#include "ui.h"

void start_curses(void)
{
    /* Setup ncurses */
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    /* Standard colors */
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    /* Highlighted colors */
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_RED);
    init_pair(8, COLOR_BLACK, COLOR_YELLOW);
    return;
}

void end_curses(void)
{
    endwin();
    return;
}

void set_color_on(double pchange, int highlight)
{
    if (pchange > 0.5)
    {
        if (!highlight)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(6));
    }
    else if (pchange < -0.5)
    {
        if (!highlight)
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(7));
    }
    else
    {
        if (!highlight)
            attron(COLOR_PAIR(4));
        else
            attron(COLOR_PAIR(8));
    }
    return;
}

void set_color_off(double pchange, int highlight)
{
    if (pchange > 0.5)
    {
        if (!highlight)
            attroff(COLOR_PAIR(2));
        else
            attroff(COLOR_PAIR(6));
    }
    else if (pchange < -0.5)
    {
        if (!highlight)
            attroff(COLOR_PAIR(3));
        else
            attroff(COLOR_PAIR(7));
    }
    else
    {
        if (!highlight)
            attroff(COLOR_PAIR(4));
        else
            attroff(COLOR_PAIR(8));
    }
    return;
}

void set_color_error_on(int highlight)
{
    if (!highlight)
        attron(COLOR_PAIR(1));
    else
        attron(COLOR_PAIR(5));
    return;
}

void set_color_error_off(int highlight)
{
    if (!highlight)
        attroff(COLOR_PAIR(1));
    else
        attroff(COLOR_PAIR(5));
    return;
}

void print_header(int row, int col)
{
    char msg[] = "STOCKTOP";
    mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);
    //attron(COLOR_PAIR(5));
    mvprintw(
            row/2 + 1,
            col/2 - 95/2,
            "%-5s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s",
            "",
            "OPEN",
            "PRICE",
            "CHANGE",
            "CHANGE%",
            "VOL",
            "VOLAVG",
            "EBITDA",
            "MARKETCAP",
            "52WKLO",
            "52WKHI");
    //attroff(COLOR_PAIR(5));
    return;
}

void print_stock(StockData *stock, int line, int row, int col, int highlight)
{
    char *volume, *volume_avg, *ebitda, *market_cap;
    // string conversion
    if (stock->error == 0)
    {
        set_color_on(stock->change_perc, highlight);
        volume = double_to_ss(stock->volume);
        volume_avg = double_to_ss(stock->volume_avg);
        ebitda = double_to_ss(stock->ebitda);
        market_cap = double_to_ss(stock->market_cap); 
        mvprintw(
                row/2 + line + 2,
                col/2 - 95/2,
                "%-5s %8.2f %8.2lf %8.2lf %8.2lf %8s %8s %8s %9s %8.2f %8.2f",
                stock->symbol,
                stock->open,
                stock->price,
                stock->change,
                stock->change_perc,
                volume,
                volume_avg,
                ebitda,
                market_cap,
                stock->fifty_two_week_low,
                stock->fifty_two_week_high );
        free(volume);
        free(volume_avg);
        free(ebitda);
        free(market_cap);
        set_color_off(stock->change_perc, highlight);
    }
    else
    {
        set_color_error_on(highlight);
        mvprintw(
                row/2 + line + 2,
                col/2 - 95/2,
                "%s is not a recognized stock symbol",
                stock->symbol);
        set_color_error_off(highlight);
    }
    return;
}

void draw (StockDataArray *stocks, int currow)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    print_header(row, col);
    int i = 0;
    StockData *current = stocks->head;
    while (current)
    {
        print_stock(current, i, row, col, (i == currow) ? 1 : 0);
        current = current->next;
        i++;
    }
    return;
}
