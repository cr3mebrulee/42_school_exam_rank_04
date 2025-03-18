The task is to implement a basic JSON parser in C that constructs an Abstract Syntax Tree (AST) from a JSON file.

WHAT AST is:

An AST stands for Abstract Syntax Tree. AST is a tree-like structure used to represent structured data.

Each node in an AST represents a construct (e.g., a number, string, or object in JSON). Nodes are linked together to form a hierarchical structure. Unlike a binary tree, an AST can have more than two children per node.

WHAT JSON is:

JSON (JavaScript Object Notation) is a text-based format for storing and exchanging data in a way that’s both human-readable and machine-parsable. JSON is relatively easy to learn and to troubleshoot. Although JSON has its roots in JavaScript, it has grown into a very capable data format that simplifies data interchange across diverse platforms and programming languages. If you're involved in web development, data analysis, or software engineering, JSON is an important data format to understand.

Developers often prefer JSON because it simplifies the exchange of data between different technologies. For example, when a user interacts with a web application to make a purchase, the application sends the user's input to the server in JSON format. The server processes the data and sends back a response, also in JSON format, which is then rendered by the web application. This allows for seamless data exchange between client and the server, facilitating fast, dynamic, and interactive web experiences. [1]

JSON Data Types

In the context of development, data types are the different types of values that can be stored and manipulated in a programming language. Each data type has its own set of attributes and behaviors. JSON supports several data types, including the following:

   1. Objects. A JSON object data type is a set of name or value pairs inserted between {} (curly braces). The keys must be strings and separated by a comma and should be unique. Values can be strings, numbers, or nested objects.
   2. Arrays. An array data type is an ordered collection of values. In JSON, array values must be type string, number, object, array, Boolean, or null.
   3. Strings. In JSON, strings are enclosed in double quotation marks, can contain any Unicode character, and are commonly used to store and transmit text-based data, such as names, addresses, or descriptions.
   4. Boolean. Boolean values are designated as either true or false. Boolean values aren’t surrounded by quotes and are treated as string values.
   5. Null. Null represents a value that is intentionally left empty. When no value is assigned to a key, it can be treated as null.
   6. Number. Numbers are used to store numerical values for various purposes, such as calculations, comparisons, or data analysis. JSON supports both positive and negative numbers as well as decimal points. A JSON number follows JavaScript’s double-precision floating-point format.

Examples of Valid JSON Objects

✅ Simple object:

{"name": "Alice"}
    { starts the object.
    "name" is the key.
    "Alice" is the value (a string).
    } ends the object.

✅ Object with multiple key-value pairs:

{"age": 25, "city": "Berlin"}
    Multiple key-value pairs are separated by commas.

✅ Nested object:

{"person": {"name": "Bob", "age": 30}}
    An object can contain another object as a value.

PURPOSE OF LEARNING PARSER:

Writing a parser is a fundamental skill in computer science and software engineering because it teaches you how to process and understand structured data

1. Understanding How Programming Languages Work

    Every compiler and interpreter has a parser. When you write code in C, Python, or Java, a parser converts it into a structured representation (like an AST) before execution. If you understand parsing, you can build your own language!

2. Parsing & Handling Structured Data (JSON, XML, YAML, CSV, etc.)

   When an application loads a JSON file, it parses it to extract data. Learning parsing you learn how to process data formats. 

3. Improving Your Problem-Solving & Algorithm Skills

    Writing a parser requires understanding recursion, state machines, and tree structures. You learn how to break a big problem (like parsing JSON) into smaller steps.

JSON AST Structure for implementing argo:

typedef enum {
    JSON_NUMBER,
    JSON_STRING,
    JSON_OBJECT
} json_type;

typedef struct json {
    json_type type;   // The type of JSON value (number, string, object)

    union {
        int number;   // If the node is a number
        char *string; // If the node is a string

        struct {
            char **keys;       // Array of keys (for objects)
            struct json **values; // Array of values (for objects)
            int size;          // Number of key-value pairs
        } object;
    } data;

} json;

Union

Definition

A union allows different data types to share the same memory space (only one member holds a value at a time). [3] It is a type of structure that can be used where the amount of memory used is a key factor. Similarly to the structure the union can contain different types of data types. Each time a new variable is initialized from the union it overwrites the previous and uses that memory location if memory offset is overlaping. This is most useful when the type of data being passed through functions is unknown, using a union which contains all possible data types can remedy this problem.

Defining a Union

union person {
char name;
int age;
double height;
};

Declaring a Union

Since the union is still a type of structure the method for declaring it is as follows:

union person {
char name;
int age;
double height;
}newPerson;

Or

Person newPerson;



References:

1. https://www.oracle.com/uk/database/what-is-json/

Sources to learn parsing:

https://craftinginterpreters.com/



