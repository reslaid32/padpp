#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <padpp/PadderFactory.h>

using namespace padpp;

void
test_create_destroy(const std::string& name)
{
  auto padder = PadderFactory::instance().create(name);
  assert(padder && "Padder creation failed");
}

void
test_pad_unpad_simple(const std::string& name)
{
  auto padder = PadderFactory::instance().create(name);
  assert(padder);

  const std::string input_str = "ABC";
  std::vector<uint8_t> input(input_str.begin(), input_str.end());
  size_t block_size = 8;

  std::vector<uint8_t> padded;
  std::vector<uint8_t> unpadded;

  padder->pad(padded, input, block_size);

  assert(padded.size() % block_size == 0);

  padder->unpad(unpadded, padded, block_size);

  assert(unpadded.size() == input.size());
  assert(std::equal(unpadded.begin(), unpadded.end(), input.begin()));
}

void
test_pad_unpad_exact_block(const std::string& name)
{
  auto padder = PadderFactory::instance().create(name);
  assert(padder);

  const std::string input_str = "12345678";
  std::vector<uint8_t> input(input_str.begin(), input_str.end());
  size_t block_size = 8;

  std::vector<uint8_t> padded;
  std::vector<uint8_t> unpadded;

  padder->pad(padded, input, block_size);

  assert(padded.size() == input.size() + block_size);

  padder->unpad(unpadded, padded, block_size);

  assert(unpadded.size() == input.size());
  assert(std::equal(unpadded.begin(), unpadded.end(), input.begin()));
}

void
test_invalid_block_size(const std::string& name)
{
  auto padder = PadderFactory::instance().create(name);
  assert(padder);

  const std::string input_str = "123";
  std::vector<uint8_t> input(input_str.begin(), input_str.end());
  std::vector<uint8_t> padded;

  bool caught = false;
  try
  {
    padder->pad(padded, input, 0);
  }
  catch (const std::exception& e)
  {
    caught = true;
  }
  assert(caught && "Expected exception for block size 0");
}

void
perform_test(const std::string& name)
{
  std::cout << "[RUN] padder = " << name << "\n";

  std::cout << "[RUN] test_create_destroy\n";
  test_create_destroy(name);
  std::cout << "[OK]  test_create_destroy\n";

  std::cout << "[RUN] test_pad_unpad_simple\n";
  test_pad_unpad_simple(name);
  std::cout << "[OK]  test_pad_unpad_simple\n";

  std::cout << "[RUN] test_pad_unpad_exact_block\n";
  test_pad_unpad_exact_block(name);
  std::cout << "[OK]  test_pad_unpad_exact_block\n";

  std::cout << "[RUN] test_invalid_block_size\n";
  test_invalid_block_size(name);
  std::cout << "[OK]  test_invalid_block_size\n";

  std::cout << "All tests passed for padder: " << name << "\n\n";
}

int
main()
{
  perform_test("ansi923");
  perform_test("pkcs7");
  perform_test("iso9797_m2");

  return 0;
}
