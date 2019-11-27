#include "html.hpp"

#include "parser.h"
std::wostream& operator<<(std::wostream& out, const head& head_tag) {
  if (!head_tag.meta.empty()) {
    for (auto m_property : head_tag.meta) {
      out << L"[ " << m_property.first << L" , " << m_property.second << " ]"
          << std::endl;
    }
  } else
    std::cout << "There is no any meta-propery" << std::endl;
  return (out);
}

html::html(std::string filepath) { *this = parse_html_file(filepath); }

body html::get_body_tag() const { return (body_tag); }

head html::get_head_tag() const { return (head_tag); }

void html::set_body(body body_tag) { this->body_tag = body_tag; }

void html::set_head(head head_tag) { this->head_tag = head_tag; }
