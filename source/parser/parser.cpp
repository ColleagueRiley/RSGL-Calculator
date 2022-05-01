

#include "../../include/exprtk.hpp"
#include "../../include/parser.hpp"

std::string parse(std::string eq)
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>   expression_t;
   typedef exprtk::parser<T>       parser_t;

   const std::string expression_string = eq;

   double x;

   symbol_table_t symbol_table;

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;
   parser.compile(expression_string,expression);

    const T y = expression.value();
    std::string output = std::to_string(y);
    bool dot =false; bool extra=true;
    for (int i=0; i < output.size(); i++){
        if (output.at(i) == '.') dot=true;
        else if (dot){
            if (output.at(i) != '0'){ extra=false; break;}
        }
    } if (extra) output=std::to_string((int)y);
    return output;
}