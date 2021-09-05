#pragma once
#include <vector>

struct MatroidExample {
    using Element = int;

    int size() const; // # of elements of set we consider

    // If I is NOT independent or e \in I, undefined.
    // If I is independent and I + {e} is not, return elements of the circuit.
    // If I + {e} is also independent, return empty vector.
    template <class State = std::vector<bool>> void set(State I);
    std::vector<Element> circuit(Element e) const;
};
