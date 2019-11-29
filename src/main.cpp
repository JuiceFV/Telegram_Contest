#include "main.h"

using namespace std;

bool	is_symb(char c)
{
	if (c == '.' || c == ',' || c == '-' || c == ';')
		return 1;
	if (isdigit(c))
		return 1;
	return 0;
}

class language
{
private:
    std::unordered_map<string, double> dict;
    std::string filename;
    uint ngram_count;
    std::string lang_name;

public:
    language(std::string fname, std::string lname)
    {
        filename = fname;
        lang_name = lname;
        ngram_count = 0;
    }

    uint get_ngram_count()
    {
        return ngram_count;
    }

	std::string get_lang()
	{
		return lang_name;
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
            	/*
                skip = 0;
                while (isdigit(line[skip]))
                    skip++;
                skip++;

                line = line.erase(0, skip);
                */
                for (int i = 0; i < (int)(line.length()) - 1; i++)
                {
                	int pizdecz = line.length();
                    string dict_key = "" + string (1, tolower(line[i])) + string (1, tolower(line[i + 1]));
					if (is_symb(line[i]) || line[i] == ' ' || is_symb(line[i + 1]))
						continue ;
                    if (dict.find(dict_key) == dict.end())
					{
						dict[dict_key] = 1;
						ngram_count++;
					}
                    else
                        dict[dict_key] += 1;
                }
            }
            file.close();
        } else {
            cout << "could not open file " << filename << endl;
            return ;
        }
		int max;
		std::unordered_map<string, double> tmp;
		string max_name;
		//cout << ngram_count << endl;
		for (int j = 0; j < 300; j++)
		{
			max = 0;
			for (auto &pair: dict)
			{
				if (max < pair.second)
				{
					max = pair.second;
					max_name = pair.first;
				}
			}
			tmp[max_name] = max;
			//cout << max_name << " ";
			dict.erase(max_name);
		}
		//cout << endl;
		dict.clear();
		dict = tmp;
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

		for (auto const& pair: dict) {
			wfile << pair.first << " " << pair.second << std::endl;
		}
        //wfile.write((char *)&dict, sizeof(dict));
        wfile.close();
    }

    void read_dict_frm_file(std::string fname){
        ifstream rfile (fname);
        std::string line;
        std::string buf;

        if (!rfile.is_open())
        {
            cout << fname << " cannot be open" << endl;
            return ;
        }
		while ( getline (rfile,line) )
		{
			buf = string(1, line[0]) + string(1, line[1]);
			line.erase(0, 2);
			dict[buf] = stod(line);
		}
		rfile.close();
    }

    void print_map()
    {
        for (auto const& pair: dict) {
            std::cout << pair.first << ": " << pair.second << std::endl;
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
			if (is_symb(text[i]) || is_symb(text[i + 1]) || text[i] == ' ')
				continue ;
            if (dict.find(dict_key) == dict.end()) {
                out += -100;
            }
            else {
                out += dict[dict_key];
                known++;
            }
            all++;
        }
        return 1 - (out / (all * -100));
    }
};


language detect_lang(language langs[], int langs_num, std::string s)
{
	double max = 0;
	double tmp;
	language *max_lang;
	string max_name = "None";
	for (int i = 0; i < langs_num; i++)
	{
		tmp = langs[i].check_prob(s);
		//cout << tmp << endl;
		if (max < tmp)
		{
			max = tmp;
			max_name = langs[i].get_lang();
			max_lang  = &(langs[i]);
		}
	}
	cout << max_name << " " << max << endl;
	return *max_lang;
}


int main() {
    //generate_prob(dict, "eng_news-typical_2016_100K-sentences.txt");
    string lang_folder_path = "../";
    language eng (lang_folder_path + "lang/eng.txt", "eng");
    language rus (lang_folder_path + "lang/rus.txt", "rus");
	language ger (lang_folder_path + "lang/ger.txt", "ger");
	language czc (lang_folder_path + "lang/czc.txt", "czc");
	language dns (lang_folder_path + "lang/dns.txt", "dns");
	language dut (lang_folder_path + "lang/dut.txt", "dut");
	language frn (lang_folder_path + "lang/frn.txt", "frn");
	language grk (lang_folder_path + "lang/grk.txt", "grk");
	language hng (lang_folder_path + "lang/hng.txt", "hng");
	language itn (lang_folder_path + "lang/itn.txt", "itn");
	language jpn (lang_folder_path + "lang/jpn.txt", "jpn");
	language lat (lang_folder_path + "lang/lat.txt", "lat");
	language lit (lang_folder_path + "lang/lit.txt", "lit");
	language ltn (lang_folder_path + "lang/ltn.txt", "ltn");
	language lux (lang_folder_path + "lang/lux.txt", "lux");
	language mls (lang_folder_path + "lang/mls.txt", "mls");
	language por (lang_folder_path + "lang/por.txt", "por");
	language rmn1 (lang_folder_path + "lang/rmn1.txt", "rmn1");
	language rum (lang_folder_path + "lang/rum.txt", "rum");
	language spn (lang_folder_path + "lang/spn.txt", "spn");
	language ukr (lang_folder_path + "lang/ukr.txt", "ukr");
	language yps (lang_folder_path + "lang/yps.txt", "yps");

	int langs_num = 22;
	language langs[22] = {eng, rus, ger, czc, dns, dut, frn, grk, hng, itn, jpn, lat, lit, ltn, lux, mls, por, rmn1, rum, spn, ukr, yps};
	string folder = "../dictionaries/";

	//for (int i = 0; i < langs_num; i++)
		//langs[i].generate_probability();

	for (int i = 0; i < langs_num; i++)
		langs[i].read_dict_frm_file(folder + langs[i].get_lang() + "_dict.txt");

	//for (int i = 0; i < langs_num; i++)
		//langs[i].write_dict_to_file(folder + langs[i].get_lang() + "_dict.txt");


    //eng.write_dict_to_file("eng_dict.bin");
    //rus.write_dict_to_file("rus_dict.bin");
    //eng.read_dict_frm_file("eng_dict.bin");
    //rus.read_dict_frm_file("rus_dict.bin");

    //eng.print_map();
    //cout << eng.get_ngram_count() << endl;
    //cout << rus.get_ngram_count() << endl;

 //   cout << "eng - " << eng.check_prob("Aber die Leute warten auf dich.") << endl;
 //   cout << "rus - " << rus.check_prob("Aber die Leute warten auf dich.") << endl;

 	std::string s1 = "The East Slavs emerged as a recognizable group in Europe between the and centuries AD Founded and ruled by a Varangian warrior elite and their descendants the medieval state of Rus arose in the century";
 	std::string s2 = "Das Regierungssystem Russlands wird von Politikwissenschaftlern entsprechend dem Wortlaut der Verfassung meist formal als Verbindung präsidentieller und parlamentarischer Formen eingeordnet";
 	std::string s3 = "Государственный строй Президентско-парламентская республика с федеративным устройством С мая года должность президента Российской Федерации занимает Владимир Путин";
 	std::string s4 = "У російській історіографії початки державності відносять до періоду Русі середньовічної держави із центром в Києві Під час періоду розпаду якої її північно-східні провінції підпали під владу Золотої Орди";
 	std::string s5 = "Раççей Федерацийĕ — нумай нациллĕ çĕршыв. Тĕпчевçĕсем каланă тăрăх, Раççейри халăхсем 176 чĕлхепе калаçаççĕ. Вĕсен кашнин хăйсен историйĕ, шăпи, аталану çул-йĕрĕ, пуласлăхĕ.";
 	std::string s6 = "Шормуӵъёсты но эксклавъёсты лыдэ басьтоно ке, тужгес уйшор интыез луэ Франц-Иосиф Музъем архипелагысь Рудольф шормуӵысь Флигели мыс";

	/*
	cout << detect_lang(langs, langs_num, s1).get_lang() << " " << "eng" << endl;
	cout << detect_lang(langs, langs_num, s2).get_lang() << " " << "ger" << endl;
	cout << detect_lang(langs, langs_num, s3).get_lang() << " " << "rus" << endl;
	cout << detect_lang(langs, langs_num, s4).get_lang() << " " << "ukr" << endl;
	*/
	cout << detect_lang(langs, langs_num, s5).get_lang() << " " << "chuvash" << endl;
	cout << detect_lang(langs, langs_num, s6).get_lang() << " " << "No rus" << endl;


	/*
	cout << "eng - " << eng.check_prob(s1) << endl;
    cout << "eng - " << eng.check_prob(s2) << endl;
	cout << "rus - " << rus.check_prob(s3) << endl;
    cout << "rus - " << rus.check_prob(s4) << endl;
	*/

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
         std::back_inserter<std::vector<std::pair<K, V>>>(vec));

    // sort the vector by increasing order of its pair's second value
    // if second value are equal, order by the pair's first value
    std::sort(vec.begin(), vec.end(),
              [](const pair<K, V>& l, const pair<K, V>& r) {
                  if (l.second != r.second)
                      return l.second > r.second;

                  return l.first > r.first;
              });

    // print the vector
    int i = 0;
    for (auto const &pair: vec) {
        std::cout << pair.first << " " << pair.second << endl;
        i++;
        if (i >= 300)
        	break;
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