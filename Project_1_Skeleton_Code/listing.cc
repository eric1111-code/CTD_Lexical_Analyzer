// CMSC 430 Compiler Theory and Design
// Project 1 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the functions that produces the
// compilation listing

#include <cstdio>
#include <queue> // Added queue header
#include <string>

using namespace std;

#include "listing.h"

static int lineNumber;
static int totalErrors = 0;

// Overhauled static tracking variables
static queue<string> errorQueue;
static int lexicalErrors = 0;
static int syntaxErrors = 0;
static int semanticErrors = 0;

static void displayErrors();

void firstLine() {
  lineNumber = 1;
  printf("\n%4d  ", lineNumber);
}

void nextLine() {
  displayErrors();
  lineNumber++;
  printf("%4d  ", lineNumber);
}

int lastLine() {
  printf("\r");
  displayErrors();
  printf("     \n");

  // End-of-File Output Logic
  if (totalErrors == 0) {
    printf("Compiled Successfully\n");
  } else {
    printf("Lexical Errors %d\n", lexicalErrors);
    printf("Syntax Errors %d\n", syntaxErrors);
    printf("Semantic Errors %d\n", semanticErrors);
  }

  return totalErrors;
}

void appendError(ErrorCategories errorCategory, string message) {
  string messages[] = {"Lexical Error, Invalid Character ", "",
                       "Semantic Error, ", "Semantic Error, Duplicate ",
                       "Semantic Error, Undeclared "};

  // Update targeted variable tallies
  if (errorCategory == LEXICAL) {
    lexicalErrors++;
  } else if (errorCategory == SYNTAX) {
    syntaxErrors++;
  } else {
    semanticErrors++;
  }

  // Buffers new message into the queue
  errorQueue.push(messages[errorCategory] + message);
  totalErrors++;
}

void displayErrors() {
  // Prints every buffered error sequentially for the final line
  while (!errorQueue.empty()) {
    printf("%s\n", errorQueue.front().c_str());
    errorQueue.pop();
  }
}
