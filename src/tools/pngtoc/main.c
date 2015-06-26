#include "lodepng.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
  unsigned char* png = NULL;
  unsigned char* image = NULL;
  FILE* file = NULL;

  unsigned error = 0;

  if(argc > 1)
  {
    size_t pngsize = 0;

    lodepng_load_file(&png, &pngsize, argv[1]);

    unsigned width = 0;
    unsigned height = 0;

    error = lodepng_decode32(&image, &width, &height, png, pngsize);

    if(error == 0)
    {
      char filename[1024];
      strcpy(filename, argv[1]);
      strcat(filename, ".c");
      file = fopen(filename, "w");

      if(file != NULL)
      {
        strcpy(filename, argv[1]);

        int i = 0;
        for(i = 0; i < strlen(filename); i++)
        {
          if(filename[i] == '.')
          {
            filename[i] = '_';
          }
        }

        char val[1024];
        memset(val, 0, sizeof(val));

        sprintf(val, "%i", width);
        fputs("int ", file);
        fputs(filename, file);
        fputs("_width = ", file);
        fputs(val, file);
        fputs(";\n", file);

        memset(val, 0, sizeof(val));

        sprintf(val, "%i", height);
        fputs("int ", file);
        fputs(filename, file);
        fputs("_height = ", file);
        fputs(val, file);
        fputs(";\n", file);

        fputs("char ", file);
        fputs(filename, file);
        fputs("_data[] = {", file);

        char* sep = "";

        int yxc = 0;
        int y = 0;
        for(y = 0; y < height; y++)
        {
          int x = 0;
          for(x = 0; x < width; x++)
          {
            int c = 0;
            for(c = 0; c < 4; c++)
            {
              fputs(sep, file);
              sep = ",";
              memset(val, 0, sizeof(val));
              sprintf(val, "%i", image[yxc]);
              fputs(val, file);

              yxc++;
            }
          }
        }

        fputs("};", file);
      }
      else
      {
        printf("Error: Failed to open output file '%s'\n", filename);
        error = 1;
      }
    }
    else
    {
      printf("Error %u: %s\n", error, lodepng_error_text(error));
    }
  }
  else
  {
    printf("Usage: %s <pngfile>\n", argv[0]);
  }

  if(png) free(png);
  if(image) free(image);
  if(file) fclose(file);

  return error;
}
