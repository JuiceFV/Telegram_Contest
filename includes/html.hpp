#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

void parser(std::string filename);

// the structure which shows the representation of the head-tag
struct Head {
  std::unordered_map<std::string, std::string>
      meta;  // <property-value, content-value>
  friend std::ostream& operator<<(std::ostream& out, const Head& head) {
    for (auto m_property : head.meta) {
      out << '[' << m_property.first << ", " << m_property.second << ']'
          << std::endl;
    }
    return (out);
  }
};

struct Body {
  std::string title;
  std::string passage;
};

class HTML {
 private:
  Head head_tag;
  Body body_tag;

 public:
  HTML(){};

 /* HTML(std::string filename)
  {
          *this = parser(filename);
  };*/

  void set_head_tag(const Head head) { head_tag = head; }

  Head get_head_tag() const { return (head_tag); }

  void set_body_tag(const Body body) { body_tag = body; }
  Body get_body_tag() const { return (body_tag); }
};

void parser(std::string filename) {
  HTML res;
  std::ifstream fin;

  // open the file
  auto open = [&fin, &filename]() {
    fin.open(filename);
    if (!fin.is_open()) {
      std::cerr << "There is no file: " << filename;
      exit(getchar());
    }
  };
  open();

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

  res.set_head_tag(get_head_info());
  //std::cout << res.get_head_tag();
  auto get_body_info = [&fin]() {
    Body res;
    bool article_open = false;
    while (!fin.eof()) {
      std::string line;
      std::getline(fin, line);
      std::cout << line << std::endl;
    }
  };
  get_body_info();
}
