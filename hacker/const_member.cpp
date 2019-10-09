#include <iostream>

class TextObject {
    public:
        const char& operator[](std::size_t position) const {
            std::cout << "\nInside the const function\n";
            return text[position];
        }

        char & operator[](std::size_t position) {
            std::cout << "\nInside the non-const function\n";
            return text[position];
        }

        TextObject(const std::string _text) {
            text = _text;
        }

        void printText() {
            std::cout << text << std::endl;
        }

    private:
        std::string text;
};

int main()
{
    TextObject to("hello");
    const TextObject to_1("world");

    to.printText();
    std::cout << "The second char is " << to[2];
    to[2] = 'm';
    to.printText();

    std::cout << "The second char is " << to_1[2];
}
