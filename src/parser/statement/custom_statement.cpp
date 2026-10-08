#include "duckdb/parser/statement/custom_statement.hpp"

namespace duckdb {

CustomStatement::CustomStatement() : SQLStatement(StatementType::CUSTOM_STATEMENT) {
}

CustomStatement::CustomStatement(string tag_p, vector<ExtensionNode> children_p, string properties_p)
    : SQLStatement(StatementType::CUSTOM_STATEMENT), tag(std::move(tag_p)), children(std::move(children_p)),
      properties(std::move(properties_p)) {
}

CustomStatement::CustomStatement(const CustomStatement &other)
    : SQLStatement(other), tag(other.tag), properties(other.properties) {
	for (auto &child : other.children) {
		children.push_back(child.Copy());
	}
}

unique_ptr<SQLStatement> CustomStatement::Copy() const {
	return unique_ptr<CustomStatement>(new CustomStatement(*this));
}

string CustomStatement::ToString() const {
	// Generic debug rendering; children are heterogeneous AST nodes, so just summarize.
	return tag + "(...)";
}

} // namespace duckdb
