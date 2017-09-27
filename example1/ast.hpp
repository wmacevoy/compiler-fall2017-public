#pragma once

#include <vector>
#include <memory>
#include <string>

class Node {
public: enum { PROGRAM, START_COMMAND, STOP_COMMAND, WORD_LITERAL, NUMBER_LITERAL };
public: std::vector < std::shared_ptr < Node > > children;
public: virtual int type() const = 0;
public: virtual ~Node() {};
};

class WordNode : public Node {
public: std::string word;
public: WordNode(const std::string &_word) : word(_word) {}
public: int type() const { return WORD_LITERAL; }
};

class NumberNode : public Node {
public: int number;
public: NumberNode(int _number) : number(_number) {}
public: int type() const { return NUMBER_LITERAL; }  
};

class StartCommandNode : public Node {
public: StartCommandNode(std::shared_ptr< WordNode > word, std::shared_ptr < NumberNode > number) {
  children.push_back(word);
  children.push_back(number);
}
public: int type() const { return START_COMMAND; }

public: const std::string & target() const {
  return (std::dynamic_pointer_cast < WordNode >(children[0]))->word;
}

public: int power() const {
  return (std::dynamic_pointer_cast < NumberNode >(children[1]))->number;
}
  
  
};

class StopCommandNode : public Node {
public: StopCommandNode(std::shared_ptr< WordNode > word) {
  children.push_back(word);
}
public: int type() const { return STOP_COMMAND; }

public: const std::string & target() const {
  return (std::dynamic_pointer_cast < WordNode >(children[0]))->word;
}

};

class ProgramNode : public Node {

};


typedef std::shared_ptr < Node > NodePtr;
typedef std::shared_ptr < ProgramNode > ProgramNodePtr;
typedef std::shared_ptr < WordNode > WordNodePtr;
typedef std::shared_ptr < NumberNode > NumberNodePtr;
typedef std::shared_ptr < StartCommandNode > StartCommandNodePtr;
typedef std::shared_ptr < StopCommandNode > StopCommandNodePtr;

int number(const NodePtr p) {
  return std::dynamic_pointer_cast < NumberNode >(p)->number;
}

const std::string & word(const NodePtr p) {
  return std::dynamic_pointer_cast < WordNode >(p)->word;
}

NodePtr node(int number) {
  return NodePtr(new NumberNode(number));
}

NodePtr node(const std::string &word) {
  return NodePtr(new WordNode(word));
}
