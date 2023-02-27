
#include "../includes/Email.h"
#include <vector>
#include <set>
#include <algorithm>

/* set of keywords defined by UCI*/
const std::set <std::string> g_word_freq = {
    "make", "address", "all", "3d",
    "our", "over", "remove", "internet",
    "order", "mail", "receive", "will",
    "people", "report", "addresses", "free",
    "business", "email", "you", "credit", "your",
    "font", "000", "money", "hp", "hpl", "george", "650",
    "lab", "labs", "telnet", "857", "data", "415",
    "85", "technology", "1999", "parts", "pm", "direct",
    "cs", "meeting", "original", "project", "re", "edu", "table",
    "conference"
};

/* set of key characters defined by UCI */
const std::set<char> g_char_freq = {
    ';', '(', '[', '!', '$', '#'        
};


/* default constructor */
Email::Email() {
    this->init();
}

/* parametrized constructor to define content of Email */
Email::Email(std::string content) {
    this->init();
    this->content = content;
}

/* initialize attributes of class */
void Email::init() {
    this->content = " ";
    this->character_count = 0;
    this->word_count = 0;
    this->capital_run_length_average = 0.0;
    this->capital_run_length_longest = 0;
    this->capital_run_length_total = 0;
    for (auto& it: g_word_freq) {
        this->word_freq.insert(std::pair<std::string, float>(it, 0));
    }
    for (auto& it: g_char_freq) {
        this->char_freq.insert(std::pair<char, float>(it, 0));
    }
}

/* if valid character increment character_count */
void Email::check_increment_ccount(const char c){ 
    if (c != ' ' && c != EOF) {
        this->character_count++; 
    }
}


/* print all 57 features as an array enclosed by square brackets */
void print_features(Email e) {
    printf("[");
    for (auto const& [key, val]: e.get_word_freq()) {
        printf("%f, ", val);
    }
    for (auto const& [key, val]: e.get_char_freq()) {
        printf("%f, ", val);
    }

    printf("%lf, ", e.get_capital_run_length_average());
    printf("%ld, ", (long) e.get_capital_run_length_longest());
    printf("%ld", (long) e.get_capital_run_length_total());

    printf("]\n");
}


/* get value of word_freq */
std::map<std::string, float> Email::get_word_freq() const {
    return this->word_freq;
}

/* get value of char_freq */
std::map<char, float> Email::get_char_freq() const {
    return this->char_freq;
}

/* get value of content */
std::string Email::get_content() const{
    return this->content;
}

/* get value of capital_run_length_total */
size_t Email::get_capital_run_length_total() const{ 
    return this->capital_run_length_total;
}

/* get value of capital_run_length_longest */
size_t Email::get_capital_run_length_longest() const{ 
    return this->capital_run_length_longest;
}

/* set value of capital_run_length_average */
double Email::get_capital_run_length_average() const {
    return this->capital_run_length_average;
}


/* set value of content */
void Email::set_content(const std::string c) {
    this->content = c;
}

/* set value of capital_run_length_average */
void Email::set_capital_run_length_average(const size_t capital_seq_num) {
    this->capital_run_length_average = capital_run_length_total / (float) capital_seq_num;
}

/* set value of capital_run_length_longest */
void Email::set_capital_run_length_longest(const size_t longest) {
    this->capital_run_length_longest = longest;
}

/* set value of capital_run_length_total */
void Email::set_capital_run_length_total(const size_t total) {
    this->capital_run_length_total = total;
}





/* function to extract attributes/features of the Email */
void Email::email_extract_attributes() {
    bool is_new_word = false;

    size_t new_word_start_index = 0;
    size_t capital_length = 0;
    size_t capital_seq_num = 0;

    std::string word;
    
    std::vector<std::string> words; 
   

    for (unsigned int i = 0; char& c: this->content) {
        
        check_increment_ccount(c);

        /* if upper increment total length, update longest; else increment total sequences and reset length*/
        if (isupper(c)) {
                this->capital_run_length_total++;
                capital_length++;
                this->capital_run_length_longest = capital_length > this->capital_run_length_longest ? capital_length : this->capital_run_length_longest;
        } else {
                if ( capital_length > 0 ) {
                    capital_seq_num++;
                }
                capital_length = 0;
        }


        /* check if alphanumeric or hyphen  */
        if (isalnum(c) || c=='-') {
            if (!is_new_word) {
                is_new_word = true;
                new_word_start_index = i;
            }

        }

        /* store word  */
        else {
            if(is_new_word) {
                word = this->content.substr(new_word_start_index, i - new_word_start_index);
                words.push_back(word);
                this->word_count++;
                is_new_word = false;
            }
        }

        /* check if character is in g_char_freq and increment if true*/
        if (g_char_freq.contains(c)) {
                this->char_freq[c]++;
        }

        
        i++;
       
    }

    for (auto& it : words) {
        
        /* remove hyphen from word for comparison */
        it.erase(
            std::remove_if(
                it.begin(), 
                it.end(),
                [](char c) { 
                    return !std::isalpha(c); 
                } 
            ),
            it.end()
        ); 
        
        /* convert word to lowercase to be able to compare with g_word_freq */
        std::transform(
            it.begin(), 
            it.end(), 
            it.begin(),
            [](unsigned char c) {
                return std::tolower(c);
            }
        );

        /* if word is one of the keywords increase percentage of words in the email that matches the word */
        if (g_word_freq.contains(it)) {
            this->word_freq[it] += 100 * (1.0 / this->word_count);
        }

    }

    /* if character is one of the key characters increase percentage of characters in the email that matches the character */
    for (auto& it : char_freq) {
        char_freq[it.first] = 100 * (it.second / this->character_count);
    }

    this->set_capital_run_length_average(capital_seq_num);

}

