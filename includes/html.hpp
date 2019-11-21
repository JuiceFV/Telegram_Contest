#pragma once

#include <list>
#include <unordered_map>
#include <string>

struct Head
{
	std::unordered_map<std::string, std::string> meta;// <property-value, content-value>
};

struct Body
{
	std::string title;
	std::string passage;
};

class HTML
{
private:
	Head head_tag;
	Body body_tag;
public:
	HTML();

};
