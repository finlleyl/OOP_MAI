#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "npc.hpp"

template <typename Numeric>
class Visitor {
public:
    ~Visitor() = default;

private:
    bool checkDistance(const NPC<Numeric>& npc1, const NPC<Numeric>& npc2, Numeric distance) const;
};

#endif // VISITOR_HPP