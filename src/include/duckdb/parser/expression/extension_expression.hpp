//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/extension_expression.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/parser/extension_node.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {
//! A generic, self-describing escape node for parser extensions. Carries a string tag, structured
//! child nodes (of any AST hierarchy, via ExtensionNode), and extension-defined metadata. Never
//! bound or executed — only parsed, serialized, and round-tripped (e.g. via json_serialize_sql) so
//! external tools can resolve it.
class ExtensionExpression : public ParsedExpression {
public:
	static constexpr const ExpressionClass TYPE = ExpressionClass::EXTENSION;

public:
	DUCKDB_API explicit ExtensionExpression(string tag, vector<ExtensionNode> children = {},
	                                        string properties = string());

	//! Extension-defined node kind, e.g. "macro_ref"
	string tag;
	//! Structured child nodes (macro arguments, definition body, ...) — any AST hierarchy
	vector<ExtensionNode> children;
	//! Extension-defined metadata, opaque to core (JSON-encoded by convention)
	string properties;

public:
	string ToString() const override;

	bool Equals(const ParsedExpression &other) const override;
	hash_t Hash() const override;

	unique_ptr<ParsedExpression> Copy() const override;

	void Serialize(Serializer &serializer) const override;
	static unique_ptr<ParsedExpression> Deserialize(Deserializer &deserializer);

private:
	ExtensionExpression();
};
} // namespace duckdb
