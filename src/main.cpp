#include <fstream>
#include "../includes/Email.h"

int file_open(std::string filepath, std::ifstream& stream) {
    try {
        stream.open(filepath.c_str());
        return 1;
    } catch (const std::exception &e) {
        printf("Error opening file.");
        return -1;
    }
} 
 
std::string get_file_contents(std::ifstream& file) {
    return std::string( std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() );
}

int main() {
    std::ifstream email_one;
    file_open("../sample_emails/spam_or_no_spam.txt", email_one);
    std::string email_one_contents = get_file_contents(email_one);
    Email email_one_obj(email_one_contents);
    
    email_one_obj.email_extract_attributes();

    print_features(email_one_obj);
    email_one.close();

    std::ifstream email_two;
    file_open("../sample_emails/spam_or_no_spam_2.txt", email_two);
    std::string email_two_contents = get_file_contents(email_two);
    Email email_two_obj(email_two_contents);
    
    email_two_obj.email_extract_attributes();

    print_features(email_two_obj);
    email_two.close();

    std::ifstream email_three;
    file_open("../sample_emails/spam_or_no_spam_3.txt", email_three);
    std::string email_three_contents = get_file_contents(email_three);
    Email email_three_obj(email_three_contents);
    
    email_three_obj.email_extract_attributes();

    print_features(email_three_obj);
    email_three.close();

    

    
    return 0;
}

