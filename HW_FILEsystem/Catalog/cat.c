#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 1024

typedef struct {
    char path[MAX_PATH];
    int selected;
    int num_files;
    char files[256][MAX_PATH];
    int is_dir[256];
} Panel;

void draw_panel(Panel *panel, int x, int y, int width, int height, int active) {
    mvprintw(y, x + 1, "Path: %s", panel->path);
    for (int i = 0; i < height - 2 && i < panel->num_files; ++i) {
        if (i == panel->selected) {
            if (active) attron(A_REVERSE);
            mvprintw(y + 2 + i, x + 1, "%s%s", panel->files[i], panel->is_dir[i] ? "/" : "");
            if (active) attroff(A_REVERSE);
        } else {
            mvprintw(y + 2 + i, x + 1, "%s%s", panel->files[i], panel->is_dir[i] ? "/" : "");
        }
    }
    for (int i = panel->num_files; i < height - 2; ++i) {
        mvprintw(y + 2 + i, x + 1, "~");
    }
}

void load_directory(Panel *panel) {
    DIR *d = opendir(panel->path);
    struct dirent *dir;
    struct stat statbuf;
    panel->num_files = 0;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            strncpy(panel->files[panel->num_files], dir->d_name, MAX_PATH);
            char fullpath[MAX_PATH];
            snprintf(fullpath, MAX_PATH, "%s/%s", panel->path, dir->d_name);
            stat(fullpath, &statbuf);
            panel->is_dir[panel->num_files] = S_ISDIR(statbuf.st_mode);
            panel->num_files++;
        }
        closedir(d);
    }
}

void change_directory(Panel *panel) {
    if (panel->selected < panel->num_files && panel->is_dir[panel->selected]) {
        char new_path[MAX_PATH];
        snprintf(new_path, MAX_PATH, "%s/%s", panel->path, panel->files[panel->selected]);
        if (chdir(new_path) == 0) {
            realpath(new_path, panel->path);
            load_directory(panel);
            panel->selected = 0;
        }
    }
}

void draw_borders(int x, int y, int width, int height) {
    for (int i = 0; i < width; ++i) {
        mvprintw(y, x + i, "-");
        mvprintw(y + height - 1, x + i, "-");
    }
    for (int i = 0; i < height; ++i) {
        mvprintw(y + i, x, "|");
        mvprintw(y + i, x + width - 1, "|");
    }
    mvprintw(y, x, "+");
    mvprintw(y, x + width - 1, "+");
    mvprintw(y + height - 1, x, "+");
    mvprintw(y + height - 1, x + width - 1, "+");
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int panel_width = COLS / 2;
    int panel_height = LINES;
    
    Panel left_panel = { .path = ".", .selected = 0 };
    Panel right_panel = { .path = ".", .selected = 0 };
    Panel *active_panel = &left_panel;
    Panel *inactive_panel = &right_panel;

    load_directory(&left_panel);
    load_directory(&right_panel);

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (active_panel->selected > 0) active_panel->selected--;
                break;
            case KEY_DOWN:
                if (active_panel->selected < active_panel->num_files - 1) active_panel->selected++;
                break;
            case 9: // Tab key
                if (active_panel == &left_panel) {
                    active_panel = &right_panel;
                    inactive_panel = &left_panel;
                } else {
                    active_panel = &left_panel;
                    inactive_panel = &right_panel;
                }
                break;
            case 10: // Enter key
                change_directory(active_panel);
                break;
        }
        clear();
        draw_borders(0, 0, panel_width, panel_height);
        draw_borders(panel_width, 0, panel_width, panel_height);
        draw_panel(&left_panel, 0, 0, panel_width, panel_height, active_panel == &left_panel);
        draw_panel(&right_panel, panel_width, 0, panel_width, panel_height, active_panel == &right_panel);
        refresh();
    }

    endwin();
    return 0;
}
