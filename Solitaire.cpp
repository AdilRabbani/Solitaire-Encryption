#include <iostream>
#include <string.h>
#include <conio.h>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

string Solitaire_Encrypt(deque<int> message) {

	deque<int> deck;
	deque<int> keystreams;

	int mydeck[] = { 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 3 ,6 ,9, 12, 15, 18, 21, 24, 27, 2, 5, 8, 11, 14, 17, 20, 23, 26 };

	for (int i = 0; i < 28; i++) {
		deck.push_back(mydeck[i]);
	}

	for (int k = 0; k < message.size(); k++) {

		for (int i = 0; i < deck.size(); i++) {

			if (deck[i] == 27 && (i + 1) != 28) {
				swap(deck[i], deck[i + 1]);
				break;
			}

			if (deck[i] == 27 && (i + 1) == 28) {
				swap(deck[i], deck[0]);
				break;
			}
		}


		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == 28 && (i + 2 != 28)) {
				swap(deck[i], deck[i + 1]);
				swap(deck[i + 1], deck[i + 2]);
				break;

			}

			else if (deck[i] == 28 && (i + 1 == 28)) {
				swap(deck[i], deck[0]);
				swap(deck[0], deck[1]);
			}

			else if (deck[i] == 28 && (i + 2 == 28)) {
				swap(deck[i], deck[i + 1]);
				swap(deck[i + 1], deck[0]);
			}

		}


		int i_for_28;
		int i_for_27;
		int first_joker;
		int second_joker;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == 27) {
				i_for_27 = i;
			}
			if (deck[i] == 28) {
				i_for_28 = i;
			}
		}

		if (i_for_27 < i_for_28) {
			first_joker = 27;
			second_joker = 28;
		}

		else {
			first_joker = 28;
			second_joker = 27;
		}



		deque<int> first_part;
		deque<int> second_part;

		int first_jokers_position;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == first_joker) {
				first_jokers_position = i;
			}
		}

		if (first_jokers_position != 0) {

			int i = 0;
			do {
				first_part.push_back(deck[i]);
				i = i + 1;
				if (i == 28) {
					break;
				}
			} while (deck[i] != first_joker);

		}



		int second_jokers_position;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == second_joker) {
				second_jokers_position = i;
			}
		}

		int i;
		if (second_jokers_position + 1 != 28) {

			i = second_jokers_position + 1;

			for (i;i < deck.size();i++) {
				second_part.push_back(deck[i]);
			}

		}

		while (deck.front() != first_joker) {
			deck.pop_front();
		}

		while (deck.back() != second_joker) {
			deck.pop_back();
		}

		for (int i = 0; i < first_part.size();i++) {
			deck.push_back(first_part[i]);
		}




		/*do {
			deck.push_front(second_part.back());
			second_part.pop_back();
		} while (!second_part.empty());
*/


		while (!second_part.empty()) {
			deck.push_front(second_part.back());
			second_part.pop_back();
		}

		first_part.~deque();
		second_part.~deque();

		int bottom_card = deck.back();

		deque<int> first_bottom_card_cards;

		i = 0;

		while (i != bottom_card) {
			first_bottom_card_cards.push_back(deck[i]);
			i = i + 1;
		}




		deque<int> newdeck;


		for (int i = 0; i < deck.size() - 1; i++) {
			newdeck.push_back(deck[i]);
		}

		for (int i = 0; i < first_bottom_card_cards.size(); i++) {
			newdeck.push_back(first_bottom_card_cards[i]);
		}

		newdeck.push_back(deck.back());

		deck = newdeck;

		i = 0;

		while (i != bottom_card) {
			deck.pop_front();
			i = i + 1;
		}

		int top_card = deck.front();

		int keystream_value;

		if (top_card == 28) {
			keystream_value = deck.back();
		}

		else {
			keystream_value = deck[top_card];
		}
		

	//	cout << "Keystream value : " << keystream_value << endl;

		keystreams.push_back(keystream_value);

	}

	deque<int> encrypted_message_;

	for (int i = 0; i < message.size(); i++) {
		int value = message[i] + keystreams[i];
		if (value > 26) {
			value = value - 26;
		}
		encrypted_message_.push_back(value);
	}

	string encrypted_message;

	for (int i = 0; i < encrypted_message_.size(); i++) {
		char character = encrypted_message_[i] + 64;
		encrypted_message.push_back(character);
	}

	return encrypted_message;

}

string Solitaire_Decrypt(deque<int> message) {

	deque<int> deck;
	deque<int> keystreams;

	int mydeck[] = { 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 3 ,6 ,9, 12, 15, 18, 21, 24, 27, 2, 5, 8, 11, 14, 17, 20, 23, 26 };

	for (int i = 0; i < 28; i++) {
		deck.push_back(mydeck[i]);
	}

	for (int k = 0; k < message.size(); k++) {

		for (int i = 0; i < deck.size(); i++) {

			if (deck[i] == 27 && (i + 1) != 28) {
				swap(deck[i], deck[i + 1]);
				break;
			}

			if (deck[i] == 27 && (i + 1) == 28) {
				swap(deck[i], deck[0]);
				break;
			}
		}


		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == 28 && (i + 2 != 28)) {
				swap(deck[i], deck[i + 1]);
				swap(deck[i + 1], deck[i + 2]);
				break;

			}

			else if (deck[i] == 28 && (i + 1 == 28)) {
				swap(deck[i], deck[0]);
				swap(deck[0], deck[1]);
			}

			else if (deck[i] == 28 && (i + 2 == 28)) {
				swap(deck[i], deck[i + 1]);
				swap(deck[i + 1], deck[0]);
			}

		}


		int i_for_28;
		int i_for_27;
		int first_joker;
		int second_joker;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == 27) {
				i_for_27 = i;
			}
			if (deck[i] == 28) {
				i_for_28 = i;
			}
		}

		if (i_for_27 < i_for_28) {
			first_joker = 27;
			second_joker = 28;
		}

		else {
			first_joker = 28;
			second_joker = 27;
		}



		deque<int> first_part;
		deque<int> second_part;

		int first_jokers_position;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == first_joker) {
				first_jokers_position = i;
			}
		}

		if (first_jokers_position != 0) {

			int i = 0;
			do {
				first_part.push_back(deck[i]);
				i = i + 1;
				if (i == 28) {
					break;
				}
			} while (deck[i] != first_joker);

		}



		int second_jokers_position;

		for (int i = 0; i < deck.size(); i++) {
			if (deck[i] == second_joker) {
				second_jokers_position = i;
			}
		}

		int i;
		if (second_jokers_position + 1 != 28) {

			i = second_jokers_position + 1;

			for (i;i < deck.size();i++) {
				second_part.push_back(deck[i]);
			}

		}

		while (deck.front() != first_joker) {
			deck.pop_front();
		}

		while (deck.back() != second_joker) {
			deck.pop_back();
		}

		for (int i = 0; i < first_part.size();i++) {
			deck.push_back(first_part[i]);
		}


		while (!second_part.empty()) {
			deck.push_front(second_part.back());
			second_part.pop_back();
		}

		first_part.~deque();
		second_part.~deque();

		int bottom_card = deck.back();

		deque<int> first_bottom_card_cards;

		i = 0;

		while (i != bottom_card) {
			first_bottom_card_cards.push_back(deck[i]);
			i = i + 1;
		}

		deque<int> newdeck;


		for (int i = 0; i < deck.size() - 1; i++) {
			newdeck.push_back(deck[i]);
		}

		for (int i = 0; i < first_bottom_card_cards.size(); i++) {
			newdeck.push_back(first_bottom_card_cards[i]);
		}

		newdeck.push_back(deck.back());

		deck = newdeck;

		i = 0;

		while (i != bottom_card) {
			deck.pop_front();
			i = i + 1;
		}

		int top_card = deck.front();

		int keystream_value;

		if (top_card == 28) {
			keystream_value = deck.back();
		}

		else {
			keystream_value = deck[top_card];
		}


		//	cout << "Keystream value : " << keystream_value << endl;

		keystreams.push_back(keystream_value);

	}

	deque<int> decrypted_message_;

	for (int i = 0; i < message.size(); i++) {
		int value = message[i] - keystreams[i];
		if (value < 0) {
			value = value + 26;
		}
		decrypted_message_.push_back(value);
	}

	string decrypted_message;

	for (int i = 0; i < decrypted_message_.size(); i++) {
		char character = decrypted_message_[i] + 64;
		decrypted_message.push_back(character);
	}

	return decrypted_message;

}



int main() {

	string message;

	cout << "Enter a message : "; cin >> message;

	transform(message.begin(), message.end(), message.begin(), toupper);
	
	deque<int> message_;
	deque<int> encrypted_message_;

	int i = 0;

	cout << endl << "          ";

	while (message[i] != 0) {
		cout << message[i];
		int converted = message[i];
		converted = converted - 64;
		message_.push_back(converted);
		i = i + 1;
	}

	cout << endl;

	for (int i = 0; i < message_.size(); i++) {
		cout << message_[i] << " ";
	}

	cout << endl;

	string encrypted_message = Solitaire_Encrypt(message_);

	cout << endl << "          " << encrypted_message << endl;

	i = 0;

	while (encrypted_message[i] != 0) {
		int converted = encrypted_message[i];
		converted = converted - 64;
		encrypted_message_.push_back(converted);
		i = i + 1;
	}

	cout << endl;

	for (int i = 0; i < encrypted_message_.size(); i++) {
		cout << encrypted_message_[i] << " ";
	}

	cout << endl << endl << "           " "DECRYPTING : " << endl;

	string decrypted_message = Solitaire_Decrypt(encrypted_message_);

	cout << endl << "          " << decrypted_message << endl;

	_getch();
}