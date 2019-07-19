/* quotes.c - Random quote program.  Must be passed a file with quotes
              separated by lines with "%" on them, and a "!" line as the
              last line of the file.
     [Rob Seace]
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define LINELEN 81
#define IS ==
#define ISNT !=
#define AND &&
#define OR ||


void main (argc, argv)
    int  argc;
    char *argv[];
{
    int num, i;
    struct stat buf;
    FILE *fp;

    if (argc < 2) {
        fprintf (stderr, "\nUsage: %s <quote_file>\n\n", argv[0]);
        exit (-1);
    }

    stat (argv[1], &buf);
    if ((fp = fopen (argv[1], "r")) IS NULL) {
        fprintf (stderr, "\nCan't open quotes file (%s) for reading!\n\n", argv[1]);
        exit (-1);
    }

    rand_quote (fp, buf.st_size);

    fclose (fp);
    exit (0);
}

/* This function gets a random quote from the given filename, and prints it
out to the screen... */

int rand_quote (fp, size)
    FILE *fp;
    long size;
{
    char line[LINELEN+1];
    long r;

    srand((unsigned) time(NULL) << 8);

    if (size > 0L) {
        r = (long)rand() % size;
        fseek (fp, r, 0);
    } else {
        printf ("The file is empty!\n");
        return;
    }

    if (fgets (line, LINELEN, fp) IS NULL) {  /* EOF */
        line[0] = '!';
    } else {
        while (line[0] ISNT '%' AND line[0] ISNT '!') {
            if (fgets (line, LINELEN, fp) IS NULL) {
                line[0] = '!';
                break;
            }
        }
    }

    if (line[0] IS '!')
        fseek (fp, 0L, 0);

    if (fgets (line, LINELEN, fp) IS NULL) {
        fprintf (stderr, "Unexpected EOF!\n");
        return;
    }

    while (line[0] ISNT '%' AND line[0] ISNT '!') {
        printf ("%s", line);
        if (fgets (line, LINELEN, fp) IS NULL)
            break;
    }
}

