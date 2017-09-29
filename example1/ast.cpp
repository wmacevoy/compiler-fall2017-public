#include "ast.hpp"

Node::~Node() {};

WordNode::WordNode(const std::string &_word)
{
	word = _word;
}

int WordNode::type() const
{
	return WORD_LITERAL;
}

NumberNode::NumberNode(int _number)
{
	number = _number;
}

int NumberNode::type() const
{
	return NUMBER_LITERAL;
}

StartCommandNode::StartCommandNode(std::shared_ptr<Node> word,
                                   std::shared_ptr<Node> number)
{
	children.push_back(word);
	children.push_back(number);
}

int StartCommandNode::type() const { return START_COMMAND; }

const std::string & StartCommandNode::target() const
{
	return std::dynamic_pointer_cast<WordNode>(children.at(0))->word;
}

int StartCommandNode::power() const
{
	return std::dynamic_pointer_cast<NumberNode>(children.at(1))->number;
}

StopCommandNode::StopCommandNode(std::shared_ptr<Node> word) {
	children.push_back(word);
}

int StopCommandNode::type() const { return STOP_COMMAND; }

const std::string & StopCommandNode::target() const {
	return std::dynamic_pointer_cast<WordNode>(children.at(0))->word;
}

int ProgramNode::type() const { return PROGRAM; }

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
