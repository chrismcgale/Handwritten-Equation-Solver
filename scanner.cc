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
 * Scan returns tokens with the following kinds:
 * ID: identifiers and keywords.
 * LABEL: labels (identifiers ending in a colon).
 * WORD: the special ".word" keyword.
 * COMMA: a comma.
 * LPAREN: a left parenthesis.
 * RPAREN: a right parenthesis.
 * INT: a signed or unsigned 32-bit integer written in decimal.
 * HEXINT: an unsigned 32-bit integer written in hexadecimal.
 * REG: a register between $0 and $31.
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
			ID = 0,
			NUM,
			LPAREN,
			RPAREN,
			INT,
			EQ,
			NE,
			LT,
			GT,
			LE,
			GE,
			PLUS,
			MINUS,
			TIMES,
			FORWARD_SLASH,
			DIV,
		};

	private:
		Kind kind;
		std::string lexeme;

	public:
		Token(Kind kind, std::string lexeme);

		Kind getKind() const;
		const std::string &getLexeme() const;

		/* Only works on tokens of type INT, HEXINT, or REG
		 *
		 * Although all results will be integers, this function
		 * returns a long since the result may be either signed
		 * or unsigned, and thus may lie anywhere in the range
		 * -2147483648 .. 4294967295
		 */
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
			case Token::ID:         out << "ID";         break;
			case Token::NUM:      out << "NUM";      break;
			case Token::LBRACE:       out << "LBRACE";       break;
			case Token::RBRACE:       out << "RBRACE";       break;
			case Token::RETURN:       out << "RETURN";       break;
			case Token::IF:       out << "IF";       break;
			case Token::ELSE:       out << "ELSE";       break;
			case Token::COMMA:      out << "COMMA";      break;
			case Token::LPAREN:     out << "LPAREN";     break;
			case Token::RPAREN:     out << "RPAREN";     break;
			case Token::WHILE:       out << "WHILE";       break;
			case Token::PRINTLN:       out << "PRINTLN";       break;
			case Token::WAIN:       out << "WAIN";       break;
			case Token::BECOMES:       out << "BECOMES";       break;
			case Token::INT:       out << "INT";       break;
			case Token::EQ:       out << "EQ";       break;
			case Token::NE:       out << "NE";       break;
			case Token::LT:       out << "LT";       break;
					      case Token::GT:       out << "GT";       break;
								    case Token::LE:       out << "LE";       break;
			case Token::GE:       out << "GE";       break;
			case Token::PLUS:       out << "PLUS";       break;
			case Token::MINUS:       out << "MINUS";       break;
			case Token::STAR:       out << "STAR";       break;
			case Token::SLASH:       out << "SLASH";       break;
			case Token::PCT:       out << "PCT";       break;
			case Token::SEMI:       out << "SEMI";       break;
			case Token::NEW:       out << "NEW";       break;
			case Token::DELETE:        out << "DELETE";        break;
			case Token::LBRACK:     out << "LBRACK";     break;
			case Token::RBRACK:        out << "RBRACK";        break;
			case Token::AMP: out << "AMP"; break;
			case Token::NULl:    out << "NULL";    break;
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
				ID = 0,
				NUM,
				LPAREN,
				RPAREN,
				LBRACE,
				RBRACE,
				RETURN,
				IF,
				ELSE,
				WHILE,
				PRINTLN,
				WAIN,
				BECOMES,
				INT,
				EQ,
				NE,
				LT,
				GT,
				LE,
				GE,
				PLUS,
				STAR,
				SLASH,
				PCT,
				COMMA,
				SEMI,
				n,
				ne,
				NEW,
				DELETE,
				LBRACK,
				RBRACK,
				AMP,
				NULl,
				WHITESPACE,
				COMMENT,
				// States that are not also kinds
				FAIL,
				START,
				ZERO,
				MINUS,
				I,
				IN,
				E,
				EL,
				ELS,
				W,
				WH,
				WHI,
				WHIL,
				D,
				DE,
				DEL,
				DELE,
				DELET,
				N,
				NU,
				NUL,
				WA,
				WAI,
				P,
				PR,
				PRI,
				PRIN,
				PRINT,
				PRINTL,
				R,
				RE,
				RET,
				RETU,
				RETUR,
				NOT,


				LARGEST_STATE = NOT
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
					case ID:         return Token::ID;
					case NUM:      return Token::NUM;
					case LBRACE:      return Token::LBRACE;
					case RBRACE:      return Token::RBRACE;
					case R:         return Token::ID;
					case RE:         return Token::ID;
					case RET:         return Token::ID;
					case RETU:         return Token::ID;
					case RETUR:         return Token::ID;
					case RETURN:      return Token::RETURN;
					case I:         return Token::ID;
					case IF:      return Token::IF;
					case E:         return Token::ID;
					case EL:         return Token::ID;
					case ELS:         return Token::ID;
					case ELSE:      return Token::ELSE;
					case W:         return Token::ID;
					case WH:         return Token::ID;
					case WHI:         return Token::ID;
					case WHIL:         return Token::ID;
					case WHILE:      return Token::WHILE;
					case P:         return Token::ID;
					case PR:         return Token::ID;
					case PRI:         return Token::ID;
					case PRIN:         return Token::ID;
					case PRINT:         return Token::ID;
					case PRINTL:         return Token::ID;
					case PRINTLN:      return Token::PRINTLN;
					case WA:         return Token::ID;
					case WAI:         return Token::ID;
					case WAIN:      return Token::WAIN;
					case BECOMES:      return Token::BECOMES;
					case COMMA:      return Token::COMMA;
					case LPAREN:     return Token::LPAREN;
					case RPAREN:     return Token::RPAREN;
					case RBRACK: return Token::RBRACK;
					case IN:         return Token::ID;
					case INT:        return Token::INT;
					case ZERO:       return Token::NUM;
					case EQ:     return Token::EQ;
					case NE:        return Token::NE;
					case LT:        return Token::LT;
					case GT:        return Token::GT;
					case LE:        return Token::LE;
					case GE:        return Token::GE;
					case PLUS:        return Token::PLUS;
					case MINUS:        return Token::MINUS;
					case STAR:        return Token::STAR;
					case SLASH:        return Token::SLASH;
					case PCT:        return Token::PCT;
					case SEMI:        return Token::SEMI;
					case N:         return Token::ID;
							case n:         return Token::ID;
					case ne:         return Token::ID;
					case NEW:        return Token::NEW;
					case D:         return Token::ID;
					case DE:         return Token::ID;
					case DEL:         return Token::ID;
					case DELE:         return Token::ID;
					case DELET:         return Token::ID;
					case DELETE:        return Token::DELETE;
					case LBRACK:        return Token::LBRACK;
					case AMP: return Token::AMP;
					case NU:         return Token::ID;
					case NUL:         return Token::ID;
					case NULl:    return Token::NULl;
					case WHITESPACE:    return Token::WHITESPACE;
					case COMMENT:    return Token::COMMENT;
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
					LBRACE,
					RBRACE,
					R,
					RE,
					RET,
					RETU,
					RETUR,
					RETURN,
					I,
					IF,
					E,
					EL,
					ELS,
					ELSE,
					W,
					WH,
					WHI,
					WHIL,
					WHILE,
					P,
					PR,
					PRI,
					PRIN,
					PRINT,
					PRINTL,
					PRINTLN,
					W,
					WA,
					WAI,
					WAIN,
					BECOMES,
					IN,
					INT,
					EQ,
					NE,
					LT,
					GT,
					LE,
					GE,
					PLUS,
					MINUS,
					STAR,
					SLASH,
					PCT,
					COMMA,
					SEMI,
					N,
					n,
					ne,
					NEW,
					D,
					DE,
					DEL,
					DELE,
					DELET,
					DELETE,
					LBRACK,
					RBRACK,
					AMP,
					NU,
					NUL,
					NULl, WHITESPACE, COMMENT};
				//Non-accepting states are DOT, MINUS, ZEROX, DOLLARS, START

				// Initialize transitions for the DFA
				for (size_t i = 0; i < transitionFunction.size(); ++i) {
					for (size_t j = 0; j < transitionFunction[0].size(); ++j) {
						transitionFunction[i][j] = FAIL;
					}
				}

				registerTransition(START, isalpha, ID);
				registerTransition(START, "+", PLUS);
				registerTransition(START, "*", STAR);
				registerTransition(START, "/", SLASH);
				registerTransition(START, "=", BECOMES);
				registerTransition(START, "0", ZERO);
				registerTransition(START, "123456789", NUM);
				registerTransition(START, "-", MINUS);
				registerTransition(START, ";", SEMI);
				registerTransition(START, isspace, WHITESPACE);
				registerTransition(START, "%", PCT);
				registerTransition(START, ",", COMMA);
				registerTransition(START, "(", LPAREN);
				registerTransition(START, ")", RPAREN);
				registerTransition(START, "<", LT);
				registerTransition(START, ">", GT);
				registerTransition(START, "[", LBRACK);
				registerTransition(START, "]", RBRACK);
				registerTransition(START, "{", LBRACE);
				registerTransition(START, "}", RBRACE);
				registerTransition(START, "!", NOT);
				registerTransition(START, "&", AMP);
				registerTransition(START, "i", I);
				registerTransition(I, isalnum, ID);
				registerTransition(I, "f", IF); 
				registerTransition(IF, isalnum, ID);
				registerTransition(I, "n", IN);
				registerTransition(IN, isalnum, ID);
				registerTransition(IN, "t", INT);
				registerTransition(INT, isalnum, ID);
				registerTransition(START, "r", R);
				registerTransition(R, isalnum, ID);
				registerTransition(R, "e", RE);
				registerTransition(RE, isalnum, ID);
				registerTransition(RE, "t", RET);
				registerTransition(RET, isalnum, ID);
				registerTransition(RET, "u", RETU);
				registerTransition(RETU, isalnum, ID);
				registerTransition(RETU, "r", RETUR);
				registerTransition(RETUR, isalnum, ID);
				registerTransition(RETUR, "n", RETURN);
				registerTransition(RETURN, isalnum, ID);
				registerTransition(START, "w", W);
				registerTransition(W, isalnum, ID);
				registerTransition(W, "h", WH);
				registerTransition(WH, isalnum, ID);
				registerTransition(WH, "i", WHI);
				registerTransition(WHI, isalnum, ID);
				registerTransition(WHI, "l", WHIL);
				registerTransition(WHIL, isalnum, ID);
				registerTransition(WHIL, "e", WHILE);
				registerTransition(WHILE, isalnum, ID);
				registerTransition(START, "e", E);
				registerTransition(E, isalnum, ID);
				registerTransition(E, "l", EL);
				registerTransition(EL, isalnum, ID);
				registerTransition(EL, "s", ELS);
				registerTransition(ELS, isalnum, ID);
				registerTransition(ELS, "e", ELSE);
				registerTransition(ELSE, isalnum, ID);
				registerTransition(START, "p", P);
				registerTransition(P, isalnum, ID);
				registerTransition(P, "r", PR);
				registerTransition(PR, isalnum, ID);
				registerTransition(PR, "i", PRI);
				registerTransition(PRI, isalnum, ID);
				registerTransition(PRI, "n", PRIN);
				registerTransition(PRIN, isalnum, ID);
				registerTransition(PRIN, "t", PRINT);
				registerTransition(PRINT, isalnum, ID);
				registerTransition(PRINT, "l", PRINTL);
				registerTransition(PRINTL, isalnum, ID);
				registerTransition(PRINTL, "n", PRINTLN);
				registerTransition(PRINTLN, isalnum, ID);
				registerTransition(START, "w", W);
				registerTransition(W, "a", WA);
				registerTransition(WA, isalnum, ID);
				registerTransition(WA, "i", WAI);
				registerTransition(WAI, isalnum, ID);
				registerTransition(WAI, "n", WAIN);
				registerTransition(WAIN, isalnum, ID);
				registerTransition(START, "d", D);
				registerTransition(D, isalnum, ID);
				registerTransition(D, "e", DE);
				registerTransition(DE, isalnum, ID);
				registerTransition(DE, "l", DEL);
				registerTransition(DEL, isalnum, ID);
				registerTransition(DEL, "e", DELE);
				registerTransition(DELE, isalnum, ID);
				registerTransition(DELE, "t", DELET);
				registerTransition(DELET, isalnum, ID);
				registerTransition(DELET, "e", DELETE);
				registerTransition(DELETE, isalnum, ID);
				registerTransition(START, "n", n);
				registerTransition(n, isalnum, ID);
				registerTransition(n, "e", ne);
				registerTransition(ne, isalnum, ID);
				registerTransition(ne, "w", NEW);
				registerTransition(NEW, isalnum, ID);
				registerTransition(START, "N", N);
                                registerTransition(N, isalnum, ID);
				registerTransition(N, "U", NU);
				registerTransition(NU, isalnum, ID);
				registerTransition(NU, "L", NUL);
				registerTransition(NUL, isalnum, ID);
				registerTransition(NUL, "L", NULl);
				registerTransition(NULl, isalnum, ID);
				registerTransition(ID, isalnum, ID);
				registerTransition(BECOMES, "=", EQ);
				registerTransition(LT, "=", LE);
				registerTransition(GT, "=", GE);
				registerTransition(NOT, "=", NE);
		                registerTransition(SLASH, "/", COMMENT);
				registerTransition(NUM, isdigit,  NUM);
				registerTransition(COMMENT, [](int c) -> int { return c != '\n'; },
						COMMENT);
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
		if (token.getKind() != Token::WHITESPACE
				&& token.getKind() != Token::Kind::COMMENT) {
			newTokens.push_back(token);
		}
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
