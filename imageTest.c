// imageTest - A program that performs some image processing.
//
// This program is an example use of the image8bit module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// João Manuel Rodrigues <jmr@ua.pt>
// 2023

#include <assert.h>
#include <errno.h>
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image8bit.h"
#include "instrumentation.h"

//variaveis globais
#define PIXMEM InstrCount[0]
#define PCOMP InstrCount[1]

int main(int argc, char* argv[]) {
  program_name = argv[0];
  /*
  if (argc != 3) {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }
  */

  // Try changing the behaviour of the program by commenting/uncommenting
  // the appropriate lines.

  //declarar variaveis
  int px, py;

  //testar a função Blur
  //ciclo para iterar sobre os vários argumentos
  for (int i = 1; i < argc; i++) {
    ImageInit();

    printf("===============================================================\n");
    printf("# LOAD image\n");
    InstrReset(); // to reset instrumentation
    Image img1 = ImageLoad(argv[1]);
    int pix = PIXMEM;
    if (img1 == NULL) {
      error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
    }
    InstrPrint(); // to print instrumentation

    Image cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));
    
    printf("\n===============================================================");
    /*
    //testar a função blur não otimizada
    printf("\n# Teste da função Blur não otimizada\n");

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_Old image (size: %d - window 7x7)\n", pix);
    ImageBlurOld(cp1, 7, 7);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_Old image (size: %d - window 50x50)\n", pix);
    ImageBlurOld(cp1, 50, 50);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_Old image (size: %d - window 100x100)\n", pix);
    ImageBlurOld(cp1, 100, 100);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_Old image (size: %d - window 200x200)\n", pix);
    ImageBlurOld(cp1, 200, 200);
    InstrPrint();

    printf("\n===============================================================");
    */
    //testar a função blur otimizada
    printf("\n# Teste da função Blur otimizada\n");

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_otimizado image (size: %d - window 7x7)\n", pix);
    ImageBlur(cp1, 7, 7);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_otimizado image (size: %d - window 50x50)\n", pix);
    ImageBlur(cp1, 50, 50);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_otimizado image (size: %d - window 100x100)\n", pix);
    ImageBlur(cp1, 100, 100);
    InstrPrint();

    cp1 = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));

    InstrReset(); // to reset instrumentation
    printf("\n# BLUR_otimizado image (size: %d - window 200x200)\n", pix);
    ImageBlur(cp1, 200, 200);
    InstrPrint();
    
    
    printf("\n===============================================================\n");
    
   
    //testar a função ImageLocateSubImage
    printf("# Teste da função ImageLocateSubImage\n");

    //criar uma imagem branca com o pixel ultimo pixel preto
    Image branca = ImageCrop(img1, 0, 0, ImageWidth(img1), ImageHeight(img1));
    ImageThreshold(branca, 0);

    //ciclo para criar varias janelas e testar a função
    for (int width = 350; width < ImageWidth(branca); width+=100) {
      //criar uma janela para o melhor cenário
      Image subBest = ImageCrop(branca, 0, 0, width, width);

      //criar uma janela para o pior cenário
      Image subWorst = ImageCrop(branca, 0, 0, width, width);
      ImageSetPixel(subWorst, ImageWidth(subWorst)-1, ImageHeight(subWorst)-1, 0);

      InstrReset(); // to reset instrumentation
      printf("\n# IMAGELOCATESUBIMAGE BEST CASE %dx%d (size: %d)\n", ImageWidth(branca), ImageWidth(branca), width);
      ImageLocateSubImage(branca, &px, &py, subBest);
      InstrPrint();

      InstrReset(); // to reset instrumentation
      printf("\n# IMAGELOCATESUBIMAGE WORST CASE %dx%d (size: %d)\n", ImageWidth(branca), ImageWidth(branca), width);
      ImageLocateSubImage(branca, &px, &py, subWorst);
      InstrPrint();

      printf("\n");

      //destruir as imagens
      ImageDestroy(&subBest);
      ImageDestroy(&subWorst);
    }
    
    //destruir as imagens
    ImageDestroy(&img1);
    ImageDestroy(&cp1);
    ImageDestroy(&branca);
  }

  printf("===============================================================\n");
  
  /*
  //img2 = ImageCrop(img1, ImageWidth(img1)/4, ImageHeight(img1)/4, ImageWidth(img1)/2, ImageHeight(img1)/2);
  Image img2 = ImageRotate(img1);
  if (img2 == NULL) {
    error(2, errno, "Rotating img2: %s", ImageErrMsg());
  }

  //ImageNegative(img2);
  //ImageThreshold(img2, 100);
  ImageBrighten(img2, 1.3);

  if (ImageSave(img2, argv[2]) == 0) {
    error(2, errno, "%s: %s", argv[2], ImageErrMsg());
  }

  ImageDestroy(&img1);
  ImageDestroy(&img2);
  */
  return 0;
}

