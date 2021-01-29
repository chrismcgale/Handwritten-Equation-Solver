int calculate(istream &in, ostream &out, int answer) {
  string line, first, second, op;
  getline(in, line);
  istringstream iss(line);
  iss >> first >> second >> op;

  if(first == "S"){
    return calculate(in, out, answer);
  } else if (first == "expr"){
          if(second == "term"){
             return calculate(in, out, answer);
          } else if(op == "-") {
             return calculate(in, out, answer) - calculate(in, out, answer);
          } else if(op == "+") {
             return calculate(in, out, answer) + calculate(in, out, answer);
          } else if(op == "times") {
             return calculate(in, out, answer) * calculate(in, out, answer);
          } else if(op == "forward_slash") {
             return calculate(in, out, answer) / calculate(in, out, answer);
          } 
  } else if(second == "NUM"){
      //int num = stoi(getline(in, line)); // Might need to ss 
      return 42;
  }
  else{
      return calculate(in, out, answer);
  }
}

int main() {
  int answer = 0;
  answer = calculate(std::cin, std::cout, answer);
  cout << answer << endl;
}
