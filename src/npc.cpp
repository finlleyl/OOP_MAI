#include <memory>
#include "npc.hpp"

template <typename Numeric>
std::unique_ptr<NPC<Numeric>> BearFactory<Numeric>::createNPC(const std::string& name, const Coords<Numeric>& coords) const {
        return std::make_unique<Bear<Numeric>>(name, coords);
    }

template <typename Numeric>
std::unique_ptr<NPC<Numeric>> ElfFactory<Numeric>::createNPC(const std::string& name, const Coords<Numeric>& coords) const {
        return std::make_unique<Elf<Numeric>>(name, coords);
    }

template <typename Numeric>
std::unique_ptr<NPC<Numeric>> BanditFactory<Numeric>::createNPC(const std::string& name, const Coords<Numeric>& coords) const {
        return std::make_unique<Bandit<Numeric>>(name, coords);
    }