#include "duckdb/parser/statement/custom_statement.hpp"

namespace duckdb {

CustomStatement::CustomStatement() : SQLStatement(StatementType::CUSTOM_STATEMENT) {
}

CustomStatement::CustomStatement(string tag_p, vector<unique_ptr<ParsedExpression>> children_p, string properties_p)
    : SQLStatement(StatementType::CUSTOM_STATEMENT), tag(std::move(tag_p)), children(std::move(children_p)),
      properties(std::move(properties_p)) {
}

CustomStatement::CustomStatement(const CustomStatement &other)
    : SQLStatement(other), tag(other.tag), properties(other.properties) {
	for (auto &child : other.children) {
		children.push_back(child->Copy());
	}
}

unique_ptr<SQLStatement> CustomStatement::Copy() const {
	return unique_ptr<CustomStatement>(new CustomStatement(*this));
}

string CustomStatement::ToString() const {
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
