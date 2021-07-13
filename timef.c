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

#define MAX_OUTPUT_LEN 28
        
void print_centered(int w, int h, const char *str) {
    int center_col = w / 2;
    int center_row = h / 2;
    int half_len = strlen(str) / 2;
    int adj_col = center_col - half_len;
    for (int i = 0; i < adj_col; i++) {

    }
}

int main(int argc, char **argv)
{
    struct winsize size;
    char *output = malloc(sizeof(char) * MAX_OUTPUT_LEN);
    ioctl(0, TIOCGWINSZ, (char *) &size);
    char *wday = NULL;

    char *mon = NULL;
    char *day = NULL; 
    char *h = NULL; 
    char *m = NULL; 
    char *s = NULL; 
    char *y = NULL; 


    int dayfmt = 0; /* default 24 hr format */
    int c = 0;
    /* Dynamic Memory Allocation is on startup, not in loop - shouldn't be a problem thereof */
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 's':
                    s = malloc(sizeof(char) * 3);
                    break;
                case 'm':                
                    m = malloc(sizeof(char) * 3);
                    break;
                case 'h':            
                    h = malloc(sizeof(char) * 3);
                    break;
                case 'y':
                    y = malloc(sizeof(char) * 5);
                    break;
                case 'd':
                    day = malloc(sizeof(char) * 3);
                    break;
                case 'M':
                    mon = malloc(sizeof(char) * 4);
                    break;
                case 'D':
                    wday = malloc(sizeof(char) * 4);
                    break;
                case '1':
                    dayfmt = 1; /* enable 12 hr format */
                default:
                    break;
            }
        }
    }

    system("clear");
    
    while (1) /* TODO: When q is pressed, exit */
    {

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
        
        /* TODO: Print ASCII art (3D) */

        /* char *output = malloc(sizeof(char) * MAX_OUTPUT_LEN); */
        /* char output[MAX_OUTPUT_LEN]; */
        if (wday != NULL) {
            sprintf(wday, "%s/", wday);
            strcat(output, wday);
            /* printf("%s", wday); */
        }

        if (mon != NULL) {
            sprintf(mon, "%s/", mon);
            strcat(output, mon);
            /* printf("%s", mon); */
        }

        if (day != NULL) {
            sprintf(day, "%s - ", day);
            strcat(output, day);
            /* printf("%s", day); */
        }

        if (dayfmt == 1 && h != NULL) { /* 12 hr string formatting */
            sprintf(h, "%i", (atoi(h) % 12));
            sprintf(h, (m != NULL && s != NULL) ? "%s:" : "%s ", h);
            strcat(output, h);
            /* printf("%s", h); */
        }

        else if (dayfmt == 0 && h != NULL) {
            sprintf(h, "%i", (atoi(h)));
            sprintf(h, (m != NULL && s != NULL) ? "%s:" : "%s ", h);
            strcat(output, h);
            /* printf("%s", h);     */
            
        }
        
        if (m != NULL) {
            sprintf(m, s != NULL ? "%s:" : "%s - ", m);
            strcat(output, m);
            /* printf("%s", m); */
        }

        if (dayfmt == 1 && s != NULL) {
            sprintf(s, "%s %s" "%s", s, atoi(h) > 12? "PM":"AM", y != NULL ? " - ": "" );
            /* strcat(output, s); */
            printf("%s", s); 
        }

        else if (dayfmt == 0 && s != NULL) {
            sprintf(s, "%s" "%s", s, y != NULL ? " - ": "" );
            strcat(output, s);
            /* printf("%s", s); */
        }
        
        if (y != NULL)
            strcat(output, y);
            /* printf("%s", y); */
        
        strcat(output, "\0");

        printf("%s", output);
        printf("\r");
        memset(output, 0, strlen(output)); /* empty the string but preserve the allocated memory */
        //output = NULL; /* first NULL, so at next iteration the string would be zeroed */
        // free(output); /* the free the memory allocated before, since at each iteration we are mallocing new memory */
        /* TODO: Just allocate the memory at start, then each iteration set it to NULL, then free it. */
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    /* Resource Deallocation */
    free(output);
    free(wday);
    free(mon);
    free(day);
    free(h);
    free(m);
    free(s);
    free(y);

}


