#include <math.h>
#include <stdio.h>
#include "sippetscript.h"

// A simple structure use to keep track of the current intepreter state.
struct State {
  const char *input;
  unsigned long index;
  char character;
};

// This function will advance the character by the give amount of units. Make
// sure that the index will not go out of bounds after being incremented by the
// units prior to calling this function.
static inline void advance(struct State *state, unsigned long units) {
  state->index += units;
  state->character = state->input[state->index];

  if (
    state->character == ' ' ||
    state->character == '\t' ||
    state->character == '\n'
  ) {
    // This will skip whitespaces as they are ignored.
    advance(state, 1);
  }
}

// This function will move the character to the given index. Make sure the
// index is not out of bounds prior to calling this function.
static inline void jump(struct State *state, unsigned long index) {
  state->index = index;
  state->character = state->input[state->index];
}

/*
"Example of adding";

"also could be written like this";
add(list) = list:0 + list:1;

"uses 'pattern matching'";
add([a, b]) = a + b;

sum = add(1, 2);

"Example of player & enemy";

player = [x = 0, y = 0, health = 100, name = "player"];
player:hitBy(enemy) {
  player:health - enemy:damage;
  print("ouch!!!!!");
};

enemy = [damage = 10, name = "enemy"];
player:hitBy(enemy);

"Example of Clamp Function";
clamp(x, min, max) = @clamped {
  x < min {
    clamped(min);
  } x > max {
    clamped(max);
  }{
    clamped(x);
  };
};

"Example of Minified Clamp Function";
c(x,a,b)=x<a{a}x<b{b}{x};
*/

// This will parse a series of statements separated by semicolons.
static double parse_block(struct State *state);

// This will parse a series of statements separated by commas.
static double parse_list(struct State *state);

// evaluation, evaluation = assignment
static double parse_statement(struct State *state);

// equality, equality & evaluation, equality | evaluation 
static double parse_evaluation(struct State *state);

// comparison, comparison < equality, comparison > equality
static double parse_equality(struct State *state);

// expression, expression ? comparison, expression ! comparison
static double parse_comparison(struct State *state);

// term, term + expression, term - expression
static double parse_expression(struct State *state);

// factor, factor * term, factor / term, factor % term
static double parse_term(struct State *state);

// power, +power, -power, ?power, !power
static double parse_factor(struct State *state);

// access, access ^ factor
static double parse_power(struct State *state);

// value, value:statement
static double parse_access(struct State *state);

// literal, indentifier
static double parse_value(struct State *state);

// number, string, (statement), [list], {block}, nothing
static double parse_literal(struct State *state);

static double parse_number(struct State *state);

enum SippetscriptStatus sippetscript(const char *input) {
  struct State state;
  state.input = input;
  state.index = 0;
  advance(&state, 0);

  printf("Result: %f\n", parse_expression(&state));

  return STATUS_SUCCESS;
}

static double parse_statement(struct State *state) {
  return parse_evaluation(state); // TODO: this
}

static double parse_evaluation(struct State *state) {
  return parse_equality(state); // TODO: this
}

static double parse_equality(struct State *state) {
  return parse_comparison(state); // TODO: this
}

static double parse_comparison(struct State *state) {
  return parse_expression(state); // TODO: this
}

static double parse_expression(struct State *state) {
  printf("Parsing Expression\n");
  
  double expression = parse_term(state);

  while (
    state->character == '+' ||
    state->character == '-'
  ) {
    char operator = state->character;
    advance(state, 1);

    switch (operator) {
      case '+':
        expression += parse_term(state);
        break;
      case '-':
        expression -= parse_term(state);
        break;
    }
  }

  return expression;
}

static double parse_term(struct State *state) {
  printf("Parsing Term\n");
  
  double term = parse_factor(state);

  while (
    state->character == '*' ||
    state->character == '/' ||
    state->character == '%'
  ) {
    char operator = state->character;
    advance(state, 1);

    switch (operator) {
      case '*':
        term *= parse_factor(state);
        break;
      case '/':
        term /= parse_factor(state);
        break;
      case '%':
        term = fmod(term, parse_factor(state));
        break;
    }
  }

  return term;
}

static double parse_factor(struct State *state) {
  printf("Parsing Factor\n");
  
  if (
    state->character == '+' ||
    state->character == '-' ||
    state->character == '?' ||
    state->character == '!'
  ) {
    char operator = state->character;
    advance(state, 1);
    
    switch (operator) {
      case '+':
        return +parse_factor(state);
      case '-':
        return -parse_factor(state);
      case '?':
        return !!parse_factor(state);
      case '!':
        return !parse_factor(state);
    }
  }

  return parse_power(state);
}

static double parse_power(struct State *state) {
  printf("Parsing Power\n");
  
  double base = parse_access(state);

  if (state->character == '^') {
    advance(state, 1);

    double exponent = parse_factor(state);
    return pow(base, exponent);
  }

  return base;
}

static double parse_access(struct State *state) {
  printf("Parsing Access\n");

  double accessed = parse_value(state);

  if (state->character == ':') {
    advance(state, 1);

    // TODO: Make this (the accessor) access 'accessed', this is not possible
    // for now as I am just working with numbers.
    return parse_access(state);
  }

  return accessed;
}

static double parse_value(struct State *state) {
  printf("Parsing Value\n");

  // TODO: Support other types of values other than literals
  return parse_literal(state);
}

static double parse_literal(struct State *state) {
  printf("Parsing Literal\n");

  // TODO: Support other types of literals other than numbers
  return parse_number(state);
}

static double parse_number(struct State *state) {
  printf("Parsing Number\n");
  
  double number = 0;
  
  // A number used to keep track of the decimal part of the parsed number. 
  int divisor = 1;

  // A flag used for showing whether a dot was just encountered.
  int trailing_dot = 0;

  // A counter for the number of dots (it should be 0 or 1).
  int dot_encounters = 0;

  while (
    (state->character >= '0' && state->character <= '9') ||
    state->character == '.'
  ) {
    printf("Parsing Digit\n");

    trailing_dot = state->character == '.';
    if (trailing_dot) {
      dot_encounters++;
      advance(state, 1);
      continue;
    }

    int digit = state->character - '0';
    if (dot_encounters) {
      number += digit / (double)divisor;
      divisor *= 10;
    } else {
      number = number * 10 + digit;
    }

    advance(state, 1);
  }
  
  if (trailing_dot || dot_encounters > 1) {
    printf("Invalid Number Literal\n");
    return NAN;
  }

  return number;
}