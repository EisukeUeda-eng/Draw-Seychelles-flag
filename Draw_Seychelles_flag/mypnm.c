#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mypnm.h"

#define BUFSIZE 1024

// Save a PGM file
int save_pgm(char *filename, unsigned char *image, int width, int height)
{
    FILE *fp;

    if((fp = fopen(filename,"wb")) == NULL) {
        fprintf(stderr, "cannot open output PGM file");
        return -1;
    }
    fprintf(fp, "P5\n%d %d\n255\n", width, height);    // Output header
    fwrite(image, sizeof(char), (size_t)width * height, fp);
    fclose(fp);
    return 0;
}

// Load a PGM file
int load_pgm(char *filename, unsigned char **img, int *width, int *height)
{
    FILE *fp;
    char buff[BUFSIZE], magic[BUFSIZE];
    int maxlevel, imgsize;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open %s\n", filename);
        return -1;
    }

    fgets(buff, BUFSIZE, fp);
    sscanf(buff, "%s", magic);
    if (strncmp(magic, "P5", 2)) {    // Check identifier
        fprintf(stderr, "Error: %s is not raw pgm format!\n", filename);
        return -1;
    }
    
    fgets(buff, BUFSIZE, fp);
    while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    // Skip comments
    sscanf(buff, "%d %d", width, height);    // Get image size
    imgsize = (*width) * (*height);
    
    fgets(buff, BUFSIZE, fp);
    while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    // Skip comments
    sscanf(buff, "%d", &maxlevel);    // Get brightness level

    (*img) = (unsigned char *)malloc(imgsize);    // Allocate memory for image
    if(*img == NULL) {
        fprintf(stderr, "Error: cannot allocate image memory");
        fclose(fp);
        return -1;
    }
    
    fread(*img, sizeof(char), (size_t)(imgsize), fp);    // Read data
    
    fclose(fp);
    return 0;
}

// Save a PPM file
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height)
{
    int i;
    FILE *fp;
    unsigned char *image;

    if((fp = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "cannot open output PPM file");
        return -1;
    }
    fprintf(fp, "P6\n%d %d\n255\n", width, height);    // Output header

    image = (unsigned char *)malloc(width * height * 3);
    for(i = 0; i < width * height; i++) {
        image[i * 3] = red[i];
        image[i * 3 + 1] = grn[i];
        image[i * 3 + 2] = blu[i];
    }

    fwrite(image, sizeof(char), (size_t)width * height * 3, fp);
    fclose(fp);
    return 0;
}

// Load a PPM file
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height)
{
    int i;
    FILE *fp;
    char buff[BUFSIZE], magic[BUFSIZE];
    int maxlevel, imgsize;
    unsigned char *img; // Temporary storage for image data

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open %s\n", filename);
        return -1;
    }

    fgets(buff, BUFSIZE, fp);
    sscanf(buff, "%s", magic);
    if (strncmp(magic, "P6", 2)) {    // Check identifier
        fprintf(stderr, "Error: %s is not raw ppm format!\n", filename);
        return -1;
    }
    
    fgets(buff, BUFSIZE, fp);
    while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    // Skip comments
    sscanf(buff, "%d %d", width, height);    // Get image size
    imgsize = (*width) * (*height);
    
    fgets(buff, BUFSIZE, fp);
    while (buff[0] == '#') fgets(buff, BUFSIZE, fp);    // Skip comments
    sscanf(buff, "%d", &maxlevel);    // Get brightness level

    img = (unsigned char *)malloc(imgsize * 3);
    if(img == NULL) {
        fprintf(stderr, "Error: cannot allocate image memory");
        fclose(fp);
        return -1;
    }
    fread(img, sizeof(char), (size_t)(imgsize * 3), fp);    // Read data
    fclose(fp);

    // Rearrange into RGB
    (*red) = (unsigned char *)malloc(imgsize);    // Allocate memory for image
    (*grn) = (unsigned char *)malloc(imgsize);    // Allocate memory for image
    (*blu) = (unsigned char *)malloc(imgsize);    // Allocate memory for image
    if(*red == NULL || *grn == NULL || *blu == NULL) {
        fprintf(stderr, "Error: cannot allocate image memory");
        fclose(fp);
        return -1;
    }

    for(i = 0; i < imgsize; i++) {
        (*red)[i] = img[i * 3];
        (*grn)[i] = img[i * 3 + 1];
        (*blu)[i] = img[i * 3 + 2];
    }

    return 0;
}
