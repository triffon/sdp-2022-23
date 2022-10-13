#include "../lstack.hpp"

using TestStack = LinkedStack<int>;

TEST_CASE("LinkedStack: след създаване на стек той е празен") {
    TestStack s;
    CHECK(s.empty());
    /*
    try {
        int* p = new int[473264872364783268];
    } catch (std::bad_alloc e) {
        std::cerr << "Грешка при заделяне на памет! " << e.what() << std::endl;
    }
    */
    /*
    int *p = new (std::nothrow) int[473264872364783268];
    if (p == nullptr)
        std::cerr << "Грешка при заделяне на памет!\n";
    */
}

TEST_CASE("LinkedStack: стекът не е празен след добавяне") {
    TestStack s;
    try {
        // TestStack s2;
        // s2.push(15);
        s.push(10);
    } catch (char const* message) {
        std::cerr << "За съжаление push хвърли изключение: " << message << std::endl;
        // throw;
        // throw "вече обработих грешката, спокойно";
    }
    CHECK(!s.empty());
}

TEST_CASE("LinkedStack: елементите се изключват в ред обратен на включване") {
    TestStack s;
    s.push(10); s.push(20); s.push(30);
    CHECK( !s.empty() );
    CHECK_EQ( s.pop(), 30);
    CHECK_EQ( s.pop(), 20);
    CHECK_EQ( s.pop(), 10);
    CHECK( s.empty() );
}

TEST_CASE("LinkedStack: peek връща последно включения елемент") {
    TestStack s;
    s.push(10);
    CHECK_EQ( s.peek(), 10);
    s.push(20);
    CHECK_EQ( s.peek(), 20);
    s.pop();
    CHECK_EQ( s.peek(), 10);
}

TEST_CASE("LinkedStack: неуспех при опит за поглеждане в празен стек") {
    TestStack s;
    int x;
    CHECK( ! s.peek(x) );
}

TEST_CASE("LinkedStack: изключение при опит за поглеждане в празен стек") {
    TestStack s;
    CHECK_THROWS( s.peek() );
}

TEST_CASE("LinkedStack: безопасният peek връща последно включения елемент") {
    TestStack s;
    s.push(10);
    int x;
    CHECK( s.peek(x));
    CHECK_EQ( x, 10 );
    s.push(20);
    CHECK( s.peek(x));
    CHECK_EQ( x, 20 );
    s.pop();
    CHECK( s.peek(x));
    CHECK_EQ( x, 10 );
}


TEST_CASE("LinkedStack: конструкторът за копиране не споделя памет") {
    TestStack s1;
    for(int i = 1; i <= 10; i++)
        s1.push(i);
    TestStack s2 = s1;
    std::cout << s2.pop() << std::endl;
    s2.push(20);
    for(int i = 10; i >= 1; i--) {
        CHECK(! s1.empty());
        CHECK_EQ(s1.pop(), i);
    }
    CHECK(s1.empty());
}

TEST_CASE("LinkedStack: pop връща грешка при опит за изключване от празен стек") {
    TestStack s;
    bool success = true;
    int x = s.pop(success);
    CHECK_FALSE( success );
}

TestStack reverse(TestStack s) {
    TestStack result;
    // !!! bool even = s.peek() % 2 == 0;
    while (!s.empty())
        result.push(s.pop());
    // !!! if (even)
    // !!!    return s;
    return result;
}

TestStack createStack(unsigned n) {
    TestStack result;
    for(int i = 1; i <= n; i++)
        result.push(i);
    return result;
}

TestStack doubleTop(TestStack s) {
    s.push(s.pop() * 2);
    return s;
}

TEST_CASE("LinkedStack: копиране при reverse") {
    std::clog << "LinkedStack: копиране при reverse\n";
    TestStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    TestStack s2 = reverse(s);
    CHECK_EQ(s2.pop(), 1);
    CHECK_EQ(s2.pop(), 2);
    CHECK_EQ(s2.pop(), 3);
    CHECK(s2.empty());
}

TEST_CASE("LinkedStack: копиране при doubleTop") {
    std::clog << "LinkedStack: копиране при doubleTop\n";
    // TestStack temp = createStack(10);
    TestStack s2 = doubleTop(createStack(10));
    //s2.push(1);
    //s2.pop();
    // s2.steal(doubleTop(createStack(10)));
}

TEST_CASE("LinkedStack: присвояване при doubleTop") {
    std::clog << "LinkedStack: присвояване при doubleTop\n";
    // TestStack temp = createStack(10);
    TestStack s2 = createStack(10);
    s2 = doubleTop(createStack(10));
}

TEST_CASE("LinkedStack: std::move") {
    std::clog << "LinkedStack: std::move\n";
    TestStack temp = createStack(10);
//    TestStack s2 = doubleTop((TestStack&&)temp);
    TestStack s2 = doubleTop(std::move(temp));
    CHECK(temp.empty());
}