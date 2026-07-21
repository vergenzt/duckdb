#include "duckdb/parser/expression/extension_expression.hpp"

#include "duckdb/common/string_util.hpp"

namespace duckdb {

ExtensionExpression::ExtensionExpression() : ParsedExpression(ExpressionType::INVALID, ExpressionClass::EXTENSION) {
}

ExtensionExpression::ExtensionExpression(string tag_p, vector<unique_ptr<ParsedExpression>> children_p,
                                         string properties_p)
    : ParsedExpression(ExpressionType::INVALID, ExpressionClass::EXTENSION), tag(std::move(tag_p)),
      children(std::move(children_p)), properties(std::move(properties_p)) {
}

string ExtensionExpression::ToString() const {
	// Generic debug rendering; extensions/consumers define the real surface form.
	string result = tag + "(";
	for (idx_t i = 0; i < children.size(); i++) {
		if (i > 0) {
			result += ", ";
		}
		result += children[i]->ToString();
	}
	result += ")";
	return result;
}

} // namespace duckdb
