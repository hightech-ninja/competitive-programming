#include <cassert>
#include <cctype>
#include <iostream>
#include <ostream>
#include <print>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

enum class TokenType {
  START, // sentinel
  END,   // sentinel
  MINUS,
  PLUS,
  NUMBER,
  OPEN_SCOPE,
  CLOSE_SCOPE,
  UNARY_MINUS,
};

struct Token {
  TokenType type;
  int pos;
  int len;
};

static unordered_map<TokenType, int> priority = {
    {TokenType::START, 0},       {TokenType::END, 0},
    {TokenType::MINUS, 1},       {TokenType::PLUS, 1},
    {TokenType::OPEN_SCOPE, 0},  {TokenType::CLOSE_SCOPE, 0},
    {TokenType::UNARY_MINUS, 2},
};

/*
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
private:
  vector<Token> tokenize(string s) {
    int n = (int)s.size();
    int pos = 0;
    vector<Token> tokens{};
    tokens.reserve(n + 2);
    tokens.push_back({TokenType::START, 0, 0});
    while (pos < n) {
      while (pos < n && isspace(s[pos]))
        pos++;
      if (pos == n)
        break;
      switch (s[pos]) {
      case '+':
        tokens.push_back({TokenType::PLUS, pos, 1});
        pos++;
        break;
      case '-':
        tokens.push_back({TokenType::MINUS, pos, 1});
        pos++;
        break;
      case '(':
        tokens.push_back({TokenType::OPEN_SCOPE, pos, 1});
        pos++;
        break;
      case ')':
        tokens.push_back({TokenType::CLOSE_SCOPE, pos, 1});
        pos++;
        break;
      default:
        int start = pos;
        while (pos < n && isdigit(s[pos]))
          pos++;
        tokens.push_back({TokenType::NUMBER, start, pos - start});
      }
    }
    tokens.push_back({TokenType::END, n, 0});
    return tokens;
  }

  int atoi(string_view s) {
    int n = 0;
    for (char c : s) {
      n = n * 10 + (c - '0');
    }
    return n;
  }

  void flush_ops(stack<TokenType> &ops, stack<int> &vals, TokenType last,
                 TokenType until = TokenType::START) {
    while (!ops.empty() && priority[ops.top()] >= priority[last]) {
      auto op = ops.top();
      ops.pop();
      switch (op) {
      case TokenType::PLUS: {
        int second = vals.top();
        vals.pop();
        int first = vals.top();
        vals.pop();

        vals.push(first + second);
        break;
      }
      case TokenType::MINUS: {
        int second = vals.top();
        vals.pop();
        int first = vals.top();
        vals.pop();

        vals.push(first - second);
        break;
      }
      case TokenType::UNARY_MINUS: {
        int value = vals.top();
        vals.pop();
        vals.push(-value);
        break;
      }
      default:
        break;
      }
      if (op == until)
        break;
    }
  }

public:
  int calculate(string s) {
    auto tokens = tokenize(s);

    // Keeps: (, +, -
    // Invariants:
    //      - top keeps current unary operator;
    //      - before top are operators of higher or equal priority or operators
    //        guarded with scope "(";
    //      - scope "(" works just as guard for operators;
    stack<TokenType> ops;
    // Keeps values for binary operators
    stack<int> vals;
    int n = (int)tokens.size();
    bool expectNumber = true;

    for (int i = 0; i < n; ++i) {
      auto tok = tokens[i];

      switch (tok.type) {
      case TokenType::OPEN_SCOPE:
        ops.push(tok.type);
        expectNumber = true;
        break;
      case TokenType::NUMBER: {
        auto sv = string_view(s.data() + tok.pos, tok.len);
        vals.push(this->atoi(sv));
        expectNumber = false;
        break;
      }
      case TokenType::PLUS:
        flush_ops(ops, vals, tok.type);
        ops.push(tok.type);
        expectNumber = true;
        break;
      case TokenType::MINUS:
        if (expectNumber) {
          tok.type = TokenType::UNARY_MINUS;
        }
        flush_ops(ops, vals, tok.type);
        ops.push(tok.type);
        expectNumber = true;
        break;
      case TokenType::CLOSE_SCOPE:
        flush_ops(ops, vals, tok.type, TokenType::OPEN_SCOPE);
        expectNumber = false;
        break;
      case TokenType::END:
        flush_ops(ops, vals, tok.type);
        break;
      default:
        break;
      }
    }
    return vals.top();
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto s = new Solution;
  int res, want;

  want = 1;
  res = s->calculate("2 + -1");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  res = s->calculate("1 + 1");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->calculate("2-1 + 2 ");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 23;
  res = s->calculate("(1+(4+5+2)-3)+(6+8)");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -1;
  res = s->calculate("-1");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 22;
  res = s->calculate("22");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2'147'483'647;
  res = s->calculate("2147483647");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  res = s->calculate("2- -3");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
