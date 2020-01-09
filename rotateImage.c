#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	clock_t start = clock(); 
	FILE *fi = fopen("./images/lena512.bmp", "r");
	FILE *fo = fopen("./lena_rotated.bmp","wb");

 	unsigned char header[54];
	unsigned char colorTable[1024];

  if (fi == (FILE *)0) {
     printf("Error opening file.\n");
     exit(0);
 	}

 	for (int i=0; i<54; i++) {
 		header[i] = getc(fi);
 	}

 	int width = *(int*)&header[18];
 	int height = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];

	printf("width: %d\nheight: %d\n", width, height);
 	unsigned char imageBuffer[height * width];
 	unsigned char imageOutput[height * width];

	if (bitDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
	fwrite(header, sizeof(unsigned char), 54, fo); 

	fread(imageBuffer, sizeof(unsigned char), (height * width), fi);

// process image - ie rotate each bit in the imageBuffer
	for (int i = 0; i < height; i++){
	      for (int j = 0; j < width; j++){
         imageOutput[i*width + j] = imageBuffer[j*width + i]; 

		 }   
	}
	if (bitDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
	fwrite(imageOutput, sizeof(unsigned char), (height * width), fo);

	printf("Time: %lf ms\n",((double)(clock() - start) * 1000.0 )/ CLOCKS_PER_SEC);

	fclose(fo);
 	fclose(fi);
  return 0;
}
