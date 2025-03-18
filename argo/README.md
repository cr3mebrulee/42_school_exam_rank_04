The task is to implement a basic JSON parser in C that constructs an Abstract Syntax Tree (AST) from a JSON file.

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


References:

1. https://www.oracle.com/uk/database/what-is-json/



