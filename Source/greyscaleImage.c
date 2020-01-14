#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	clock_t start = clock(); 
	FILE *fi = fopen("./images/lena_color.bmp", "r");
	FILE *fo = fopen("./images/lena_greyscale.bmp","wb");

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
 	unsigned char imageBuffer[height * width * 3];
 	unsigned char imageOutput[height * width];

	if (colorDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
	fread(imageBuffer, sizeof(unsigned char), (height * width * 3), fi);

  // process image - ie invert each bit in the imageBuffer
	for (int i = 0; i < height; i++){
	  for (int j = 0; j < width; j++){
      imageOutput[(i*width + j)] = 0;

      for (int k = 0; k < 3; k++){
        if (k == 0)
		      imageOutput[(i*width + j)] =\
          0.3*imageBuffer[3*(i*width + j) + k];
        else if (k == 1)
		      imageOutput[(i*width + j)] +=\
          0.59 * imageBuffer[3*(i*width + j) + k];
        else
		      imageOutput[(i*width + j)] +=\
          0.11 * imageBuffer[3*(i*width + j) + k];              
      }
  	}
	}

	fwrite(header, sizeof(unsigned char), 54, fo); 
	if (colorDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
	fwrite(imageOutput, sizeof(unsigned char), (height * width * 3), fo);

	printf("Time: %2.3f ms\n",((double)(clock() - start) * 1000.0 )/ CLOCKS_PER_SEC);

	fclose(fo);
 	fclose(fi);
  return 0;
}
