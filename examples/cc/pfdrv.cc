#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <padpp/PadderFactory.h>

int
padpp_factory_driver(const std::string& name)
{
  std::cout << "Running factory driver with " << name << "\n";

  std::unique_ptr<padpp::IBytePadder> padder =
      padpp::PadderFactory::instance().create(name);
  if (!padder)
  {
    std::cerr << "Failed to create padder context\n";
    return 1;
  }

  const std::string message = "Hello\n";
  const size_t block_size = 16;

  std::vector<uint8_t> input(message.begin(), message.end());
  std::vector<uint8_t> padded;
  std::vector<uint8_t> unpadded;

  try
  {
    padder->pad(padded, input, block_size);

    std::cout << "Padded (" << padded.size() << " bytes): ";
    for (uint8_t b : padded)
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) b << " ";
    std::cout << std::dec << "\n";

    padder->unpad(unpadded, padded, block_size);

    std::cout << "Unpadded (" << static_cast<uint64_t>(unpadded.size())
              << " bytes): ";
    std::cout.write(reinterpret_cast<char*>(unpadded.data()), unpadded.size());
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

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
