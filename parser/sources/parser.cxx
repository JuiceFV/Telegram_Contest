#include "parser.h"

bool open_file(std::wifstream& fin, const std::string filepath) {
  fin.open(filepath);
  if (!fin.is_open()) {
    std::cerr << "File " << filepath << " was not found!\n";
    return (false);
  }
  return (true);
}

head get_head_info(std::wifstream& fin, std::wstring& line) {
  head result;
  int start_content;
  std::wstring properties[] = {L"og:url", L"og:site_name",
                              L"article:published_time", L"og:title",
                              L"og:description"};
  int i = 0;

  while (line.find(L"</head>") == std::wstring::npos) {
    std::getline(fin, line);
    if ((start_content = line.find(L"content=")) != std::wstring::npos)
      result.meta[properties[i++]] = line.substr(
          size_t(start_content) + 9, line.size() - 12 - start_content);
  }
  return (result);
}

void remove_html_tags(std::wstring& str) {
  size_t start_html_tag;
  size_t end_html_tag;
  while ((start_html_tag = str.find(L"<")) != std::wstring::npos) {
    end_html_tag = str.find(L">") + 1;
    if (end_html_tag != std::wstring::npos)
      str.replace(start_html_tag, end_html_tag - start_html_tag, L" ");
  }
}


body get_body_info(std::wifstream& fin, std::wstring& line) {
  body result;
  size_t h1_start;
  size_t p_start;
  while (line.find(L"</body>") == std::wstring::npos) {
    std::getline(fin, line);
    if ((h1_start = line.find(L"<h1>")) != std::wstring::npos) {
      if (line.find(L"</h1>") != std::wstring::npos) {
        result.title.append(
            line.substr(h1_start + 4, line.size() - 10 - h1_start));
        remove_html_tags(result.title);
      }
    }
    if ((p_start = line.find(L"<p>")) != std::wstring::npos) {
      if (line.find(L"</p>") != std::wstring::npos)
	  { 
        result.passage.append(
            line.substr(p_start + 3, line.size() - p_start - 7)
                .append(L" "));
			remove_html_tags(result.passage);
	  }
	  
    }
  }
  return (result);
}

html parse_html_file(const std::string filepath) {
  std::wifstream fin;
  std::wstring line;
  html result;

  if (!open_file(fin, filepath)) exit(getchar());
  while (!fin.eof()) {
    std::getline(fin, line);
    if (line.find(L"<head>") != std::wstring::npos)
      result.set_head(get_head_info(fin, line));
    if (line.find(L"<body>") != std::wstring::npos)
      result.set_body(get_body_info(fin, line));
  }
  fin.close();
  return (result);
}
