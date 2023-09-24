// Library
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>

// For reducing code redundancy
using namespace std;

// Function to generate random secret number
vector<string> get_secret_num(int max_digit)
{
    // Setting for random number
    random_device rd;  // Seed for random number generator
    mt19937 gen(rd()); // Random number generator

    // Create vector for random_string_list
    vector<string> random_string_list;
    uniform_int_distribution<int> distr(0, 9); // Distribution for random numbers

    for (int number = 1; number <= max_digit; number += 1)
    {
        int random_number = distr(gen); // Generate a random number using the distribution and generator
        string random_string = to_string(random_number);
        random_string_list.push_back(random_string);
    }
    return random_string_list;
}

// Function to provide clues to the user
vector<string> get_clues(vector<string> random_string_list, vector<string> guess_num) {
    vector<string> clues_list;
    // If secret number matches guess number
    if (random_string_list == guess_num) {
        clues_list.push_back("You got it!");
        return clues_list;
    }
    bool found;
    // To compare the answer given with secret number
    for (int digit = 0; digit < guess_num.size(); digit++) {
        found = false;
        for (int index = 0; index < random_string_list.size(); index++) {
            if (guess_num[digit] == random_string_list[index]) {
                if (digit == index) {
                    clues_list.push_back("Fermi"); //If position is correct
                }
                else {
                    clues_list.push_back("Pico"); //If position is incorrect
                }
                found = true;
                break;
            }
        }
        if (!found) {
            clues_list.push_back("Bagels"); //If element does not exist
        }
    }
    // If input is empty
    if (clues_list.empty()) {
        clues_list.push_back("Try again");
    }
    return clues_list;
}


// Function to get user guess and validate the input
vector<string> get_user_guess(int max_digit)
{
    vector<string> guess;
    string user_input;

    // To validate obtain and validate input
    while (user_input.length() != max_digit)
    {
        cout << "Guess a " << max_digit << "-digit number: ";
        cin >> user_input;

        // Check if input only contain number in string
        if (user_input.length() != max_digit || find_if_not(user_input.begin(), user_input.end(), [](char c) { return std::isdigit(c); }) != user_input.end())
        {
            cout << "ERROR: Please enter a valid " << max_digit << "-digit number." << endl;
            continue;
        }
    }
    // Add input into guess vector
    for (int letter = 0; letter < user_input.size(); letter++)
    {
        guess.push_back(string(1, user_input[letter]));
    }
    return guess;
}

// Main program
int main()
{
    int max_digit, max_try;
    bool gameover = false;

    cout << "Bagels, a deductive logic game." << endl;
    cout << "Here are some clues:" << endl;
    cout << "When I say:\tThat means:" << endl;
    cout << "  Pico\t\tOne digit is correct but in the wrong position." << endl;
    cout << "  Fermi\t\tOne digit is correct and in the right position." << endl;
    cout << "  Bagels\tNo digit is correct." << endl;

    cout << "Enter the number of digits in the secret number: \n";
    cin >> max_digit;
    cout << "Enter the maximum number of guesses allowed: \n";
    cin >> max_try;

    vector<string> secret_num = get_secret_num(max_digit);

    cout << "I have thought up a number. You have " << max_try << " guesses to get it." << endl;
    cout << "I am thinking of a " << max_digit << "-digit number. Try to guess what it is." << endl << endl;

    while (!gameover && max_try > 0)
    {
        vector<string> user_guess = get_user_guess(max_digit);
        vector<string> clue_number = get_clues(secret_num, user_guess);

        // Print out clues
        for (string clue : clue_number) {
            cout << clue << " ";
        }
        cout << endl;
        max_try--;

        if (user_guess == secret_num)
        {
            gameover = true;
        }
        else if (max_try == 0)
        {
            cout << "Sorry, you ran out of guesses. The number was ";
            for (int index = 0; index < secret_num.size(); index++)
            {
                cout << secret_num[index] << " ";
            }
            cout << "\n";
        }
        else
        {
            cout << "Guess #" << max_try << ":" << endl;
            cout << "\n";
        }
    }
    cout << "Do you want to play again? (yes or no)" << endl;
    string playAgain = "";
    cin >> playAgain;
    if (playAgain == "yes")
    {
        main();
    }
    else
    {
        cout << "Thanks for playing!" << endl;
    }
    return 0;
}