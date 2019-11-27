#include <Windows.h>

#include "html.hpp"
#include "parser.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "ru");
  std::string filepath(
      "D:\\Projects\\Telegram_Contest\\parser\\data_"
      "1\\20191101\\00\\993065305003958.html");
  html test(filepath);
  std::cout << test.get_body_tag().title << std::endl;
  std::cout << std::endl << test.get_body_tag().passage << std::endl;

  system("pause");
  return (0);
}
