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

void remove_html_tags(std::string& str) {
  size_t start_html_tag;
  size_t end_html_tag;
  while ((start_html_tag = str.find("<")) != std::string::npos) {
    end_html_tag = str.find(">") + 1;
    if (end_html_tag != std::string::npos)
      str.replace(start_html_tag, end_html_tag - start_html_tag, " ");
  }
}
body get_body_info(std::ifstream& fin, std::string& line) {
  body result;
  int h1_start;
  int p_start;
  while (line.find("</body>") == std::string::npos) {
    std::getline(fin, line);
    if ((h1_start = line.find("<h1>")) != std::string::npos) {
      if (line.find("</h1>") != std::string::npos) {
        result.title.append(
            line.substr(size_t(h1_start) + 4, line.size() - 10 - h1_start));
        remove_html_tags(result.title);
      }
    }
    if ((p_start = line.find("<p>")) != std::string::npos) {
      if (line.find("</p>") != std::string::npos)
	  { 
        result.passage.append(
            line.substr(size_t(p_start) + 3, line.size() - p_start - 7)
                .append(" "));
		remove_html_tags(result.passage);
	  }
	  
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
  fin.close();
  return (result);
}
