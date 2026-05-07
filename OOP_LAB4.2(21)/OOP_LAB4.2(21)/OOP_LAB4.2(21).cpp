#include <iostream>
#include <typeinfo>

#include "Human.h"
#include "Dog.h"
#include "Cat.h"
#include "Crow.h"

using namespace std;

int main()
{
    Human human;
    Dog dog;
    Cat cat;
    Crow crow;

    IVertebrate* arr[4];

    arr[0] = &human;
    arr[1] = &dog;
    arr[2] = &cat;
    arr[3] = &crow;

    for (int i = 0; i < 4; i++)
    {
        cout << "---------------------" << endl;

        cout << "Type: " << arr[i]->GetType() << endl;

        cout << "typeid: "
            << typeid(*arr[i]).name()
            << endl;

        arr[i]->Description();
    }

    return 0;
}