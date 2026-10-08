#include "duckdb/parser/extension_node.hpp"

#include "duckdb/common/serializer/serializer.hpp"
#include "duckdb/common/serializer/deserializer.hpp"

namespace duckdb {

ExtensionNode::ExtensionNode(const ExtensionNode &other) : node_type(other.node_type), type(other.type) {
	expression = other.expression ? other.expression->Copy() : nullptr;
	query_node = other.query_node ? other.query_node->Copy() : nullptr;
	table_ref = other.table_ref ? other.table_ref->Copy() : nullptr;
	statement = other.statement ? other.statement->Copy() : nullptr;
}

ExtensionNode &ExtensionNode::operator=(const ExtensionNode &other) {
	node_type = other.node_type;
	type = other.type;
	expression = other.expression ? other.expression->Copy() : nullptr;
	query_node = other.query_node ? other.query_node->Copy() : nullptr;
	table_ref = other.table_ref ? other.table_ref->Copy() : nullptr;
	statement = other.statement ? other.statement->Copy() : nullptr;
	return *this;
}

ExtensionNode ExtensionNode::FromExpression(unique_ptr<ParsedExpression> expression) {
	ExtensionNode node;
	node.node_type = ExtensionNodeType::EXPRESSION;
	node.expression = std::move(expression);
	return node;
}

ExtensionNode ExtensionNode::FromQueryNode(unique_ptr<QueryNode> query_node) {
	ExtensionNode node;
	node.node_type = ExtensionNodeType::QUERY_NODE;
	node.query_node = std::move(query_node);
	return node;
}

ExtensionNode ExtensionNode::FromTableRef(unique_ptr<TableRef> table_ref) {
	ExtensionNode node;
	node.node_type = ExtensionNodeType::TABLE_REF;
	node.table_ref = std::move(table_ref);
	return node;
}

ExtensionNode ExtensionNode::FromStatement(unique_ptr<SQLStatement> statement) {
	ExtensionNode node;
	node.node_type = ExtensionNodeType::STATEMENT;
	node.statement = std::move(statement);
	return node;
}

ExtensionNode ExtensionNode::FromType(LogicalType type) {
	ExtensionNode node;
	node.node_type = ExtensionNodeType::TYPE;
	node.type = std::move(type);
	return node;
}

void ExtensionNode::Serialize(Serializer &serializer) const {
	serializer.WriteProperty<ExtensionNodeType>(100, "node_type", node_type);
	switch (node_type) {
	case ExtensionNodeType::EXPRESSION:
		serializer.WritePropertyWithDefault<unique_ptr<ParsedExpression>>(101, "node", expression);
		break;
	case ExtensionNodeType::QUERY_NODE:
		serializer.WritePropertyWithDefault<unique_ptr<QueryNode>>(101, "node", query_node);
		break;
	case ExtensionNodeType::TABLE_REF:
		serializer.WritePropertyWithDefault<unique_ptr<TableRef>>(101, "node", table_ref);
		break;
	case ExtensionNodeType::STATEMENT:
		serializer.WritePropertyWithDefault<unique_ptr<SQLStatement>>(101, "node", statement);
		break;
	case ExtensionNodeType::TYPE:
		serializer.WriteProperty<LogicalType>(101, "node", type);
		break;
	}
}

ExtensionNode ExtensionNode::Deserialize(Deserializer &deserializer) {
	ExtensionNode result;
	result.node_type = deserializer.ReadProperty<ExtensionNodeType>(100, "node_type");
	switch (result.node_type) {
	case ExtensionNodeType::EXPRESSION:
		deserializer.ReadPropertyWithDefault<unique_ptr<ParsedExpression>>(101, "node", result.expression);
		break;
	case ExtensionNodeType::QUERY_NODE:
		deserializer.ReadPropertyWithDefault<unique_ptr<QueryNode>>(101, "node", result.query_node);
		break;
	case ExtensionNodeType::TABLE_REF:
		deserializer.ReadPropertyWithDefault<unique_ptr<TableRef>>(101, "node", result.table_ref);
		break;
	case ExtensionNodeType::STATEMENT:
		deserializer.ReadPropertyWithDefault<unique_ptr<SQLStatement>>(101, "node", result.statement);
		break;
	case ExtensionNodeType::TYPE:
		result.type = deserializer.ReadProperty<LogicalType>(101, "node");
		break;
	}
	return result;
}

} // namespace duckdb
