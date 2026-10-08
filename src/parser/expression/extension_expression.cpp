#include "duckdb/parser/expression/extension_expression.hpp"

#include "duckdb/common/string_util.hpp"

namespace duckdb {

ExtensionExpression::ExtensionExpression() : ParsedExpression(ExpressionType::INVALID, ExpressionClass::EXTENSION) {
}

ExtensionExpression::ExtensionExpression(string tag_p, vector<ExtensionNode> children_p, string properties_p)
    : ParsedExpression(ExpressionType::INVALID, ExpressionClass::EXTENSION), tag(std::move(tag_p)),
      children(std::move(children_p)), properties(std::move(properties_p)) {
}

string ExtensionExpression::ToString() const {
	// Generic debug rendering; children are heterogeneous AST nodes, so just summarize.
	return tag + "(...)";
}

} // namespace duckdb
