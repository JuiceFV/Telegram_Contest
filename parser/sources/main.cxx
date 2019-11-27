#include "html.hpp"
#include "parser.h"

int main(int argc, char **argv) {
	std::string filepath(
      "D:\\Projects\\Telegram_Contest\\parser\\data_"
      "1\\20191101\\00\\993065305003958.html");
  html test(filepath);
  std::wcout << test.get_body_tag().title << std::endl;
  std::wcout << std::endl << test.get_body_tag().passage << std::endl;
  
	/*
	std::wcout<<L"\xe2\x80\x98"<<std::endl; // one opening quote
	std::wcout<<L"\xe2\x80\x99"<<std::endl; // one closing quote
*/
  system("pause");
  return (0);
}
