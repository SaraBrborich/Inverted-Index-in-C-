# Inverted Index in C++

This project implements a C++ program that generates an inverted index from a text file, ignoring specified exception words provided in another file. The program supports advanced search capabilities and ensures efficient data management. Below are the main features and functionalities of the program:

## Features

1. **Text File Reading**:  
   - Reads a generic text file containing the information to process.  
   - Reads an exception words file (e.g., `the`, `a`, `an`), which are excluded from the index.

2. **Inverted Index Creation**:  
   - Uses a map (`<string, list<Pairs>>`) to create an inverted index.  
   - Associates each word (excluding exceptions) with the lines and positions where it appears in the text file.

3. **Exporting the Index**:  
   - Outputs the inverted index to a text file, sorted alphabetically, with one word per line and its respective occurrences.

4. **Single Word Search**:  
   - Allows users to search for a specific word and displays the lines and positions where it appears.

5. **Group Word Search**:  
   - Supports searching for groups of words, showing the lines where all the queried words appear together.

## Example Usage

### Input Text File:
```
This is an example text file.
It contains multiple lines.
Some lines have repeated words.
This text is for testing purposes.
```

### Exception Words File:
```
this, is, an, the, a
```

### Output Inverted Index:
```
contains (2,4)
example (1,3)
file (1,5)
lines (2,2) (3,2)
multiple (2,3)
repeated (3,3)
testing (4,3)
text (1,5) (4,2)
purposes (4,4)
```

### Searching for a Word:
```
> Enter a word: text
> text (1,5) (4,2)
```

### Searching for Multiple Words:
```
> Enter words: lines text
> Lines where all words appear: 2, 3
```
