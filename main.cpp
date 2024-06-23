#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename Type>
bool isValidInput(const unordered_set<Type>& set, const Type& input) {
	return set.find(input) != set.end();
}

static void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

static string toLower(const string& data) {
	string lowerData = data;
	transform(lowerData.begin(), lowerData.end(), lowerData.begin(), [](unsigned char c) { return tolower(c); });
	return lowerData;
}

template <typename Type>
Type getValidInput(const unordered_set<Type>& validInputs, const string& prompt) {
	Type input{};
	do {
		clearScreen();
		cout << prompt;
		if constexpr (is_same_v<Type, char>) {
			cin >> input;
			input = tolower(input);
		}
		else if constexpr (is_same_v<Type, string>) {
			getline(cin, input);
			input = toLower(input);
		}
	} while (!isValidInput(validInputs, input));
	return input;
}

string getComputerPick(const unordered_set<string>& options) {
	srand(static_cast<unsigned int>(time(NULL)));
	int index{ static_cast<int>(rand() % options.size()) };
	return *next(options.begin(), index);
}

static void announceWinner(int64_t userIndex, int64_t computerIndex) {
	if (userIndex == computerIndex) {
		cout << "The game ended with a tie." << '\n';
		return;
	}

	if ((userIndex == 0 && computerIndex == 1) || (userIndex == 1 && computerIndex == 2) || (userIndex == 2 && computerIndex == 0)) {
		cout << "The computer won." << '\n';
		return;
	}

	cout << "You won!" << '\n';
}

int main() {
	unordered_set<char> yesNo{ 'y', 'n' };
	unordered_set<string> schaarSteenPapier{ "schaar", "steen", "papier" };

	char readyToPlay = getValidInput(yesNo, "Schaar Steen Papier\nReady to play? (y/n) ");

	if (readyToPlay == 'n') {
		cout << "Ok, maybe next time.";
		return 0;
	}

	do {
		string usersPick{ getValidInput(schaarSteenPapier, "Select your weapon!\nSchaar, steen of papier. ")};
		int64_t userIndex = distance(schaarSteenPapier.begin(), schaarSteenPapier.find(usersPick));

		string computerPick = getComputerPick(schaarSteenPapier);
		int64_t computerIndex = distance(schaarSteenPapier.begin(), schaarSteenPapier.find(computerPick));

		cout << "Computer Picked: " << computerPick << '\n';

		announceWinner(userIndex, computerIndex);

		cin.get();

		readyToPlay = getValidInput(yesNo, "Ready to play again? (y/n) ");

		if (readyToPlay == 'n') {
			cout << "Ok, maybe next time.";
			return 0;
		}
	} while (readyToPlay =='y');

	cout << "How did you get here?" << endl;
	cin.get();
	return 0;
}
