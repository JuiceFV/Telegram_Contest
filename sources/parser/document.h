#include <string>
#include <unordered_map>
#include "tag_detector.h"

namespace prsr {
	class HTMLDocument {
	private:
		std::string doc_path;
		std::string title;
		std::string entire_body;
		std::unordered_map<Element, std::string> data_per_tag;
	public:
		HTMLDocument(std::string doc_path);
	};
}
