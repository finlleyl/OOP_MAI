#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <memory>
#include "coords.hpp"

template <typename Numeric>
class NPC {
public:
    NPC(const std::string& name, const Coords<Numeric>& coords, int health, int damage)
        : name(name), coords(coords), health(health), damage(damage) {}

    virtual ~NPC() = default;

private:
    std::string name;
    Coords<Numeric> coords;
    int health;
    int damage;
};

template <typename Numeric>
class NPCFactory {
public:
    virtual std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords) const = 0;
    virtual ~NPCFactory() = default;
};

template <typename Numeric>
class Bear : public NPC<Numeric> {
public:
    Bear(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}

    ~Bear() override = default;

private:
    int health_ = 300;
    int damage_ = 100;
};

template <typename Numeric>
class BearFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords) const override;
    }
};

template <typename Numeric>
class Elf : public NPC<Numeric> {
public:
    Elf(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}

    ~Elf() override = default;

private:
    int health_ = 100;
    int damage_ = 30;
};

template <typename Numeric>
class ElfFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords) const override;
    }
};

template <typename Numeric>
class Bandit : public NPC<Numeric> {
public:
    Bandit(const std::string& name, const Coords<Numeric>& coords)
        : NPC<Numeric>(name, coords, health_, damage_) {}
    
    ~Bandit() = default;

private:
    int health_ = 120;
    int damage_ = 20;
};

template <typename Numeric>
class BanditFactory : public NPCFactory<Numeric> {
public:
    std::unique_ptr<NPC<Numeric>> createNPC(const std::string& name, const Coords<Numeric>& coords) const override;
};

#endif // NPC_HPP