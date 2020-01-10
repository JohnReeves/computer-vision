# Image processing in plain c

## Input, Processing and Output

Processing images is surprisingly easy:   

* `Open` the image files;   

```c
  FILE *fi = fopen("./images/picture.bmp", "r");
  FILE *fo = fopen("./images/inverted.bmp", "wb");
```

* `Read` the image description;  

```c
 	unsigned char header[54];
  unsigned char colorTable[1024];

  if (fi == (FILE *)0) {
     printf("Error opening file.\n");
     exit(0);
 	}

 	for (int i=0; i<54; i++) header[i] = getc(fi);

 	int width = *(int*) &header[18];
 	int height = *(int*) &header[22];
  int bitDepth = *(int*) &header[28];
```

* `Read` the image given by the description;  

```c
 	unsigned char imageBuffer[height * width];

  if (bitDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
  fread(imageBuffer, sizeof(unsigned char), (height * width), fi);
```
* `Change` each pixel in the image;   

For example, invert each bit in the imageBuffer by subtracting from 255:
```c
 	unsigned char imageOutput[height * width];

  for (int i = 0; i < height; i++){
	      for (int j = 0; j < width; j++){
          imageOutput[i*width + j] = 255 - imageBuffer[i*width + j]; 
		 }
	}
```
* `Write` the new image to a file.   

```c
  fwrite(header, sizeof(unsigned char), 54, fo);

  if (bitDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
  fwrite(imageOutput, sizeof(unsigned char), (height * width), fo);
```

* `Close` the files;   

```c
  fclose(fo);
 	fclose(fi);
```

`NB:` There is lots more information in the links below!

## Examples

* copy image;   
* invert the pixels;   
* rotate the image;   
* threshold the pixels;   
* blur using a `Gaussian` kernel;   
* edge detection using a `Laplace` kernel;   

[wiki on computer vision](https://en.wikipedia.org/wiki/Feature_detection_(computer_vision)) .  
[wiki on Gaussian kernels](https://en.wikipedia.org/wiki/Gaussian_blur) .  
[wiki on Edge detection](https://en.wikipedia.org/wiki/Edge_detection) .  

## Art and Technology

[SailorHg](https://twitter.com/sailorhg) .  
[Pixel Perfect](https://shop.bubblesort.io/) .  


## Image formats

[Bitmap Images](http://www.fastgraph.com/help/bmp_header_format.html) .  
[The Book](http://adaptiveart.eecs.umich.edu/2011/wp-content/uploads/2011/09/The-pocket-handbook-of-image-processing-algorithms-in-C.pdf) .  
[Another Book](http://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/cips2ed.pdf) .  
[Harder description](http://paulbourke.net/dataformats/bitmaps/) .  


## Remember our computer science history   
[Losing Lena](https://www.losinglena.com/)

.

