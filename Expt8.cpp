#include <iostream>

#include <cstring>

#include <chrono>

#include <utility>

using namespace std;
using namespace chrono;


class String

{

private:

    char* data;

    size_t length;

public:

    // Constructor
    String(const char* str = "")

    {

        length = strlen(str);

        data = new char[length + 1];

        strcpy(data, str);

    }



    // Copy Constructor

    String(const String& other)

    {

        length = other.length;

        data = new char[length + 1];

        strcpy(data, other.data);

    }

    // Move Constructor
    String(String&& other) noexcept

    {

        data = other.data;

        length = other.length;

        other.data = nullptr;

        other.length = 0;

    }



    // Copy Assignment Operator

    String& operator=(const String& other)

    {
        if (this != &other)

        {

            delete[] data;



            length = other.length;

            data = new char[length + 1];

            strcpy(data, other.data);

        }



        return *this;

    }



    // Move Assignment Operator

    String& operator=(String&& other) noexcept

    {

        if (this != &other)

        {

            delete[] data;



            data = other.data;

            length = other.length;



            other.data = nullptr;

            other.length = 0;

        }



        return *this;

    }



    // Destructor

    ~String()

    {

        delete[] data;

    }



    void display() const

    {

        if (data != nullptr)

            cout << data << endl;

    }

};


// Perfect Forwarding Function

template <typename T>

String createString(T&& value)

{

    return String(forward<T>(value));

}



int main()

{

    const int SIZE = 100000;



    String original(
        "This is a resource-heavy string used to demonstrate "

        "copy and move semantics in C++.");



    // Benchmark Copy Operations

    auto startCopy = high_resolution_clock::now();



    for (int i = 0; i < SIZE; i++)

    {

        String copy = original;

    }



    auto endCopy = high_resolution_clock::now();



    auto copyTime =
        duration_cast<milliseconds>(endCopy - startCopy);


    // Benchmark Move Operations

    auto startMove = high_resolution_clock::now();

    for (int i = 0; i < SIZE; i++)

    {

        String temp(

          "This is a resource-heavy string used for "

          "move semantics.");



        String moved = move(temp);

    }



    auto endMove = high_resolution_clock::now();



    auto moveTime =
        duration_cast<milliseconds>(endMove - startMove);



// Perfect Forwarding Demonstration

String forwarded = createString(

    "Perfect Forwarding Example");



cout << "Perfect Forwarding Result: ";

forwarded.display();



// Display Benchmark Results

cout << "\nCopy Operation Time: "
    << copyTime.count()

    << " milliseconds" << endl;



cout << "Move Operation Time: "

       << moveTime.count()

       << " milliseconds" << endl;



    return 0;

}
