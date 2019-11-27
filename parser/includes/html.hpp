#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct head {
  // The meta tag. If be more esspecialy meta contain
  // <priority-value, content-value>.
  // Also, the unordered_map has one advantage
  // The complexity of the find of the certain ellemet is O(1) or O(n).
  std::unordered_map<std::string, std::string> meta;
  friend std::ostream& operator<<(std::ostream& out, const head& head_tag);
};

struct body {
  // It will contain the title of the passage
  // In our case <h1>There is the title</h1>
  std::string title;
  // It will contain the main body of the paassage
  std::string passage;
};

// The class html contains specific data from our html
class html {
 private:
  head head_tag;
  body body_tag;

 public:
  html(){};
  html(std::string filepath);
  head get_head_tag() const;
  body get_body_tag() const;
  void set_head(head head_tag);
  void set_body(body body_tag);
};
