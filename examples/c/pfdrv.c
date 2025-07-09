#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <padpp-c/PadderFactory.h>

int
padpp_factory_driver(const char* name)
{
  printf("Running factory driver with %s\n", name);

  padpp_handle_t padder = padpp_create(name);

  if (!padder)
  {
    fprintf(stderr, "Failed to create padder context\n");
    return 1;
  }

  const char* message = "Hello\n";
  const size_t block_size = 16;

  uint8_t padded[64];
  size_t padded_len = sizeof(padded);

  int pad_result = padpp_pad(padder, padded, &padded_len, (const uint8_t*) message,
                             strlen(message), block_size);

  if (pad_result != 0)
  {
    fprintf(stderr, "Padding failed: error code %d\n", pad_result);
    padpp_destroy(padder);
    return 1;
  }

  printf("Padded (%zu bytes): ", padded_len);
  for (size_t i = 0; i < padded_len; ++i)
    printf("%02x ", padded[i]);
  printf("\n");

  uint8_t unpadded[64];
  size_t unpadded_len = sizeof(unpadded);

  int unpad_result = padpp_unpad(padder, unpadded, &unpadded_len, padded,
                                 padded_len, block_size);

  if (unpad_result != 0)
  {
    fprintf(stderr, "Unpadding failed: error code %d\n", unpad_result);
    padpp_destroy(padder);
    return 1;
  }

  printf("Unpadded (%zu bytes): ", unpadded_len);
  fwrite(unpadded, 1, unpadded_len, stdout);
  printf("\n");

  padpp_destroy(padder);
  return 0;
}

int
main(void)
{
  padpp_factory_driver("ansi923");
  padpp_factory_driver("pkcs7");
  padpp_factory_driver("iso9797_m1");
  padpp_factory_driver("iso9797_m2");

  return 0;
}
