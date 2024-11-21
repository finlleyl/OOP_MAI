#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <memory>
#include "coords.hpp"
#include "concept.hpp"

template <typename Numeric>
class Visitor;

template <typename Numeric>
class Subject;

template <typename Numeric>
class NPC {
public:
    NPC(const std::string& name, const Coords<Numeric>& coords, int health, int damage)
        : name(name), coords(coords), health(health), damage(damage) {}

    virtual ~NPC() = default;

    const std::string& getName() const {
        return name;
    }

    const Coords<Numeric>& getCoords() const {
        return coords;
    }

    int getHealth() const {
        return health;
    }

    int getDamage() const {
        return damage;
    }

    void setHealth(int val) {
        health = val;
    }

    virtual void accept(Visitor<Numeric>& visitor) = 0;

protected:
    std::string name;
    Coords<Numeric> coords;
    int health;
    int damage;
};

template <typename Numeric>
class NPCFactory {
public:
    virtual std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords, Subject<Numeric>& subject) const = 0;
    virtual ~NPCFactory() = default;
};

template <typename Numeric>
class Bear : public NPC<Numeric> {
public:
    Bear(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}

    void accept(Visitor<Numeric>& visitor) override {
        visitor.visit(*this);
    }

private:
    static const int health_ = 300;
    static const int damage_ = 100;
};

template <typename Numeric>
class BearFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords, Subject<Numeric>& subject) const override {
        auto npc = std::make_unique<Bear<Numeric>>(name, coords);
        subject.notifyNPCCreated(*npc);
        return npc;
    }
};

template <typename Numeric>
class Elf : public NPC<Numeric> {
public:
    Elf(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}

    void accept(Visitor<Numeric>& visitor) override {
        visitor.visit(*this);
    }

private:
    static const int health_ = 100;
    static const int damage_ = 30;
};

template <typename Numeric>
class ElfFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords, Subject<Numeric>& subject) const override {
        auto npc = std::make_unique<Elf<Numeric>>(name, coords);
        subject.notifyNPCCreated(*npc);
        return npc;
    }
};

template <typename Numeric>
class Bandit : public NPC<Numeric> {
public:
    Bandit(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}

    void accept(Visitor<Numeric>& visitor) override {
        visitor.visit(*this);
    }

private:
    static const int health_ = 120;
    static const int damage_ = 20;
};

template <typename Numeric>
class BanditFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords, Subject<Numeric>& subject) const override {
        auto npc = std::make_unique<Bandit<Numeric>>(name, coords);
        subject.notifyNPCCreated(*npc);
        return npc;
    }
};

#endif // NPC_HPP
