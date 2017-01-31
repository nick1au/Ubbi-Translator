/* Nicholas Lau, Darren Su
December 5, 2015 -- MODIFIED: Dec. 6, Dec. 7
Ubbi Translator Program

This program is able to translate English into ubbi by adding ub before vowels. If vowel is capitalized, program will automatically switch it to lowercase
if necessary. Can also read and write into files with full error correcting (file conflicts, file extensions)
*/


#include <iostream>
#include <cstdlib>
#include <limits>
#include <fstream>


using namespace std;
// Constants for menu function.
const int ENCODE_WORD = 1;
const int READ = 2;
const int ENCODE_FILE = 3;
const int WRITE_FILE = 4;
const int QUIT = 0;

void menu();
void get_menu_input(int&);

//void encode_wfunc(string&, string&);
void encode_wfunc(string array1[], string array2[], int);
//void input(string&);
void input(string array[], int);
//void output_onscreen(string&, string&);
void output_onscreen(string array1[], string array2[]);
void readfunc(ifstream&, string&);
//void encode_ffunc(ifstream&, string&, string&); **D
void get_write_ffunc(ofstream&, string, string&, string&);
int getnumber_ofchar(string);
void clearfunc(string&, string&);
void writing_to_file(ofstream&, string, string, string);
void check_fileext(string&);
void upper_to_lower_case(string&, int);
//bool return_to_menu(string);
bool check_file_conflict(string&, string&);
//bool valid_filename(string);

/* Main function to call upon all primary functions and menu via switch and do while loop. Loops if user does not want to quit.
In_stream and out_stream will automatically close if user quits.
*/
int main()
{
    int choice;
    int w_lim;

    ifstream in_stream;
    ofstream out_stream;

    //string original; **D
    //string translated; **D

    string original[w_lim];
    string translated[w_lim];

    string filename_in;
    string filename_out;

    //bool translatecheck = 0; //0 = none, 1 = encoded word, 2 = encoded file

    do
    {
        //clearfunc(original, translated); // **D
        menu();
        get_menu_input(choice);

        switch(choice)
        {
            case ENCODE_WORD:

                cout << "Encode word" << endl;
                //clearfunc(original, translated); **D
                w_lim = 1;
                input(original, w_lim);
                encode_wfunc(original, translated, w_lim);
                output_onscreen(original, translated);
                break;
            case READ:
                cout << "Reading File" << endl;
                readfunc(in_stream, filename_in);
                break;
            case ENCODE_FILE:
                cout << "Encoding to file" << endl;
                //clearfunc(original, translated); **D
                w_lim = 100;
                //encode_ffunc(original, translated);
                encode_wfunc(original, translated, w_lim);
                output_onscreen(original, translated);
                break;
            /*
            case WRITE_FILE:
                cout << "Writing to File" << endl;
                get_write_ffunc(out_stream, translated, filename_in, filename_out);
                writing_to_file(out_stream, original, translated, filename_out);
                out_stream.close();
                break;
            */

        }



    } while (choice != QUIT);

    in_stream.close();
    out_stream.close();

    cout << "Closing... Thanks for running!" << endl;
    return 0;
}

/* Clears original and translated words for a new set.
Input: Original and Translated words
Output: Empty original and translated
*/
void clearfunc(string& original, string& translated)
{
    translated.erase(0,translated.length());
    original.erase(0, original.length());
}

/* Introduces user to program and lists options.
Input: None
Output: Intro, menu options
*/
void menu()
{
    cout << "Hello. Welcome to the Ubbi Dubbi Translator Program."<< endl;
    cout << "Enter a choice" << endl;
    cout << QUIT << '\t' << "Quit" << endl;
    cout << ENCODE_WORD << '\t' << "Encode a word." << endl;
    cout << READ << '\t' << "Read a file." << endl;
    cout << ENCODE_FILE << '\t' << "Encode a File" << endl;
    cout << WRITE_FILE << '\t' << "Write to a File" << endl;

    return;
}

/* Gets the menu input specified by user. Error corrects so only numbers specified are entered.
Input: User's menu choice
Output: The user's choice to the switch
*/
void get_menu_input(int& choice)
{
    while (!(cin >> choice) || (choice == '\n') || (choice < 0 || choice > 4))
    {
        cout << "Invalid. REenter." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return;
}
/* Inputs the word for the word translation
Input: User inputs word
Output: The original word is sent back for translation
*/
//void input(string& original)
void input(string original[], int w_lim)
{
    cout << "Please input what you want translated." << endl;

    cin >> original[w_lim];
    //string word = original;
    /*
    bool clear = false;
    do
    {
        int index = original.find(' ');
        if (index >= 0)
        {
            int totalchar = 100 - index;
            string tmp = word.substr(index + 1, totalchar);
            word.erase(index + 1, totalchar);
            word = tmp;
            cout << tmp;
        }
        else
        {
            clear = true;
        }
    } while (clear == false);
    */

    return;
}
/* Words are translated here by looking for vowels, both captial and lower case. Translated is assigned to be the original word for translation.
If found, tmp stores all letters after, then deletes everything after including the found vowel in the translated string to add ub or Ub.
Input: original word.
Output: original word and translated word
*/
void encode_wfunc(string original[], string translated[], int w_lim)
{
    translated = original;
    string ub = "ub";
    string Ub = "Ub";
    string tmp;
    string TRANSLATED;

    for (int i = 0; i < w_lim; i++)
    {
        TRANSLATED = translated[i];

        for (int i2 = 0; i2 < TRANSLATED.length(); i2++)
        {

            if ((translated[i].at(i) == 'a') || (translated[i].at(i) == 'e') || (translated[i].at(i) == 'i') || (translated[i].at(i) == 'o') || (translated[i].at(i) == 'u'))
            {

                tmp = TRANSLATED.substr(i2, TRANSLATED.length());
                TRANSLATED.erase(i2, TRANSLATED.length());

                TRANSLATED = translated[i] + ub + tmp;

                translated[i] = TRANSLATED;

                i=i+2;
            }
            /*
            else if ((TRANSLATED.at(i) == 'A') || (TRANSLATED.at(i) == 'E') || (TRANSLATED.at(i) == 'I') || (TRANSLATED.at(i) == 'O') || (TRANSLATED.at(i) == 'U'))
            {
                upper_to_lower_case(TRANSLATED, i2);
                /*
                tmp = translated.substr(i, translated.length());
                translated.erase(i, translated.length());
                translated = translated + Ub + tmp;
                i=i+2;
                */ // **D
                //i--;
            //}
        }

    }

    return;
}
/* Assigns upper case vowels to lower case
Input: The integer point where vowel was found in translated word, translated string
Output: the new translated string with lower cased vowel at i of word.
*/
void upper_to_lower_case(string translated, int i)
{
    if (translated.at(i) == 'A')
        translated[i] = 'a';
    else if (translated.at(i) == 'E')
        translated[i] = 'e';
    else if (translated.at(i) == 'I')
        translated[i] = 'i';
    else if (translated.at(i) == 'O')
        translated[i] = 'o';
    else if (translated.at(i) == 'U')
        translated[i] = 'u';

    return;
}
/* Outputs the original words and translated words onscreen.
Input: Original and translated words
Output: Both onscreen.
*/
//void output_onscreen(string& original, string& translated)
void output_onscreen(string original[], string translated[])
{
    cout << "Original:" << endl;
    cout << original << endl << endl;
    cout << "Translated:" << endl;
    cout << translated << endl << endl;

    return;

}
/* Checks if user wants to return to menu
Input: Response string given by other functions
Output: True if user wants to go back. False if anything else.
*/
bool return_to_menu(string response)
{
    if (response == "<--")
    {
        return true;

    }
    return false;
}
/* Reads the file by asking for the filename. It then checks for .txt extension, and automatically adds it if necessary. Then attempts to open said file.
Input: Filename
Output: the filename with extension and in_stream.
*/
void readfunc(ifstream& in_stream, string& filename_in)
{
    filename_in.erase (0,filename_in.length());
    in_stream.close();
    do
    {
        cout << "Input the name of your file with the file extension .txt." << endl;
        cin >> filename_in;
        /*
        if (return_to_menu(filename_in))
        {
            cout << "Quiting function... Returning to menu." << endl;
            return;
        }

        if (!(valid_filename(filename_in)))
        {
            cout << "FAiled"<< endl;
            filename_in = "abcedf";
        }
        */
        check_fileext(filename_in);

        in_stream.open(filename_in.c_str());
        if (in_stream.fail())
        {
            cout << "Failed to open. Reenter." << endl;
            cin.clear();
            filename_in.erase (0,filename_in.length());
        }

    }
    while (in_stream.fail());

    cout << "Successfully opened " << filename_in << endl;
    return;
}
/*
bool valid_filename(string filename)
{
    for (int i = 0; i < filename.length(); i++)
    {
        if (filename.at(i) >= 'a' || filename.at(i) <= 'z' || filename.at(i) >= 'A' || filename.at(i) <= 'Z' || filename.at(i) >= 0 || filename.at(i) <= 9)
            return true;
        else
        {
            cout << "FAILED" << endl;
            return false;
        }

    }

}
*/

/* Encodes file for transaltion by grabbing each word in the file and combining them into the original string, and then sending them
as word string to translation word function. Then it will retrieve translated file to be combined to form the final translated string.
At 100 words, it will return an error message saying that the limit was reached and stopped translating. In_stream will be closed after finishing.
Input: In_stream of file
Output: Original and translated strings in their final form.
*/
/*
void encode_ffunc(ifstream& in_stream, string& original, string& translated)
{
    string word;
    string translated2; //holder string to get translation for one word for the whole sentence.
    int counter = 0;


    while (in_stream >> word)
    {
        if (counter == 100)
        {
            cout << "You have reached the 100 word limit. Stopping translation..." << endl;
            break;
        }
        encode_wfunc(word, translated2);
        translated = translated + translated2 + " ";
        original = original + word + " ";
        counter++;
    }
    in_stream.close();

    return;
}
*/

/* Grabs the filename for writing to a new file. It first checks if any translation was done, then asks for a filename.
If the user wants to return, they will type <-- arrow, which will be picked up by another function, and return true to go back to the menu.
If not extension found, it will add one if necessary, and then check if the output filename was the same as the input filename.
If it is the same, it will ask again. Finally, it will open the outstream file if all clear.
Input: filename_in for file conflict checking, filename_out as specified by user, translated string for checking if translation was done.
Output: Returns out_stream file for writing.
*/
void get_write_ffunc(ofstream& out_stream, string translated, string& filename_in, string& filename_out)
{
    filename_out.erase (0,filename_out.length());
    if (translated.empty())
    {
        cout << "No translation done. Please do one first." << endl;
        return;
    }

    do
    {
        cout << "Specify name of output file (with file extension .txt)." << endl;
        cin >> filename_out;
        /*
        if (return_to_menu(filename_out))
        {
            return;
        }*/

        check_fileext(filename_out);
    } while (check_file_conflict(filename_in, filename_out) == true);

    out_stream.open(filename_out.c_str());

    return;
}
/* Writes the original and translation to out_stream. Will not do anything if user specified that they want to go back to menu.
Input: Original and translated string, out_stream, filename_out for menu checking.
Output: out_stream writes to file.
*/
void writing_to_file(ofstream& out_stream, string original, string translated, string filename_out)
{

    if (return_to_menu(filename_out))
    {
        return;
    }
    cout << "Writing. Please Wait..." << endl;

    out_stream << "Original:" << endl;
    out_stream << original << endl << endl;
    out_stream << "Translated:" << endl;
    out_stream << translated << endl << endl;


    cout << "Done writing to " << filename_out << endl;
}
/* Checks the file if .txt file extension is included in filename. If not, it will add it automatically.
Input: Filename received from function
Output: Return filename with .txt if not included originally. Otherwise does nothing.
*/
void check_fileext(string& filename)
{

    if (filename.substr(filename.length() - 4, filename.length()) != ".txt")
    {
        filename = filename + ".txt";
        cout << "No file extension found. Adding .txt" << endl;
    }

    return;
}
/* Checks the filenames for conflicting in and out.
Input: Filename_in and FIlename_out
Output: True if conflict found, false if OK.
*/
bool check_file_conflict(string& filename_in, string& filename_out)
{
    if (filename_in == filename_out)
    {
        cout << "Conflicting filenames for in and out found. Enter a different filename" << endl;
        return true;
    }
    return false;
}
