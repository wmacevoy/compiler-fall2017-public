#pragma once

#include <vector>
#include <memory>

class Node {
public: enum { PROGRAM, START_COMMAND, STOP_COMMAND, WORD_LITERAL, NUMBER_LITERAL };
public: std::vector < std::shared_ptr < Node > > children;
public: virtual int type() = 0;
public: virtual ~Node() {};
};

class WordNode : public Node {
public: std::string word;
public: WordNode(const std::string &_word) : word(_word) {}
public: int type() { return WORD_LITERAL; }
};

class NumberNode : public Node {
public: int number;
public: NumberNode(int _number) : number(_number) {}
public: int type() { return NUMBER_LITERAL; }  
};

class StartCommandNode : public Node {
public: StartCommandNode(std::shared_ptr< WordNode > word, std::shared_ptr < NumberNode > number) {
  children.push_back(word);
  children.push_back(number);
}
public: int type() { return START_COMMAND; }

public: const std::string & target() const {
  return ((std::shared_ptr < WordNode > )children[0])->word;
}

public: int power() const {
  return ((std::shared_ptr < NumberNode > )children[1])->number;
}
  
  
};

class StopCommandNode : public Node {
public: StopCommandNode(std::shared_ptr< WordNode > word) {
  children.push_back(word);
}
public: int type() { return STOP_COMMAND; }

public: const std::string & target() const {
  return ((std::shared_ptr < WordNode > )children[0])->word;
}

};

class ProgramNode : public Node {

}

typedef std::shared_ptr < Node > NodePtr;

