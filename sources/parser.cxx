#include "parser.hpp"
#include "html.hpp"

void parser(std::string filename) {
  std::ifstream fin;

  // open the file
  fin.open(filename);
  if (!fin.is_open()) {
    std::cerr << "There is no file: " << filename;
    exit(getchar());
  }

  // here start the lambda wich acquire the info from tag head.
  auto get_head_info = [&fin]() {
    Head res;
    bool head_open = false;
    std::string property[] = {"og:url", "og:site_name",
                              "article:published_time", "og:title",
                              "og:description"};
    size_t content_start;
    int i = 0;

    while (!fin.eof()) {
      std::string line;
      std::getline(fin, line);
      if (line.find("</head>") != std::string::npos)
        break;
      if (head_open) {
        if ((content_start = line.find("content=")) != std::string::npos)
          res.meta.insert({property[i++],
                           line.substr(content_start + 9,
                                       line.size() - 2 - content_start - 10)});
      }
      if (line.find("<head>") != std::string::npos) head_open = true;
    }
    return (res);
  };

  auto get_body_info = [&fin]() {
    Body res;
    while (!fin.eof()) {
      std::string line;
      std::getline(fin, line);
	  if (line.find("<article>") != std::string::npos)
	  {
		  int start_h1;
		  while (line.find("</article>") == std::string::npos)
		  {
			  getline(fin, line);
			  if ((start_h1 = line.find("<h1>")))
		  }
	  }
    }
  };
}