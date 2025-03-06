# Contributing

Thank you for your interest in contributing to this project! Please follow the
guidelines below to maintain consistency across the codebase.

## Getting Started
Fork the repository – Click the fork button to create a copy of the repository
in your account.
```
git clone https://github.com/SippetBox/SippetScript.git
cd your-project
```

Create a new Branch – Try to use a meaningful name.
```
git checkout -b feature/your-feature-name
Install Dependencies – Check the README.md for setup instructions.
```

## Coding Style
### Indentation
Use **2 spaces** (no tabs) for indentation. This is to make sure they look the
same on all devices.

### Line Length & Breaking Long Lines
Please keep your lines with a maximum of **80 characters**.

For assignments with expressions, place all the symbols on a new line with an
indent. The semicolon (that ends the statement) goes at the end of last line.

```
int long_variable_name
  = integer_with_long_name_1
  + integer_with_long_name_2
  + integer_with_long_name_3;
```

### Braces
Use the **K&R style** for placing braces. Always use braces, even for
single-line statements.
```
if (condition) {
  do_something();
}
```

### Whitespace and New Lines
Avoid trailing whitespace and groups of more than one consecutive blank lines.

### Naming Conventions
- Use `snake_case` for `variables` and `functions`
- Use `PascalCase` for `structs` and `enums`
- Use `SCREAMING_SNAKE_CASE` for `macros`
- Use `snake_case` for naming `files` and `folders`