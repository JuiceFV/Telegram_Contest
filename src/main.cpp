#include "main.h"

using namespace std;

class language
{
private:
    std::unordered_map<string, double> dict;
    std::string filename;
    uint ngram_count;

public:
    language(std::string fname)
    {
        filename = fname;
        ngram_count = 0;
    }

    uint get_ngram_count()
    {
        return ngram_count;
    }

    void generate_probability()
    {
        int skip;
        string line;
        ifstream file (filename);

        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                skip = 0;
                while (isdigit(line[skip]))
                    skip++;
                skip++;
                line = line.erase(0, skip);
                for (int i = 0; i < line.length() - 1; i++)
                {
                    string dict_key = "" + string (1, tolower(line[i])) + string (1, tolower(line[i + 1]));
                    if (dict.find(dict_key) == dict.end())
                        dict[dict_key] = 1;
                    else
                        dict[dict_key] += 1;
                    ngram_count++;
                }
            }
            file.close();
        } else {
            cout << "could not open file " << filename << endl;
            return ;
        }
        for (auto & pair: dict) {
            pair.second = log(pair.second / ngram_count);
        }
    }

    void write_dict_to_file(std::string fname){
        ofstream wfile (fname);

        if (!wfile.is_open())
        {
            cout << fname << " cannot be open" << endl;
            return ;
        }

        wfile.write((char *)&dict, sizeof(dict));
        wfile.close();
    }

    void read_dict_frm_file(std::string fname){
        ifstream rfile (fname);

        if (!rfile.is_open())
        {
            cout << fname << " cannot be open" << endl;
            return ;
        }
        rfile.read((char *)&dict, rfile.tellg());

        rfile.close();
    }

    void print_map()
    {
        for (auto const& pair: dict) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
    }

    double check_prob(std::string text)
    {
        double out = 0;
        double all = 0;
        double known = 0;

        for (int i = 0; i < text.length() - 1; i++)
        {
            string dict_key = "" + string (1, tolower(text[i])) + string (1, tolower(text[i + 1]));
            if (dict.find(dict_key) == dict.end()) {
                out += -30;
            }
            else {
                out += dict[dict_key];
                known++;
            }
            all++;
        }
        return 1 - (out / (all * -30));
    }
};

int main() {
    //generate_prob(dict, "eng_news-typical_2016_100K-sentences.txt");
    language eng ("eng_news-typical_2016_100K-sentences.txt");
    language rus ("rus_wikipedia_2016_100K-sentences.txt");
    eng.generate_probability();
    rus.generate_probability();

    //eng.write_dict_to_file("eng_dict.bin");
    //rus.write_dict_to_file("rus_dict.bin");
    //eng.read_dict_frm_file("eng_dict.bin");
    //rus.read_dict_frm_file("rus_dict.bin");

    //eng.print_map();
    cout << eng.get_ngram_count() << endl;
    cout << rus.get_ngram_count() << endl;

 //   cout << "eng - " << eng.check_prob("Aber die Leute warten auf dich.") << endl;
 //   cout << "rus - " << rus.check_prob("Aber die Leute warten auf dich.") << endl;

    cout << "eng - " << eng.check_prob("¿Cuándo se acaba la escuela?.") << endl;
    cout << "rus - " << rus.check_prob("¿Cuándo se acaba la escuela?.") << endl;


    //ENG.print_map();

    //map<string, double> dictmap(dict.begin(), dict.end());
    /*
    for (auto it = ordered.begin(); it != ordered.end(); ++it)
        std::cout << it->first << " " << it->second << endl;
    */
    //prints_map(dictmap);
    return 0;
}

template<typename K, typename V>
void prints_map (map<K, V> ordered){
    vector<pair<K, V>> vec;

    // copy key-value pairs from the map to the vector
    copy(ordered.begin(),
         ordered.end(),
         std::back_inserter<std::vector<pair<K, V>>>(vec));

    // sort the vector by increasing order of its pair's second value
    // if second value are equal, order by the pair's first value
    std::sort(vec.begin(), vec.end(),
              [](const pair<K, V>& l, const pair<K, V>& r) {
                  if (l.second != r.second)
                      return l.second > r.second;

                  return l.first > r.first;
              });

    // print the vector
    for (auto const &pair: vec) {
        std::cout << pair.first << " " << pair.second << endl;
    }
}

template<typename K, typename V>
void generate_prob(unordered_map<K, V> &dict, string filename)
{
    double all = 0;
    int skip;
    string line;
    ifstream file (filename);

    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            skip = 0;
            while (isdigit(line[skip]))
                skip++;
            skip++;
            line = line.erase(0, skip);
            for (int i = 0; i < line.length() - 1; i++)
            {
                string dict_key = "" + string (1, tolower(line[i])) + string (1, tolower(line[i + 1]));
                if (dict.find(dict_key) == dict.end())
                    dict[dict_key] = 1;
                else
                    dict[dict_key] += 1;
                all++;
            }
        }
        file.close();
    } else {
        cout << "could not open file" << endl;
        return ;
    }
    for (auto & pair: dict) {
        pair.second = log(pair.second / all);
    }
}