#include "visitor.hpp"

template <typename Numeric>
bool Visitor<Numeric>::checkDistance(const NPC<Numeric> &npc1, const NPC<Numeric> &npc2, Numeric distance) const {
    return npc1.coords.distance(npc2.coords) <= distance;
}