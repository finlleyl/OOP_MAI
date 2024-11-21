#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "concept.hpp"
#include "observer.hpp"
#include <typeinfo>

template <typename Numeric>
class NPC;

template <typename Numeric>
class Bear;

template <typename Numeric>
class Elf;

template <typename Numeric>
class Bandit;

template <typename Numeric>
class Subject;

template <typename Numeric>
class Visitor {
public:
    virtual void visit(Bear<Numeric>& npc) = 0;
    virtual void visit(Elf<Numeric>& npc) = 0;
    virtual void visit(Bandit<Numeric>& npc) = 0;
    virtual ~Visitor() = default;
};

template <typename Numeric>
class CombatVisitor : public Visitor<Numeric> {
public:
    CombatVisitor(NPC<Numeric>& attacker, Subject<Numeric>& subject)
        : attacker(attacker), subject(subject) {}

    void visit(Bear<Numeric>& npc) override {
        processCombat(npc);
    }

    void visit(Elf<Numeric>& npc) override {
        processCombat(npc);
    }

    void visit(Bandit<Numeric>& npc) override {
        processCombat(npc);
    }

private:
    NPC<Numeric>& attacker;
    Subject<Numeric>& subject;

    void processCombat(NPC<Numeric>& defender) {
        bool attackerWins = false;
        bool defenderWins = false;

        if (typeid(attacker) == typeid(Bear<Numeric>) && typeid(defender) == typeid(Elf<Numeric>)) {
            attackerWins = true;
        } else if (typeid(attacker) == typeid(Elf<Numeric>) && typeid(defender) == typeid(Bandit<Numeric>)) {
            attackerWins = true;
        } else if (typeid(attacker) == typeid(Bandit<Numeric>) && typeid(defender) == typeid(Bandit<Numeric>)) {
            attackerWins = true;
            defenderWins = true;
        }

        if (attackerWins) {
            defender.setHealth(defender.getHealth() - attacker.getDamage());
            subject.notifyAttack(attacker, defender);  
        }

        if (defenderWins) {
            attacker.setHealth(attacker.getHealth() - defender.getDamage());
            subject.notifyAttack(defender, attacker);
        }
    }
};

#endif // VISITOR_HPP
