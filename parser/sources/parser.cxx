#include "parser.h"

bool open_file(std::ifstream& fin, const std::string filepath) {
  fin.open(filepath);
  if (!fin.is_open()) {
    std::cerr << "File " << filepath << " was not found!\n";
    return (false);
  }
  return (true);
}

head get_head_info(std::ifstream& fin, std::string& line) {
  head result;
  int start_content;
  std::string properties[] = {"og:url", "og:site_name",
                              "article:published_time", "og:title",
                              "og:description"};
  int i = 0;

  while (line.find("</head>") == std::string::npos) {
    std::getline(fin, line);
    if ((start_content = line.find("content=")) != std::string::npos)
      result.meta[properties[i++]] = line.substr(
          size_t(start_content) + 9, line.size() - 12 - start_content);
  }
  return (result);
}

static std::string remove_html_tags(std::string str) {
  size_t start_html_tag;
  size_t end_html_tag;
  while ((start_html_tag = str.find("<")) != std::string::npos) {
    end_html_tag = str.find(">") + 1;
    if (end_html_tag != std::string::npos)
      str.erase(start_html_tag, end_html_tag - start_html_tag);
  }
  return (str);
}
body get_body_info(std::ifstream& fin, std::string& line) {
  body result;
  int h1_start;
  int p_start;
  while (line.find("</body>") == std::string::npos) {
    std::getline(fin, line);
    if ((h1_start = line.find("<h1>")) != std::string::npos) {
      if (line.find("</h1>") != std::string::npos)
        result.title.append(remove_html_tags(line));
    }
    if ((p_start = line.find("<p>")) != std::string::npos) {
      if (line.find("</p>") != std::string::npos)
        result.passage.append(remove_html_tags(line).append(" "));
    }
  }
  return (result);
}

html parse_html_file(const std::string filepath) {
  std::ifstream fin;
  std::string line;
  html result;

  if (!open_file(fin, filepath)) exit(getchar());
  while (!fin.eof()) {
    std::getline(fin, line);
    if (line.find("<head>") != std::string::npos)
      result.set_head(get_head_info(fin, line));
    if (line.find("<body>") != std::string::npos)
      result.set_body(get_body_info(fin, line));
  }
  return (result);
}
