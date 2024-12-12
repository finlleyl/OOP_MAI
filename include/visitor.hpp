#pragma once

class Elf;
class Rogue;
class Bear;

class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visit(Elf&) = 0;
    virtual void visit(Rogue&) = 0;
    virtual void visit(Bear&) = 0;
};