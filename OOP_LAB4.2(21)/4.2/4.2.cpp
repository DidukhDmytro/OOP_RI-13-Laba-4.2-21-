#include "pch.h"
#include "CppUnitTest.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace VertebrateUnitTest
{
    class IVertebrate
    {
    public:
        virtual void Description() const = 0;
        virtual string GetType() const = 0;
        virtual ~IVertebrate() {}
    };

    class Mammal : public IVertebrate
    {
    public:
        virtual string GetGroup() const = 0;
    };

    class Bird : public IVertebrate
    {
    public:
        virtual string GetGroup() const = 0;
    };

    class Animal : public Mammal
    {
    public:
        virtual string GetAnimalType() const = 0;
    };

    class Human : public Mammal
    {
    public:
        void Description() const override {}

        string GetType() const override
        {
            return "Human";
        }

        string GetGroup() const override
        {
            return "Mammal";
        }
    };

    class Dog : public Animal
    {
    public:
        void Description() const override {}

        string GetType() const override
        {
            return "Dog";
        }

        string GetGroup() const override
        {
            return "Mammal";
        }

        string GetAnimalType() const override
        {
            return "Domestic animal";
        }
    };

    class Cat : public Animal
    {
    public:
        void Description() const override {}

        string GetType() const override
        {
            return "Cat";
        }

        string GetGroup() const override
        {
            return "Mammal";
        }

        string GetAnimalType() const override
        {
            return "Domestic animal";
        }
    };

    class Crow : public Bird
    {
    public:
        void Description() const override {}

        string GetType() const override
        {
            return "Crow";
        }

        string GetGroup() const override
        {
            return "Bird";
        }
    };

    TEST_CLASS(VertebrateTests)
    {
    public:

        TEST_METHOD(TestHumanType)
        {
            Human human;
            Assert::AreEqual(string("Human"), human.GetType());
            Assert::AreEqual(string("Mammal"), human.GetGroup());
        }

        TEST_METHOD(TestDogType)
        {
            Dog dog;
            Assert::AreEqual(string("Dog"), dog.GetType());
            Assert::AreEqual(string("Mammal"), dog.GetGroup());
            Assert::AreEqual(string("Domestic animal"), dog.GetAnimalType());
        }

        TEST_METHOD(TestCatType)
        {
            Cat cat;
            Assert::AreEqual(string("Cat"), cat.GetType());
            Assert::AreEqual(string("Mammal"), cat.GetGroup());
            Assert::AreEqual(string("Domestic animal"), cat.GetAnimalType());
        }

        TEST_METHOD(TestCrowType)
        {
            Crow crow;
            Assert::AreEqual(string("Crow"), crow.GetType());
            Assert::AreEqual(string("Bird"), crow.GetGroup());
        }

        TEST_METHOD(TestPolymorphism)
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

            Assert::AreEqual(string("Human"), arr[0]->GetType());
            Assert::AreEqual(string("Dog"), arr[1]->GetType());
            Assert::AreEqual(string("Cat"), arr[2]->GetType());
            Assert::AreEqual(string("Crow"), arr[3]->GetType());
        }

        TEST_METHOD(TestDynamicCast)
        {
            Dog dog;
            Crow crow;

            IVertebrate* obj1 = &dog;
            IVertebrate* obj2 = &crow;

            Mammal* mammal = dynamic_cast<Mammal*>(obj1);
            Bird* bird = dynamic_cast<Bird*>(obj2);

            Assert::IsNotNull(mammal);
            Assert::IsNotNull(bird);
        }
    };
}