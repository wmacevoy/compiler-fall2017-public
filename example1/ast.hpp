#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Node {
public: enum {
    PROGRAM,
    START_COMMAND,
    STOP_COMMAND,
    WORD_LITERAL,
    NUMBER_LITERAL
  };
public: std::vector < std::shared_ptr < Node > > children;
public: virtual int type() const = 0;
public: virtual void print(std::ostream &out) const = 0;
public: virtual ~Node();
};

typedef std::shared_ptr < Node > NodePtr;

class WordNode : public Node {
public: std::string word;
public: WordNode(const std::string &_word);
public: int type() const;
public: void print(std::ostream &out) const;
};

typedef std::shared_ptr < WordNode > WordNodePtr;

class NumberNode : public Node {
public: int number;
public: NumberNode(int _number);
public: int type() const;
public: void print(std::ostream &out) const;  
};

typedef std::shared_ptr < NumberNode > NumberNodePtr;


class StartCommandNode : public Node {
public: StartCommandNode(const NodePtr &target, const NodePtr &power);
public: int type() const;
public: void print(std::ostream &out) const;  

public: const std::string & target() const;

public: int power() const;
  
};

typedef std::shared_ptr < StartCommandNode > StartCommandNodePtr;

class StopCommandNode : public Node {
public: StopCommandNode(const NodePtr &target);
public: int type() const;
public: void print(std::ostream &out) const;

public: const std::string & target() const;

};

typedef std::shared_ptr < StopCommandNode > StopCommandNodePtr;

class ProgramNode : public Node {
public: int type() const;
public: void print(std::ostream &out) const;  
};

typedef std::shared_ptr < ProgramNode > ProgramNodePtr;

int number(const NodePtr &p);

const std::string & word(const NodePtr &p);

NodePtr node(int number);

NodePtr node(const std::string &word);

std::ostream &operator<< (std::ostream& out, const NodePtr &p);
