#include <string>
#include <vector>
#include <set>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <utility>
#include <set>
#include <array>
using namespace std;
/* Scans a single line of input and produces a list of tokens.
 *
 */

/* A scanned token produced by the scanner.
 * The "kind" tells us what kind of token it is
 * while the "lexeme" tells us exactly what text
 * the programmer typed. For example, the token
 * "abc" might have kind "ID" and lexeme "abc".
 *
 * While you can create tokens with any kind and
 * lexeme, the list of kinds produced by the
 * starter code can be found in the documentation
 * for scan above.
 */
class Token {
	public:
		enum Kind {
			NUM,
			LPAREN,
			RPAREN,
			MINUS,
			PI,
		};

	private:
		Kind kind;
		std::string lexeme;

	public:
		Token(Kind kind, std::string lexeme);

		Kind getKind() const;
		const std::string &getLexeme() const;

		int64_t toLong() const;

};

std::ostream &operator<<(std::ostream &out, const Token &tok);

/* An exception class thrown when an error is encountered while scanning.
*/
class ScanningFailure {
	std::string message;

	public:
	ScanningFailure(std::string message);

	// Returns the message associated with the exception.
	const std::string &what() const;
};


/*
 * C++ Starter code for CS241 A3
 * All code requires C++14, so if you're getting compile errors make sure to
 * use -std=c++14.
 *
 * This file contains helpers for asm.cc and you don't need to modify it.
 * Furthermore, while this code may be helpful to understand starting with
 * the DFA assignments, you do not need to understand it to write the assembler.
 */

Token::Token(Token::Kind kind, std::string lexeme):
	kind(kind), lexeme(std::move(lexeme)) {}

	Token:: Kind Token::getKind() const { return kind; }
	const std::string &Token::getLexeme() const { return lexeme; }

	std::ostream &operator<<(std::ostream &out, const Token &tok) {
		switch (tok.getKind()) {
			case Token::NUM:      out << "NUM";      break;
			case Token::LPAREN:     out << "LPAREN";     break;
			case Token::RPAREN:     out << "RPAREN";     break;
			case Token::PLUS:       out << "PLUS";       break;
			case Token::MINUS:       out << "MINUS";       break;
			case Token::STAR:       out << "STAR";       break;
			case Token::SLASH:       out << "SLASH";       break;
			case Token::PCT:       out << "PCT";       break;
		}
		out << " " << tok.getLexeme();

		return out;
	}

int64_t Token::toLong() const {
	std::istringstream iss;
	int64_t result;

	if (kind == NUM) {
		iss.str(lexeme);
	} else {
		// This should never happen if the user calls this function correctly
		return 0;
	}

	iss >> result;
	return result;
}

ScanningFailure::ScanningFailure(std::string message):
	message(std::move(message)) {}

	const std::string &ScanningFailure::what() const { return message; }

	/* Represents a DFA (which you will see formally in class later)
	 * to handle the scanning
	 * process. You should not need to interact with this directly:
	 * it is handled through the starter code.
	 */
	class AsmDFA {
		public:
			enum State {
				// States that are also kinds
				NUM,
				LPAREN,
				RPAREN,
				EQ,
				PLUS,
				STAR,
				SLASH,
				PCT,
				// States that are not also kinds
				FAIL,
				START,
				ZERO,
				MINUS,


				LARGEST_STATE = MINUS
			};

		private:
			/* A set of all accepting states for the DFA.
			 * Currently non-accepting states are not actually present anywhere
			 * in memory, but a list can be found in the constructor.
			 */
			std::set<State> acceptingStates;

			/*
			 * The transition function for the DFA, stored as a map.
			 */

			std::array<std::array<State, 128>, LARGEST_STATE + 1> transitionFunction;

			/*
			 * Converts a state to a kind to allow construction of Tokens from States.
			 * Throws an exception if conversion is not possible.
			 */
			Token::Kind stateToKind(State s) const {
				switch(s) {
					case NUM:      return Token::NUM;
					case LPAREN:     return Token::LPAREN;
					case RPAREN:     return Token::RPAREN;
					case ZERO:       return Token::NUM;
					case EQ:     return Token::EQ;
					case PLUS:        return Token::PLUS;
					case MINUS:        return Token::MINUS;
					case STAR:        return Token::STAR;
					case SLASH:        return Token::SLASH;
					case PCT:        return Token::PCT;
					default: throw ScanningFailure("ERROR: Cannot convert state to kind.");
				}
			}


		public:
			/* Tokenizes an input string according to the SMM algorithm.
			 * You will learn the SMM algorithm in class around the time of Assignment 6.
			 */
			std::vector<Token> simplifiedMaximalMunch(const std::string &input) const {
				std::vector<Token> result;

				State state = start();
				std::string munchedInput;

				// We can't use a range-based for loop effectively here
				// since the iterator doesn't always increment.
				for (std::string::const_iterator inputPosn = input.begin();
						inputPosn != input.end();) {
					State oldState = state;
					state = transition(state, *inputPosn);

					if (!failed(state)) {
						munchedInput += *inputPosn;
						oldState = state;

						++inputPosn;
					}

					if (inputPosn == input.end() || failed(state)) {
						if (accept(oldState)) {
							if(Token(stateToKind(oldState), munchedInput).toLong() > 2147483647){
								throw ScanningFailure("ERROR: Numeric literal out of range "
                                                                        + munchedInput);
							}
							result.push_back(Token(stateToKind(oldState), munchedInput));

							munchedInput = "";
							state = start();
						} else {
							if (failed(state)) {
								munchedInput += *inputPosn;
							}
							throw ScanningFailure("ERROR: Simplified maximal munch failed on input: "
									+ munchedInput);
						}
					}
				}

				return result;
			}

			/* Initializes the accepting states for the DFA.
			*/
			AsmDFA() {
				acceptingStates = {ID,
					NUM,
					ZERO,
					LPAREN,
					RPAREN,
					EQ,
					PLUS,
					MINUS,
					STAR,
					SLASH,
					PCT,
					};
				//Non-accepting states are DOT, MINUS, ZEROX, DOLLARS, START

				// Initialize transitions for the DFA
				for (size_t i = 0; i < transitionFunction.size(); ++i) {
					for (size_t j = 0; j < transitionFunction[0].size(); ++j) {
						transitionFunction[i][j] = FAIL;
					}
				}

				registerTransition(START, "+", PLUS);
				registerTransition(START, "*", STAR);
				registerTransition(START, "/", SLASH);
				registerTransition(START, "=", BECOMES);
				registerTransition(START, "0", ZERO);
				registerTransition(START, "123456789", NUM);
				registerTransition(START, "-", MINUS);
				registerTransition(START, "%", PCT);
				registerTransition(START, ",", COMMA);
				registerTransition(START, "(", LPAREN);
				registerTransition(START, ")", RPAREN);
				registerTransition(START, "!", NOT);
				registerTransition(START, "&", AMP);
				registerTransition(BECOMES, "=", EQ);
				registerTransition(LT, "=", LE);
				registerTransition(GT, "=", GE);
				registerTransition(NOT, "=", NE);
		                registerTransition(SLASH, "/", COMMENT);
				registerTransition(NUM, isdigit,  NUM);
				registerTransition(WHITESPACE, isspace, WHITESPACE);
			}

			// Register a transition on all chars in chars
			void registerTransition(State oldState, const std::string &chars,
					State newState) {
				for (char c : chars) {
					transitionFunction[oldState][c] = newState;
				}
			}

			// Register a transition on all chars matching test
			// For some reason the cctype functions all use ints, hence the function
			// argument type.
			void registerTransition(State oldState, int (*test)(int), State newState) {

				for (int c = 0; c < 128; ++c) {
					if (test(c)) {
						transitionFunction[oldState][c] = newState;
					}
				}
			}

			/* Returns the state corresponding to following a transition
			 * from the given starting state on the given character,
			 * or a special fail state if the transition does not exist.
			 */
			State transition(State state, char nextChar) const {
				return transitionFunction[state][nextChar];
			}

			/* Checks whether the state returned by transition
			 * corresponds to failure to transition.
			 */
			bool failed(State state) const { return state == FAIL; }

			/* Checks whether the state returned by transition
			 * is an accepting state.
			 */
			bool accept(State state) const {
				return acceptingStates.count(state) > 0;
			}

			/* Returns the starting state of the DFA
			*/
			State start() const { return START; }
	};

std::vector<Token> scan(const std::string &input) {
	static AsmDFA theDFA;

	std::vector<Token> tokens = theDFA.simplifiedMaximalMunch(input);

	// We need to:
	// * Throw exceptions for WORD tokens whose lexemes aren't ".word".
	// * Remove WHITESPACE and COMMENT tokens entirely.

	std::vector<Token> newTokens;

	for (auto &token : tokens) {
			newTokens.push_back(token);
	}

	return newTokens;
}


int main() {
	std::string line;

	try {
		while (getline(std::cin, line)) {
			// For example, just print the scanned tokens
			std::vector<Token> tokenLine = scan(line);
			for (auto &token : tokenLine) {
				std::cout << token << endl;

			}
		}
	} catch (ScanningFailure &f) {
		std::cerr << f.what() << std::endl;

		return 1;
	}

	return 0;
}
