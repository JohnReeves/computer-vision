# Image processing in plain c

Processing images as they do in Photoshop is really quite easy.   

Images are made of a sequence of pixels that draw out a picture when arranged in the correct height and width, and with the correct colours or shades of grey.

So as well as the pixels making up the picture, there is also a description of the picture - letting you know the height and width to draw the picture, and perhaps the palette to use to colour the picture. 

The steps for processing an image are:   
1. open the image file;   
2. read the description;   
3. read the picture;   
4. change each pixel;   
5. write the changed pixels to the image file;   

You can get good image effects with about 25 lines of code - the code below is for a bitmap image and the links below have other image formats and other effects!


## Input, Processing and Output

### `Open` the image files   

```c
FILE *fi = fopen("./images/picture.bmp", "r");
FILE *fo = fopen("./images/inverted.bmp", "wb");

if (fi == (FILE *)0) {
  printf("Error opening file.\n");
  exit(0);
}
```

### `Read` the image description  

```c
unsigned char header[54];
unsigned char colorTable[1024];

fread(header, sizeof(unsigned char), 54, fi);

int width = *(int*) &header[18];
int height = *(int*) &header[22];
int colorDepth = *(int*) &header[28];
```

### `Read` the image given by the description  

```c
unsigned char imageBuffer[height * width];

if (colorDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, fi);
fread(imageBuffer, sizeof(unsigned char), (height * width), fi);
```

### `Change` each pixel in the image   

For example, invert each bit in the imageBuffer by subtracting from 255:
```c
unsigned char imageOutput[height * width];

for (int i = 0; i < height; i++){
  for (int j = 0; j < width; j++){
    imageOutput[i*width + j] = 255 - imageBuffer[i*width + j]; 
  }
}
```

### `Write` the new image to a file   

```c
fwrite(header, sizeof(unsigned char), 54, fo);
if (colorDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);
fwrite(imageOutput, sizeof(unsigned char), (height * width), fo);
```

### `Close` the files;   

```c
fclose(fo);
fclose(fi);
```

`NB:` There is lots more information in the links below!

## Examples

* copy a greyscale image;   
* invert the pixels;   
* rotate the image;   
* threshold the pixels;   
* blur using a Gaussian kernel;   
* edge detection using a Laplace kernel;   
* brighten image;  
* redden a colour image;    

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

[Finding Lena](https://www.wired.com/story/finding-lena-the-patron-saint-of-jpegs/) .  
[Losing Lena](https://www.losinglena.com/) .  
[Experiencing Lena](https://www.cmc.edu/news/every-picture-tells-a-story) .  
[Image Reconstruction with Fabio](https://arxiv.org/pdf/1202.6429.pdf) .  

.

