/* @Author

 * Student Name: Burak Bozdað
 * Student ID: 150170110
 * Date: 7.11.2018 */

#include <cstdlib> //mbtowc
#include <cstring> //strlen
#include <cwctype> //iswalpha, iswpunct, etc.
#include <fstream> //wifstream
#include <iostream>
#include <locale> //locale, setlocale

using namespace std;

/*
 * @fn charValue
 * @brief Returns fixed value for turkish characters

 * @param character Character */
double charValue(wchar_t character)
{
    double char_value;
    if (character == 231) { //ç
        char_value = 99.5;
    } else if (character == 287) { //ð
        char_value = 103.5;
    } else if (character == 305) { //ý
        char_value = 105; //104.5 changed to 105 because of the last announcement
    } else if (character == 246) { //ö
        char_value = 111.5;
    } else if (character == 351) { //þ
        char_value = 115.5;
    } else if (character == 252) { //ü
        char_value = 117.5;
    } else {
        char_value = (double)character;
    }
    return char_value;
}

/*
 * @struct occur_node
 * @brief Stores occurred characters

 * @param character Character 
 * @param next Points to the next node
 * @param occurrence Occurrence count */
struct occur_node {
    wchar_t character;
    occur_node* next;
    int occurrence;
};

/*
 * @struct vocab_node
 * @brief Stores characters

 * @param character Character 
 * @param next Points to the next node
 * @param list Points to the first occur_node */
struct vocab_node {
    wchar_t character;
    vocab_node* next;
    occur_node* list;
};

/*
 * @struct vocab_list
 * @brief Stores vocab nodes

 * @param head Points to the first vocab_node
 * @fn create Creates the vocab_list
 * @fn print Prints the whole language model
 * @fn add_char Adds character to the list
 * @fn add_occurrence Adds occurrence infos to the list
 * @fn get_occurrence Returns occurrence count of a character
 * @fn get_union_occurrence Returns union occurrence count of two characters */
struct vocab_list {
    vocab_node* head;

    void create()
    {
        vocab_node* temp = new vocab_node;
        temp->character = '\0';
        temp->next = NULL;
        temp->list = NULL;
        head = temp;
    }

    void print()
    {
        vocab_node* temp = head;
        while (temp != NULL) {
            if (temp->list != NULL) {
                if (temp->character == ' ') {
                    wcout << "<SP>:" << endl;
                } else {
                    wcout << temp->character << ":" << endl;
                }

                occur_node* occur = temp->list;
                while (occur != NULL) {
                    if (occur->character == ' ') {
                        wcout << "\t<<SP>," << occur->occurrence << ">" << endl;
                        occur = occur->next;
                    } else {
                        wcout << "\t<" << occur->character << "," << occur->occurrence << ">" << endl;
                        occur = occur->next;
                    }
                }
                temp = temp->next;
            } else {
                temp = temp->next;
            }
        }
    }

    void add_char(wchar_t character, char mode)
    {
        if (character == 65279) { //ZERO WIDTH NO-BREAK SPACE
            return;
        }

        if (head->character == '\0') {
            head->next = NULL;
            head->list = NULL;
            head->character = character;
            return;
        }

        vocab_node* check = head;

        while (check != NULL) { //Checking existence
            if (check->character == character) {
                return;
            } else if (check->next != NULL) {
                check = check->next;
            } else {
                break;
            }
        }

        if (mode == 'g' || mode == 's') { //For non-letters
            vocab_node* temp = new vocab_node;
            temp->next = NULL;
            temp->character = character;
            temp->list = NULL;
            vocab_node* traverse = head;
            while (traverse->next != NULL) {
                traverse = traverse->next;
            }
            traverse->next = temp;
        } else { //For letters
            vocab_node* previous = NULL;
            vocab_node* current = head;
            double char_value = charValue(character);

            while (current != NULL) {
                if (!iswalpha(current->character)) {
                    if (current == head) {
                        vocab_node* temp = new vocab_node;
                        temp->next = current;
                        temp->list = NULL;
                        temp->character = character;
                        head = temp;
                        return;
                    } else {
                        vocab_node* temp = new vocab_node;
                        temp->next = current;
                        temp->list = NULL;
                        temp->character = character;
                        previous->next = temp;
                        return;
                    }
                } else if ((iswalpha(current->character)) && (charValue(current->character) > char_value)) {
                    if (current == head) {
                        vocab_node* temp = new vocab_node;
                        temp->next = current;
                        temp->list = NULL;
                        temp->character = character;
                        head = temp;
                        return;
                    } else {
                        vocab_node* temp = new vocab_node;
                        temp->next = current;
                        temp->list = NULL;
                        temp->character = character;
                        previous->next = temp;
                        return;
                    }
                } else {
                    if (current->next != NULL) {
                        previous = current;
                        current = current->next;
                    } else {
                        vocab_node* temp = new vocab_node;
                        temp->next = NULL;
                        temp->list = NULL;
                        temp->character = character;
                        vocab_node* traverse = head;
                        while (traverse->next != NULL) {
                            traverse = traverse->next;
                        }
                        traverse->next = temp;
                        return;
                    }
                }
            }
        }
    }

    void add_occurrence(wchar_t pre, wchar_t cur)
    {
        vocab_node* temp = head;
        while (temp != NULL) {
            if (temp->character == pre) {
                if (temp->list == NULL) {
                    occur_node* occur_new = new occur_node;
                    occur_new->next = NULL;
                    occur_new->character = cur;
                    occur_new->occurrence = 1;
                    temp->list = occur_new;
                    return;
                } else {
                    occur_node* current = temp->list;
                    while (current != NULL) {
                        if (current->character == cur) {
                            current->occurrence += 1;
                            return;
                        } else if (current->next == NULL) {
                            occur_node* occur = new occur_node;
                            occur->next = NULL;
                            occur->character = cur;
                            occur->occurrence = 1;
                            current->next = occur;
                            return;
                        } else {
                            current = current->next;
                        }
                    }
                }
            } else {
                temp = temp->next;
            }
        }
    }

    int get_occurrence(wchar_t character)
    {
        int counter = 0;
        vocab_node* temp = head;
        while (temp != NULL) {
            if (temp->character == character) {
                occur_node* occur = temp->list;
                while (occur != NULL) {
                    counter += occur->occurrence;
                    occur = occur->next;
                }
                return counter;
            } else {
                temp = temp->next;
            }
        }
        return counter;
    }

    int get_union_occurrence(wchar_t first, wchar_t second)
    {
        vocab_node* temp = head;
        int counter = 0;
        while (temp != NULL) {
            if (temp->character == first) {
                occur_node* occur = temp->list;
                while (occur != NULL) {
                    if (occur->character == second) {
                        return occur->occurrence;
                    } else {
                        occur = occur->next;
                        counter++;
                        if (counter >= 50) {
                            return 0;
                        }
                    }
                }
            } else {
                temp = temp->next;
            }
        }
        return 0;
    }
};

/*
 * @struct language_model
 * @brief Stores the language model

 * @param vl Points to the vocab list
 * @fn readData Reads data from input file and develops the language model
 * @fn calculateProbability Calculates the occurrence probability of two characters */
struct language_model {
    vocab_list* vl;

    void readData(const char* argv)
    {
        wifstream read_char(argv); //Opening file
        read_char.imbue(locale("en_US.utf8"));
        vl->create(); //Creating vocab_list
        wchar_t character;
        while (!read_char.eof()) {
            if (read_char.eof()) {
                break;
            }
            read_char.get(character);

            if (iswalpha(character)) {
                character = towlower(character);
                if (character == 305) { //Converting ý to i
                    character = 105;
                }
                vl->add_char(character, 'a');
            } else if (iswgraph(character)) {
                vl->add_char(character, 'g');
            } else if (iswblank(character) && !iswcntrl(character)) {
                vl->add_char(character, 's');
            } else {
                continue;
            }
        }
        read_char.close();

        wifstream read_occur(argv); //Opening file
        read_occur.imbue(locale("en_US.utf8"));
        wchar_t pre = '\0', cur = '\0';
        read_occur.get(pre);
        read_occur.get(cur);
        while (!read_occur.eof()) {
            if (read_occur.eof()) {
                break;
            }
            if ((iswgraph(pre) || (iswblank(pre) && !iswcntrl(pre))) && (iswgraph(cur) || (iswblank(cur) && !iswcntrl(cur))) && (pre != 65279 && cur != 65279)) {
                if (iswalpha(pre)) {
                    pre = towlower(pre);
                }
                if (iswalpha(cur)) {
                    cur = towlower(cur);
                }
                if (pre == 305) { //Converting ý to i
                    pre = 105;
                }
                if (cur == 305) { //Converting ý to i
                    cur = 105;
                }
                vl->add_occurrence(pre, cur);
            }
            if (!read_occur.eof()) {
                pre = cur;
                read_occur.get(cur);
            } else {
                wcout << endl;
                break;
            }
        }
    }

    double calculateProbability(wchar_t first, wchar_t second)
    {
        int union_occur = vl->get_union_occurrence(first, second);
        if (union_occur == 0) {
            return 0;
        }
        int occur = vl->get_occurrence(first);
        if (occur == 0) {
            return -1;
        }
        return (double)union_occur / occur;
    }
};

int main(int argc, char** argv)
{
    locale::global(locale("")); //Localizing
    setlocale(LC_ALL, "en_US.utf8"); //Localizing

    language_model* lm = new language_model;
    lm->readData(argv[1]);

    if (argc == 2) { //Different inputs according to argument count
        lm->vl->print();
    } else if (argc == 4) {
        mbtowc(NULL, 0, 0);
        const char* first_p = argv[2] + strlen(argv[2]);
        wchar_t first = '\0';
        mbtowc(&first, argv[2], first_p - argv[2]); //Converting char to wchar_t

        mbtowc(NULL, 0, 0);
        const char* second_p = argv[3] + strlen(argv[3]);
        wchar_t second = '\0';
        mbtowc(&second, argv[3], second_p - argv[3]);

        first = towlower(first);
        second = towlower(second);

        if (first == 305) { //Converting ý to i
            first = 105;
        }
        if (second == 305) { //Converting ý to i
            second = 105;
        }

        double prob = lm->calculateProbability(first, second);
        if (prob == -1) {
            return 1;
        }
        wcout << prob << endl;
    } else {
        return 1;
    }
    delete lm;
    return 0;
}
