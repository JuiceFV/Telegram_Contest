#include "html.hpp"
#include "parser.h"

int main(int argc, char **argv) {
  std::string filepath(
      "D:\\Projects\\Telegram_Contest\\data_1\\20191102\\08\\7659932528100305."
      "html");
  html test(filepath);
  std::cout << test.get_body_tag().title << std::endl;
  std::cout << std::endl << test.get_body_tag().passage << std::endl;

  system("pause");
  return (0);
}
