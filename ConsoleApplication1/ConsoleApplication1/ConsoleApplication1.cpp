#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>
using namespace std;

void print_letter(vector<char> words_play, vector<char> words_print)
{
    cout << "\n\n";

    for (auto const& i : words_play)
    {
        bool finding = false;
        for (auto const& j : words_print)
            if (i == j) 
            {
                cout << j << "\t";
                finding = true;
            }
        if (finding != true)
            cout << " " << "\t";
    }

    cout << "\n";
    for (auto const& i : words_play)
        cout << "_\t";

    cout << "\n\n\n";
}

void print_menu(vector<char> words_play, vector<char> words_print)
{
    cout << "\n\n\nЗагаданное слово: \n\n";

    print_letter(words_play, words_print);

    cout << "Поле ввода (Введите один символ): ";
}

void paint_gallows(int glasses_loser)
{
    switch (glasses_loser)
    {
    case 1:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    case 2:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        O             $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    case 3:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        O             $\n"
            "      /   \\           $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    case 4:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        O             $\n"
            "      / | \\           $\n"
            "        |             $\n"
            "                      $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    case 5:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        O             $\n"
            "      / | \\           $\n"
            "        |             $\n"
            "       /              $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    case 6:
        cout << "\n\n";
        cout << "        $$$$$$$$$$$$$$$\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        |             $\n"
            "        O             $\n"
            "      / | \\           $\n"
            "        |             $\n"
            "       / \\            $\n"
            "                      $\n"
            "                      $\n"
            " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
            " $                          $\n";
        cout << "\n\n";
        break;
    default:
        break;
    }
}

int main()
{
    system("chcp 1251");

    time_t start, end;


    time(&start);


    vector<char> words_play{};
    vector<char> words_print{};

    ifstream in("words_dictionary.shifr");
    if (in.is_open())
    {
        string line;

        srand( time(0) );
        int fortune_start = 0;
        int fortune_end = rand() % 5;

        while (getline(in, line))
        {
            if (fortune_start == fortune_end)
            {
                ofstream out("word_play.shifr");
                if (out.is_open())
                    out << line << endl;
                out.close();

                break;
            }
            fortune_start++;
        }
    }
    in.close();


    fstream fin("word_play.shifr", fstream::in);
    if (fin.is_open())
    {
        char ch;

        while (fin >> noskipws >> ch)
            if (ch != '\n')
                words_play.push_back(ch);
    }
    fin.close();


    int glasses_over = 0;
    for (auto const& i : words_play)
        glasses_over += 1;

    int glasses_loser = 0;
    int glasses_win = 0;
    bool play = true;

    while (play)
    {
        back:

        print_menu(words_play, words_print);
        char letter_while;
        cin >> letter_while;

        bool finding = false;
        for (auto const& i : words_play)
        {
            if (letter_while == i)
            {
                for (auto const& i : words_print)
                    if (letter_while == i)
                        goto back;

                words_print.push_back(letter_while);
                glasses_win++;

                finding = true;
            }
        }
        if (finding == false)
        {
            glasses_loser++;
            paint_gallows(glasses_loser);
        }

        if (glasses_win == glasses_over)
        {
            print_letter(words_play, words_print);
            break;
        }
        if (glasses_loser == 6)
            play = false;
    }

    if (play == 1)
        cout << "\n\nПоздравляем с победой!" << endl;
    else
        cout << "\n\nВаше тело ютится на виселице..." << endl;


    time(&end);


    double seconds = difftime(end, start);
    cout << "\n\n\nВремя игры: " << seconds << " секунд;" << endl;

    cout << "\nКоличество попыток: " << glasses_win + glasses_loser << ";" << endl;

    cout << "\nИскомое слово: ";
    for (auto const& i : words_play)
        cout << i;
    cout << ";" << endl;

    cout << "\nВерно введённые символы: ";
    for (auto const& i : words_print)
        cout << i << " ";
    cout << ";" << endl;
}