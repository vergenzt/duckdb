//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/extension_expression.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {
//! A generic, self-describing escape node for parser extensions. Carries a string tag,
//! structured child expressions, and extension-defined metadata. Never bound or executed —
//! only parsed, serialized, and round-tripped (e.g. via json_serialize_sql) so external
//! tools can resolve it.
class ExtensionExpression : public ParsedExpression {
public:
	static constexpr const ExpressionClass TYPE = ExpressionClass::EXTENSION;

public:
	DUCKDB_API explicit ExtensionExpression(string tag, vector<unique_ptr<ParsedExpression>> children = {},
	                                        string properties = string());

	//! Extension-defined node kind, e.g. "macro_ref", "metavar", "macro_def"
	string tag;
	//! Structured child expressions (macro arguments, definition body, ...)
	vector<unique_ptr<ParsedExpression>> children;
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
