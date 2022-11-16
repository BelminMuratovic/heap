#include "Heap.hpp"

int main(int argc, char const *argv[])
{
    // default konstruktor i metod insert
    Heap<int> heap1;
    heap1.insert(10);
    heap1.insert(5);
    heap1.insert(20);
    heap1.insert(17);
    heap1.insert(8);

    // operator<< i ocekivani ispis: 5 17 8 20 10
    std::cout << "default konstruktor" << std::endl;
    std::cout << heap1 << std::endl;
    std::cout << std::endl;

    // copy konstruktor i copy operator=
    Heap<int> heap2{heap1};
    Heap<int> heap3;
    heap3 = heap1;

    // ocekivani ispis za heap2 i heap3 je: 5 17 8 20 10
    std::cout << "copy konstruktor i copy operator=" << std::endl;
    std::cout << heap2 << std::endl;
    std::cout << heap3 << std::endl;
    std::cout << std::endl;

    // move konstruktor i move operator=
    Heap<int> heap4{std::move(heap1)};
    Heap<int> heap5;
    heap5 = std::move(heap2);

    // ocekivani ispis za heap4 i heap5 je: 5 17 8 20 10, a ispisa za heap1 i heap2 nema zbog move-anja
    std::cout << "move konstruktor i move operator=" << std::endl;
    std::cout << heap4 << std::endl;
    std::cout << heap5 << std::endl;
    std::cout << heap1 << std::endl;
    std::cout << heap2 << std::endl;
    std::cout << std::endl;

    // metod insert na novom objektu
    heap3.insert(100);
    heap3.insert(50);

    // ocekivani ispis je: 5 17 8 100 10 50 20
    std::cout << "metod insert na novom objektu" << std::endl;
    std::cout << heap3 << std::endl;
    std::cout << std::endl;

    // metodi min i max
    std::cout << "metodi min i max" << std::endl;
    std::cout << heap3 << std::endl;
    std::cout << heap3.min() << "  " << heap3.max() << std::endl;
    std::cout << std::endl;

    // metodi removeMin i removeMax
    std::cout << "metodi removeMin i removeMax" << std::endl;
    std::cout << heap3 << std::endl;
    heap3.removeMin();
    heap3.removeMax();
    std::cout << heap3 << std::endl;
    std::cout << std::endl;

    return 0;
}
