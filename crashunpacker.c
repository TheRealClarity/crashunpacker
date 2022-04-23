#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct pasc
{
    unsigned a : 7;
    unsigned b : 7;
    unsigned c : 7;
    unsigned d : 7;
    unsigned e : 7;
    unsigned f : 7;
    unsigned g : 7;
    unsigned h : 7;
} __attribute__((packed));

void unpackA(char *, uint32_t);
typedef struct pasc pasc_t;

void unpackA(char *inbuf, uint32_t length)
{
    pasc_t packs;
    unsigned i = 0;
    length = (length * 8) / 7;
    while (i < length)
    {
        packs = *(pasc_t *)&inbuf[i];
        bcopy(&inbuf[i + 7], &inbuf[i + 8], MAX(0, (int)(length - i - 8)));
        inbuf[i++] = packs.a;
        inbuf[i++] = packs.b;
        inbuf[i++] = packs.c;
        inbuf[i++] = packs.d;
        inbuf[i++] = packs.e;
        inbuf[i++] = packs.f;
        inbuf[i++] = packs.g;
        inbuf[i++] = packs.h;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        perror("Failed to open file");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    uint32_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(size + 1);
    fread(buffer, size, 1, f);
    fclose(f);
    unpackA(buffer, size);
    printf("%s\n", buffer);
    return 0;
}