/*
    Author: Emir Hurturk, github.com/ehurturk
    Date: July 2021 
    Project Description: A cli program that display the current time, that is specified as flags, as output.  
    Usage: ./timef -[flags]
    Flags:
        => -s : show seconds
        => -m : show minutes
        => -h : show hours
        => -y : show years
        => -d : show days
        => -D : show names of the days
        => -M : show months
        => -2 : show hours in 24h format (default 24 hour format if no -1 is specified)
        => -1 : show hours in 12h format
    Example Usage: ./timef -s -m -h -2 would output: 13:30:34
*/


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* unix */
#include <termios.h> /* unix */
#include <sys/ioctl.h> /* unix */
#include <fcntl.h> /* unix */

#define MAX_OUTPUT_LEN 28

struct termios orig_term;

/* goto center */
void goto_center(int w, int h, int len) {
    int center_c = w /2;
    int center_row = h/2;
    int half_len = len / 2;
    int adj_col = center_c - half_len;
    for (int i = 0; i < center_row; i++) {
        printf("\n");
    }
    /* now the cursor is placed at the very center of the terminal to print the selected string */
}

void turnechoon() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term);
}

void turnechooff() {
    tcgetattr(STDIN_FILENO, &orig_term);
    atexit(turnechoon);
    struct termios raw = orig_term;
    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag &= ~(ECHO | ICANON); /* flip both the 4th bit and the 3rd bit of the local flags to turn off echo and canon mode */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void render() {
    /* TODO: Render ASCII art here */
    /*
        honestly, I guess it would be a difficult job to render and update ASCII art. I will try to implement it though.
    */
}


char *output;

char *wday;
char *mon; 
char *day; 
char *h;
char *m;
char *s;
char *y;

void cleanup() {
    system("clear");
    printf("\n");
    
    if (output != NULL) free(output);
    
    if (wday != NULL)   free(wday);
    if (mon != NULL)    free(mon);
    if (day != NULL)    free(day);
    if (h != NULL)      free(h);
    if (m != NULL)      free(m);
    if (s != NULL)      free(s);
    if (y != NULL)      free(y);

}

int main(int argc, char **argv)
{
    turnechooff();
    struct winsize size;
    ioctl(0, TIOCGWINSZ, (char *) &size);
    system("clear");
    /* print_centered(size.ws_col, size.ws_row, "Hello there!\n"); */
    
    int str_len = 0;
    output = malloc(sizeof(char) * MAX_OUTPUT_LEN);
    wday = NULL;

    mon = NULL;
    day = NULL; 
    h = NULL; 
    m = NULL; 
    s = NULL; 
    y = NULL; 


    int dayfmt = 0; 
    int c = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 's':
                    s = malloc(sizeof(char) * 3);
                    str_len += 3;
                    break;
                case 'm':                
                    m = malloc(sizeof(char) * 3);
                    str_len += 3;
                    break;
                case 'h':            
                    h = malloc(sizeof(char) * 3);
                    str_len += 2;
                    break;
                case 'y':
                    y = malloc(sizeof(char) * 5);
                    str_len += 4;
                    break;
                case 'd':
                    day = malloc(sizeof(char) * 3);
                    str_len += 3; /* additional / char */
                    break;
                case 'M':
                    mon = malloc(sizeof(char) * 4);
                    str_len += 4; /* additional / char */
                    break;
                case 'D':
                    wday = malloc(sizeof(char) * 4);
                    str_len += 3;
                    break;
                case '1':
                    dayfmt = 1; 
                default:
                    break;
            }
        }
    }

    /* str_len += 6; */
    str_len -= 10;
    system("clear");
    goto_center(size.ws_col, size.ws_row, str_len); /* goto center, place the cursor into the very center */
         
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    while (1) 
    {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (c == 'q') {
            cleanup();   
            return 0;
        }
        time_t _time = time(NULL);
        char *time_str = ctime(&_time);
        time_str[strlen(time_str) - 1] = '\0';
        
        if (wday != NULL)
        {
            wday[0] = time_str[0];
            wday[1] = time_str[1];
            wday[2] = time_str[2];
            wday[3] = '\0';
        }

        if (mon != NULL)
        {
            mon[0] = time_str[4];
            mon[1] = time_str[5];
            mon[2] = time_str[6];
            mon[3] = '\0';
        }

        if (day != NULL)
        {
            day[0] = time_str[8];
            day[1] = time_str[9];
            day[2] = '\0';
        }

        if (h != NULL)
        {
                    
            h[0] = time_str[11];
            h[1] = time_str[12];
            h[2] = '\0';
        }

        if (m != NULL)
        {
            m[0] = time_str[14];
            m[1] = time_str[15];
            m[2] = '\0';
        }

        if (s != NULL)
        {
            s[0] = time_str[17];
            s[1] = time_str[18];
            s[2] = '\0';
        }

        if (y != NULL)
        {
            y[0] = time_str[20];
            y[1] = time_str[21];
            y[2] = time_str[22];
            y[3] = time_str[23];
            y[4] = '\0';
        }
        

        if (wday != NULL) {
            if (mon != NULL || (mon == NULL && day != NULL))    sprintf(wday, "%s/", wday);
            else if (mon == NULL && day == NULL)                sprintf(wday, "%s - ", wday);
            strcat(output, wday);
        }

        if (mon != NULL) {
            if (day != NULL)                                    sprintf(mon, "%s/", mon);
            else                                                sprintf(mon, "%s - ", mon);
            strcat(output, mon);
        }

        if (day != NULL) {
            sprintf(day, "%s - ", day);
            strcat(output, day);
        }

        if (dayfmt == 1 && h != NULL) { 
            sprintf(h, "%i", (atoi(h) % 12));
            sprintf(h, (m != NULL && s != NULL) ? "%s:" : "%s ", h);
            strcat(output, h);
        }

        else if (dayfmt == 0 && h != NULL) {
            sprintf(h, "%i", (atoi(h)));
            sprintf(h, (m != NULL && s != NULL) ? "%s:" : (s!=NULL)?"%s:":"%s ", h);
            strcat(output, h);
        }
        
        if (m != NULL) {
            sprintf(m, s != NULL ? "%s:" : "%s - ", m);
            strcat(output, m);
        }

        if (dayfmt == 1 && s != NULL) {
            sprintf(s, "%s %s" "%s", s, atoi(h) > 12? "PM":"AM", y != NULL ? " - ": "" );
            strcat(output, s);
        }

        else if (dayfmt == 0 && s != NULL) {
            sprintf(s, "%s" "%s", s, y != NULL ? " - ": "" );
            strcat(output, s);
        }
        
        if (y != NULL)
            strcat(output, y);
        
        strcat(output, "\0");
        /* crucial: print the blank lines to center the text */
        for (int i = 0; i < size.ws_col / 2 - str_len; i++) {
            printf(" ");
        }
        printf("%s", output);
        printf("\r"); 
        memset(output, 0, strlen(output)); 
        fflush(stdout);
        sleep(1);
    }

    cleanup();
    return 0;
    
}


