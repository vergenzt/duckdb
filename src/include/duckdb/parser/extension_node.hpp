//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/extension_node.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/common.hpp"
#include "duckdb/common/types.hpp"
#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/parser/query_node.hpp"
#include "duckdb/parser/tableref.hpp"
#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {
class Serializer;
class Deserializer;

//! Which top-level DuckDB parse hierarchy an ExtensionNode holds. A bounded, stable set; adding
//! one is a one-line change here plus a case in Serialize/Deserialize/the copy ctor.
enum class ExtensionNodeType : uint8_t { EXPRESSION, QUERY_NODE, TABLE_REF, STATEMENT, TYPE };

//! A tagged holder for a single arbitrary serializable AST node. It lets the extension escape
//! nodes (ExtensionExpression / CustomStatement) carry children from ANY grammatical position —
//! expressions, query nodes, table refs, statements, types — not just expressions. Each hierarchy
//! already serializes polymorphically within itself; this just picks the hierarchy by node_type.
//! Value-semantic (deep copy) so it composes with the generated Copy/Serialize machinery.
struct ExtensionNode {
	ExtensionNodeType node_type;
	unique_ptr<ParsedExpression> expression;
	unique_ptr<QueryNode> query_node;
	unique_ptr<TableRef> table_ref;
	unique_ptr<SQLStatement> statement;
	LogicalType type;

	ExtensionNode() : node_type(ExtensionNodeType::EXPRESSION), type(LogicalType::SQLNULL) {
	}
	ExtensionNode(const ExtensionNode &other);
	ExtensionNode &operator=(const ExtensionNode &other);
	ExtensionNode(ExtensionNode &&) noexcept = default;
	ExtensionNode &operator=(ExtensionNode &&) noexcept = default;

	ExtensionNode Copy() const {
		return ExtensionNode(*this);
	}

	static ExtensionNode FromExpression(unique_ptr<ParsedExpression> expression);
	static ExtensionNode FromQueryNode(unique_ptr<QueryNode> query_node);
	static ExtensionNode FromTableRef(unique_ptr<TableRef> table_ref);
	static ExtensionNode FromStatement(unique_ptr<SQLStatement> statement);
	static ExtensionNode FromType(LogicalType type);

	void Serialize(Serializer &serializer) const;
	static ExtensionNode Deserialize(Deserializer &deserializer);
};

} // namespace duckdb
