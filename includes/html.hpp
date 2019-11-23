#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "parser.hpp"

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


