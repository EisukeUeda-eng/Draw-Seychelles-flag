// Input/output functions for PGM grayscale images
int save_pgm(char *filename, unsigned char *image, int width, int height);
int load_pgm(char *filename, unsigned char **image, int *width, int *height);

// Input/output functions for PPM color images
int save_ppm(char *filename, unsigned char *red, unsigned char *grn, unsigned char *blu, int width, int height);
int load_ppm(char *filename, unsigned char **red, unsigned char **grn, unsigned char **blu, int *width, int *height);
