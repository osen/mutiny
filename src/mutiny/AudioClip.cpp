#include "AudioClip.h"
#include "Application.h"
#include "internal/platform.h"
#include "Debug.h"

#include <vorbis/vorbisfile.h>
#include <AL/al.h>

#ifdef USE_OPENAL
  #define BUFFER_SIZE 32768 // 32 KB buffers
#endif

namespace mutiny
{

namespace engine
{

#ifdef USE_OPENAL
void LoadOGG(char *fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
  int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
  int bitStream = 0;
  long bytes = 0;
  char array[BUFFER_SIZE] = {}; // Local fixed size array
  FILE *f = NULL;

  // Open for binary reading
  f = fopen(fileName, "rb");

  if(f == NULL)
  {
    throw Exception("Failed to open audio file");
  }

  vorbis_info *pInfo = NULL;
  OggVorbis_File oggFile = {};

  // Try opening the given file
  if(ov_open(f, &oggFile, NULL, 0) != 0)
  {
    throw Exception("Failed to open audio file for decoding");
  }

  // Get some information about the OGG file
  pInfo = ov_info(&oggFile, -1);

  // Check the number of channels... always use 16-bit samples
  if(pInfo->channels == 1)
    format = AL_FORMAT_MONO16;
  else
    format = AL_FORMAT_STEREO16;

  // The frequency of the sampling rate
  freq = pInfo->rate;

  // Keep reading until all is read
  do
  {
    // Read up to a buffer's worth of decoded sound data
    bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

    if(bytes < 0)
    {
      ov_clear(&oggFile);
      throw Exception("Error decoding ");
    }

    // Append to end of buffer
    buffer.insert(buffer.end(), array, array + bytes);
  }
  while (bytes > 0);

  // Clean up!
  ov_clear(&oggFile);
}
#endif

ref<AudioClip> AudioClip::load(std::string path)
{
  ref<AudioClip> audioClip = new AudioClip();
#ifdef USE_SDL
  audioClip->data = Chunk::LoadWAV(path + ".ogg");
#endif

  return audioClip;
}

}

}

