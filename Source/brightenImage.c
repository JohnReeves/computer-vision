#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int main(int argc, char *argv[]) {
	clock_t start = clock(); 
	FILE *fi = fopen("./images/lena512.bmp", "r");
	FILE *fo = fopen("./images/lena_brightened.bmp","wb");
  int threshold = 100;

 	unsigned char header[54];
	unsigned char colorTable[1024];

  if (fi == (FILE *)0) {
     printf("Error opening file.\n");
     exit(0);
 	}

  fread(header, sizeof(unsigned char), 54, fi);

 	int width = *(int*)&header[18];
 	int height = *(int*)&header[22];
	int colorDepth = *(int*)&header[28];

	printf("width: %d\nheight: %d\ncolor depth: %d\n", width, height, colorDepth);
 	unsigned char imageBuffer[height * width];

	if (colorDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
	fread(imageBuffer, sizeof(unsigned char), (height * width), fi);

  // process image - ie brighten each pixel in the imageBuffer
	for (int i = 0; i < height; i++){
	  for (int j = 0; j < width; j++){                   
		  if ((imageBuffer[i*width + j] + threshold) < 255) 
		    imageBuffer[i*width + j] += threshold; 
      else
        imageBuffer[i*width + j] = 255; 
		 }   
	}

  fwrite(header, sizeof(unsigned char), 54, fo); 
	if (colorDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
	fwrite(imageBuffer, sizeof(unsigned char), (height * width), fo);

	printf("Time: %2.3f ms\n",((double)(clock() - start) * 1000.0 )/ CLOCKS_PER_SEC);

	fclose(fo);
 	fclose(fi);
  return 0;
}
