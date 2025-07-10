#include "padpp-c/Pkcs7BytePadder.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <padpp-c/Padders.h>

int
main(void)
{
  padpp_handle_t padder = padpp_create_pkcs7();
  if (!padder)
  {
    fprintf(stderr, "Failed to create padder context\n");
    return 1;
  }

  const char* message = "Hello\n";
  const size_t block_size = 16;

  // Prepare buffers
  uint8_t padded[64];
  size_t padded_len = sizeof(padded);

  int pad_result =
      padpp_pad_pkcs7(padder, padded, &padded_len, (const uint8_t*) message,
                      strlen(message), block_size);

  if (pad_result != 0)
  {
    fprintf(stderr, "Padding failed: error code %d\n", pad_result);
    padpp_destroy_pkcs7(padder);
    return 1;
  }

  printf("Padded (%zu bytes): ", padded_len);
  for (size_t i = 0; i < padded_len; ++i)
    printf("%02x ", padded[i]);
  printf("\n");

  // Unpad
  uint8_t unpadded[64];
  size_t unpadded_len = sizeof(unpadded);

  int unpad_result = padpp_unpad_pkcs7(padder, unpadded, &unpadded_len, padded,
                                       padded_len, block_size);

  if (unpad_result != 0)
  {
    fprintf(stderr, "Unpadding failed: error code %d\n", unpad_result);
    padpp_destroy_pkcs7(padder);
    return 1;
  }

  printf("Unpadded (%zu bytes): ", unpadded_len);
  fwrite(unpadded, 1, unpadded_len, stdout);
  printf("\n");

  padpp_destroy_pkcs7(padder);
  return 0;
}
