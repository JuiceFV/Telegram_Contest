#pragma once

#include <list>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

void parser(std::string filename);

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
	HTML()
	{
		head_tag.meta = {'\0', '\0'};
		body_tag.passage = '\0';
		body_tag.title = '\0';
	};

	/*HTML(std::string filename)
	{
		*this = parser(filename);
	};*/

	void set_head_tag(const Head head)
	{
		head_tag = head;
	}

	Head get_head_tag() const
	{
		return (head_tag);
	}

	void set_body_tag(const Body body)
	{
		body_tag = body;
	}
	Body get_body_tag() const
	{
		return (body_tag);
	}
};

void parser(std::string filename)
{
	HTML res;
	std::ifstream fin;
	auto open = [&fin, &filename](){
		fin.open(filename);
		if (!fin.is_open())
		{
			std::cerr << "There is no file: " << filename;
			exit(getchar());
		}
	};
	open();

	auto get_head_info = [&fin](){
		Head res; 
		bool head_open = false;
		std::string property[] = {"og:url", "og:site_name", "article:published_time", "og:title", "og:description"};
		size_t content_start;
		int i = 0;

		while (!fin.eof())
		{
			std::string line;
			std::getline(fin, line);
			if (line.find("</head>") != std::string::npos)
			{ 
				head_open = false;
				break;
			}
			if (head_open)
			{ 
				if ((content_start = line.find("content=")) != std::string::npos)
					res.meta.insert({property[i++], line.substr(content_start + 8, line.size() - 2 - content_start - 8)});
			}
			if (line.find("<head>") != std::string::npos)
				head_open = true;
		}
		return (res);
	};

	res.set_head_tag(get_head_info());
	
	auto get_body_info = [&fin]() {
		Body res;
		bool article_open = false;
		while (!fin.eof())
		{
			std::string line;
			std::getline(fin, line);
			std::cout << line << std::endl;
		}
	};
	get_body_info();
}



