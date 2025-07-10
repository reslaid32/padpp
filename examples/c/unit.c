#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <padpp-c/PadderFactory.h>

void
test_create_destroy(const char* padder_name)
{
  padpp_handle_t h = padpp_create(padder_name);
  assert(h != NULL);
  padpp_destroy(h);
}

void
test_pad_unpad_simple(const char* padder_name)
{
  const char* input = "ABC";
  size_t input_len = strlen(input);
  size_t block_size = 8;

  padpp_handle_t h = padpp_create(padder_name);
  assert(h != NULL);

  uint8_t padded[32] = { 0 };
  size_t padded_len = sizeof(padded);

  assert(padpp_pad(h, padded, &padded_len, (const uint8_t*) input, input_len,
                   block_size)
         == 0);
  assert(padded_len % block_size == 0);

  uint8_t unpadded[32] = { 0 };
  size_t unpadded_len = sizeof(unpadded);

  assert(padpp_unpad(h, unpadded, &unpadded_len, padded, padded_len, block_size)
         == 0);
  assert(unpadded_len == input_len);
  assert(memcmp(unpadded, input, input_len) == 0);

  padpp_destroy(h);
}

void
test_pad_unpad_exact_block(const char* padder_name)
{
  const char* input = "12345678";
  size_t input_len = strlen(input);
  size_t block_size = 8;

  padpp_handle_t h = padpp_create(padder_name);
  assert(h != NULL);

  uint8_t padded[32] = { 0 };
  size_t padded_len = sizeof(padded);

  assert(padpp_pad(h, padded, &padded_len, (const uint8_t*) input, input_len,
                   block_size)
         == 0);
  assert(padded_len == input_len + block_size);

  uint8_t unpadded[32] = { 0 };
  size_t unpadded_len = sizeof(unpadded);

  assert(padpp_unpad(h, unpadded, &unpadded_len, padded, padded_len, block_size)
         == 0);
  assert(unpadded_len == input_len);
  assert(memcmp(unpadded, input, input_len) == 0);

  padpp_destroy(h);
}

void
test_invalid_block_size(const char* padder_name)
{
  const char* input = "123";
  size_t input_len = strlen(input);
  uint8_t out[32];
  size_t out_len = sizeof(out);

  padpp_handle_t h = padpp_create(padder_name);
  assert(h != NULL);

  assert(padpp_pad(h, out, &out_len, (const uint8_t*) input, input_len, 0) != 0);

  padpp_destroy(h);
}

void
perform_test(const char* padder_name)
{
  printf("[RUN] padder = %s\n", padder_name);

  printf("[RUN] test_create_destroy\n");
  test_create_destroy(padder_name);
  printf("[OK]  test_create_destroy\n");

  printf("[RUN] test_pad_unpad_simple\n");
  test_pad_unpad_simple(padder_name);
  printf("[OK]  test_pad_unpad_simple\n");

  printf("[RUN] test_pad_unpad_exact_block\n");
  test_pad_unpad_exact_block(padder_name);
  printf("[OK]  test_pad_unpad_exact_block\n");

  printf("[RUN] test_invalid_block_size\n");
  test_invalid_block_size(padder_name);
  printf("[OK]  test_invalid_block_size\n");

  printf("All tests passed for padder: %s\n\n", padder_name);
}

int
main()
{
  perform_test("ansi923");
  perform_test("pkcs7");
  perform_test("iso9797_m2");

  return 0;
}
