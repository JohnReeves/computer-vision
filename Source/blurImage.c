#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	clock_t start = clock(); 
	FILE *fi = fopen("./images/lena512.bmp", "r");
	FILE *fo = fopen("./images/lena_blurred.bmp","wb");

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

  float v=1.0 / 9.0;											
  float kernel[3][3]={{v,v,v}, {v,v,v}, {v,v,v}};

	if (bitDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
	fwrite(header, sizeof(unsigned char), 54, fo); 

	fread(imageBuffer, sizeof(unsigned char), (height * width), fi);

// process image - ie blur each bit in the imageBuffer with a matrix
	for (int i = 0; i < height; i++){
	      for (int j = 0; j < width; j++){

 		     	float sum= 0.0;
		    	for(int x = -1; x <= 1; ++x) {
			  	  for(int y = -1; y <= 1; ++y) {
			  		  sum=\
              sum + (float)(kernel[x+1][x+1] * imageBuffer[(x+i) * width+(y+j)]);
			  	}
			  }
		  	imageOutput[i*width+j]=sum;
		 }
	}

	if (bitDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
	fwrite(imageOutput, sizeof(unsigned char), (height * width), fo);

	printf("Time: %2.3f ms\n",((double)(clock() - start) * 1000.0 )/ CLOCKS_PER_SEC);

	fclose(fo);
 	fclose(fi);
  return 0;
}
