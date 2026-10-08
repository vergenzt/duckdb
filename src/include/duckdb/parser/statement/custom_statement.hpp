//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/custom_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"
#include "duckdb/parser/extension_node.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {
//! Generic, self-describing escape statement for parser extensions — the statement-level twin of
//! ExtensionExpression. Carries a string tag, structured child nodes (any AST hierarchy, via
//! ExtensionNode), and extension-defined metadata. Never bound or executed; only parsed,
//! serialized, and round-tripped (e.g. via json_serialize_sql) so external tools can resolve it.
class CustomStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::CUSTOM_STATEMENT;

public:
	DUCKDB_API explicit CustomStatement(string tag, vector<ExtensionNode> children = {}, string properties = string());

	//! Extension-defined node kind, e.g. "macro_def"
	string tag;
	//! Structured child nodes (e.g. the macro body) — any AST hierarchy
	vector<ExtensionNode> children;
	//! Extension-defined metadata, opaque to core (JSON-encoded by convention)
	string properties;

protected:
	CustomStatement(const CustomStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;

private:
	CustomStatement();
};
} // namespace duckdb
