#ifdef USE_LIBPNG

#include "pngwrapper.h"

#include <png.h>

#include <vector>
#include <memory>
#include <functional>
#include <iostream>

struct PngWrapperData
{
  int id;
  std::vector<GLbyte> data;
  int width;
  int height;
  int stride;

};

std::vector<PngWrapperData*> pngwrapper_datas;
int pngwrapper_nextid = 1;

void pngwrapper_freerows(png_bytep* rows, int height)
{
  for (int y = 0; y < height; y++)
  {
    if(rows[y] != NULL)
    {
      free(rows[y]);
    }
  }

  free(rows);
}

void pngwrapper_freereadstruct(png_structp png_ptr, png_infop info_ptr)
{
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}

PngWrapperData* pngwrapper_getdata(int pngId)
{
  for(int i = 0; i < pngwrapper_datas.size(); i++)
  {
    if(pngwrapper_datas.at(i)->id == pngId)
    {
      return pngwrapper_datas.at(i);
    }
  }

  return NULL;
}

int pngwrapper_load(std::string path)
{
  std::unique_ptr<PngWrapperData> pngData;

  FILE* fp = NULL; std::shared_ptr<void> _fp;
  png_structp png_ptr; png_infop info_ptr; std::shared_ptr<void> _png_ptr;
  png_bytep* row_pointers; std::shared_ptr<void> _row_pointers;
  char header[8];

#ifdef _MSC_VER
  fopen_s(&fp, path.c_str(), "rb");
#else
  fp = fopen(path.c_str(), "rb");
#endif

  if (!fp)
  {
    return 0;
  }

  _fp.reset(&fp, std::bind(fclose, fp));
  fread(header, 1, 8, fp);

  if (png_sig_cmp((png_bytep)header, 0, 8))
  {
    return 0;
  }

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
  {
    return 0;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr)
  {
    // HACK: Cannot change deleter and it needs to change for info struct cleanup.
    _png_ptr.reset(&png_ptr, std::bind(pngwrapper_freereadstruct, png_ptr, (png_infop)NULL));
    return 0;
  }

  _png_ptr.reset(&png_ptr, std::bind(pngwrapper_freereadstruct, png_ptr, info_ptr));

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    return 0;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);
  pngData.reset(new PngWrapperData());

  pngData->width = png_get_image_width(png_ptr, info_ptr);
  pngData->height = png_get_image_height(png_ptr, info_ptr);

  png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    return 0;
  }

  row_pointers = (png_bytep*)calloc(pngData->height, sizeof(png_bytep));

  _row_pointers.reset(&row_pointers, std::bind(pngwrapper_freerows, row_pointers, pngData->height));

  for (int y = 0; y < pngData->height; y++)
  {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
  }

  png_read_image(png_ptr, row_pointers);
  pngData->stride = 4;

  if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA &&
      png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB)
  {
    return 0;
  }

  if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
  {
    pngData->stride = 3;
  }

  pngData->data = std::vector<GLbyte>(pngData->height * pngData->width * pngData->stride);
  int c = 0;

  for (int y = 0; y < pngData->height; y++)
  {
    png_byte* row = row_pointers[y];

    for (int x = 0; x < pngData->width; x++)
    {
      png_byte* ptr = &(row[x*pngData->stride]);

      pngData->data[c] = ptr[0]; c++;
      pngData->data[c] = ptr[1]; c++;
      pngData->data[c] = ptr[2]; c++;

      if(pngData->stride == 4)
      {
        pngData->data[c] = ptr[3]; c++;
      }
    }
  }

  pngData->id = pngwrapper_nextid;
  pngwrapper_datas.push_back(pngData.get());
  pngwrapper_nextid++;

  return pngData.release()->id;
}

void pngwrapper_unload(int id)
{
  for(int i = 0; i < pngwrapper_datas.size(); i++)
  {
    if(pngwrapper_datas.at(i)->id == id)
    {
      pngwrapper_datas.erase(pngwrapper_datas.begin() + i);
      i--;
    }
  }
}

int pngwrapper_width(int id)
{
  for(int i = 0; i < pngwrapper_datas.size(); i++)
  {
    if(pngwrapper_datas.at(i)->id == id)
    {
      return pngwrapper_datas.at(i)->width;
    }
  }

  return 0;
}

int pngwrapper_height(int id)
{
  for(int i = 0; i < pngwrapper_datas.size(); i++)
  {
    if(pngwrapper_datas.at(i)->id == id)
    {
      return pngwrapper_datas.at(i)->height;
    }
  }

  return 0;
}

int pngwrapper_poweroftwo(int input)
{
  input--;
  input |= input >> 1;
  input |= input >> 2;
  input |= input >> 4;
  input |= input >> 8;
  input |= input >> 16;
  input++;

  return input;
}

void pngwrapper_texture(int id)
{
  PngWrapperData* pngData = NULL;

  for(int i = 0; i < pngwrapper_datas.size(); i++)
  {
    if(pngwrapper_datas.at(i)->id == id)
    {
      pngData = pngwrapper_datas.at(i);
      break;
    }
  }

  if(pngData == NULL)
  {
    return;
  }

  int sampleWidth = pngData->width;
  int sampleHeight = pngData->height;

  sampleWidth = pngwrapper_poweroftwo(pngData->width);
  sampleHeight = pngwrapper_poweroftwo(pngData->height);

  std::cout << sampleWidth << " " << sampleHeight << std::endl;

  std::vector<GLbyte> imageBytes(sampleHeight * sampleWidth * pngData->stride);

  double scaleWidth =  (double)sampleWidth / (double)pngData->width;
  double scaleHeight = (double)sampleHeight / (double)pngData->height;

  for(int cy = 0; cy < sampleHeight; cy++)
  {
    for(int cx = 0; cx < sampleWidth; cx++)
    {
      int pixel = (cy * (sampleWidth * pngData->stride)) + (cx*pngData->stride);
      int nearestMatch =  (((int)(cy / scaleHeight) * (pngData->width * pngData->stride)) + ((int)(cx / scaleWidth) * pngData->stride) );
      imageBytes[pixel    ] =  pngData->data[nearestMatch    ];
      imageBytes[pixel + 1] =  pngData->data[nearestMatch + 1];
      imageBytes[pixel + 2] =  pngData->data[nearestMatch + 2];

      if(pngData->stride == 4)
      {
        imageBytes[pixel + 3] =  pngData->data[nearestMatch + 3];
      }
    }
  }

  if(pngData->stride == 4)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sampleWidth, sampleHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageBytes[0]);
  }
  else
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sampleWidth, sampleHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageBytes[0]);
  }
}
#endif
