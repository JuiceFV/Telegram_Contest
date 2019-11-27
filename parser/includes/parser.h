#pragma once

#include <fstream>

#include "html.hpp"

bool open_file(std::wifstream &fin, const std::string filepath);

html parse_html_file(const std::string filepath);
