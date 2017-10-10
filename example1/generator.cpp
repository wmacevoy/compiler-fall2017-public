#include <set>
#include "generator.hpp"

Generator::Generator(const NodePtr &_ast)
  : ast(_ast) { }

struct HeaderGenerator : public Generator {
  std::set < std::string > symbols;

  HeaderGenerator(const NodePtr &_ast) : Generator(_ast) {
  }
  virtual void generate(std::ostream &out) {
    out << "#include <GPIO.h>" << std::endl;
    out << std::endl;

    symbols.clear();
    findSymbols(ast);
    for (auto word : symbols) {
      out << "GPIO " << word << ";" << std::endl;
    }
    out << std::endl;
  }

  void findSymbols(const NodePtr &ast) {
    switch(ast->type()) {
    case Node::WORD_LITERAL: symbols.insert(word(ast)); break;
    default: for (auto child: ast->children) {
        findSymbols(child);
      }
    }
  }
};


struct SetupGenerator : public Generator {
  SetupGenerator(const NodePtr &_ast) : Generator(_ast) {
  }
  virtual void generate(std::ostream &out) {
    out << "void setup() {" << std::endl;
    setup(ast,out);
    out << "}" << std::endl;
  }
    
  void setup(const NodePtr &ast, std::ostream &out) {
    switch(ast->type()) {
    case Node::START_COMMAND: {
      StartCommandNodePtr start = std::dynamic_pointer_cast<StartCommandNode>(ast);
      out << "  " << start->target() << "." << "level(" << start->power() << ");" << std::endl;
      break;
    } // start case
    case Node::STOP_COMMAND: {
      StopCommandNodePtr stop = std::dynamic_pointer_cast<StopCommandNode>(ast);
      out << "  " << stop->target() << "." << "disabled();" << std::endl;
      break;
    } // stop case
    default: {
      for (auto child: ast->children) {
        setup(child,out);
      }
    } // default case
    } // switch(type())
  }
};

struct LoopGenerator : public Generator {
  std::set < std::string > symbols;

  LoopGenerator(const NodePtr &_ast) : Generator(_ast) { }

  virtual void generate(std::ostream &out) {
    out << std::endl;
    out << "void loop() {" << std::endl;

    symbols.clear();
    findSymbols(ast);
    for (auto word : symbols) {
      out << "  " << word << ".update();" << std::endl;
    }
    out << "}" << std::endl;
    out << std::endl;
  }

  void findSymbols(const NodePtr &ast) {
    switch(ast->type()) {
    case Node::WORD_LITERAL: symbols.insert(word(ast)); break;
    default: for (auto child: ast->children) {
        findSymbols(child);
      }
    }
  }
};

struct ProgramGenerator : Generator {
  HeaderGenerator header;
  SetupGenerator setup;
  LoopGenerator loop;

  ProgramGenerator(const NodePtr &_ast)
    : Generator(_ast), header(_ast), setup(_ast), loop(_ast) {}

  virtual void generate(std::ostream &out) {
    header.generate(out);
    setup.generate(out);
    loop.generate(out);
  }
};

GeneratorPtr generator(const NodePtr &ast) {
  return GeneratorPtr(new ProgramGenerator(ast));
}
