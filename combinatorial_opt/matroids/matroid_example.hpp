#pragma once
#include <vector>

struct MatroidExample {
    using Element = int;

    int size() const; // # of elements of set we consider

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    template <class State = std::vector<bool>> void set(State I);
    std::vector<Element> circuit(Element e) const;
};
