#ifndef _EMAIL_H_
#define _EMAIL_H_

#include <string>
#include <map>


class Email {
    private:
        std::string content;
        std::map<std::string, float> word_freq;
        std::map<char, float> char_freq;
        size_t capital_run_length_total;
        size_t capital_run_length_longest;
        double capital_run_length_average;
        size_t word_count;
        size_t character_count;

    public:
        Email();
        Email(const std::string);

        void init();
        void check_increment_ccount(const char c);

        std::map<std::string, float> get_word_freq() const;
        std::map<char, float> get_char_freq() const;
        std::string get_content() const;
        size_t get_capital_run_length_total() const;
        size_t get_capital_run_length_longest() const;
        double get_capital_run_length_average() const;

        void set_content(const std::string);
        void set_capital_run_length_average(const size_t);
        void set_capital_run_length_longest(const size_t);
        void set_capital_run_length_total(const size_t);

        void email_extract_attributes();
};

void print_features(Email e); 

#endif
